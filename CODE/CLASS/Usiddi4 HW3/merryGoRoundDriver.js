/* MerryGoRoundDriver.js
//	
//	Written by Usman Siddiqui for CS 425, Fall 2020
    
    
*/

// Globals are evil, but necessary when callback functions are used

// Object-independent variables
var gl;				// WebGL graphics environment
var program;		// The shader program

var theAxes;
var theMerryGoRound;

var lightPosition = vec4(1.0, 1.0, 1.0, 0.0);
var lightAmbient = vec4(0.2, 0.2, 0.2, 1.0);
var lightDiffuse = vec4(1.0, 1.0, 1.0, 1.0);
var lightSpecular = vec4(1.0, 1.0, 1.0, 1.0);

var materialAmbient = vec4(1.0, 0.0, 1.0, 1.0);
var materialDiffuse = vec4(1.0, 0.8, 0.0, 1.0);
var materialSpecular = vec4(1.0, 1.0, 1.0, 1.0);
var materialShininess = 50.0;

// Initialization function runs whenever the page is loaded

window.onload = function init( ) {
	
	// Set up the canvas, viewport, and clear color

	var canvas = document.getElementById( "gl-canvas" );
	gl=WebGLUtils.setupWebGL( canvas );
	if( !gl ) {
		alert( "No WebGL" );
	}
	
	gl.viewport( 0, 0, canvas.width, canvas.height );
	aspectRatio = canvas.width / canvas.height ;
	gl.clearColor( 1.0, 1.0, 0.5, 1.0 );
	
	// Load the shaders, create a GLSL program, and use it.
	program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );

	var projection = perspective(60, aspectRatio, 0.1, 100.0);
	var vProjection = gl.getUniformLocation(program, "vProjection");
	gl.uniformMatrix4fv(vProjection, false, flatten(projection));


	theAxes = new Axes(gl, program);
	theMerryGoRound = new MerryGoRound(gl, program);

	var ambientProduct = mult(lightAmbient, materialAmbient);
	var diffuseProduct = mult(lightDiffuse, materialDiffuse);
	var specularProduct = mult(lightSpecular, materialSpecular);

	gl.enable( gl.DEPTH_TEST );	// Note:  This line had an error in the exercise template.
	

	gl.uniform4fv(gl.getUniformLocation(program, "ambientProduct"), flatten(ambientProduct));
	gl.uniform4fv(gl.getUniformLocation(program, "diffuseProduct"), flatten(diffuseProduct));
	gl.uniform4fv(gl.getUniformLocation(program, "specularProduct"), flatten(specularProduct));
	gl.uniform4fv(gl.getUniformLocation(program, "lightPosition"), flatten(lightPosition));
	gl.uniform1f(gl.getUniformLocation(program, "shininess"), materialShininess);

    // Initialization is done.  Now initiate first rendering
	render( );
}

var time = 0.0;
var x = 15;
var y = 5;
var z = 15;
var speed = 1;

function render( ) {
	
    time += speed;
	// Clear out the color buffers and the depth buffers.
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    // Check keyboard input and do the correct actions
	window.onkeydown = function (event) {
	    var key = String.fromCharCode(event.keyCode);
	    switch (key) {
	        case 'A':
	            x -= .5;
	            z += .5;
	            break;
	        case 'S':
	            y -= .5;
	            break;
	        case 'W':
	            y += .5;
	            break;
	        case 'D':
	            x += .5;
	            z -= .5;
	            break;
	        case 'R': // Reset MGR
	            x = 15;
	            y = 5;
	            z = 15;
	            speed = 1;
	            hide();
	            break;
	        case 'F':// Speed up the merry go round
	            speed += 1;
	            break;
	        default:
	            unhide();
	            console.log(key);
	            break;
	    }
	};
	var modelView = lookAt( vec3( x, y, z ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );
	var vModelView = gl.getUniformLocation( program, "vModelView" );
	gl.uniformMatrix4fv( vModelView, false, flatten( modelView ) );
	// Set the transformation matrix as a mat4 Identity matrix and send it to the GPU

	var transformation = mat4( );
	var vTransformation = gl.getUniformLocation( program, "vTransformation" );
	gl.uniformMatrix4fv( vTransformation, false, flatten( transformation ) );
	
	var normalTransformation = [
        vec3(modelView[0][0], modelView[0][1], modelView[0][2]),
        vec3(modelView[1][0], modelView[1][1], modelView[1][2]),
        vec3(modelView[2][0], modelView[2][1], modelView[2][2])
	];
	var vNormalTransformation = gl.getUniformLocation(program, "vNormalTransformation");
	gl.uniformMatrix4fv(vNormalTransformation, false, flatten(normalTransformation));
	
	transformation = scalem(10, 10, 10); //mat4( );
	gl.uniformMatrix4fv(vTransformation, false, flatten(transformation));
	theAxes.render();
	gl.uniformMatrix4fv(vNormalTransformation, false, flatten(normalTransformation));
	theMerryGoRound.render(time, [5, 0, 0]);
	requestAnimFrame(render);
}
// Shows the options menu
function unhide() {
    var hid = document.getElementsByClassName("exp");
    if (hid[0].offsetWidth > 0 && hid[0].offsetHeight > 0) {
        hid[0].style.visibility = "visible";
    }
}
// Hides the options menu
function hide() {
    var hid = document.getElementsByClassName("exp");
    if (hid[0].offsetWidth > 0 && hid[0].offsetHeight > 0) {
        hid[0].style.visibility = "hidden";
    }
}