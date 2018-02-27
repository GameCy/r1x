INCLUDEPATH += $$PWD/../core
include($$PWD/../core/core.pri)

RESOURCES += \
    $$PWD/shaders/shaders.qrc

SOURCES += \
    $$PWD/AngleInterpolator.cpp \
    $$PWD/BlinkFloat.cpp \
    $$PWD/Graphics.cpp \
    $$PWD/AtlasImporter.cpp \
    $$PWD/Camera.cpp \
    $$PWD/CellMap.cpp \
    $$PWD/DPIHelper.cpp \
    $$PWD/FrameRate.cpp \
    $$PWD/Hermite.cpp \
    $$PWD/Material.cpp \
    $$PWD/Mesh.cpp \
    $$PWD/Model.cpp \
    $$PWD/ModelManager.cpp \
    $$PWD/Ogl.cpp \
    $$PWD/QuadRendererBase.cpp \
    $$PWD/Shader.cpp \
    $$PWD/Sprite.cpp \
    $$PWD/SpriteMap.cpp \
    $$PWD/Texture.cpp \
    $$PWD/TextureManager.cpp \
    $$PWD/Utils.cpp \
    $$PWD/OBJLoader.cpp \
    $$PWD/Vertex.cpp \
    $$PWD/InstanceRender.cpp \
    $$PWD/Interpolator.cpp \
    $$PWD/UVAnim.cpp \
    $$PWD/QuadTypes.cpp \
    $$PWD/QuadRenderers.cpp

HEADERS += \
    $$PWD/AngleInterpolator.h \
    $$PWD/AtlasImporter.h \
    $$PWD/BlinkFloat.h \
    $$PWD/Camera.h \
    $$PWD/CellMap.h \
    $$PWD/DPIHelper.h \
    $$PWD/FrameRate.h \
    $$PWD/Graphics.h \
    $$PWD/Hermite.h \
    $$PWD/IClipper.h \
    $$PWD/Material.h \
    $$PWD/Mesh.h \
    $$PWD/Model.h \
    $$PWD/ModelManager.h \
    $$PWD/Ogl.h \
    $$PWD/QuadRendererBase.h \
    $$PWD/Shader.h \
    $$PWD/Sprite.h \
    $$PWD/SpriteMap.h \
    $$PWD/Texture.h \
    $$PWD/TextureManager.h \
    $$PWD/Utils.h \
    $$PWD/OBJLoader.h \
    $$PWD/Vertex.h \
    $$PWD/InstanceRenderer.h \
    $$PWD/ViewPort.h \
    $$PWD/Interpolator.h \
    $$PWD/UVAnim.h \
    $$PWD/QuadTypes.h \
    $$PWD/QuadRenderers.h
