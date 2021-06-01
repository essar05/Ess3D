#version 330 core

// Interpolated values from the vertex shaders
//in vec4 fragmentColor;
in vec2 fragmentUV;

// Ouput data
out vec4 color;

uniform sampler2D material_texDiffuse1;
uniform bool use_material_texDiffuse1;

void main() {
  if (use_material_texDiffuse1) {
    color = texture(material_texDiffuse1, fragmentUV);
  } else {
    color = vec4(0.1, 0.1, 0.1, 1.0);
  }
}
