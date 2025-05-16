precision mediump float;
varying highp vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform int columns;
uniform int row;

//一屏多画面滤镜
void main() {
    //fract：截取浮点数的小数部分
    vec2 coordinate = vec2(fract(texCoordVarying.x * float(columns)), fract(texCoordVarying.y * float(row)));
    gl_FragColor = texture2D(inputImageTexture, coordinate);
}