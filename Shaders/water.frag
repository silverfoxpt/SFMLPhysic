#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

float hash(vec2 p) {
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);
    
    return mix(mix(hash(i + vec2(0.0, 0.0)), hash(i + vec2(1.0, 0.0)), f.x),
               mix(hash(i + vec2(0.0, 1.0)), hash(i + vec2(1.0, 1.0)), f.x), f.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    
    // Add time to the noise for animation
    float oceanDepth = 5.0 + 10.0 * noise(st * 10.0 + u_time * 0.2);
    
    // Smoothly blend colors based on depth
    vec3 deepColor = vec3(0.0, 0.02, 0.1);
    vec3 shallowColor = vec3(0.0, 0.1, 0.3);
    float blendFactor = smoothstep(0.0, 1.0, oceanDepth);
    vec3 color = mix(deepColor, shallowColor, blendFactor);
    
    gl_FragColor = vec4(color, 1.0);
}