precision mediump float;
uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture1;
uniform vec2 fboSize;
varying vec2 texCoordVarying;
uniform float progress;

vec4 transition(vec2 p) {
    // make sure progress's value is between 0.0 and 1.0
    float iTime = clamp(progress, 0.0 , 1.0);

    vec4 sample0 = texture2D(inputImageTexture, texCoordVarying);
    vec4 sample1 = texture2D(inputImageTexture1, texCoordVarying);
    return  mix(sample0, sample1, iTime);
}

void main () {
    gl_FragColor = transition(texCoordVarying);
}