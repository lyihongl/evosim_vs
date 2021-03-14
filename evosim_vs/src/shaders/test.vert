#version 430 core
layout (location = 0) in vec2 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aOffset;
layout (location = 2) in vec3 aColor;
//layout (location = 1) in vec3 aColor; // the position variable has attribute position 0
//layout (location = 2) in vec2 aTest; // the position variable has attribute position 0

  
out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 position;
out vec2 center;

uniform mat4 scale;
uniform mat4 ortho;

void main()
{
    gl_Position = ortho * vec4(aPos+aOffset, 1.0, 1.0); // see how we directly give a vec3 to vec4's constructor
    position = aPos + aOffset;
    center = aOffset;
    //vertexColor = vec4(aColor, 1.0); // set the output variable to a dark-red color
    vertexColor = vec4(aColor, 1);
}