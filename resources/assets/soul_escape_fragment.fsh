precision highp float;
varying highp vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform float progress;

float getScale(){
    if (progress > 0.0 && progress <= 0.64) {
        return 1.0 + 1.15 * progress;
    }
    return 1.0;
}

float getPercent(){
    if (progress == 0.0) {
        return 0.2;
    } else if (progress > 0.64) {
        return 0.0;
    } else {
        return 0.195;
    }
}

void main()
{
    lowp float mixturePercent = getPercent();
    highp float scale = getScale();
    lowp vec4 textureColor = texture2D(inputImageTexture, texCoordVarying);
    vec2 texCoordVaryingToUse = texCoordVarying;
    vec2 center = vec2(0.5, 0.5);
    texCoordVaryingToUse -= center;
    texCoordVaryingToUse = texCoordVaryingToUse / scale;
    texCoordVaryingToUse += center;
    lowp vec4 textureColor2 = texture2D(inputImageTexture, texCoordVaryingToUse);
    gl_FragColor = mix(textureColor, textureColor2, mixturePercent);
}