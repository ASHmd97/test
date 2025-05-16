precision mediump float;
varying highp vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture1;

void main() {
    vec4 sample1 = texture2D(inputImageTexture1, texCoordVarying);
    vec4 sample0 = texture2D(inputImageTexture, texCoordVarying);
    gl_FragColor = vec4(mix(sample0.rgb, sample1.rgb, sample1.a), sample0.a);
}