set(CRAFT_CORE_SOURCES
    core/AssetPath.cpp
)

set(CRAFT_GRAPHICS_SOURCES
    graphics/Example3DMesh.cpp
    graphics/Shader.cpp
    graphics/StbImage.cpp
    graphics/Window.cpp
)

add_library(craft_core STATIC
    ${CRAFT_CORE_SOURCES}
    ${CRAFT_GRAPHICS_SOURCES}
    app/SceneBenchmark.cpp
)

target_include_directories(craft_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(craft_core
    PUBLIC
        glm::glm
    PRIVATE
        glfw
        FastNoise2
        stb::headers
)

target_compile_definitions(craft_core PRIVATE
    CRAFT_ASSET_DIR="${PROJECT_SOURCE_DIR}/assets"
)

if(APPLE)
    target_link_libraries(craft_core PRIVATE "-framework OpenGL")
    target_compile_definitions(craft_core PRIVATE GL_SILENCE_DEPRECATION)
else()
    # PUBLIC because the starter's main.cpp includes graphics/OpenGL.h.
    target_link_libraries(craft_core PUBLIC craft_glad_gl_core_33)
endif()

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(Craft
    main.cpp
    app/AppUi.cpp
    app/CustomUi.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(Craft PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(Craft PRIVATE
    craft_core
    glfw
)

# Keep the existing Pixi command (`build/Craft`) stable after adding src/.
set_target_properties(Craft PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

# Running from the build directory should work without source-tree paths.
add_custom_command(TARGET Craft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:Craft>/assets"
    COMMENT "Copying runtime assets"
)
