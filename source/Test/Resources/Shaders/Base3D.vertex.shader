#version 130

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition;
//in vec4 vertexColor;
in vec2 vertexUV;

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
