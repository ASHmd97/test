precision highp float;
varying highp vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform float progress;

float getScale () {
    if (progress > 0.6 && progress <= 1.0){
        return 1.0 + progress * 0.15;
    }
    return 1.0;
}

void main() {
    float scale = getScale();
    vec2 newTextureCoordinate = vec2((scale - 1.0) * 0.3 + texCoordVarying.x / scale, (scale - 1.0) * 0.7 + texCoordVarying.y /scale);
    vec4 textureColor = texture2D(inputImageTexture, newTextureCoordinate);
    vec4 shiftColor1 = texture2D(inputImageTexture, newTextureCoordinate+vec2(-0.05 * (scale - 1.0), - 0.05 *(scale - 1.0)));
    vec4 shiftColor2 = texture2D(inputImageTexture, newTextureCoordinate+vec2(-0.1 * (scale - 1.0), - 0.1 *(scale - 1.0)));
    vec4 blend3DColor = vec4(shiftColor2.r, textureColor.g, shiftColor1.b, 1.0);
    vec4 originalColor = texture2D(inputImageTexture, texCoordVarying);
    gl_FragColor = mix(originalColor, blend3DColor, 0.7);
}
