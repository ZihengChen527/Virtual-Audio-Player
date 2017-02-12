# Virtual Audio Player -- Music256A Final Project


### Description:

Virtual Audio Player is an audio player utilizing augmented reality. User can design and draw the audio player elements(play button, sliders, etc.) on a transparent paper and cover the paper on a flat computer screen. Then user can use finger to to press the button or move the sliders, just like using a real audio player. A web camera detects the finger position and audio elements by color, and transfer the information to the computer to change the output sound. The computer can also draw waveform, current slider value and other elements on the screen to interact with the drawing. 


### Installation: 

External camera on the top, external screen covered with transparent paper, different colors of mark pens.


### Guide in running the program:

1. Set the width and height value according to your camera settings. You should configure this properly or the tracking won't work.
   Recommend setting:
       Logitech web camera: 1280 * 960
       Macbook Pro laptop camera: 1280 * 720
		
2. Run the HueTest program to detect the hue value for your drawings (also every time when you switch to a new environment, it would be good to run HueTest to detect the value again). You can also use the hue value at the below section "Color hue value in different environment" as a rough estimation. The program will perform best at dark environment with  only one yellow light for finger testing. After testing, change the target hue value in Virtual Audio Player program.

3. Start the Virtual Audio Player program, press 't' to start tracking.

4. Paste a paper with dark red color on your finger. Press the button or move the slider.


### Project demo video: https://youtu.be/VRHCBn_fqmM


### Step by step progress in implementing the project

Milestone1:

Implemented a simple finger-controlled audio player. Buttons and volume control sliders are drawn on the paper. The web camera grabs the video and the program knows if finger is covered on the button by detecting the brightness change. The program is unstable sometimes and the performance is affected by environment brightness.
Next step would be let the program detect the elements by color (RGB value) rather than brightness.

Milestone2:

Implemented a color tracker which tracks different colors in the picture by hue value. Combined the color tracker with the previous milestone1 result. Now the web camera can recognize different elements of the plug-in drawn on paper by color, rather than position, which is more stable. The "audio playback" button is red color, "volume" slider is blue color, "audio stop" button is black color, and my finger (which points to the button and slider) is painted with purple. When the centroid of my finger (purple color) is inbound of contour of the element, then that element will make effect to the sound.
Next step: screen display values, design more advanced elements

Final version: 

A well-tested virtual audio player, with play button, stop button, volume slider, audio playback rate slider, waveform display. Camera detect different elements by hue value. Stable in yellow light environment.


### Color hue value in different environment

No light circumstance:
Red: 176,
Dark Blue: 117,
Grass Green: 54,
Pink: 159,
Yellow: 34,
Blue: 108,
Purple: 127

Mild light circumstance:
Red: 174,
Dark Blue: 130,
Grass Green: 56,
Pink: 160,
Yellow: 34,
Blue: 110,
Purple: 123,
Finger + Pink = 178

Studio C without light (not good with light)
Dark Red: 176,
Red: 164~170,
Dark Blue: 113~118,
Blue: 101~109,
Pink: 146~152,
Grass Green: 47~56 (not good),
Green: 80~85,
Yellow: 39 (not good in distinction),
Purple: 125~130,
Finger: (dark, can not distinct)

Stage with light (No.8 light configuration):
Dark Red: 176,
Red: 164~172,
Dark Blue: 116~120,
Blue: 106~109,
Pink: 147~156,
Green: 82~88,
Purple: 129~137,
Grass Green: 35~57 (not very good),
Yellow: 34 (not good in distinction),
Finger: 6~8 (not good in distinction)
