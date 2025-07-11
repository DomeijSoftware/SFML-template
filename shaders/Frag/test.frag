//test.frag

precision mediump float;

uniform float iTime;
uniform vec2 iResolution;

varying vec2 v_texCoord;



void main()
{
    vec2 uv = (gl_FragCoord.xy * 2.0 - iResolution.xy) / iResolution.y;
    //vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;

    float d = length(uv);
    d = sin(d * 8.0 + iTime) / 8.0;
    d = abs(d);
    //d = smoothstep(0.0, 0.5, d);

    d = 0.01 / d;

    //vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0., 2.,4.));
    gl_FragColor = vec4(d, 0.0, 0.0, 1.0);
    
}
