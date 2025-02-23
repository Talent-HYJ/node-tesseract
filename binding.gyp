{
  "targets": [
    {
      "target_name": "tesseract-addon",
      "sources": ["src/ocr.cc"],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include_dir\")",
        "/usr/local/include"
      ],
      "libraries": [
        "-L/usr/local/lib",
        "-ltesseract",
        "/usr/local/lib/libtesseract.a"
      ],
     'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}