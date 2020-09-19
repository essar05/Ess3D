#version 130

// Input vertex data, different for all executions of this shader.
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

// Values that stay constant for the whole mesh.
uniform mat4 P;

void main(){

    gl_Position = P * vec4( vertexPosition.x, vertexPosition.y, 0.0, 1.0 );

    // UV of the vertex. No special space for this one.
    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
    fragmentUV = vec2(vertexUV.x, 1.0f - vertexUV.y);

}