################################################################################
# Source groups
################################################################################

SET(HEADER_LIST
    ../include/Ess3D/2d/animations/Animation.h
    ../include/Ess3D/2d/animations/AnimationManager.h
    ../include/Ess3D/2d/camera/Camera2D.h
    ../include/Ess3D/2d/models/Object2D.h
    ../include/Ess3D/2d/models/Vertex2D.h
    ../include/Ess3D/2d/rendering/SpriteBatch.h
    ../include/Ess3D/2d/utils/Utils2D.h

    ../include/Ess3D/3d/camera/Camera3D.h
    ../include/Ess3D/3d/model/Mesh.h
    ../include/Ess3D/3d/model/Model.h
    ../include/Ess3D/3d/model/Vertex3D.h
    ../include/Ess3D/3d/rendering/MeshRenderer.h

    ../include/Ess3D/audio/AudioManager.h

    ../include/Ess3D/core/IGame.h
    ../include/Ess3D/core/IGameScreen.h
    ../include/Ess3D/core/ScreenManager.h

    ../include/Ess3D/errors/RuntimeException.h

    ../include/Ess3D/gl/ColorRGBA8.h
    ../include/Ess3D/gl/FBORenderer.h
    ../include/Ess3D/gl/FrameBufferObject.h
    ../include/Ess3D/gl/Shader.h
    ../include/Ess3D/gl/Window.h
    ../include/Ess3D/gl/UV.h

    ../include/Ess3D/gui/GUI.h

    ../include/Ess3D/input/InputManager.h

    ../include/Ess3D/resources/ModelCache.h
    ../include/Ess3D/resources/Texture.h
    ../include/Ess3D/resources/TextureAtlas.h
    ../include/Ess3D/resources/TextureAtlasSection.h
    ../include/Ess3D/resources/TextureCache.h

    ../include/Ess3D/utils/Timing.h
    ../include/Ess3D/utils/Utils.h
    ../include/Ess3D/2d/traits/IRenderable2D.h
    ../include/Ess3D/2d/rendering/Renderer2D.h
    ../include/Ess3D/2d/Scene2D.h
    ../include/Ess3D/core/State.h
    ../include/Ess3D/core/State.h
    ../include/Ess3D/core/traits/IUpdatable.h
    ../include/Ess3D/core/traits/IInterpolatable.h
    ../include/Ess3D/core/traits/IHandlesInput.h
    ../include/Ess3D/2d/rendering/B2DebugRenderer.h

    ../include/Ess3D/2d/models/Entity2D.h
    ../include/Ess3D/core/SceneGraph.h
    ../include/Ess3D/data/QuadTree.h
    ../include/Ess3D/2d/rendering/QuadTreeRenderer.h)

SOURCE_GROUP(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

SET(SOURCE_LIST
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

    2d/traits/IRenderable2D.cpp
    2d/rendering/Renderer2D.cpp
    2d/Scene2D.cpp
    core/State.cpp
    core/Config.cpp
    core/traits/IUpdatable.cpp
    core/traits/IInterpolatable.cpp
    core/traits/IHandlesInput.cpp
    2d/rendering/B2DebugRenderer.cpp
    2d/models/Entity2D.cpp
    data/QuadTree.cpp
    core/SceneGraph.cpp
    2d/rendering/QuadTreeRenderer.cpp)

################################################################################
# Target
################################################################################
ADD_LIBRARY(${PROJECT_NAME} SHARED ${HEADER_LIST} ${SOURCE_LIST})

SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

USE_PROPS(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
SET(ROOT_NAMESPACE Ess3D)

################################################################################
# Output directory
################################################################################
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../build/${PLATFORM_ARCHITECTURE}/$<CONFIG>/"
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
        "CEGUIBase-0;"
        "CEGUIRapidXMLParser;"
        "CEGUISDL2ImageCodec;"
        "CEGUIOpenGLRenderer-0;"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/unix;"
        "/usr/local/lib/cegui-0.8/;" #not too elegant, use Find modules in the future
        )
ENDIF (UNIX)
IF (MSVC)
    TARGET_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/lib/${PLATFORM_ARCHITECTURE}/$<CONFIG>/;"
        )
ENDIF (MSVC)

IF (UNIX)
    SET(ADDITIONAL_INCLUDE_DIRECTORIES
        "/usr/local/include/cegui-0/;"
        )
ENDIF (UNIX)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/include/;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/;"
    "${ADDITIONAL_INCLUDE_DIRECTORIES}"
    )
