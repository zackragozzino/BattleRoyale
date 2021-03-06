#version 330 core

layout(location = 0) in vec2 v_vPos;

uniform int v_operation;

uniform vec2 v_scale;
uniform vec2 v_translate;
uniform float v_depth;

out vec2 f_texPos;
flat out int f_operation;

void main() {
    vec2 screenPos;

    f_operation = v_operation;
    f_texPos = (v_vPos + vec2(1.f, 1.f)) / 2.f;

    screenPos = vec2(v_vPos.x * v_scale.x, v_vPos.y * v_scale.y);
    screenPos = screenPos + v_translate;

    //gl_Position = vec4(v_vPos, -1.f, 1.f);
    gl_Position = vec4(screenPos.x, screenPos.y, v_depth, 1.f);
}
