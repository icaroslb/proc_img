OBJ = obj/
IMGUI_DIR = imgui/

IMGUI_SOURCES  = $(IMGUI_DIR)imgui.cpp $(IMGUI_DIR)imgui_demo.cpp $(IMGUI_DIR)imgui_draw.cpp $(IMGUI_DIR)imgui_widgets.cpp
IMGUI_SOURCES += $(IMGUI_DIR)backends/imgui_impl_sdl.cpp $(IMGUI_DIR)backends/imgui_impl_opengl3.cpp
IMGUI_OBJS     = $(addprefix obj/, $(addsuffix .o, $(basename $(notdir $(IMGUI_SOURCES)))))

LITO_SOURCES  = lito_engine/engines/Engine_OpenGl.cpp lito_engine/engines/Engine_OpenGl.h
LITO_SOURCES += lito_engine/engines/Engine_SDL.cpp lito_engine/engines/Engine_SDL.h
LITO_SOURCES += lito_engine/shaders/Shader.cpp lito_engine/shaders/Shader.h
LITO_SOURCES += lito_engine/io/Leitor_imagem.cpp lito_engine/io/Leitor_imagem.h
LITO_OBJS     = $(addprefix obj/, $(addsuffix .o, $(basename $(notdir $(LITO_SOURCES)))))

IMG_SOURCES  = geren_img/Imagem.cpp geren_img/Imagem.h
IMG_SOURCES += geren_img/Camada.cpp geren_img/Camada.h
IMG_OBJS     = $(addprefix obj/, $(addsuffix .o, $(basename $(notdir $(IMG_SOURCES)))))

ALGEBRA = $(wildcard lito_engine/algebra/*.h)

LIBS = -lGL -ldl -lGLEW `sdl2-config --libs`
FLAGS = -O3 -g -Wall -Wformat `sdl2-config --cflags`
IMGUI_FLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)backends/
VERSION = --std=c++11
MAIN = main

CXX = g++

all: $(OBJ) $(MAIN)

$(OBJ):
	if test ! -d $(OBJ); then mkdir $(OBJ); fi

$(OBJ)%.o: $(IMGUI_DIR)%.cpp
	$(CXX) -g -c -o $@ $< $(FLAGS) $(IMGUI_FLAGS)

$(OBJ)%.o: $(IMGUI_DIR)backends/%.cpp
	$(CXX) -g -c -o $@ $< $(FLAGS) $(IMGUI_FLAGS)

$(OBJ)%.o: lito_engine/engines/%.cpp lito_engine/engines/%.h
	$(CXX) -g -c -o $@ $< $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(OBJ)Shader.o: lito_engine/shaders/Shader.cpp lito_engine/shaders/Shader.h
	$(CXX) -g -c -o $@ $< $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(OBJ)Leitor_imagem.o: lito_engine/io/Leitor_imagem.cpp lito_engine/io/Leitor_imagem.h
	$(CXX) -g -c -o $@ $< $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(OBJ)%.o: geren_img/%.cpp geren_img/%.h
	$(CXX) -g -c -o $@ $< $(INCLUDES) $(FLAGS) $(VERSION) $(LIBS)

$(MAIN): $(IMGUI_OBJS) $(LITO_OBJS) $(IMG_OBJS) $(MAIN).cpp
	$(CXX) $^ -o $@ $(INCLUDES) $(FLAGS) $(IMGUI_FLAGS) $(VERSION) $(LIBS)

clean:
	rm -r $(MAIN) $(OBJ)*.o

