// softMax归一化指数函数
function softMax(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    return arr.map(function(value,index) {
      return Math.exp(value) / arr.map(function(y){ return Math.exp(y) } ).reduce( function(a,b){ return a+b });
    })
}
// 返回数组中最大值和下标
function maxWithIndex(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    let max = arr[0];
    let maxIndex = 0;
    for (let i = 1; i < arr.length; i++) {
        if (arr[i] > max) {
            max = arr[i];
            maxIndex = i;
        }
    }
    return {index: maxIndex, value: max};
}
// map序列化
function mapToJson(map) {
    if (map == null || map == undefined) {
        return '{}';
    }
    return JSON.stringify([...map]);
}
// map反序列化
function jsonToMap(jsonStr) {
    if (jsonStr == null || jsonStr == undefined || jsonStr == '') {
        return new Map();
    }
    return new Map(JSON.parse(jsonStr));
}
// set序列化
function setToJson(set) {
    if (set == null || set == undefined) {
        return '{}';
    }
    return JSON.stringify([...set]);
}
// set反序列化
function jsonToSet(jsonStr) {
    if (jsonStr == null || jsonStr == undefined || jsonStr == '') {
        return new Set();
    }
    return new Set(JSON.parse(jsonStr));
}
//最小值
function min(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var min = arr[0];
    for (let i = 1; i < arr.length; i++) {
        var cur = arr[i];
        cur < min ? min = cur : null;
    }
    return min;
}

//最大值
function max(arr){
    if (arr == null || arr.length == 0) {
        return null;
    }
    var max = arr[0];
    for (let i = 1; i < arr.length; i++) {
        var cur = arr[i];
        cur > max ? max = cur : null;
    }
    return max;
}

//数组是否完全相同（顺序、值）
function isSame(array1, array2) {

    if(!(array1 || array2)) {
        return false;
      }
      if (array1 == null && array2 != null || (array1 != null && array2 == null)) {
          return false;
      }
      // 先比较长度
      if (array1.length != array2.length)
          return false;

      for (var i = 0, l = array1.length; i < l; i++) {
          // 检查是否为内嵌数组
          if (array1[i] instanceof Array && array2[i] instanceof Array) {
              // 递归比较数组
              if (!isSame(array1[i], array2[i]))
                  return false;
          } else if (array1[i] != array2[i]) { //标量比较
              return false;
          }
      }
      return true;
}

//中位数绝对偏差
function mad(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var md = median(arr);
    var absArr = new Array();
    for (let i = 0; i < arr.length; i++) {
        absArr[i] = Math.abs(arr[i] - md);
    }
    return median(absArr);
}



function iqr(data) {
    return Quartile(data, 0.75) - Quartile(data, 0.25);
}

//0.25分位数
function Quartile_25(data) {
    return Quartile(data, 0.25);
}

//中位数
function median(data) {
    return Quartile(data, 0.5);
}

function Quartile(input, q) {
    var data = input.slice();
    data = Array_Sort_Numbers(data);
    if (data != null) {
        var pos = ((data.length) - 1) * q;
        var base = Math.floor(pos);
        var rest = pos - base;
        if( (data[base+1]!==undefined) ) {
          return data[base] + rest * (data[base+1] - data[base]);
        } else {
          return data[base];
        }
    }
    return null;
}
function Array_Sort_Numbers(inputarray) {
    if (inputarray == null || inputarray.length == 0) {
        return null;
    }
    return inputarray.sort(function (a, b) {
        return a - b;
    });
}


//样本方差
function variance(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var m = mean(arr);
    const deviation = arr.map((x) => x - m);
    return deviation.map((x) => x * x).reduce((acc, val) => acc + val) / arr.length;
}


//标准差
function std(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var std = Math.sqrt(variance(arr));
    return std
}

//均值
function mean(arr){
    if (arr == null || arr.length == 0) {
        return null;
    }
    return arr.reduce((acc, val) => acc + val) / arr.length;
}

//峰度
function kurt(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    if (arr.length == 1) {
        return -3
    }
    arr_mean = mean(arr)
    arr_std = std(arr)
    if (arr_std == 0) {
        return -3
    }
    val_sum = 0
    for (var i = 0; i < arr.length; i++) {
        val_sum = val_sum + Math.pow((arr[i] - arr_mean), 4)
    }
    return (val_sum / (arr.length * (arr_std ** 4))) - 3
}

//偏度
function skew(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    if (arr.length == 1) {
        return 0
    }
    arr_mean = mean(arr)
    arr_std = std(arr)
    if (arr_std == 0) {
        return 0
    }
    val_sum = 0
    for(var i=0; i < arr.length; i++) {
        val_sum  = val_sum + Math.pow(arr[i],3)
    }
    //偏度计算公式
    skew_val = (val_sum/arr.length -3*arr_mean*arr_std**2-arr_mean**3)/(arr_std**3)
    return skew_val;
}

// 波峰检测
function peakDetect(sumAcc, trendList) {
    var stayFlag = 0;
    var peakNum = 0;
    if (std(sumAcc) < stayThreshold) {
        stayFlag = 1;
    }
    for (var i = 2; i < sumAcc.length - 3; i++) {
        if (trendList[i - 1] == 1 && trendList[i] == 1 && trendList[i + 1] == -1 && trendList[i + 2] == -1 && sumAcc[i + 1] > peakThreshold) {
            peakNum += 1;
        }
    }
    return [stayFlag, peakNum];
}

function amplitudes(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var amp = [];
    for (var i = 0; i < arr.length; i++) {
        amp[i] = Math.sqrt(arr[i][0] * arr[i][0] + arr[i][1] * arr[i][1]) * 2 / arr.length;
    }
    return amp;
}

function energy(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var e = [];
    for (var i = 0; i < arr.length; i++) {
        e[i] = Math.sqrt(arr[i][0] * arr[i][0] + arr[i][1] * arr[i][1]);
    }
    return e.map((x) => x * x).reduce((acc, val) => acc + val) / e.length;
}

function zeroCrossingRate(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var count = 0;
    for (var i = 1; i < arr.length; i++) {
        if (arr[i - 1] * arr[i] < 0) {
            count += 1;
        }
    }
    return count / arr.length;
}

function meanCrossingRate(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    var count = 0;
    var m = mean(arr);
    for (var i = 1; i < arr.length; i++) {
        if ((arr[i - 1] - m) * (arr[i] - m) < 0) {
            count += 1;
        }
    }
    return count / arr.length;
}

function rms(arr) {
    if (arr == null || arr.length == 0) {
        return null;
    }
    return Math.sqrt(arr.map((x) => x * x).reduce((acc, val) => acc + val) / arr.length);
}

//-----------------SG滤波-----------------------------------------------------------------------
/**
 * SG滤波
 * https://github.com/mljs/savitzky-golay-generalized
 * @param {*} data
 * @param {*} h
 * @param {*} options
 */
function SavitzkyGolay(data, h, options = {}) {
    let { windowSize = 9, derivative = 0, polynomial = 3 } = options;

    if (windowSize % 2 === 0 || windowSize < 5 || !Number.isInteger(windowSize)) {
        throw new RangeError(
            'Invalid window size (should be odd and at least 5 integer number)',
        );
    }
    if (windowSize > data.length) {
        throw new RangeError(
            `Window size is higher than the data length ${windowSize}>${data.length}`,
        );
    }
    if (derivative < 0 || !Number.isInteger(derivative)) {
        throw new RangeError('Derivative should be a positive integer');
    }
    if (polynomial < 1 || !Number.isInteger(polynomial)) {
        throw new RangeError('Polynomial should be a positive integer');
    }
    if (polynomial >= 6) {
        // eslint-disable-next-line no-console
        console.warn(
            'You should not use polynomial grade higher than 5 if you are' +
            ' not sure that your data arises from such a model. Possible polynomial oscillation problems',
        );
    }

    let half = Math.floor(windowSize / 2);
    let np = data.length;
    let ans = new Array(np);
    let weights = fullWeights(windowSize, polynomial, derivative);
    let hs = 0;
    let constantH = true;
    if (Array.isArray(h)) {
        constantH = false;
    } else {
        hs = Math.pow(h, derivative);
    }

    //For the borders
    for (let i = 0; i < half; i++) {
        let wg1 = weights[half - i - 1];
        let wg2 = weights[half + i + 1];
        let d1 = 0;
        let d2 = 0;
        for (let l = 0; l < windowSize; l++) {
            d1 += wg1[l] * data[l];
            d2 += wg2[l] * data[np - windowSize + l - 1];
        }
        if (constantH) {
            ans[half - i - 1] = d1 / hs;
            ans[np - half + i] = d2 / hs;
        } else {
            hs = getHs(h, half - i - 1, half, derivative);
            ans[half - i - 1] = d1 / hs;
            hs = getHs(h, np - half + i, half, derivative);
            ans[np - half + i] = d2 / hs;
        }
    }

    //For the internal points
    let wg = weights[half];
    for (let i = windowSize; i <= np; i++) {
        let d = 0;
        for (let l = 0; l < windowSize; l++) d += wg[l] * data[l + i - windowSize];
        if (!constantH) hs = getHs(h, i - half - 1, half, derivative);
        ans[i - half - 1] = d / hs;
    }
    return ans;
}

function getHs(h, center, half, derivative) {
    let hs = 0;
    let count = 0;
    for (let i = center - half; i < center + half; i++) {
        if (i >= 0 && i < h.length - 1) {
            hs += h[i + 1] - h[i];
            count++;
        }
    }
    return Math.pow(hs / count, derivative);
}

/**
 *
 * @param m  Number of points
 * @param n  Polynomial grade
 * @param s  Derivative
 */
function fullWeights(m, n, s) {
    let weights = new Array(m);
    let np = Math.floor(m / 2);
    for (let t = -np; t <= np; t++) {
        weights[t + np] = new Array(m);
        for (let j = -np; j <= np; j++) {
            weights[t + np][j + np] = Weight(j, t, np, n, s);
        }
    }
    return weights;
}

function Weight(i, t, m, n, s) {
    let sum = 0;
    for (let k = 0; k <= n; k++) {
        //console.log(k);
        sum +=
            (2 * k + 1) *
            (GenFact(2 * m, k) / GenFact(2 * m + k + 1, k + 1)) *
            GramPoly(i, m, k, 0) *
            GramPoly(t, m, k, s);
    }
    return sum;
}

function GramPoly(i, m, k, s) {
    let Grampoly = 0;
    if (k > 0) {
        Grampoly =
            ((4 * k - 2) / (k * (2 * m - k + 1))) *
            (i * GramPoly(i, m, k - 1, s) + s * GramPoly(i, m, k - 1, s - 1)) -
            (((k - 1) * (2 * m + k)) / (k * (2 * m - k + 1))) *
            GramPoly(i, m, k - 2, s);
    } else {
        if (k === 0 && s === 0) {
            Grampoly = 1;
        } else {
            Grampoly = 0;
        }
    }
    return Grampoly;
}
function GenFact(a, b) {
    let gf = 1;
    if (a >= b) {
        for (let j = a - b + 1; j <= a; j++) {
            gf *= j;
        }
    }
    return gf;
}

