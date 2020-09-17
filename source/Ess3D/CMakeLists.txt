project(Ess3D VERSION 0.0.1 LANGUAGES CXX)

################################################################################
# Source groups
################################################################################

set(Headers
    2d/animations/Animation.h
    2d/animations/AnimationManager.h
    2d/camera/Camera2D.h
        2d/models/Object2D.h
        2d/models/Vertex2D.h
    2d/rendering/SpriteBatch.h
    2d/utils/Utils2D.h

    3d/camera/Camera3D.h
    3d/model/Mesh.h
    3d/model/Model.h
    3d/model/Vertex3D.h
    3d/rendering/MeshRenderer.h

    audio/AudioManager.h

    core/IGame.h
    core/IGameScreen.h
    core/ScreenManager.h

    gl/ColorRGBA8.h
    gl/FBORenderer.h
    gl/FrameBufferObject.h
    gl/Shader.h
    gl/Window.h
    gl/UV.h

    gui/GUI.h

    input/InputManager.h

    resources/ModelCache.h
    resources/Texture.h
    resources/TextureAtlas.h
    resources/TextureAtlasSection.h
    resources/TextureCache.h

    utils/Timing.h
    utils/Utils.h
    )
source_group("Headers" FILES ${Headers})

set(Sources
    2d/animations/Animation.cpp
    2d/animations/AnimationManager.cpp
    2d/camera/Camera2D.cpp
    2d/rendering/SpriteBatch.cpp
    2d/utils/Utils2D.cpp
        2d/models/Object2D.cpp

    3d/camera/Camera3D.cpp
    3d/model/Mesh.cpp
    3d/model/Model.cpp
    3d/rendering/MeshRenderer.cpp

    audio/AudioManager.cpp

    core/IGame.cpp
    core/ScreenManager.cpp

    errors/RuntimeException.cpp

    gl/FBORenderer.cpp
    gl/FrameBufferObject.cpp
    gl/Shader.cpp
    gl/Window.cpp

    gui/GUI.cpp

    input/InputManager.cpp

    resources/ModelCache.cpp
    resources/Texture.cpp
    resources/TextureAtlas.cpp
    resources/TextureAtlasSection.cpp
    resources/TextureCache.cpp

    utils/Timing.cpp
    utils/Utils.cpp
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
        2d/traits/IRenderable2D.cpp 2d/traits/IRenderable2D.h
    2d/rendering/Renderer2D.cpp 2d/rendering/Renderer2D.h
    2d/Scene2D.cpp 2d/Scene2D.h
    core/State.cpp core/State.h
    core/Config.cpp core/State.h
        core/traits/IUpdatable.cpp core/traits/IUpdatable.h
        core/traits/IInterpolatable.cpp core/traits/IInterpolatable.h core/traits/IHandlesInput.cpp core/traits/IHandlesInput.h)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Ess3D)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
    )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../build/$<CONFIG>/${PROJECT_NAME}/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../build/$<CONFIG>/${PROJECT_NAME}/"
    )
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
      "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
      "NDEBUG"
    ">"
    "WIN32;"
    "_LIB;"
    "UNICODE;"
    "_UNICODE"
    )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE
      $<$<CONFIG:Debug>:
        /Od;
        ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
      >
      $<$<CONFIG:Release>:
        /O2;
        /Oi;
        /MD;
        /Gy
      >
      /wd4251;
      /wd4275;
      /sdl;
      /W3;
      ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
      ${DEFAULT_CXX_EXCEPTION_HANDLING};
      /Y-
      )

  target_link_options(${PROJECT_NAME} PRIVATE
      $<$<CONFIG:Debug>:
        /DEBUG;
        /SUBSYSTEM:CONSOLE;
        /INCREMENTAL;
        /verbose:lib
      >
      $<$<CONFIG:Release>:
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
      >
      )
endif ()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
      "fmodL_vc;"
      "fmodstudioL_vc;"
      "CEGUIBase-0_d;"
      "CEGUIOpenGLRenderer-0_d"
    ">"
    "$<$<CONFIG:Release>:"
      "fmod_vc;"
      "fmodstudio_vc;"
      "CEGUIBase-0;"
      "CEGUIOpenGLRenderer-0"
    ">"
    "freeglut;"
    "glew32;"
    "SDL2;"
    "SDL2main;"
    "SDL2_image;"
    "opengl32;"
    "freetype255d;"
    "box2d;"
    "assimp-4.1.0-vc140-mtd"
    )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/box2d/lib/$<CONFIG>/x86/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/CEGUI/lib/$<CONFIG>/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/freetype/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/freeglut/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/glew/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/SDL2_Image/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/SDL2/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/FMOD/lowlevel/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/FMOD/studio/lib/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/assimp-4.1.0/lib/;"
    "$ENV{LibraryPath}"
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/SDL2/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/SDL2_Image/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/glew/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/freeglut/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/glm/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/freetype/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/rapidjson/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/box2d/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/FMOD/lowlevel/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/FMOD/studio/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/FMOD/fsbank/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/CEGUI/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/assimp-4.1.0/include/;"
    "${PROJECT_SOURCE_DIR}"
)