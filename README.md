# Music256A-2016Fall-FinalProject

Description:

Virtual Plug-in is an audio plug-in utilizing augmented reality. User can design and draw the plug-in elements and borders on a tracing paper (or acrylic paper) and cover the paper on a flat computer screen. There's a camera recording what is drawn on the paper and transfer the information to the computer. The computer will distinguish different elements by color, and will show slider values, button colors or other elements on the screen to interact with the drawing. User can also use fingers to press the button or move the slider, which will result in the change of the output sound.


Installation: 

External camera on the top, external screen covered with acrylic paper, different colors of pens (computer will use color to distinguish different elements), moderate background color/light.



Milestone1:

Implemented a simple finger-controlled audio player. Buttons and volume control sliders are drawn on the paper. The web camera grabs the video and the program knows if finger is covered on the button by detecting the brightness change. The program is unstable sometimes and the performance is affected by environment brightness.

Next step would be let the program detect the elements by color (RGB value) rather than brightness.



Milestone2:

Implemented a color tracker which tracks different colors in the picture by hue value. Combined the color tracker with the previous milestone1 result. Now the web camera can recognize different elements of the plug-in drawn on paper by color, rather than position, which is more stable. The "audio playback" button is red color, "volume" slider is blue color, "audio stop" button is black color, and my finger (which points to the button and slider) is painted with purple. When the centroid of my finger (purple color) is inbound of contour of the element, then that element will make effect to the sound.

Next step: screen display values, design more advanced plug-in.