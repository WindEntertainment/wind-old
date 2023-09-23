<vtx>
    #version 400

    layout (location = 0) in vec3 vp;
    layout (location = 1) in vec2 aTexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec2 TexCoord;

    void main() {
        gl_Position = projection * view * model * vec4(vp, 1.0);
        TexCoord = aTexCoord;
    }
</vtx>
<fgt>
    #version 400

    out vec4 FragColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main() {
        FragColor = texture(ourTexture, TexCoord);
    }
</fgt>