# version 330

in vec2 v_texture;

out vec4 out_color;

uniform vec3 idCol;

void main() {
    out_color = vec4(idCol.r/255.0, idCol.g/255.0, idCol.b/255.0, 1.0);
}