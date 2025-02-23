#include <napi.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

Napi::String RecognizeText(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "One argument expected: image path").ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }

  std::string imagePath = info[0].As<Napi::String>().Utf8Value();

  // 初始化 Tesseract API
  tesseract::TessBaseAPI tess;
  if (tess.Init(NULL, "eng"))
  { // 默认使用英文
    Napi::Error::New(env, "Could not initialize tesseract").ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }

  // 读取图像
  Pix *image = pixRead(imagePath.c_str());
  if (!image)
  {
    Napi::Error::New(env, "Could not read image").ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }

  tess.SetImage(image);
  char *outText = tess.GetUTF8Text();

  std::string result(outText);
  tess.End();
  pixDestroy(&image);
  delete[] outText;

  return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("recognizeText", Napi::Function::New(env, RecognizeText));
  return exports;
}

NODE_API_MODULE(tesseractAddon, Init)