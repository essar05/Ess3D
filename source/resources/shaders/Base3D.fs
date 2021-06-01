#version 330 core

// Interpolated values from the vertex shaders
//in vec4 fragmentColor;
in vec2 fragmentUV;

// Ouput data
out vec4 color;

uniform sampler2D material_texDiffuse1;

void main() {
  color = texture(material_texDiffuse1, fragmentUV);
}
