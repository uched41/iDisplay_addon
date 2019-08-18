/* cppsrc/main.cpp */
#include <napi.h>
#include <string>
#include "iDisplay_ButtonDisplay.h"

Napi::Number DeviceOpenWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    } 

    int vid = (info[0].As<Napi::Number>()).Int32Value();
    int pid = (info[1].As<Napi::Number>()).Int32Value();

    int returnValue = iD_USB_DeviceOpen(vid, pid);
    return Napi::Number::New(env, returnValue);
}

Napi::Number DeviceCloseWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() > 0) {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    } 

    int returnValue = iD_USB_DeviceClose();
    return Napi::Number::New(env, returnValue);
}

Napi::Number ShowImageWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString()) {
        Napi::TypeError::New(env, "Incorrect arguments.").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    } 

    int idx = (info[0].As<Napi::Number>()).Int32Value();
    std::string path = (info[1].As<Napi::String>()).Utf8Value();

    FILE* fd = fopen(path.c_str(), "rb");
    if (fd==NULL) {
        Napi::Error::New(env, "Unable to Open file.").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }

    fseek(fd, 0, SEEK_END);
    int dataLength = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    uint8_t *imgBuf = (uint8_t*)malloc(dataLength);
    if (imgBuf==NULL) {
        Napi::Error::New(env, "Alloc memory fail!").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }

    int retCnt = fread(imgBuf, sizeof(uint8_t), dataLength, fd);
    if (retCnt != dataLength) {
        Napi::Error::New(env, "Read image fail!\n").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }
    fclose(fd);
    int returnValue = iD_USB_ShowImageOnButton(idx, imgBuf);
    free(imgBuf);
    return Napi::Number::New(env, returnValue);
}

Napi::Number FirmwareUpdateWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Incorrect arguments.").ThrowAsJavaScriptException();
    } 

    std::string path = (info[0].As<Napi::String>()).Utf8Value();

    FILE* fd = fopen(path.c_str(), "rb");
    if (fd==NULL) {
        Napi::Error::New(env, "Unable to Open file.").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }

    fseek(fd, 0, SEEK_END);
    uint32_t dataLength = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    uint8_t *firBuf = (uint8_t*)malloc(dataLength);
    if (firBuf==NULL) {
        Napi::Error::New(env, "Alloc memory fail!").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }

    int retCnt = fread(firBuf, sizeof(uint8_t), dataLength, fd);
    if (retCnt != dataLength) {
        Napi::Error::New(env, "Read image fail!\n").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    }
    fclose(fd);
    int returnValue = iD_USB_FirmwareUpdate(firBuf, dataLength);
    free(firBuf);
    return Napi::Number::New(env, returnValue);
}

Napi::Number CleanScreenWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Incorrect arguments.").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    } 

    int r = (info[0].As<Napi::Number>()).Int32Value();
    int g = (info[1].As<Napi::Number>()).Int32Value();
    int b = (info[2].As<Napi::Number>()).Int32Value();

    int returnValue = iD_USB_CleanScreen(r, g, b);
    return Napi::Number::New(env, returnValue);
}

Napi::Number SetBrightnessWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Incorrect arguments.").ThrowAsJavaScriptException();
        return Napi::Number::New(env, -1);
    } 

    int per = (info[0].As<Napi::Number>()).Int32Value();

    int returnValue = iD_USB_SetBrightness(per);
    return Napi::Number::New(env, returnValue);
}

Napi::ArrayBuffer FirmwareVersionWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    uint8_t out_verStr[32];
    int returnValue = iD_USB_GetFirmwareVersion(out_verStr);
    if(returnValue){	// 0 => no error
    	Napi::Error::New(env, "Get FirmwareVersion failed !\n").ThrowAsJavaScriptException();
        return Napi::ArrayBuffer::New(env, 0);
    }
    return Napi::ArrayBuffer::New(env, out_verStr, sizeof(out_verStr)/sizeof(out_verStr[0]));
}

Napi::ArrayBuffer SerialNumberWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    uint8_t out_sn[32];
    int returnValue = iD_USB_GetCustomSerialNumber(out_sn);
    if(returnValue){	// 0 => no error
    	Napi::Error::New(env, "Get SerialNumber failed !\n").ThrowAsJavaScriptException();
        return Napi::ArrayBuffer::New(env, 0);
    }
    return Napi::ArrayBuffer::New(env, out_sn, sizeof(out_sn)/sizeof(out_sn[0]));
}

Napi::ArrayBuffer LibraryVersionWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    uint8_t out_ver[32];
    int returnValue = iD_USB_GetCustomSerialNumber(out_ver);
    if(returnValue){	// 0 => no error
    	Napi::Error::New(env, "Get LibaryVersion failed !\n").ThrowAsJavaScriptException();
        return Napi::ArrayBuffer::New(env, 0);
    }
    return Napi::ArrayBuffer::New(env, out_ver, sizeof(out_ver)/sizeof(out_ver[0]));
}

Napi::ArrayBuffer ButtonEventWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber() ) {
        Napi::TypeError::New(env, "Incorrect arguments.").ThrowAsJavaScriptException();
    } 

    int timeout = (info[0].As<Napi::Number>()).Int32Value();
    uint8_t arr[256];

    int returnValue = iD_USB_WaitEvent(arr, timeout);
    if(returnValue){	// 0 => no error
    	Napi::Error::New(env, "No Data Button Event!\n").ThrowAsJavaScriptException();
        return Napi::ArrayBuffer::New(env, 0);
    }
    return Napi::ArrayBuffer::New(env, arr, sizeof(arr)/sizeof(arr[0]));
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	exports.Set("deviceOpen", 		Napi::Function::New(env, DeviceOpenWrapper));
	exports.Set("deviceClose", 		Napi::Function::New(env, DeviceCloseWrapper));
	exports.Set("showImage", 		Napi::Function::New(env, ShowImageWrapper));
	exports.Set("cleanScreen", 		Napi::Function::New(env, CleanScreenWrapper));
	exports.Set("brightness", 		Napi::Function::New(env, SetBrightnessWrapper));
	exports.Set("firmwareVersion", 	Napi::Function::New(env, FirmwareVersionWrapper));
	exports.Set("serialNumber", 	Napi::Function::New(env, SerialNumberWrapper));
	exports.Set("libraryVersion", 	Napi::Function::New(env, LibraryVersionWrapper));
	exports.Set("updateFirmware", 	Napi::Function::New(env, FirmwareUpdateWrapper));
	exports.Set("getButtonData", 	Napi::Function::New(env, ButtonEventWrapper));
  	return exports;
}

NODE_API_MODULE(idisplay, InitAll)