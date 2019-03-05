#version 130

// Interpolated values from the vertex shaders
//in vec4 fragmentColor;
in vec2 fragmentUV;

// Ouput data
out vec4 color;

uniform sampler2D textureSampler;

void main() {
  color = texture(textureSampler, fragmentUV);
}
