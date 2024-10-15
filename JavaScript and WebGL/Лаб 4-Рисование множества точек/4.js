// 04.js

"use strict";

// Vertex shader program
const VSHADER_SOURCE =
    '#version 100\n' +
  'attribute vec4 a_Position;\n' +
  'attribute float a_PointSize;\n' +
  'void main() {\n' +
  '  gl_Position = a_Position;\n' +
  // '  gl_PointSize = 10.0;\n' +
  '  gl_PointSize = a_PointSize;\n' +
  '}\n';

// Fragment shader program
const FSHADER_SOURCE =
  'void main() {\n' +
  '  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
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

  // Write the positions of vertices to a vertex shader
  const n = initVertexBuffers(gl);
  if (n < 0) {
    console.log('Failed to set the positions of the vertices');
    return;
  }

  // Specify the color for clearing <canvas>
  gl.clearColor(0, 0, 0, 1);

  // Clear <canvas>
  gl.clear(gl.COLOR_BUFFER_BIT);

  // Draw three points
  gl.drawArrays(gl.POINTS, 0, n);
}

function initVertexBuffers(gl) {
	
  const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  const a_PointSize = gl.getAttribLocation(gl.program, 'a_PointSize');
  if (a_PointSize < 0) {
    console.log('Failed to get the storage location of a_PointSize');
    return -1;
  }
  
    const n = 3; // The number of vertices

    //const vertices = new Float32Array([0.0, 0.5, -0.5, -0.5, 0.5, -0.5]);
    const vertices = new Float32Array(2 * n);

    vertices[0] = 0.0;
    vertices[1] = 0.5;
    vertices[2] = -0.5;
    vertices[3] = -0.5;
    vertices[4] = 0.5;
    vertices[5] = -0.5;
	
	// vertices[0] = -0.5;
    // vertices[1] = 0.5;
    // vertices[2] = -0.5;
    // vertices[3] = -0.5;
    // vertices[4] = 0.5;
    // vertices[5] = 0.5;
	// vertices[6] = 0.5;
	// vertices[7] = -0.5;

  // Create a buffer object
  const vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  // Write date into the buffer object
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

  // Assign the buffer object to a_Position variable
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);

  // Enable the assignment to a_Position variable
  gl.enableVertexAttribArray(a_Position);
  
  
  const sizes = new Float32Array(n);
  sizes[0] = 10.0;
  sizes[1] = 20.0;
  sizes[2] = 30.0;
  
  const sizesBuffer = gl.createBuffer();
  
  if (!sizesBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, sizesBuffer);
  
  gl.bufferData(gl.ARRAY_BUFFER, sizes, gl.STATIC_DRAW);

  // Assign the buffer object to a_Position variable
  gl.vertexAttribPointer(a_PointSize, 1, gl.FLOAT, false, 0, 0);

  // Enable the assignment to a_Position variable
  gl.enableVertexAttribArray(a_PointSize);
  
  
  // -------------------------------------------
  const verticesSizes = new Float32Array([
	10.0, 0.0, 0.5, // Первая точка
	20.0, -0.5, -0.5, // Вторая точка
	30.0, 0.5, -0.5, // Третья точка
  ]);
  
  const vsBuffer = gl.createBuffer();
  if (!vsBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, vsBuffer);
  
  gl.bufferData(gl.ARRAY_BUFFER, verticesSizes, gl.STATIC_DRAW);  

  const FSIZE =  verticesSizes.BYTES_PER_ELEMENT;
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, FSIZE*3, FSIZE);
  gl.enableVertexAttribArray(a_Position);
  gl.vertexAttribPointer(a_PointSize, 1, gl.FLOAT, false, FSIZE*3, 0);
  gl.enableVertexAttribArray(a_PointSize);
  
  
  // ------------------------------------------
  const newBuffer = gl.createBuffer();
  if (!newBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, newBuffer);
  
  gl.bufferData(gl.ARRAY_BUFFER, FSIZE*9, gl.STATIC_DRAW);  
  gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
  gl.bufferSubData(gl.ARRAY_BUFFER, FSIZE*6, sizes);
  
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);
  gl.vertexAttribPointer(a_PointSize, 1, gl.FLOAT, false, 0, FSIZE*6);
  gl.enableVertexAttribArray(a_PointSize);
  
  return n;
}
