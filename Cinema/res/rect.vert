#version 330 core

layout(location = 0) in vec2 inPos;

uniform vec2 uScale;   
uniform vec2 uOffset;  

void main() {
    gl_Position = vec4(inPos * uScale + uOffset, 0.0, 1.0);
}
