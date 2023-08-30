cmake_minimum_required(VERSION 3.5)

project(examples VERSION 0.3 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGLWidgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui OpenGLWidgets Multimedia)

include(${CMAKE_CURRENT_SOURCE_DIR}/../graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/../components/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/../audio/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/../user-interface/CMakeLists.txt)


set(PROJECT_SOURCES
    ${R1X_GRAPHICS}
    ${R1X_COMPONENTS}
    ${R1X_AUDIO}
    ${R1X_USER_INTERFACE}

   DragToTarget.cpp
   InputTracker.cpp
   PlaySoundFx.cpp
   main.cpp
   mainwidget.cpp
   UIFactory.cpp
   SpritesFromAtlas.cpp
   UserInterface.cpp
   Viewd3dModels.cpp
   SpriteParticleFade.cpp
   TiledMap.cpp
   DragToTarget.h
   InputTracker.h
   PlaySoundFx.h
   mainwidget.h
   UIFactory.h
   ExampleBase.h
   SpritesFromAtlas.h
   UserInterface.h
   Viewd3dModels.h
   SpriteParticleFade.h
   TiledMap.h
)

set(RESOURCE_FILES
    assets/Sounds.qrc
    assets/textures.qrc
    assets/fonts.qrc
    assets/models.qrc
    assets/tiledmaps.qrc
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(examples
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RESOURCE_FILES}
    )
    # Define target properties for Android with Qt 6 as:
    set_property(TARGET examples APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(examples SHARED
            ${PROJECT_SOURCES}
            ${RESOURCE_FILES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(examples
            ${PROJECT_SOURCES}
            ${RESOURCE_FILES}
        )
    endif()
endif()

target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../core/)
target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../graphics/)
target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../components/)
target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../user-interface/)
target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../audio/)

target_link_libraries(examples PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.r1xlib.examples)
endif()
set_target_properties(examples PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS examples
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(examples)
endif()
