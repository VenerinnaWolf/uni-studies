// 07.js

"use strict";

// Vertex shader program
const VSHADER_SOURCE =
    '#version 100\n' +
  'attribute vec4 a_Position;\n' +
  'uniform mat4 u_Matrix;\n' +
  'attribute vec4 a_FragColor;\n' +
  'varying vec4 v_FragColor;\n' +
  'void main() {\n' +
  '  gl_Position = u_Matrix*a_Position;\n' +
  '  gl_PointSize = 10.0;\n' +
  '  v_FragColor = a_FragColor;\n' +
  '}\n';

// Fragment shader program
const FSHADER_SOURCE =
  'precision mediump float;\n' +
  'varying vec4 v_FragColor;\n' +
  'void main() {\n' +
  '  gl_FragColor = v_FragColor;\n' +
  '}\n';

const {mat2, mat3, mat4, vec2, vec3, vec4} = glMatrix;

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
  //const n = initVertexBuffers_wf(gl);
  //const n = initVertexBuffers_pg(gl);
  
  if (n < 0) {
    console.log('Failed to set the positions of the vertices');
    return;
  }
  
  const u_Matrix = gl.getUniformLocation(gl.program, 'u_Matrix');
  if (!u_Matrix) {
     console.log('Failed to get the storage location of u_Matrix');
     return;
  }  

  // Specify the color for clearing <canvas>
  gl.clearColor(0, 0, 0, 1);
  gl.enable(gl.DEPTH_TEST);

  const controls = {
    view: 'axonometry',
    perspective_method: 'perspective',
    zoom: 'in',
    perspective_effect: 'more'
  };

  const gui = new dat.GUI();

  let matV = mat4.create(); //матрица вида
  let matP = mat4.create(); //матрица проекции
  mat4.ortho(matP, -1.0, 1.0, -1.0, 1.0, 0.001, 10.0);

  let lastView = 'axonometry'
  
  const projection = {
      type: "Orthographic",
      switchCamera: function () {
          if (this.type == "Perspective") {           
			  mat4.ortho(matP, -10.0, 1.0, -1.0, 1.0, 0.001, 10.0);

              this.type = "Orthographic";
              gui.remove(view);
              if (perspective_method != undefined)
                gui.remove(perspective_method);
              if (perspective_effect != undefined)
                gui.remove(perspective_effect);
              controls.view = lastView;
              view = gui.add(controls, 'view', ['left', 'right', 'top', 'bottom', 'front', 'back', 'isometry', 'axonometry']);
              zoom = gui.add(controls, 'zoom', ['in', 'out']);
          } else {
              mat4.perspective(matP, 0.6*Math.PI, 1, 0.001, 10);

              this.type = "Perspective";

              gui.remove(view);
              gui.remove(zoom);
              controls.view = '3-point';
              view = gui.add(controls, 'view', ['1-point', '2-point', '3-point']);
              perspective_method = gui.add(controls, 'perspective_method', ['perspective', 'frustum']);
              perspective_effect = gui.add(controls, 'perspective_effect', ['more', 'less']);
          }
      }
  };

  gui.add(projection, 'switchCamera');
  gui.add(projection, 'type').listen();
  let view = gui.add(controls, 'view', ['left', 'right', 'top', 'bottom', 'front', 'back', 'isometry', 'axonometry']);
  let zoom = gui.add(controls, 'zoom', ['in', 'out']);
  let perspective_method;
  let perspective_effect;

  let zoomMultiplier = 1

  let eye = vec3.create();
  let center = vec3.fromValues(0,0,0);
  let up = vec3.fromValues(0.0,1.0,0.0);
  // -------- 7.2 --------
  //eye = vec3.fromValues(0.5,0.5,0.5);
  
  function render() {
	switch (controls.zoom) {
        case 'in':
            if (projection.type == "Orthographic") {
                    mat4.ortho(matP, -1, 1, -1, 1, 0.001, 10)
                }
            zoomMultiplier = 1
			break;
        case 'out':
            if (projection.type == "Orthographic") {
                    mat4.ortho(matP, -2, 2, -2, 2, .001, 10)
                }
            zoomMultiplier = 2
            break;
        }

    switch (controls.view) {
        case 'left':
            vec3.set(eye, -zoomMultiplier, 0, 0);
			vec3.set(up, 0, 1, 0);
        break;
        case 'right':
            vec3.set(eye, zoomMultiplier, 0, 0);
			vec3.set(up, 0, 1, 0);
        break;
        case 'top':
            vec3.set(eye, 0, zoomMultiplier, 0);
			vec3.set(up, 0, 0, -1.0);
        break;
        case 'bottom':
            vec3.set(eye, 0, -zoomMultiplier, 0);
			vec3.set(up, 0, 0, 1.0);
        break;
        case 'front':
            vec3.set(eye, 0, 0, zoomMultiplier);
			vec3.set(up, 0, 1, 0);
        break;
        case 'back':
            vec3.set(eye, 0, 0, -zoomMultiplier);
			vec3.set(up, 0, 1, 0);
        break;
		
        case 'isometry':
            vec3.set(eye, zoomMultiplier, zoomMultiplier, zoomMultiplier);
			vec3.set(up, 0, 1, 0);
        break;
        case 'axonometry':
            vec3.set(eye, zoomMultiplier*0.5, zoomMultiplier*0.1, zoomMultiplier*0.4); 
			vec3.set(up, 0, 1, 0);           
        break;
		
        case '1-point':
            switch (controls.perspective_method) {
              case 'perspective':
                switch (controls.perspective_effect) {
                case 'more':
                  vec3.set(eye, 0, 0, 1)
                  mat4.perspective(matP, 0.6*Math.PI, 1, .001, 10)
                  break;
                case 'less':
				  vec3.set(eye, 0, 0, 2)
                  mat4.perspective(matP, 0.3*Math.PI, 1, .001, 10)
                  break;
                }
                break;
				
              case 'frustum':                
                switch (controls.perspective_effect) {
                  case 'more':
                    vec3.set(eye, 0, 0, 1)
					mat4.frustum(matP, -0.14, 0.14, -0.14, 0.14, 0.1, 500)
                    break;
                  case 'less':
                    vec3.set(eye, 0, 0, 2)
					mat4.frustum(matP, -0.12, 0.12, -0.12, 0.12, 0.2, 500)
                    break;
                  }
                break;
            }
        break;
		
        case '2-point':
            switch (controls.perspective_method) {
              case 'perspective':
                switch (controls.perspective_effect) {
                    case 'more':
                        eye = [-0.5, 0, 1];
                        mat4.perspective(matP, 0.6*Math.PI, 1, 0.001, 10);
                        break;
        
                    case 'less':
                        eye = [-0.5*2, 0, 1*2];
                        mat4.perspective(matP, 0.3*Math.PI, 1, 0.001, 10);
                        break;
					}
                break;
              case 'frustum':
                switch (controls.perspective_effect) {
                  case 'more':
                    vec3.set(eye, -0.5, 0, 1)
					mat4.frustum(matP, -0.14, 0.14, -0.14, 0.14, 0.1, 500)
                    break;
                  case 'less':
                    vec3.set(eye, -0.5*2, 0, 1*2)
					mat4.frustum(matP, -0.12, 0.12, -0.12, 0.12, 0.2, 500)
                    break;
                  }
                break;
              break;
            }
        break;
        case '3-point':
            switch (controls.perspective_method) {
              case 'perspective':
                switch (controls.perspective_effect) {
                    case 'more':
                        eye = [-0.5, 0.8, 1];
                        mat4.perspective(matP, 0.6*Math.PI, 1, 0.001, 10);
                        break;
        
                    case 'less':
                        eye = [-0.5*2, 0.8*2, 1*2];
                        mat4.perspective(matP, 0.3*Math.PI, 1, 0.001, 10);
                        break;
					}
                break;
              case 'frustum':
                switch (controls.perspective_effect) {
					case 'more':
						vec3.set(eye, -0.5, 0.8, 1)
						mat4.frustum(matP, -0.14, 0.14, -0.14, 0.14, 0.1, 500)
						break;
					case 'less':
						vec3.set(eye, -0.5*2, 0.8*2, 1*2)
						mat4.frustum(matP, -0.12, 0.12, -0.12, 0.12, 0.2, 500)
						break;
					}
                break;
              break;
            }
        break;
    }
	
	//матрица вида
    mat4.lookAt(matV, eye, center, up);
	
	let mvp = mat4.create();
	mat4.multiply(mvp, matP, matV);
	gl.uniformMatrix4fv(u_Matrix, false, mvp);
	
	//gl.clear(gl.COLOR_BUFFER_BIT);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

     gl.drawArrays(gl.LINE_LOOP, 0, 4); //Без индексов
     gl.drawArrays(gl.LINE_LOOP, 4, 4);
     gl.drawArrays(gl.LINES, 8, 8);
	//gl.drawElements(gl.LINES, 24, gl.UNSIGNED_SHORT, 0); //Каркасная модель
	//gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_SHORT, 0); //Полигональная

    // render using requestAnimationFrame
    requestAnimationFrame(render);
  }

  // call the render function
  render();

}

function initVertexBuffers(gl) {
    const n = 16; // The number of vertices

    const vertices = new Float32Array([0.4, 0.4, 0.4, 
									   -0.4, 0.4, 0.4, 
									   -0.4, -0.4, 0.4, 
									   0.4, -0.4, 0.4,				   
									   
									   0.4, -0.4, -0.4,
									   0.4, 0.4, -0.4,  
									   -0.4, 0.4, -0.4, 
									   -0.4, -0.4, -0.4, 
									   
									   0.4, -0.4, 0.4, 
									   0.4, -0.4, -0.4, 
									   
									   0.4, 0.4, 0.4, 
									   0.4, 0.4, -0.4, 
									   
									   -0.4, -0.4, 0.4, 
									   -0.4, -0.4, -0.4, 
									   
									   -0.4, 0.4, 0.4, 
									   -0.4, 0.4, -0.4
									   ]);
  
  const colors = new Float32Array([1.0,0.0,0.0,
								   0.0,1.0,0.0,
								   0.0,0.0,1.0,
								   1.0,1.0,0.0,
								   
								   0.0,1.0,1.0,
								   1.0,0.0,1.0,
								   1.0,0.5,0.0,
								   1.0,0.0,0.5,
								   
								   1.0,1.0,0.0,
								   0.0,1.0,1.0,
								   
								   1.0,0.0,0.0,
								   1.0,0.0,1.0,
								   
								   0.0,0.0,1.0,
								   1.0,0.0,0.5,
								   
								   0.0,1.0,0.0,
								   1.0,0.5,0.0]);

  const newBuffer = gl.createBuffer();
  if (!newBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  gl.bindBuffer(gl.ARRAY_BUFFER, newBuffer);
  
  const FSIZE =  colors.BYTES_PER_ELEMENT;
  gl.bufferData(gl.ARRAY_BUFFER, FSIZE*(3*n + 3*n), gl.STATIC_DRAW);  
  gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
  gl.bufferSubData(gl.ARRAY_BUFFER, 3 * n * FSIZE, colors);
	
  const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  
  gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);
  
  const a_FragColor = gl.getAttribLocation(gl.program, 'a_FragColor');
  if (!a_FragColor) {
    console.log('Failed to get the storage location of a_FragColor');
    return -1;
  }
  
  gl.vertexAttribPointer(a_FragColor, 3, gl.FLOAT, false, 0, 3*n*FSIZE);
  gl.enableVertexAttribArray(a_FragColor);  
  
  return n;
}

function initVertexBuffers_wf(gl) {
    const n = 8 
    const vertices = new Float32Array([ 
         0.4,  0.4, 0.4,
        -0.4,  0.4, 0.4,
        -0.4, -0.4, 0.4,
         0.4, -0.4, 0.4,

         0.4,  0.4, -0.4,
        -0.4,  0.4, -0.4,
        -0.4, -0.4, -0.4,
         0.4, -0.4, -0.4
    ]);
	
	const colors = new Float32Array([
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
		1.0,1.0,0.0,

		1.0,0.0,1.0,
		1.0,0.5,0.0,
		1.0,0.0,0.5,
		0.0,1.0,1.0
	]);

    const indices = new Uint16Array([
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    ]);
  
    const indexBuffer = gl.createBuffer()
    if (!indexBuffer) {
        console.log('Failed to create the buffer object')
        return -1
    }

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer)
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW)

    const vertexBuffer = gl.createBuffer()
    if (!vertexBuffer) {
        console.log('Failed to create the buffer object')
        return -1
    }

	gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

	const FSIZE =  colors.BYTES_PER_ELEMENT;
	gl.bufferData(gl.ARRAY_BUFFER, FSIZE*(3*n + 3*n), gl.STATIC_DRAW);  
	gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
	gl.bufferSubData(gl.ARRAY_BUFFER, 3 * n * FSIZE, colors);

	const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
		if (a_Position < 0) {
		console.log('Failed to get the storage location of a_Position');
		return -1;
	}

	gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(a_Position);

	const a_FragColor = gl.getAttribLocation(gl.program, 'a_FragColor');
		if (!a_FragColor) {
		console.log('Failed to get the storage location of a_FragColor');
		return -1;
	}

	gl.vertexAttribPointer(a_FragColor, 3, gl.FLOAT, false, 0, 3*n*FSIZE);
	gl.enableVertexAttribArray(a_FragColor);      

    return n
}

function initVertexBuffers_pg(gl) {
    const n = 8 
    const vertices = new Float32Array([ 
         0.4,  0.4, 0.4,
        -0.4,  0.4, 0.4,
        -0.4, -0.4, 0.4,
         0.4, -0.4, 0.4,

         0.4,  0.4, -0.4,
        -0.4,  0.4, -0.4,
        -0.4, -0.4, -0.4,
         0.4, -0.4, -0.4
    ]);
	
	const colors = new Float32Array([
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,

		0.0,0.0,1.0,
		0.0,0.0,1.0,
		1.0,0.0,1.0,
		1.0,0.0,1.0
	]);
	
	const indices = new Uint16Array([
        0, 1, 2, 0, 2, 3,    // front
        0, 3, 7, 0, 7, 4,    // right
        0, 4, 5, 0, 5, 1,    // up
        1, 5, 6, 1, 6, 2,    // left
        7, 6, 5, 7, 5, 4,    // down
        3, 2, 6, 3, 6, 7     // back
    ]);
  
    const indexBuffer = gl.createBuffer()
    if (!indexBuffer) {
        console.log('Failed to create the buffer object')
        return -1
    }

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer)
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW)

    const vertexBuffer = gl.createBuffer()
    if (!vertexBuffer) {
        console.log('Failed to create the buffer object')
        return -1
    }

	gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

	const FSIZE =  colors.BYTES_PER_ELEMENT;
	gl.bufferData(gl.ARRAY_BUFFER, FSIZE*(3*n + 3*n), gl.STATIC_DRAW);  
	gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
	gl.bufferSubData(gl.ARRAY_BUFFER, 3 * n * FSIZE, colors);

	const a_Position = gl.getAttribLocation(gl.program, 'a_Position');
		if (a_Position < 0) {
		console.log('Failed to get the storage location of a_Position');
		return -1;
	}

	gl.vertexAttribPointer(a_Position, 3, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(a_Position);

	const a_FragColor = gl.getAttribLocation(gl.program, 'a_FragColor');
		if (!a_FragColor) {
		console.log('Failed to get the storage location of a_FragColor');
		return -1;
	}

	gl.vertexAttribPointer(a_FragColor, 3, gl.FLOAT, false, 0, 3*n*FSIZE);
	gl.enableVertexAttribArray(a_FragColor);      

    return n
}