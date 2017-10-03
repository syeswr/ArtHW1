#pragma once

#include "ofMain.h"
#include "ofImage.h"
#include "ofxAnimatableFloat.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    private:
        ofImage desktop;
        ofImage cursor;
        int cursX = 0;
        int cursY = 0;
        ofxAnimatableFloat imgZoom;
        ofxAnimatableFloat vertEnlong;
        float imgZoomValue = 0;
        float deltaHeight = 0;
        float deltaWidth = 0;
        float deltaMouseHeight = 0;
        float deltaMouseWidth = 0;
        float initialRatioX = 0;
        float initialRatioY = 0;
        float zoomCenterX = 0;
        float zoomCenterY = 0;
        float relativePosX = 0;
        float relativePosY = 0;
        bool mousePressing = false;
        float xComp = 0;
        float yComp = 0;
        float destX = 0;
        float destY = 0;
        //y = kx + b
        float k = 0;
        float b = 0;
        string mode = "DESKTOP";
        vector<ofColor> colors;
        ofPixels_<unsigned char> dpixel;
        //true for right, false for left
        bool direction = true;
        float screenSpaceY =0;
        float screenSpaceX =0;
        float screenSpaceDist =0;
        int beatCounter = 0;
        int rythm = 30;
        int step =0;
        int initial = 0;
        int determined = 0;
        ofSoundPlayer b1;
        ofSoundPlayer b2;
        ofSoundPlayer b3;
        ofSoundPlayer b4;
        ofSoundPlayer doS;
        ofSoundPlayer riS;
        ofSoundPlayer miS;
        ofSoundPlayer faS;
        ofSoundPlayer soS;
        ofSoundPlayer laS;
        ofSoundPlayer xiS;
        int playK = 0;
        int ryN = 0;
};
