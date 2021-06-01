#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
//out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
  gl_Position = projection * view * model * vec4( vertexPosition, 1.0 );

  fragmentUV = vertexUV;
}
