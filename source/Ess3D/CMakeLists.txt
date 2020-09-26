PROJECT(Ess3D VERSION 0.0.1 LANGUAGES CXX)

################################################################################
# Source groups
################################################################################

SET(Headers
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

    errors/RuntimeException.h

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
SOURCE_GROUP("Headers" FILES ${Headers})

SET(Sources
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
SOURCE_GROUP("Sources" FILES ${Sources})

SET(ALL_FILES
    ${Headers}
    ${Sources}
    2d/traits/IRenderable2D.cpp 2d/traits/IRenderable2D.h
    2d/rendering/Renderer2D.cpp 2d/rendering/Renderer2D.h
    2d/Scene2D.cpp 2d/Scene2D.h
    core/State.cpp core/State.h
    core/Config.cpp core/State.h
    core/traits/IUpdatable.cpp core/traits/IUpdatable.h
    core/traits/IInterpolatable.cpp core/traits/IInterpolatable.h
    core/traits/IHandlesInput.cpp core/traits/IHandlesInput.h
    2d/rendering/B2DebugRenderer.cpp 2d/rendering/B2DebugRenderer.h
    )

################################################################################
# Target
################################################################################
ADD_LIBRARY(${PROJECT_NAME} SHARED ${ALL_FILES})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

USE_PROPS(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
SET(ROOT_NAMESPACE Ess3D)

################################################################################
# Output directory
################################################################################
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../build/${PROJECT_NAME}/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../build/${PROJECT_NAME}/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
    )
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )

################################################################################
# Compile and link options
################################################################################
IF (MSVC)
    ################################################################################
    # Compile definitions
    ################################################################################

    TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "WIN32;"
        "_LIB;"
        "UNICODE;"
        "_UNICODE;"
        )

    TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /Od;
        ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY};
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
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
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
        )

    TARGET_LINK_OPTIONS(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /DEBUG;
        /INCREMENTAL;
        /verbose:lib
        >
        $<$<CONFIG:Release>:
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
        >
        )
ENDIF ()

################################################################################
# Dependencies
################################################################################

IF (UNIX)
    SET(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
        "fmodL;"
        "fmodstudioL;"
        "CEGUIBase-0;"
        "CEGUIRapidXMLParser;"
        "CEGUISDL2ImageCodec;"
        "CEGUIOpenGLRenderer-0"
        ">"
        "$<$<CONFIG:Release>:"
        "fmod;"
        "fmodstudio;"
        "CEGUIBase;"
        "CEGUIRapidXMLParser;"
        "CEGUISDL2ImageCodec;"
        "CEGUIOpenGLRenderer"
        ">"
        "GLEW;"
        "GLU;"
        "GL;"
        "SDL2;"
        "SDL2main;"
        "SDL2_image;"
        "freetype;"
        "box2d;"
        "assimp"
        )
ENDIF (UNIX)
IF (MSVC)
    SET(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
        "box2d_d;"
        "CEGUIBase-0_d;"
        "CEGUIRapidXMLParser_d;"
        "CEGUISDL2ImageCodec_d;"
        "CEGUIOpenGLRenderer-0_d;"
        "fmodL_vc;"
        "fsbank_vc;"
        "fmodstudioL_vc;"
        "glew32d;"
        "SDL2_d;"
        "SDL2_image_d;"
        "assimp_d;"
        ">"
        "$<$<CONFIG:Release>:"
        "box2d;"
        "CEGUIBase-0;"
        "CEGUIRapidXMLParser;"
        "CEGUISDL2ImageCodec;"
        "CEGUIOpenGLRenderer-0;"
        "fmod_vc;"
        "fsbank_vc;"
        "fmodstudio_vc;"
        "glew32;"
        "SDL2;"
        "SDL2_image;"
        "assimp;"
        ">"
        "opengl32;"
        "SDL2main;"
        )
ENDIF (MSVC)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

IF (UNIX)
    TARGET_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/lib/unix;"
        )
ENDIF (UNIX)
IF (MSVC)
    TARGET_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/lib/${PLATFORM_ARCHITECTURE}/$<CONFIG>/;"
        )
ENDIF (MSVC)

IF (UNIX)
    SET(ADDITIONAL_INCLUDE_DIRECTORIES
        "/usr/local/include/cegui-0/;"
        )
ENDIF (UNIX)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/include/;"
    "${ADDITIONAL_INCLUDE_DIRECTORIES}"
    "${PROJECT_SOURCE_DIR}"
    )