#version 330 core
layout (location = 0) in vec2 position;// <position>
layout (location = 1) in vec2 texCords;// <position>

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main() {
    TexCoords =texCords;
    gl_Position = u_Projection * u_Model * vec4(position, 0.0, 1.0);
}

