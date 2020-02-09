#version 330 core
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D material_texDiffuse1;

void main()
{
    color = texture(material_texDiffuse1, fragmentUV);
}