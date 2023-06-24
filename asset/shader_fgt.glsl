#version 400

out vec4 frag_colour;
uniform float[800] canvas;

void main() {
  if (gl_FragCoord.y > canvas[int(gl_FragCoord.x)])
    frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
  else 
    frag_colour = vec4(0.0, 0.0, 0.0, 1.0);
}