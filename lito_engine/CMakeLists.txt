cmake_minimum_required( VERSION 2.8 )
project( Testes )

find_package( SDL2 REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

include_directories( ${SDL2_INCLUDE_DIRS} ${OPENGL_gl_DIRS} ${GLEW_INCLUDE_DIRS} )

file( GLOB SOURCES teste_fisica.cpp
                   envoltorios/AABB_2d.h envoltorios/Circulo_2d.h envoltorios/Envoltorio_2d.h
                   camera/Camera.h camera/Camera.inl
                   engines/Engine_OpenGl.h engines/Engine_OpenGl.cpp
                   engines/Engine_SDL.h    engines/Engine_SDL.cpp
                   shaders/Shader.h shaders/Shader.cpp
                   fisica/fisica.h fisica/fisica.inl
                   "algebra/*" )

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE  ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )
