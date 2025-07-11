//test.vert

#version 120

attribute vec4 position;
attribute vec2 texCoord;

uniform vec2 iResolution;
uniform mat4 transform;

varying vec2 v_texCoord;

void main()
{
    v_texCoord = texCoord;
    gl_Position = transform * position * 2. - 1.;
}