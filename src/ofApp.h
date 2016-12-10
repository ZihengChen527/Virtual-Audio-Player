#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxStk.h"

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioOut(float *output, int bufferSize, int nChannels);
        void DrawWav(ofPoint start, float* wavData, int wavDataSize,
                     int direction/*+1 or -1*/, float xFactor);
        ~ofApp();
		
    private:
        ofVideoGrabber camera;
        ofSoundPlayer mySound;
        ofSoundStream soundStream;
        ofxCvColorImage rgb, hsb;
        ofxCvGrayscaleImage hue, sat, bri,
                            filteredDarkRed, filteredRed, filteredDarkBlue, filteredBlue,
                            filteredGreen, filteredPink, filteredYellow, filteredPurple,
                            filteredGrassGreen, filteredFinger;
        ofxCvContourFinder contoursDarkRed, contoursRed, contoursDarkBlue, contoursBlue,
                           contoursGreen, contoursPink, contoursYellow,contoursPurple,
                           contoursGrassGreen, contoursFinger;
        ofTrueTypeFont trackingNotice, playingNotice, volumeNotice;
    
        int width, height;
        int hueDarkRed, hueRed, hueDarkBlue, hueBlue, hueGrassGreen,
            hueGreen, huePink, hueYellow, huePurple, hueFinger;
        bool colorTrackingStart;
        bool showVolumeValue, showRateValue;
        bool isPlaying, isStop;
        float* buffer;
        int bufferSize, samplingRate, nChannelOut, nChannelIn, delay;
        float volume;
    
        stk::FileWvIn fileWvIn;
        stk::StkFrames leftChannel;
        stk::StkFrames rightChannel;

};
