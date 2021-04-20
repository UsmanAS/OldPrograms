/* MerryGoRoundDriver.js
//	
//	Written by Usman Siddiqui for CS 425, Fall 2020
    
    
*/

// Globals are evil, but necessary when callback functions are used

// Object-independent variables
var gl;				// WebGL graphics environment
var program1, program2;		// The shader program
var canvas;
var texture1;
var framebuffer, renderbuffer;

var theAxes;
var theMerryGoRound;
var theTexture;

var lightPosition = vec4(1.0, 1.0, 1.0, 1.0);
var lightAmbient = vec4(0.5, 0.5, 0.0, 1.0);
var lightDiffuse = vec4(1.0, 1.0, 1.0, 1.0);
var lightSpecular = vec4(1.0, 1.0, 1.0, 1.0);

var materialAmbient = vec4(1.0, 0.0, 1.0, 1.0);
var materialDiffuse = vec4(1.0, 0.8, 0.0, 1.0);
var materialSpecular = vec4(1.0, 0.8, 0.0, 1.0);
var materialShininess = 100.0;

// Initialization function runs whenever the page is loaded

window.onload = function init( ) {
	

    var points = [];
    var colors = [];
    var texCoords = [];
	// Set up the canvas, viewport, and clear color

	var canvas = document.getElementById( "gl-canvas" );
	gl=WebGLUtils.setupWebGL( canvas );
	if( !gl ) {
		alert( "No WebGL" );
	}
    
	gl.viewport( 0, 0, canvas.width, canvas.height );
	aspectRatio = canvas.width / canvas.height ;
	gl.clearColor( 1.0, 1.0, 0.5, 1.0 );
	
    // Load in the second shader that is used for texture mapping and do the textures
	program2 = initShaders(gl, "vertex-shader2", "fragment-shader2");
	gl.useProgram(program2);

    // Initialize the texture
	theTexture = new texture(gl, program2);




    // Unbind the buffer, for safety sake.

	gl.bindBuffer(gl.ARRAY_BUFFER, null);

	gl.enable(gl.DEPTH_TEST);
	gl.clearColor(1.0, 1.0, 0.5, 1.0);

	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);


    //Use the other program for the actual merry go round

	program1 = initShaders( gl, "vertex-shader1", "fragment-shader1" );
	gl.useProgram( program1 );


	theAxes = new Axes(gl, program1);
	theMerryGoRound = new MerryGoRound(gl, program1);

	var ambientProduct = mult(lightAmbient, materialAmbient);
	var diffuseProduct = mult(lightDiffuse, materialDiffuse);
	var specularProduct = mult(lightSpecular, materialSpecular);

	gl.enable( gl.DEPTH_TEST );	// Note:  This line had an error in the exercise template.
	

	gl.uniform4fv(gl.getUniformLocation(program1, "ambientProduct"), flatten(ambientProduct));
	gl.uniform4fv(gl.getUniformLocation(program1, "diffuseProduct"), flatten(diffuseProduct));
	gl.uniform4fv(gl.getUniformLocation(program1, "specularProduct"), flatten(specularProduct));
	gl.uniform4fv(gl.getUniformLocation(program1, "lightPosition"), flatten(lightPosition));
	gl.uniform1f(gl.getUniformLocation(program1, "shininess"), materialShininess);

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
    //  Switch to the first program for most of the objects
    gl.useProgram(program1);
    // Clear out the color buffers and the depth buffers.
    //gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
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

	var projection = perspective(60, aspectRatio, 0.1, 100.0);
	var vProjection = gl.getUniformLocation(program1, "vProjection");
	gl.uniformMatrix4fv(vProjection, false, flatten(projection));


	var modelView = lookAt( vec3( x, y, z ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );
	var vModelView = gl.getUniformLocation( program1, "vModelView" );
	gl.uniformMatrix4fv( vModelView, false, flatten( modelView ) );
	// Set the transformation matrix as a mat4 Identity matrix and send it to the GPU

	var transformation = mat4( );
	var vTransformation = gl.getUniformLocation( program1, "vTransformation" );
	gl.uniformMatrix4fv( vTransformation, false, flatten( transformation ) );
	
	
	transformation = scalem(10, 10, 10); //mat4( );
	gl.uniformMatrix4fv(vTransformation, false, flatten(transformation));
	theAxes.render();
	var normalTransformation = normalMatrix(transformation, true);
	var vNormalTransformation = gl.getUniformLocation(program1, "vNormalTransformation");
	gl.uniformMatrix4fv(vNormalTransformation, false, flatten(normalTransformation));

	gl.uniformMatrix4fv(vNormalTransformation, false, flatten(normalTransformation));
	theMerryGoRound.render(time, [5, 0, 0]);

    // Go back to program 2 for the texture
	gl.useProgram(program2);
    // render the texture with modelview and projection passed in that were used before to make it uniform
	theTexture.render(modelView, projection);
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