cmake_minimum_required( VERSION 2.8 )
project( main )

find_package( SDL2 REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

include_directories( ${SDL2_INCLUDE_DIRS} ${OPENGL_gl_DIRS} ${GLEW_INCLUDE_DIRS} imgui/ imgui/backends/ )

file( GLOB SOURCES main.cpp
                   imgui/*.cpp imgui/*.h
                   imgui/backends/imgui_impl_sdl.cpp imgui/backends/imgui_impl_sdl.h
                   imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_opengl3.h
                   lito_engine/algebra/*.inl lito_engine/algebra/*.h
                   lito_engine/engines/*.cpp lito_engine/engines/*.h
                   lito_engine/io/*.cpp lito_engine/io/*.h
                   lito_engine/shaders/*.cpp lito_engine/shaders/*.h
                   geren_img/*.cpp geren_img/*.h )

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE  ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )
