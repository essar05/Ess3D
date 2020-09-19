#version 330

// Interpolated values from the vertex shaders
in vec2 fragmentPosition;
in vec2 fragmentUV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;

void main() {
  color = texture(textureSampler, fragmentUV).rgba;
}
