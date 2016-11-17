#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 1024;
    height = 768;
    camera.setup(width, height);
    mySound.load("yuqing.mp3");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    for (int y = 0; y < height; y += 50) {
        for (int x = 0; x < width; x += 50) {
            //get pixel color
            int i = (y * width + x) * 3;
            //int i = (y * width) * 3;
            int r = camera.getPixels()[i + 0];
            int g = camera.getPixels()[i + 1];
            int b = camera.getPixels()[i + 2];
            
            //calculate brightness
            float br = (r + b + g) / 765.0;
            
            //std::cout << br << endl;
            
            
            //use HSB color
            //ofSetColor(ofColor::fromHsb(br*255,255,255));
         
            
            //if (br < 0.2) {
            //    cout << x<< " " << y << " "  << endl;
                
            //}
            
            
            
            if (x < 300 && y < 400 && br < 0.1) {
                mySound.play();
            }
            if (x < 300 && y > 600 && y < 800 && br < 0.1) {
                mySound.stop();
            }
            if (x > 750 && x < 1000 && br < 0.1) {
                //cout << y << endl;
                mySound.setVolume(y*0.002);
            }
            
            
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        mySound.play();
    } else if (key == 'p') {
        mySound.setPaused(true);
    } else if (key == 'b') {
        mySound.setPaused(false);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
