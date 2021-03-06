uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2D texture;

float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    //vec2 st = gl_TexCoord[0].xy;

    // Smooth interpolation between 0.1 and 0.9
    //float y = smoothstep(0.1,0.9,st.x);
    float y = log(sin(st.x*2) + sin(st.x*4)+ sin(st.x*8))+2;

    vec3 color = vec3(y);

    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(0.0,1.0,0.0);

    gl_FragColor = vec4(color,1.0);
}