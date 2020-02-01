project(Ess3D CXX)

################################################################################
# Source groups
################################################################################

set(Headers
    "Animation.h"
    "AnimationManager.h"
    "AudioManager.h"
    "Camera2D.h"
    "Camera3D.h"
    "FrameBufferObject.h"
    "GUI.h"
    "IGame.h"
    "IGameScreen.h"
    "InputManager.h"
    "IOManager.h"
    "ResourceManager.h"
    "ScreenManager.h"
    "Shader.h"
    "SpriteBatch.h"
    "Texture2D.h"
    "TextureAtlas.h"
    "TextureCache.h"
    "Timing.h"
    "Vertex.h"
    "Window.h"
    )
source_group("Headers" FILES ${Headers})

set(Sources
    "Animation.cpp"
    "AnimationManager.cpp"
    "AudioManager.cpp"
    "Camera2D.cpp"
    "Camera3D.cpp"
    "Errors/RuntimeException.cpp"
    "FrameBufferObject.cpp"
    "GUI.cpp"
    "IGame.cpp"
    "InputManager.cpp"
    "IOManager.cpp"
    "ResourceManager.cpp"
    "ScreenManager.cpp"
    "Shader.cpp"
    "SpriteBatch.cpp"
    "Texture2D.cpp"
    "TextureAtlas.cpp"
    "TextureCache.cpp"
    "Timing.cpp"
    "Window.cpp"
    )
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
    )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Ess3D)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
    )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/../build/$<CONFIG>/${PROJECT_NAME}/"
    OUTPUT_DIRECTORY_DEBUGNCP "${CMAKE_SOURCE_DIR}/../build/$<CONFIG>/${PROJECT_NAME}/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../build/$<CONFIG>/${PROJECT_NAME}/"
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
    "$<$<CONFIG:DebugNCP>:"
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
      $<$<CONFIG:DebugNCP>:
      /Od;
      ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
      >
      $<$<CONFIG:Release>:
      /O2;
      /Oi;
      /MD;
      /Gy
      >
      /sdl;
      /W3;
      ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
      ${DEFAULT_CXX_EXCEPTION_HANDLING};
      /Y-
      )
  target_link_options(${PROJECT_NAME} PRIVATE
      $<$<CONFIG:Release>:
      /OPT:REF;
      /OPT:ICF
      >
      /SUBSYSTEM:WINDOWS
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
    "$<$<CONFIG:DebugNCP>:"
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
    "Box2D"
    )
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:"
    "${CMAKE_SOURCE_DIR}/../lib/box2d/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/CEGUI/lib/$<CONFIG>"
    ">"
    "$<$<CONFIG:DebugNCP>:"
    "${CMAKE_SOURCE_DIR}/../lib/box2d/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/CEGUI/lib/Debug/"
    ">"
    "$<$<CONFIG:Release>:"
    "${CMAKE_SOURCE_DIR}/../lib/box2d/lib/Release/;"
    "${CMAKE_SOURCE_DIR}/../lib/CEGUI/lib/$<CONFIG>/"
    ">"
    "${CMAKE_SOURCE_DIR}/../lib/freetype/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/freeglut/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/glew/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/SDL2_Image/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/SDL2/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/FMOD/lowlevel/lib/;"
    "${CMAKE_SOURCE_DIR}/../lib/FMOD/studio/lib/;"
    "$ENV{LibraryPath}"
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/../lib/SDL2/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/SDL2_Image/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/glew/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/freeglut/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/glm/;"
    "${CMAKE_SOURCE_DIR}/../lib/freetype/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/rapidjson/;"
    "${CMAKE_SOURCE_DIR}/../lib/FMOD/lowlevel/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/FMOD/studio/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/FMOD/fsbank/include/;"
    "${CMAKE_SOURCE_DIR}/../lib/CEGUI/include/;"
    "Errors/;",
    "$ENV{LibraryPath}"
)