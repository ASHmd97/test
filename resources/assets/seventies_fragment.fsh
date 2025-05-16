precision highp float;
varying highp vec2 texCoordVarying;
uniform sampler2D inputImageTexture;
uniform highp float progress;

float nrand(float x, float y)
{
    return fract(sin(dot(vec2(x, y), vec2(12.9898, 78.233))) * 43758.5453);
}

vec2 getScanLineJitter(){
    if ((progress >= 0.15 && progress < 0.2) || (progress >= 0.25 && progress < 0.3)){
        return vec2(0.03, 0.03);
    }
    return vec2(0.0, 0.0);
}

float getHorizontalShake(){
    if ((progress >= 0.15 && progress < 0.2) || (progress >= 0.25 && progress < 0.3)){
        return 0.005;
    }
    return 0.0;
}


void main(){

    vec2 scanLineJitter = getScanLineJitter();
    float horizontalShake = getHorizontalShake();
    vec2 verticalJump = vec2(0.0, 0.0);
    vec2 colorDrift = vec2(0.0, 0.0);

    float u = texCoordVarying.x;
    float v = texCoordVarying.y;
    float time = scanLineJitter.y;
    //scan line jitter
    float jitter = nrand(v, time) * 2.0 - 1.0;
    jitter *= step(scanLineJitter.y, abs(jitter)) * scanLineJitter.x;

    //vertical
    float jump = mix(v, fract(v + verticalJump.y), verticalJump.x);

    //shake
    float shake = (nrand(time, 2.0) - 0.5) * horizontalShake;

    //color
    float drift = sin(jump + colorDrift.y) * colorDrift.x;


    vec2 cord1 = vec2(u + jitter + shake, jump);
    vec2 cord2 = vec2(u + jitter + shake + drift, jump);

    vec4 scr1 = texture2D(inputImageTexture, fract(cord1));
    vec4 scr2 = texture2D(inputImageTexture, fract(cord2));

    vec4 finalShakeColor = vec4(scr1.r, scr2.g, scr1.b, 1.0);

    vec2 nv =  0.5 + (texCoordVarying - 0.5)*(0.98 + 0.001*sin(0.95*time));
    //偏移
    vec3 col;
    col.r = texture2D(inputImageTexture, vec2(nv.x + 0.008, nv.y)).x;
    col.g = texture2D(inputImageTexture, vec2(nv.x + 0.000, nv.y)).y;
    col.b = texture2D(inputImageTexture, vec2(nv.x - 0.008, nv.y)).z;

    //限制到 0-1
    col = clamp(col * 0.5 + 0.5 * col * col * 1.2, 0.0, 1.0);
    col *= 0.6 + 0.4*16.0*nv.x*nv.y*(1.0-nv.x)*(1.0-nv.y);

    //颜色变暗 和闪烁
    col *= vec3(0.9, 1.0, 0.7);
    col *= 0.8 + 0.2 * sin(10.0 * time + nv.y * 900.0);
    col *= 1.0 - 0.07 * nrand(time, tan(time));

    vec4 finalColor = vec4(col.xyz, 1.0);
    gl_FragColor = mix(finalShakeColor, finalColor, 0.4);
}