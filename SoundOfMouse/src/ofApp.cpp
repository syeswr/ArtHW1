#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //Perform screenshot
    string command = "/usr/sbin/screencapture -m -x " + ofFilePath::getAbsolutePath( ofToDataPath("")) + "tmp.png";
    system(command.c_str());
    //Load resources in from data folder
    desktop.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "tmp.png" );
    cursor.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "Cursor.png" );
    b1.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "b.wav");
    b2.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "b2.wav");
    b3.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "b3.wav");
    doS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "doS.wav");
    riS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "riS.wav");
    miS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "miS.wav");
    faS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "faS.wav");
    soS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "soS.wav");
    laS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "laS.wav");
    xiS.load(ofFilePath::getAbsolutePath( ofToDataPath("")) + "xiS.wav");
    
    //Setup
    dpixel = desktop.getPixels();
    CGDisplayHideCursor(kCGDirectMainDisplay);
    cursX = ofGetWindowWidth()/2;
    cursY = ofGetWindowHeight()/2;
    initialRatioX = cursor.getWidth()/ofGetWindowWidth();
    initialRatioY = cursor.getHeight()/ofGetWindowHeight();
    imgZoom.reset( 0.0f );
    imgZoom.setRepeatType(PLAY_ONCE);
    imgZoom.setCurve(EASE_IN_EASE_OUT);
    vertEnlong.reset(0.0f);
    vertEnlong.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
    vertEnlong.setCurve(OBJECT_DROP);
    ofBackground(0,0,0);
    mode = "DESKTOP";
    direction = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    //update animated vars
    imgZoom.update(1.0f/60.0f);
    vertEnlong.update(1.0f/60.0f);
}

//--------------------------------------------------------------
void ofApp::draw(){
    //If it is within first 4 DRAGs. Try to capture the interval between DRAGs.
    if(initial!=0 && determined!=4){
        if(initial<480){
            initial++;
        }
        else{
            initial=1;
            determined = 0;
        }
    }
    //If complete first 4 DRAGs, the rhythm should in.
    if(determined==4){
        if(beatCounter==0){
            //Use beat counter as a timer to trigger beats
            //play beat
            beatCounter++;
        }
        else{
            if(beatCounter%rythm==0){
                //Play rhythm according to different bpm
                if(ryN==0 && rythm == 33){
                    b1.play();
                }
                else if(ryN==0 && rythm == 60){
                    b2.play();
                }
                else if(ryN==0 && rythm == 120){
                    b3.play();
                }
                
                //Make the screen 'heart beat' with rhythm
                imgZoom.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
                imgZoom.setDuration(0.1);
                imgZoom.animateTo(100);
                if(ryN<3){
                    //We use a 4/4 beat system here
                    ryN++;
                }
                else{
                    ryN = 0;
                }
            }
            beatCounter++;
        }
    }
    
    if (mode == "DESKTOP"){
        //Display cursor and desktop screenshot
        deltaWidth = imgZoom;
        deltaHeight = (float(imgZoom) / ofGetWindowWidth() * ofGetWindowHeight());
        xComp = relativePosX * ofGetWindowWidth() - (relativePosX * (ofGetWindowWidth()+deltaWidth) - (deltaWidth)/2.0f);
        yComp = relativePosY * ofGetWindowHeight() - (relativePosY * (ofGetWindowHeight()+deltaHeight) - (deltaHeight)/2.0f);
        desktop.draw((-deltaWidth)/2.0f + xComp, (-deltaHeight)/2.0f + yComp, ofGetWindowWidth()+deltaWidth, ofGetWindowHeight()+ deltaHeight);
        if (mousePressing == false) {
            cursor.draw(cursX, cursY, (float(ofGetWindowWidth())+deltaWidth)*initialRatioX,  (float(ofGetWindowHeight())+deltaHeight)*initialRatioY);
        }
        else{
            cursor.draw((float(ofGetWindowWidth())+deltaWidth) * relativePosX - deltaWidth/2.0f+xComp, (float(ofGetWindowHeight())+deltaHeight) * relativePosY - deltaHeight/2.0f + yComp, (float(ofGetWindowWidth())+deltaWidth)*initialRatioX,  (float(ofGetWindowHeight())+deltaHeight)*initialRatioY);
        }
    }
    else if (mode == "PLAYING"){
        //display circles
        
        //direction: true = left to right, false = right to left
        if (direction == true) {
            for (int i=0; i<colors.size(); i++) {
                float x = screenSpaceX + i*screenSpaceDist;
                float y = screenSpaceY - i*k*screenSpaceDist;
                ofSetColor(colors[i]);
                float spec = 0;
                if (playK == i){
                    spec = 100;
                }
                ofDrawCircle(x, y, spec+screenSpaceDist/3.0f+float(imgZoom)/80.0f/float(i));
            }
        }
        else if (direction == false) {
            for (int i=colors.size()-1; i>=0; i--) {
                float x = screenSpaceX + i*screenSpaceDist;
                float y = screenSpaceY - i*k*screenSpaceDist;
                ofSetColor(colors[i]);
                float spec = 0;
                if (playK == i){
                    spec = 100;
                }
                ofDrawCircle(x, y, spec+screenSpaceDist/3.0f+float(imgZoom)/80.0f/float(i));
            }
        }
        if (step<colors.size()) {
            if(beatCounter%rythm==0){
                step++;
                //Play a note according to the color
                float note = (colors[step].r+colors[step].g+colors[step].b)/3.0f;
                float per = 255.0f/7.0f;
                if (note < per){
                    doS.play();
                }
                else if (note < per*2){
                    riS.play();
                }
                else if (note < per*3){
                    miS.play();
                }
                else if (note < per*4){
                    faS.play();
                }
                else if (note < per*5){
                    soS.play();
                }
                else if (note < per*6){
                    laS.play();
                }
                else if (note <= per*7+1){
                    xiS.play();
                }
                vertEnlong.setDuration(0.2);
                vertEnlong.animateTo(ofGetWindowHeight());
            }
            if(beatCounter%rythm<=rythm/2){
                float x;
       
                ofColor compensate;
                if(direction == true){
                    x = screenSpaceX + (step)*screenSpaceDist - screenSpaceDist/3.0f;
                    ofSetColor(colors[step]);
                    compensate.r = 255.0f - colors[step-1].r;
                    compensate.g = 255.0f - colors[step-1].g;
                    compensate.b = 255.0f - colors[step-1].b;
                    
                }
                if(direction == false){
                    x = screenSpaceX + (colors.size()-(step-1)-1)*screenSpaceDist - screenSpaceDist/3.0f;
                    ofSetColor(colors[colors.size()-step]);
                    compensate.r = 255.0f - colors[colors.size()-step].r;
                    compensate.g = 255.0f - colors[colors.size()-step].g;
                    compensate.b = 255.0f - colors[colors.size()-step].b;
                }
                
                ofDrawRectangle(x, 0, screenSpaceDist/3.0f*2.0f, vertEnlong);
                //ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetWindowHeight()-float(vertEnlong));
            }
        }
        else{
            mode = "DESKTOP";
            step = 0;
            imgZoom.setRepeatType(PLAY_ONCE);
            imgZoom.setDuration(0.5);
            imgZoom.animateTo(0);
            imgZoomValue = 0;
            zoomCenterX = 0;
            zoomCenterY = 0;
            ofSetColor(ofColor(255, 255, 255));
            colors.clear();
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int k;
    if(colors.size()>5){
        if(key == 97){
            k = 1;
        }
        else if(key == 115){
            k = 2;
        }
        else if(key == 100){
            k = 3;
        }
        else if(key == 102){
            k = 4;
        }
        else if(key == 103){
            k = 5;
        }
        else{
            return;
        }
        ofColor c = colors[k];
        playK = k;
        float note = (c.r+c.g+c.b)/3.0f;
        float per = 255.0f/7.0f;
        if (note < per){
            doS.play();
        }
        else if (note < per*2){
            riS.play();
        }
        else if (note < per*3){
            miS.play();
        }
        else if (note < per*4){
            faS.play();
        }
        else if (note < per*5){
            soS.play();
        }
        else if (note < per*6){
            laS.play();
        }
        else if (note <= per*7+1){
            xiS.play();
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    playK = -1;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    cursX = x;
    cursY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    imgZoom.setDuration(0.01);
    imgZoom.animateTo(imgZoomValue+200.0f);
    imgZoomValue += 200;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    zoomCenterX = cursX;
    zoomCenterY = cursY;
    relativePosX = zoomCenterX/ofGetWindowWidth();
    relativePosY = zoomCenterY/ofGetWindowHeight();
    mousePressing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (imgZoomValue < desktop.getWidth()*0.5f || determined!=4){
        if(determined==0){
            initial++;
        }
        if(determined!=4){
            determined+=1;
        }
        if(determined==4){
            if(float(initial)/4.0f>60){
                rythm = 120;
            }
            else if(float(initial)/4.0f>30){
                rythm = 60;
            }
            else{
                rythm = 33;
            }
        }
        imgZoom.setRepeatType(PLAY_ONCE);
        imgZoom.setDuration(0.5);
        imgZoom.animateTo(0);
        imgZoomValue = 0;
        zoomCenterX = 0;
        zoomCenterY = 0;
    }
    else{
        mode = "PLAYING";
        destX = x;
        destY = y;
        //k = (y2-y1)/(x2 - x1)
        k = (- destY + zoomCenterY) / (destX - zoomCenterX);
        b = destY - k*destX;
        if (destX < zoomCenterX) {
            for (int i=destX; i<zoomCenterX; i+=50) {
                int x = i;
                int y = k*x +b;
                int ii = desktop.getWidth();
                int si = desktop.getHeight();
                ofColor c = dpixel.getColor(x*(desktop.getWidth()/ofGetWidth()), y*(desktop.getHeight()/ofGetHeight()));
                colors.push_back(c);
                //dpixel.getColor(x/ofGetWidth()*desktop.getWidth(), y/ofGetHeight()*desktop.getHeight()
            }
            direction = false;
        }
        else if(destX > zoomCenterX) {
            for (int i=zoomCenterX; i<destX; i+=50) {
                int x = i;
                int y = k*x +b;
                ofColor c = dpixel.getColor(x*(desktop.getWidth()/ofGetWidth()), y*(desktop.getHeight()/ofGetHeight()));
                colors.push_back(c);
                //deal with macOS retina resolution
            }
            direction = true;
        }
        //Arrange Circles for Screen space
        float horiDist = ofGetWindowWidth()/colors.size()+1;
        float vertDist = ofGetWindowHeight()/colors.size()+1;
        float finalDist = min(horiDist, vertDist);
        float horiLen = (colors.size()-1)*finalDist;
        screenSpaceX = (ofGetWindowWidth() - horiLen)/2;
        if(k>0){
            screenSpaceY = horiLen + (ofGetWindowHeight() - horiLen)/2;
        }
        else{
            screenSpaceY = finalDist;
        }
        screenSpaceDist = finalDist;
        
        
    }
    mousePressing = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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



