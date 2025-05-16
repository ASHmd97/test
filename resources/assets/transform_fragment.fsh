precision highp float;
uniform sampler2D inputImageTexture;
uniform sampler2D inputImageTexture1;
uniform vec2 fboSize;
varying vec2 texCoordVarying;
uniform float progress;
uniform float start_angle; // = 10.0;
uniform float end_angle; // = 10.0;
uniform float start_scale_x; // = 1.0;
uniform float end_scale_x; // = 1.0;
uniform float start_scale_y; // = 1.0;
uniform float end_scale_y; // = 1.0;
uniform float start_translate_x; // = 0.0;
uniform float end_translate_x; // = 0.0;
uniform float start_translate_y; // = 0.0;
uniform float end_translate_y; // = 0.0;
uniform float start_alpha; // = 1.0;
uniform float end_alpha; // = 1.0;
const float PI = 3.1415926;

bool inBounds (vec2 p) {
    return p.x >= 0.0 && p.x <= 1.0 && p.y >= 0.0 && p.y <= 1.0;
}

// 此着色器的思路为把当前要画的点通过变换转换为（平移、旋转、缩放之前）的原始点
// 并判断此点是否在纹理范围内，如果在则画出原始点纹理，如果不在则画黑色
void main () {
    // 使用mix函数计算变量
    float scaleX = mix(start_scale_x, end_scale_x, progress);
    float scaleY = mix(start_scale_y, end_scale_y, progress);
    float translateX = mix(start_translate_x, end_translate_x, progress);
    float translateY = mix(start_translate_y, end_translate_y, progress);
    float angle = mix(start_angle * PI / 180.0, end_angle * PI / 180.0, progress);
    float alpha = mix(start_alpha, end_alpha, progress);

    vec2 center = vec2(0.5) ;
    // 归一化坐标转换为真实像素坐标，并计算出与中点的向量
    vec2 fbov = (texCoordVarying - (center + vec2(translateX, translateY))) * fboSize;
    // 计算距离
    float hypot = sqrt(fbov.x * fbov.x + fbov.y * fbov.y);
    // 旋转向量
    float baseAngle = atan(fbov.y, fbov.x);
    vec2 rot = vec2(hypot * cos(baseAngle + angle), hypot * sin(baseAngle + angle));
    // 重新归一化
    vec2 urot = rot / vec2(scaleX, scaleY) / fboSize + center ;
    if (inBounds(urot)) {
        gl_FragColor = vec4(texture2D(inputImageTexture, urot).xyz, alpha);
    } else {
        gl_FragColor = vec4(0.0);
    }
}