precision highp float;

const float PI = 3.14159265359;

varying vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform vec2 fboSize;

uniform float progress;

void main()
{
    vec2 unit_uv        = 1.5 / fboSize;
    //unit_uv *= sin(PI * progress) * 1.72 * progress;

    const int radius = 4;
    float half_gaussian_weight[5];

    half_gaussian_weight[0]= 0.2270270270;
    half_gaussian_weight[1]= 0.1945945946;
    half_gaussian_weight[2]= 0.1216216216;
    half_gaussian_weight[3]= 0.0540540541;
    half_gaussian_weight[4]= 0.0162162162;

    vec4 sum = texture2D(inputImageTexture, texCoordVarying) * half_gaussian_weight[0];

    for (int i=1;i<=radius;i++)
    {
        vec2 curBottomCoordinate    = texCoordVarying+vec2(float(i), 0.0) * unit_uv;
        vec2 curTopCoordinate       = texCoordVarying+vec2(float(-i), 0.0) * unit_uv;
        sum+=texture2D(inputImageTexture, curBottomCoordinate) * half_gaussian_weight[i];
        sum+=texture2D(inputImageTexture, curTopCoordinate) * half_gaussian_weight[i];
    }

    gl_FragColor = vec4(sum.rgb, 1.0);

}