#version 400

out vec4 frag_colour;
uniform float[800] canvas;

void main() {
  int ind = int(gl_FragCoord.x);
  float bottom = 300 - canvas[ind] / 2;
  float top = 300 + canvas[ind] / 2;

  float color = canvas[ind] / 600;
  if (gl_FragCoord.y > bottom && gl_FragCoord.y < top)
    frag_colour = vec4(color, color, color, 1.0);
  else 
    if (gl_FragCoord.y > 300)
      frag_colour = vec4(0.3, 0.3, 1, 1.0);
    else 
      frag_colour = vec4(0.7, 0.5, 0.3, 1.0);
}