//test.frag

precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

varying vec2 v_texCoord;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    //vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0., 2.,4.));
    //gl_FragColor = vec4(col, 1.0);
    gl_FragColor = vec4(uv, 0.0, 1.0);
}
