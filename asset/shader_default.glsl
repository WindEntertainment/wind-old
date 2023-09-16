<vtx>
    #version 400

    layout (location = 0) in vec3 vp;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * view * model * vec4(vp, 1.0);
    }
</vtx>
<fgt>
    #version 400

    out vec4 FragColor;

    void main() {
        FragColor = vec4(1, 1, 1, 1);
    }
</fgt>