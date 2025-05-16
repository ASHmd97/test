precision highp float;
uniform sampler2D inputImageTexture;

uniform vec2 imageSize;// = vec2(360, 720);
uniform float sigma;// = 1.0;

uniform vec2 fboSize;
varying vec2 texCoordVarying;
uniform float progress;

const float PI = 3.1415926;
const vec2 center = vec2(0.5, 0.5);

//这两个参数也会影响模糊效果
#define radius 7
#define gaussian 10.

float gaussianWeights[radius+1];
vec2 imageXBounds;
vec2 imageYBounds;

bool inBounds (vec2 p) {
    return p.x >= 0.0 && p.x <= 1.0 && p.y >= 0.0 && p.y <= 1.0;
}

bool inImageXBounds (float p) {
    return p >= imageXBounds.x && p <= imageXBounds.y;
}

bool inImageYBounds (float p){
    return p >= imageYBounds.x && p <= imageYBounds.y;
}

// gussian
vec4 blur(vec2 uv, vec2 unitUV) {
    // start 初始化高斯权重
    float sumWeight = 0.0;
    for (int i = 0; i <= radius; i++){
        gaussianWeights[i] = (1.0 / sqrt(2.0 * PI * pow(gaussian, 2.0))) * exp(-pow(float(i), 2.0) / (2.0 * pow(gaussian, 2.0)));
        if (i == 0) {
            sumWeight += gaussianWeights[i];
        } else {
            sumWeight += 2.0 * gaussianWeights[i];
        }
    }

    for (int i = 0;i <= radius; i++) {
        gaussianWeights[i] = gaussianWeights[i] / sumWeight;
    }
    // end

    // 填充模糊矩阵
    float blur_matrix[2 * radius + 1];
    for (int i=0; i < 2*radius+1; i++){
        int idx = int(abs(float(radius)-float(i)));
        blur_matrix[i] = gaussianWeights[idx];
    }

    // gauss blur
    vec4 result = vec4(vec3(0.0), 1.0);
    float r = float(radius);
    for (float i=-r; i<=r; i=i+1.0){
        vec2 adb = uv;
        adb.x = uv.x+i * unitUV.x;
        if (!inImageXBounds(adb.x)){
            adb.x = uv.x - i * unitUV.x;
        }
        for (float j=-r; j<=r; j=j+1.0){
            adb.y = uv.y + j * unitUV.y;
            if (!inImageYBounds(adb.y)){
                adb.y = uv.y - j * unitUV.y;
            }
            vec4 color = texture2D(inputImageTexture, adb);
            result.rgb += blur_matrix[int(i+r)] * blur_matrix[int(j+r)] * color.rgb;
        }
    }
    return result;
}

vec2 getuv(){
    if (imageSize.x * fboSize.y > imageSize.y * fboSize.x) {
        float width = imageSize.x * (fboSize.y / imageSize.y);
        float scale = fboSize.x / width;
        vec2 texCoord = (texCoordVarying - center) * scale + center;
        return texCoord;
    } else {
        float height = imageSize.y * (fboSize.x / imageSize.x);
        float scale = fboSize.y / height;
        vec2 texCoord = (texCoordVarying - center) * scale + center;
        return texCoord;
    }
}



void main () {
    vec2 image_scale = imageSize / fboSize;
    // ---------------------------- step1 ---------------------------------
    // ------------------------- 检查原图的范围 -----------------------------
    vec2 uv = ((texCoordVarying - center) / image_scale) + center;
    if (inBounds(uv)) {
        gl_FragColor = texture2D(inputImageTexture, texCoordVarying);
        return;
    }

    // ---------------------------- step2 ---------------------------------
    // ------------------- 对超出原图范围的部分进行变换 ------------------------

    vec2 imageOffset = (vec2(1., 1.) - image_scale) / 2.;
    imageXBounds = vec2(imageOffset.x, 1. - imageOffset.x);
    imageYBounds = vec2(imageOffset.y, 1. - imageOffset.y);
    uv = getuv();
    vec2 unitUV = sigma / fboSize;
    gl_FragColor = blur(uv, unitUV);
}

