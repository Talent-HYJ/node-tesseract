const tesseractAddon = require('../build/Release/tesseract-addon.node');

const imagePath = "./test.png"

tesseractAddon.recognizeText(imagePath)
    .then((text) => {
        console.log('识别结果:', text);
    })
    .catch((err) => {
        console.error('识别失败:', err);
    });