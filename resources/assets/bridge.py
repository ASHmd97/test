# 扩展，与Android/iOS提供桥实现一一对应，方便使用方直接调用:使用方将提供好的bridge module install到开发环境中即可
# 具体桥方法定义见:wiki
# 请使用 py.version >= 3.7

import native


def nativeLog(log_level, log_tag, log_str):
    return invoke("nativeLog", log_level, log_tag, log_str)


def screenOn(log_str):
    return invoke("screenOn", log_str)


def feature(key, type, extra):
    return invoke("feature", key, type, extra)

def featurePy(key, type, extra):
    return invoke("_feature", key, type, extra)

def featureByInterval(key, start_time, end_time):
    return invoke("featureByInterval", key, start_time, end_time)


def cacheFeature(feature_key, value, expire_time):
    return invoke("cacheFeature", feature_key, value, expire_time)


def featureWaybill(key_prefix, waybill, type, extra):
    return invoke("featureWaybill", key_prefix, waybill, type, extra)


def fft(input):
    return invoke("fft", input)


def ioTDataReport(real_time, interval, link_type, result):
    return invoke("ioTDataReport", real_time, interval, link_type, result)


def loadScript(script_node, script):
    return invoke("_loadScript", script_node, script)


def time():
    return invoke("_time", )

# 兼容函数重载
def matrixEventReport(*var_args):
    args = [*var_args]
    if len(args)==1:
        return invoke("matrixEventReport", args[0])
    if len(args) == 2:
        return  invoke("matrixEventReport", args[0], args[1])
    return invoke("matrixEventReport", args)


def md5(input):
    return invoke("md5", input)


def report2ES(type, code, json):
    return invoke("report2ES", type, code, json)


def getNativeConfig(scene, field_name, default_value):
    return invoke("_getNativeConfig", scene, field_name, default_value)


def tflite(model_key, shape):
    return invoke("tflite", model_key, shape)


def xgb(model_key, input):
    return invoke("xgb", model_key, input)

def xgbList(model_key, input):
    return invoke("xgbList", model_key, input)


def report(result):
    return invoke("report", result)


def aoiMatch(lat, lng, list):
    return invoke("_aoiMatch", lat, lng, list)


def aoiDist(lat, lng, list):
    return invoke("_aoiDist", lat, lng, list)


def evaluate(expression):
    return invoke("evaluate", expression)


# 注意，如果交给上层，上层需要关注创建销毁、生命周期的问题
def nativeTimer(functions, *var_args):
    return invoke("nativeTimer", functions, *var_args)


def nativeTimerCancel(timerId):
    return invoke("nativeTimerCancel", timerId)


def arrivePoiVoiceReport(result):
    return invoke("arrivePoiVoiceReport", result)


def cacheRead(key, value):
    return invoke("_cacheRead", key, value)


def cacheRemove(key):
    return invoke("_cacheRemove", key)


def cacheWrite(key, data):
    return invoke("_cacheWrite", key, data)

def floor_detect(key, data):
    return invoke("_floor_detect", key, data)

#9.0.0新增
def clearFeature(key):
    return invoke("clearFeature", key)

def mtnn(modelKey, *params):
    return invoke("_mtnn", modelKey, params)

def strMd5(str, number):
    return invoke("_strMd5", str, number)

def injectDslVariable(key, value):
    return invoke("_injectDslVariable", key, value)

def junctionData(lat, lng):
    return invoke("_junctionData", lat, lng)

def poiWifiMatch(scanVector, model):
    return invoke("_poiWifiMatch", scanVector, model)

def userWifiMatch(scanVector, model):
    return invoke("_userWifiMatch", scanVector, model)

def parseMerchantBLE(advData):
    return invoke("_parseMerchantBLE", advData)

def harReport(data):
    return invoke("harReport", data)

def getAppConfig(key, default_value):
    return invoke("getAppConfig", key, default_value)

#930新增桥
def geoHashFence(fenceModelKey, lat, lng):
    return invoke("_geoHashFence", fenceModelKey, lat, lng)

#940新增桥
def matrixIpcEvent(taskKey, tags, timestamp,extra):
    return invoke("matrixIpcEvent", taskKey, tags, timestamp,extra)


# 格式化输出调用信息，方便调试
def invoke(function_name, *var_args):
    lists = [*var_args]
    lists.insert(0, function_name)
    return native.call(lists)
