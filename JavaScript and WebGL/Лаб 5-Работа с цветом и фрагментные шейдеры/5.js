// 05.js

"use strict";

// Vertex shader program
const VSHADER_SOURCE =
  '#version 100\n' +
  'attribute vec4 a_Position;\n' +
  'attribute float a_PointSize;\n' +
  'attribute vec4 a_FragColor;\n' +
  'varying vec4 v_FragColor;\n' +
  'void main() {\n' +
  '  gl_Position = a_Position;\n' +
  '  gl_PointSize = a_PointSize;\n' +
  '  v_FragColor = a_FragColor;\n' +
  '}\n';

// Fragment shader program
const FSHADER_SOURCE =
  'precision mediump float;\n' +
  'varying vec4 v_FragColor;\n' +
  'void main() {\n' +
  '  gl_FragColor = v_FragColor;\n' +
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
    console.log('Failed to get the storage location of v_FragColor');
    return -1;
  }
  const a_FragColor = gl.getAttribLocation(gl.program, 'a_FragColor');
  if (!a_FragColor) {
    console.log('Failed to get the storage location of a_FragColor');
    return -1;
  }
  
  const n = 3; // The number of vertices
  const vertices = new Float32Array(2 * n);
  vertices[0] = 0.0;
  vertices[1] = 0.5;
  vertices[2] = -0.5;
  vertices[3] = -0.5;
  vertices[4] = 0.5;
  vertices[5] = -0.5;
	
  const sizes = new Float32Array(n);
  sizes[0] = 10.0;
  sizes[1] = 20.0;
  sizes[2] = 30.0;
  
  const colors = new Float32Array(n*3);
  colors[0] = 1.0;
  colors[1] = 0.0;
  colors[2] = 0.0;
  colors[3] = 0.0;
  colors[4] = 1.0;
  colors[5] = 0.0;
  colors[6] = 0.0;
  colors[7] = 0.0;
  colors[8] = 1.0;

  const newBuffer = gl.createBuffer();
  if (!newBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  // Bind the buffer object to target
  gl.bindBuffer(gl.ARRAY_BUFFER, newBuffer);
  
  const FSIZE =  vertices.BYTES_PER_ELEMENT;
  gl.bufferData(gl.ARRAY_BUFFER, (vertices.length + sizes.length + colors.length)*FSIZE, gl.STATIC_DRAW);  
  gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
  gl.bufferSubData(gl.ARRAY_BUFFER, vertices.length * FSIZE, sizes);
  gl.bufferSubData(gl.ARRAY_BUFFER, (vertices.length + sizes.length) * FSIZE, colors);
  
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);
  gl.vertexAttribPointer(a_PointSize, 1, gl.FLOAT, false, 0, vertices.length * FSIZE);
  gl.enableVertexAttribArray(a_PointSize);
  gl.vertexAttribPointer(a_FragColor, 3, gl.FLOAT, false, 0, (vertices.length + sizes.length)*FSIZE);
  gl.enableVertexAttribArray(a_FragColor);  
  
  return n;
}
