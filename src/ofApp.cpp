/* Virtual Audio Player
 *
 * Track different colors to distinguish different elements of the 
 * audio player drawn on the screen. Detect finger position, display
 * values and play audio according to the finger position.
 *
 * To start tracking, press key 't'.
 *
 * Current color setting:
 *    Dark blue -- audio play
 *    Red -- audio stop
 *    Purple -- waveform display area
 *    Pink -- volume slider
 *    Blue -- playback rate slider
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /* video setup */
    
    // camera width and height, should be specified for different camera
    // 1280 * 960 for web camera
    // 1280 * 720 for Macbook Pro camera
    width = 1280;
    height = 960;
    
    // target hue values for color tracking, maybe changed
    // after testing the hue value using HueTester program
    // in different enviroment
    hueDarkRed = 176;     // 176
    hueRed = 171;         // 168~172
    hueDarkBlue = 118;    // 116~120
    hueBlue = 105;        // 101~109
    huePink = 158;        // 156~162
    huePurple = 130;      // 124~136
    hueFinger = 179;      // finger hue value, paint dark red on the finger here
    // hueGreen = 86;          // 84~88     // not good performance
    // hueGrassGreen = 48;     // 35~57     // not good performance
    // hueYellow = 34;         // 34        // not good performance
    
    // start color tracking if this sign is "true", set in the
    // keyPressed() function
    colorTrackingStart = false;
    
    // if the slider value be drawn show on the screen
    showVolumeValue = false;
    showRateValue = false;
    
    // initialize audio playing state
    isPlaying = false;
    isStop = true;
    
    // setup camera
    camera.setup(width, height);
    camera.initGrabber(width, height, true);
    
    // reserve memory for cv images
    rgb.allocate(width, height);
    hsb.allocate(width, height);
    hue.allocate(width, height);
    sat.allocate(width, height);
    bri.allocate(width, height);
    filteredDarkRed.allocate(width, height);
    filteredRed.allocate(width, height);
    filteredDarkBlue.allocate(width, height);
    filteredBlue.allocate(width, height);
    filteredGreen.allocate(width, height);
    filteredPink.allocate(width, height);
    filteredYellow.allocate(width, height);
    filteredPurple.allocate(width, height);
    filteredGrassGreen.allocate(width, height);
    filteredFinger.allocate(width, height);
    
    // initialize font and size for the text displayed
    trackingNotice.loadFont("Philosopher-Regular.ttf", 40);
    playingNotice.loadFont("Xerox Sans Serif Narrow.ttf", 30);
    volumeNotice.loadFont("Philosopher-Regular.ttf", 20);
    
    
    /* audio setup */
    
    // audio parameters
    bufferSize = 512;
    samplingRate = 44100;
    nChannelOut = 2;
    nChannelIn = 0;
    delay = 2;
    
    // load audio input
    fileWvIn.openFile(ofToDataPath("yuqing.wav", true));
    soundStream.setup(this, nChannelOut, nChannelIn, samplingRate, bufferSize, delay);
    
    // initialize audio buffers and initial playback rate and volume
    buffer = new float[bufferSize];
    leftChannel.resize(bufferSize, 1);
    rightChannel.resize(bufferSize, 1);
    volume = 1;
    fileWvIn.setRate(1.0);
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    
    // copy webcam pixels to rgb image
    rgb.setFromPixels(camera.getPixels());
    
    // mirror horizontal and vertical
    rgb.mirror(true, true);
    
    if (camera.isFrameNew() && colorTrackingStart) {
        
        // duplicate rgb
        hsb = rgb;
        
        // convert to hsb
        hsb.convertRgbToHsv();
        
        // store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        // comment it out since dark red value is used for finger
        /*
        // filter image based on the dark red hue value
        for (int i = 0; i < width * height; i++) {
            filteredDarkRed.getPixels()[i] = ofInRange(hue.getPixels()[i], hueDarkRed-2,
                                                   hueDarkRed+2) ? 255 : 0;
        }
        filteredDarkRed.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with dark red hue
        contoursDarkRed.findContours(filteredDarkRed, 50, width*height/2, 1, false);
        */
         
        // filter image based on the red hue value
        for (int i = 0; i < width * height; i++) {
            filteredRed.getPixels()[i] = ofInRange(hue.getPixels()[i], hueRed-4,
                                                   hueRed+4) ? 255 : 0;
        }
        filteredRed.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with red hue
        contoursRed.findContours(filteredRed, 50, width*height/2, 1, false);
        
        // filter image based on the dark blue hue value
        for (int i = 0; i < width * height; i++) {
            filteredDarkBlue.getPixels()[i] = ofInRange(hue.getPixels()[i], hueDarkBlue-3,
                                                    hueDarkBlue+3) ? 255 : 0;
        }
        filteredDarkBlue.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with dark blue hue
        contoursDarkBlue.findContours(filteredDarkBlue, 50, width*height/2, 1, false);
        
        
        // filter image based on the blue hue value
        for (int i = 0; i < width * height; i++) {
            filteredBlue.getPixels()[i] = ofInRange(hue.getPixels()[i], hueBlue-4,
                                                        hueBlue+4) ? 255 : 0;
        }
        filteredBlue.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with dark blue hue
        contoursBlue.findContours(filteredBlue, 50, width*height/2, 1, false);
        
        
        // filter image based on the pink hue value
        for (int i = 0; i < width * height; i++) {
            filteredPink.getPixels()[i] = ofInRange(hue.getPixels()[i], huePink-6,
                                                     huePink+6) ? 255 : 0;
        }
        filteredPink.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with pink hue
        contoursPink.findContours(filteredPink, 50, width*height/2, 1, false);
         
        // filter image based on the purple hue value
        for (int i = 0; i < width * height; i++) {
            filteredPurple.getPixels()[i] = ofInRange(hue.getPixels()[i], huePurple-6,
                                                     huePurple+6) ? 255 : 0;
        }
        filteredPurple.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with purple hue
        contoursPurple.findContours(filteredPurple, 50, width*height/2, 1, false);
        
        // filter image based on the finger hue value
        for (int i = 0; i < width * height; i++) {
            filteredFinger.getPixels()[i] = ofInRange(hue.getPixels()[i], hueFinger-2,
                                                      hueFinger+2) ? 255 : 0;
        }
        filteredFinger.flagImageChanged();
        // run the contour finder on the filtered image to find blobs with red hue
        contoursFinger.findContours(filteredFinger, 50, width*height/2, 1, false);
        
        
        // audio play action -- Dark Blue
        if (contoursDarkBlue.nBlobs > 0 && contoursFinger.nBlobs > 0) {
            if (contoursDarkBlue.blobs[0].boundingRect.inside(contoursFinger.blobs[0].centroid)) {
                if (isStop) {
                    fileWvIn.openFile(ofToDataPath("yuqing.wav", true));
                    isStop = false;
                }
                if (!isPlaying) {
                    isPlaying = true;
                }
                soundStream.start();
            }
        }
        
        // audio stop action -- Red
        if (contoursRed.nBlobs > 0 && contoursFinger.nBlobs > 0) {
            if (contoursRed.blobs[0].boundingRect.inside(contoursFinger.blobs[0].centroid)) {
                if (isPlaying) {
                    soundStream.stop();
                    isPlaying = false;
                    isStop = true;
                }
            }
        }
        
        // audio volume slider -- Pink
        if (contoursPink.nBlobs > 0 && contoursFinger.nBlobs > 0) {
            if (contoursPink.blobs[0].boundingRect.inside(contoursFinger.blobs[0].centroid)) {
                showVolumeValue = true;
                volume = contoursFinger.blobs[0].centroid.y * 0.0015;
                cout << contoursFinger.blobs[0].centroid.y << endl;
            } else {
                showVolumeValue = false;
            }
        }
        
        
        // audio playback rate slider -- blue
        if (contoursBlue.nBlobs > 0 && contoursFinger.nBlobs > 0) {
            if (contoursBlue.blobs[0].boundingRect.inside(contoursFinger.blobs[0].centroid)) {
                showRateValue = true;
                fileWvIn.setRate(contoursFinger.blobs[0].centroid.y * 0.003);
                cout << contoursFinger.blobs[0].centroid.y << endl;
            } else {
                showRateValue = false;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    ofBackground(255, 255, 255);
    //rgb.draw(0, 0);      // use for test, uncomment it to see the detected contour on camera
    
    if (colorTrackingStart) {  // press key "t" to start tracking
        
        // draw contours    // use for test, uncomment it to see the detected contour
        //contoursRed.draw();
        //contoursDarkBlue.draw();
        //contoursPink.draw();
        //contoursPurple.draw();
        //contoursBlue.draw();
        
        // display "start tracking" on the external screen
        ofSetColor(ofColor::black);
        trackingNotice.drawString("Start Tracking", ofGetWindowWidth() / 3 + 100, 1100);
        
        // display "playing" while the audio is playing
        if (isPlaying) {
            playingNotice.drawString("Playing", (contoursDarkBlue.blobs[0].centroid.x + 10) * 1600 / 1280, contoursDarkBlue.blobs[0].centroid.y * 1600 / 1280);
        }
        
        // display volume if detecting user is changing volume
        ofSetColor(ofColor::black);
        if (showVolumeValue) {
            volumeNotice.drawString(ofToString(contoursFinger.blobs[0].centroid.y * 0.0015),
                                    (contoursPink.blobs[0].centroid.x + 50) * 1600 / 1280,
                                    (contoursPink.blobs[0].centroid.y + 200) * 1600 / 1280);
        }
        
        // display playback rate if detecting user is changing volume
        if (showRateValue) {
            volumeNotice.drawString(ofToString(contoursFinger.blobs[0].centroid.y * 0.003),
                                    (contoursBlue.blobs[0].centroid.x - 100) * 1600 / 1280,
                                    (contoursBlue.blobs[0].centroid.y + 200) * 1600 / 1280);
        }
        
        // draw green dot at the finger position
        ofSetColor(ofColor::green);
        ofFill();
        for (int i=0; i<contoursFinger.nBlobs; i++) {
            ofCircle(contoursFinger.blobs[i].centroid.x, contoursFinger.blobs[i].centroid.y, 20);
        }
    }
    
    // draw waveform
    ofPoint start;
    start.set(680, 700);
    ofSetColor(0, 0, 0);
    if (!isStop) {
        DrawWav(start, buffer, bufferSize, +1, 1000);
        cout << *buffer << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){   // key control for playing files, use for testing
    if (key == ' ') {
        if (isStop) {
            fileWvIn.openFile(ofToDataPath("yuqing.wav", true));
            isStop = false;
        }
        isPlaying = !isPlaying;
        soundStream.start();
    } else if (key == 's') {
        soundStream.stop();
        isPlaying = false;
        isStop = true;
    } else if (key == 'u') {
        volume += 0.1;
    } else if (key == 'd') {
        volume -= 0.1;
    } else if (key == 't') { // control color tracking start/stop
        colorTrackingStart = !colorTrackingStart;
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

// destructor
ofApp::~ofApp() {
    delete []buffer; 
    soundStream.close();
}

//--------------------------------------------------------------
// audioOut() -- deal with output audio buffer
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels) {
    if (isPlaying) {
        stk::StkFrames frames(bufferSize, 2);
        fileWvIn.tick(frames);
        
        leftChannel.resize(bufferSize, 1);
        rightChannel.resize(bufferSize, 1);
        frames.getChannel(0, leftChannel, 0);
        frames.getChannel(1, rightChannel, 0);

        buffer = &leftChannel[0];

        for (int i = 0; i < bufferSize; i++) {
            buffer[i] *= volume;
        }

        for (int i = 0; i < bufferSize; i++) {
            output[2*i] = leftChannel(i, 0) * volume;
            output[2*i+1] = rightChannel(i, 0) * volume;
        }
    }
}

//---------------------------------------------------------------
// DrawWav() -- draw waveform of a buffer
//---------------------------------------------------------------
void ofApp::DrawWav(ofPoint start, float* wavData, int wavDataSize,
             int direction/*+1 or -1*/, float xFactor) {
    for (int i = 0; i < wavDataSize; i++)
    {
        if(i % 2 == 0)
        {
            float firstx = start.x + direction*(i / 2);
            float firsty = start.y - (wavData[i] * xFactor);
            float secondy = start.y - (wavData[i+1] * xFactor);
            ofDrawLine( firstx, firsty, firstx, secondy);
        }
    }
}
