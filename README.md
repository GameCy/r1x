# r1x

r1x is intended to become an OpenGL ES 2.0 rendering / game engine.

It is in early stage. Tested on Ubuntu and Android.

Simple examples with some animated sprites from a texture atlas and rendering 3d mmodels (obj) can be found in the examples folder

![screenshot 1](https://gitlab.com/GameCy/r1x/-/blob/master/examples/screenshots/ScreenshotExample1.png)

![screenshot 2](https://gitlab.com/GameCy/r1x/-/blob/master/examples/screenshots/ScreenshotExample2.png)

![screenshot 3](https://gitlab.com/GameCy/r1x/-/blob/master/examples/screenshots/ScreenshotExample3.png)

![screenshot 4](https://gitlab.com/GameCy/r1x/-/blob/master/examples/screenshots/ScreenshotExample4.png)


Features

---------------

graphics/

* Loading Textures
* Texture Atlases (from Cheetah Texture Packer, json format)
* Sprites - Sprite sheet animations - colormask and transparency per sprite (1 rendering call for whole SpriteMap)
* Shaders
* Hermite curves
* Loading and Rendering 3D models from OBJ files
* Mesh Instancing
* ViewPort and Camera abstraction classes
* Loading levels built with the Tiled editor and exported in json format. (see examples/TiledMap.cpp)

audio/

* Playing wav files, (play, pause,resume,loop, stop)

user-interface/

* Texture Fonts / color text rendering
* Buttons. 
* Icons
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
