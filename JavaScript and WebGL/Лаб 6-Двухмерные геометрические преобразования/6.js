// 06.js

"use strict";

const {mat2, mat3, mat4, vec2, vec3, vec4} = glMatrix;

// Vertex shader program
const VSHADER_SOURCE =
    '#version 100\n' +
  'attribute vec4 a_Position;\n' +
  'uniform mat4 u_Matrix;\n' +
  'void main() {\n' +
  '  gl_Position = u_Matrix*a_Position;\n' +
  '  gl_PointSize = 10.0;\n' +
  '}\n';

// Fragment shader program
const FSHADER_SOURCE =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' +  // uniform-переменная
  'void main() {\n' +
  '  gl_FragColor = u_FragColor;\n' +
  '}\n';

function main() {
  // Retrieve <canvas> element
  const canvas = document.getElementById('webgl');

  // Get the rendering context for WebGL
  const gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }

  // Initialize shaders
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }

  const n = initVertexBuffers(gl);
  if (n < 0) {
    console.log('Failed to set the positions of the vertices');
    return;
  }
  
  const u_Matrix = gl.getUniformLocation(gl.program, 'u_Matrix');
  if (!u_Matrix) {
     console.log('Failed to get the storage location of u_Matrix');
     return;
  }
  
  gl.clearColor(0, 0, 0, 1);
  gl.clear(gl.COLOR_BUFFER_BIT);
  
  let vec = vec3.create();
  let color = vec4.fromValues(1.0,0.0,0.0,1);
  let angle = Math.PI/2;
  initColor(gl, color);
  
  // ----- Рисование изначального треугольника
  // moveTriangle(gl, vec, u_Matrix);
  // gl.drawArrays(gl.LINE_LOOP, 0, n);
  // color = vec4.fromValues(0.0,1.0,0.0,1); 

  // ----- 1. Перемещение -----  
  // vec = [0.1,-0.1,0];
  // moveTriangle(gl, vec, u_Matrix);
  
  // ----- 2. Вращение -----
  // vec = [0,0,1];
  // rotateTriangle(gl, angle, vec, u_Matrix);
  
  // ----- 3. Масштабирование -----
  // vec = [0.5, 1.5, 0];
  // scaleTriangle(gl, vec, u_Matrix);
  
  // ----- 4,5. Несколько преобразований -----
  // let vec1 = [0.4,0.0,0.0];
  // vec = [0,0,1];
  // moveRotateTriangle(gl, vec1, angle, vec, u_Matrix);
  // rotateMoveTriangle(gl, vec1, angle, vec, u_Matrix);
  
  // ----- Рисование конечного результата
  // initColor(gl, color);
  // gl.drawArrays(gl.LINE_LOOP, 0, n);
  
  // ----- 6. Анимация -----
  animation(gl, u_Matrix, n);
}

function initVertexBuffers(gl) {
	
  const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  
    const n = 3; // The number of vertices
    const vertices = new Float32Array(2 * n);

    vertices[0] = 0.0;
    vertices[1] = 0.4;
    vertices[2] = -0.5;
    vertices[3] = -0.2;
    vertices[4] = 0.5;
    vertices[5] = -0.2;

  const vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);
  
  return n;
}

function initColor(gl,colors){

  const u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
  if (!u_FragColor) {
     console.log('Failed to get the storage location of u_FragColor');
     return;
  }
  
  gl.uniform4fv(u_FragColor, colors);
}

function moveTriangle(gl, vec, u_Matrix) {  
  let mat = mat4.create();
  mat4.fromTranslation(mat, vec);  
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
}

function rotateTriangle(gl, angle, axis, u_Matrix) {  
  let mat = mat4.create();
  mat4.fromRotation(mat, angle, axis);  
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
}	

function scaleTriangle(gl, scalingVec, u_Matrix) {
  let mat = mat4.create();
  mat4.fromScaling(mat, scalingVec);
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
}

function moveRotateTriangle(gl, movingVec, angle, axis, u_Matrix) {
  let mat = mat4.create();
  mat4.fromRotation(mat, angle, axis);   
  mat4.translate(mat, mat, movingVec);
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
  initColor(gl, [0.0, 0.0, 1.0, 1.0]);
  gl.drawArrays(gl.LINE_LOOP, 0, 3);
  
  mat = mat4.create();
  mat4.fromTranslation(mat, movingVec);
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
}

function rotateMoveTriangle(gl, movingVec, angle, axis, u_Matrix) {
  let mat = mat4.create();
  mat4.fromTranslation(mat, movingVec);   
  mat4.rotate(mat, mat, angle, axis);
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
  initColor(gl, [0.0, 0.0, 1.0, 1.0]);
  gl.drawArrays(gl.LINE_LOOP, 0, 3);
  
  mat = mat4.create();
  mat4.fromRotation(mat,angle,axis);
  
  gl.uniformMatrix4fv(u_Matrix, false, mat);
}

function animation(gl, u_Matrix, n) {
	let newAngle = 0;
	var now;
	var g_last = new Date().getTime();
	var elapsed;
	const rotSpeed = Math.PI/4;
	let mat = mat4.create();
	
	const drawStep = function() {
		gl.clear(gl.COLOR_BUFFER_BIT);
		now = new Date().getTime();
		elapsed = now - g_last;
		g_last = now;
		newAngle = newAngle + (rotSpeed*elapsed)/1000.0;
		if (newAngle > 2*(Math.PI)) { 
			newAngle = newAngle - 2*(Math.PI); 
		}
		
		mat4.fromRotation(mat,newAngle,[0,0,1]);
		gl.uniformMatrix4fv(u_Matrix, false, mat);
		mat = mat4.create();
		gl.drawArrays(gl.TRIANGLES, 0, n);
		requestAnimationFrame(drawStep);
	}
	
	drawStep();
}