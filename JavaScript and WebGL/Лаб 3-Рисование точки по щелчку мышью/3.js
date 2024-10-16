// 03.js

"use strict";

// Vertex shader program
const VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'void main() {\n' +
  '  gl_Position = a_Position;\n' +
  '  gl_PointSize = 10.0;\n' +
  '}\n';

// Fragment shader program
const FSHADER_SOURCE =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' +  // uniform-переменная
  'void main() {\n' +
  // '  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
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

  // Get the storage location of a_Position
  const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return;
  }

  // Get the storage location of u_FragColor
  const u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
  if (!u_FragColor) {
     console.log('Failed to get the storage location of u_FragColor');
     return;
  }

  // Register function (event handler) to be called on a mouse press
  canvas.onmousedown = function (ev) { click(ev, gl, canvas, a_Position, u_FragColor); };

  // Specify the color for clearing <canvas>
  gl.clearColor(0.0, 0.0, 0.0, 1.0);

  // Clear <canvas>
  gl.clear(gl.COLOR_BUFFER_BIT);
}

const g_points = []; // The array for the position of a mouse press
const g_colors = [];
function click(ev, gl, canvas, a_Position, u_FragColor) {
  let x = ev.clientX; // x coordinate of a mouse pointer
  let y = ev.clientY; // y coordinate of a mouse pointer
  const rect = ev.target.getBoundingClientRect();

  x = ((x - rect.left) - canvas.width/2)/(canvas.width/2);
  y = (canvas.height/2 - (y - rect.top))/(canvas.height/2);
  // Store the coordinates to g_points array
  // g_points.push(x); g_points.push(y);
  g_points.push([x,y])
  
  let r = 1.0;
  let g = 1.0;
  let b = 1.0;
  
  if (x > 0 && y > 0) {
	  g = 0.0;	
	  b = 0.0;
  }
  if (x <= 0 && y <= 0) {
	  r = 0.0;
	  b = 0.0;
  }
  g_colors.push([r,g,b]);
  
  // Clear <canvas>
  gl.clear(gl.COLOR_BUFFER_BIT);

  const len = g_points.length;
  for (let i = 0; i < len; i += 1) {
    // Pass the position of a point to a_Position variable
    // gl.vertexAttrib3f(a_Position, g_points[i], g_points[i + 1], 0.0);
	gl.vertexAttrib3f(a_Position, g_points[i][0], g_points[i][1], 0.0);
	gl.uniform4f(u_FragColor, g_colors[i][0], g_colors[i][1], g_colors[i][2], 1.0);

    // Draw
    gl.drawArrays(gl.POINTS, 0, 1);
  }
}
