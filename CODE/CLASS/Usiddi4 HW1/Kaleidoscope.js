//Usman Siddiqui usiddi4
//CS425 HW 1 Kaleidoscope

var gl;
var vertices = [];
var colors = [];
// This is the sets of 8 triangles
var amount;

window.onload = function init() {
    var canvas = document.getElementById("gl-canvas");

    gl = WebGLUtils.setupWebGL(canvas);
    if (!gl) { alert("WebGL isn't available"); }

    // Make the amount of sets of 8 triangles and then loop to make that many sets
    amount = Math.random() * 50;
    for (var i = 0; i < amount; i++) {
        // Make 24 vertices
        makeVertices();
        // Make color for the 8 traingles
        makeColor();
    }

    //
    //  Configure WebGL
    //
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearColor(1.0, 1.0, 1.0, 1.0);

    //  Load shaders and initialize attribute buffers

    var program = initShaders(gl, "vertex-shader", "fragment-shader");
    gl.useProgram(program);

    // Load the data into the GPU

    var bufferId = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, bufferId);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);

    // Associate out shader variables with our data buffer

    var vPosition = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPosition, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vPosition);

    // Set up buffer for color now

    var cbufferID = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, cbufferID);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW);

    var vColor = gl.getAttribLocation(program, "vColor");
    gl.vertexAttribPointer(vColor, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vColor);

    render();
};


function render() {
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.drawArrays(gl.TRIANGLES, 0, amount * 24);
}

function makeVertices() {

    // Making vertices using arrays
    var X = [];
    var Y = [];

    for (var i = 0; i < 3; i++) {
        X[i] = Math.random();
        Y[i] = Math.random() * X[i];
    }
    // Push vertices
    for (var j = 0; j < 8; j++) {
        for (var i = 0; i < 3; i++) {
            if (j == 0) {
                vertices.push(X[i], Y[i]);
            }
            if (j == 1) {
                vertices.push(X[i], -Y[i]);
            }
            if (j == 2) {
                vertices.push(-X[i], Y[i]);
            }
            if (j == 3) {
                vertices.push(-X[i], -Y[i]);
            }
            if (j == 4) {
                vertices.push(Y[i], X[i]);
            }
            if (j == 5) {
                vertices.push(-Y[i], X[i]);
            }
            if (j == 6) {
                vertices.push(Y[i], -X[i]);
            }
            if (j == 7) {
                vertices.push(-Y[i], -X[i]);
            }
        }
    }
}

function makeVerticesOld() {

    // Make the 3 X, Y Cordinates coded in individually
    var X = Math.random();
    var Y = Math.random() * X;

    var X2 = Math.random();
    var Y2 = Math.random() * X2;

    var X3 = Math.random();
    var Y3 = Math.random() * X3;

    // Push vertices into vertices array

    vertices.push(vec2(X, Y));
    vertices.push(vec2(X2, Y2));
    vertices.push(vec2(X3, Y3));
    vertices.push(vec2(-X, Y));
    vertices.push(vec2(-X2, Y2));
    vertices.push(vec2(-X3, Y3));
    vertices.push(vec2(X, -Y));
    vertices.push(vec2(X2, -Y2));
    vertices.push(vec2(X3, -Y3));
    vertices.push(vec2(-X, -Y));
    vertices.push(vec2(-X2, -Y2));
    vertices.push(vec2(-X3, -Y3));
    vertices.push(vec2(Y, X));
    vertices.push(vec2(Y2, X2));
    vertices.push(vec2(Y3, X3));
    vertices.push(vec2(-Y, X));
    vertices.push(vec2(-Y2, X2));
    vertices.push(vec2(-Y3, X3));
    vertices.push(vec2(Y, -X));
    vertices.push(vec2(Y2, -X2));
    vertices.push(vec2(Y3, -X3));
    vertices.push(vec2(-Y, -X));
    vertices.push(vec2(-Y2, -X2));
    vertices.push(vec2(-Y3, -X3));
}

function makeColor() {
    // Making color

    var color1 = Math.random();
    var color2 = Math.random();
    var color3 = Math.random();
    for (var i = 0; i < 8; i++) {
        colors.push(vec3(color1, color2, color3));
        colors.push(vec3(color2, color3, color1));
        colors.push(vec3(color3, color2, color1));
    }

}