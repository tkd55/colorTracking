#include "ofApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
    windowWidth = ofGetWidth();
    windowHeight = ofGetHeight();

    // カメラの初期化
    cam.initGrabber(windowWidth, windowHeight);
    
    // それぞれの映像情報の大きさを指定
    // HSVデータを格納する領域
    colorImgHSV.allocate(ofGetWidth(), ofGetHeight());
  	hueImg.allocate(windowWidth, windowHeight);
   	satImg.allocate(windowWidth, windowHeight);
   	briImg.allocate(windowWidth, windowHeight);
    
    // 二値画像を作るための配列の大きさを指定
    unsigned char* colorTrackedPixels = new unsigned char [windowWidth * windowHeight];
    colorTrackedPixelsArry.push_back(colorTrackedPixels);

    // マスクした画像を出力する領域の確保
    toMaskImage.allocate(windowWidth, windowHeight, OF_IMAGE_COLOR);
    
    int hsvInit = 100;
    int hsvMin  = 0;
    int hsvMax  = 255;

    //--------------------------------------
    // GUI
    //--------------------------------------
    gui.setup();
    gui.add(hsvValueHMax.setup("hue Max", hsvInit, hsvMin, hsvMax));
    gui.add(hsvValueHMin.setup("hue Min", hsvInit, hsvMin, hsvMax));

    gui.add(hsvValueSMax.setup("Saturation Max", hsvInit, hsvMin, hsvMax));
    gui.add(hsvValueSMin.setup("Saturation Min", hsvInit, hsvMin, hsvMax));
    
    gui.add(hsvValueVMax.setup("Brightness Max", hsvInit, hsvMin, hsvMax));
    gui.add(hsvValueVMin.setup("Brightness Min", hsvInit, hsvMin, hsvMax));
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
    //------------------------------------
    // 色の検出
    //------------------------------------
    cv::Mat camMat = ofxCv::toCv(cam);
    unsigned char* matData = camMat.data;
    colorImgHSV.setFromPixels(matData, windowWidth, windowHeight);
 
    // 色相、彩度、明度にマッピング
    colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
    
    // ofxOpenCvアドオンにたいして画像が変更したことを通知
    hueImg.flagImageChanged();
    satImg.flagImageChanged();
    briImg.flagImageChanged();
    
    // ピクセルの配列をそれぞれに作成
    unsigned char * huePixels = hueImg.getPixels();
    unsigned char * satPixels = satImg.getPixels();
    unsigned char * briPixels = briImg.getPixels();
    
    // ピクセルの色が指定した色と色相と彩度が近ければ、colorTrackedPixelsArryに255を、遠ければ0を代入。
    int nPixels = ofGetWidth() * ofGetHeight(); // ピクセルの数
    for (int cnt = 0; cnt < nPixels; cnt++) {
        if( (hsvValueHMin <= huePixels[cnt] && huePixels[cnt] <= hsvValueHMax) &&
            (hsvValueSMin <= satPixels[cnt] && satPixels[cnt] <= hsvValueSMax) &&
            (hsvValueVMin <= briPixels[cnt] && briPixels[cnt] <= hsvValueVMax)){
             colorTrackedPixelsArry[0][cnt] = 255;
        }
        else{
            colorTrackedPixelsArry[0][cnt] = 0;
        }
    }
    
    // マスク用にピクセルデータの設定
    fromMaskImage.setFromPixels(colorTrackedPixelsArry[0], windowWidth, windowHeight, OF_IMAGE_GRAYSCALE);
    
    
    //--------------------------------------
    // マスク処理
    // 通常画像と検出した色でのマスク
    //--------------------------------------
    toMaskImage.clear();
    
    // ofImageをMat形式に変換
    cv::Mat toMastImageMat = ofxCv::toCv(toMaskImage);
    cv::Mat comMat = ofxCv::toCv(cam);
    cv::Mat fromMaskImageMat = ofxCv::toCv(fromMaskImage);
    comMat.copyTo(toMastImageMat, fromMaskImageMat);
    
    // Mat形式をunsigned charポインタに変換
    unsigned char* data = toMastImageMat.data;
    
    // 出力用にピクセルデータの設定
    toMaskImage.setFromPixels(data, windowWidth, windowHeight, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    colors.draw(0, 0, windowWidth, windowHeight);
    toMaskImage.draw(0, 0, windowWidth, windowHeight);
    
    // GUI表示
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}