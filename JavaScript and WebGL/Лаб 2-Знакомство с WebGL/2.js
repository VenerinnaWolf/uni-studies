// 02.js

"use strict";

// Vertex shader program
const VSHADER_SOURCE =
 'attribute vec4 a_Position;\n' + // attribute variable
 'attribute float a_PointSize;\n' +
 'void main() {\n' +
 // '  gl_Position = vec4(0.5, 0.0, 0.0, 1.0);\n' + // Set the vertex coordinates of the point
 '  gl_Position = a_Position;\n' +
 '	gl_PointSize = a_PointSize;\n' +
 // '  gl_PointSize = 10.0;\n' +                    // Set the point size
 '}\n';

// Fragment shader program
const FSHADER_SOURCE =
 'void main() {\n' +
 '  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' + // Set the point color
 '}\n';

function main() {
  // Retrieve <canvas> element
    const canvas = document.getElementById('mycanvas');

  // Get the rendering context for WebGL
  const gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }

  // Set clear color
  gl.clearColor(0.0, 0.0, 0.0, 1.0);

  // Clear <canvas>
  gl.clear(gl.COLOR_BUFFER_BIT);

   // Initialize shaders
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
     console.log('Failed to intialize shaders.');
     return;
   }

   // Get the storage location of a_Position
  const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
     console.log('Failed to get the storage location of a_Position');
     return;
  }

  const a_PointSize = gl.getAttribLocation(gl.program, 'a_PointSize');
  if (a_PointSize < 0) {
     console.log('Failed to get the storage location of a_PointSize');
     return;
  }
   // Pass vertex position to attribute variable
  gl.vertexAttrib3f(a_Position, 0.5, 0.0, 0.0);
  gl.vertexAttrib1f(a_PointSize, 15.0);

   // Draw a point
  gl.drawArrays(gl.POINTS, 0, 1);
  
  for (let i = 1; i < 10; i++){
	gl.vertexAttrib3f(a_Position, 0.1*i, -0.1*i, 0.0);
	gl.vertexAttrib1f(a_PointSize, 5.0*i);
	gl.drawArrays(gl.POINTS, i, 1);
  }
}
