# r1x

r1x is intended to become an OpenGL ES 2.0 rendering / game engine.

It is in early stage. 

Simple examples with some animated sprites from a texture atlas and rendering 3d mmodels (obj) can be found in the examples folder

![alt text](https://github.com/GameCy/r1x/blob/master/examples/screenshots/ScreenshotExample1.png)
![alt text](https://github.com/GameCy/r1x/blob/master/examples/screenshots/ScreenshotExample2.png)

Tested on Ubuntu and Android.


Features

---------------

graphics/

* Loading Textures
* Texture Atlases (from Cheetah Texture Packer, json format)
* Sprites - Sprite sheet animations
* Shaders
* Hermite curves
* Loading and Rendering 3D models from OBJ files
* Mesh Instancing
* ViewPort and Camera abstraction classes

audio/

* Playing wav files, (play, pause,resume,loop, stop)

user-interface/

* Texture Fonts / color text rendering
* Buttons. 
* TextLabels
* InputArea (processing tap/mouse clicks)

core/

* events 
* delegates
* event dispatcher,
* delegate dispatcher, 
* timer
* pseudo randomizer
* smart pointers
