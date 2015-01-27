#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    private:
        int windowWidth;
        int windowHeight;
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoGrabber cam;
        ofxCvColorImage colorImgHSV;                        // 色検出用（HSV系に変換した映像情報）
        vector<unsigned char *>  colorTrackedPixelsArry;    // 追跡するピクセルデータを保持
    
        ofImage     fromMaskImage;                          // 検出した色を出力するデータ（マスク元）
        ofImage     toMaskImage;                            // マスクした先
    
        // HSV系の色相、彩度、明度のマップ
        ofxCvGrayscaleImage hueImg;
        ofxCvGrayscaleImage satImg;
        ofxCvGrayscaleImage briImg;
    
    
        //-----------------------------------------
        // gui関連
        //-----------------------------------------
        ofxPanel gui;
        ofxIntSlider    hsvValueHMax;
        ofxIntSlider    hsvValueHMin;
        ofxIntSlider    hsvValueSMax;
        ofxIntSlider    hsvValueSMin;
        ofxIntSlider    hsvValueVMax;
        ofxIntSlider    hsvValueVMin;

};
