#include <iostream>
#include "lito_engine/engines/Engine_OpenGl.h"
#include "lito_engine/engines/Engine_SDL.h"
#include "lito_engine/shaders/Shader.h"

#include "lito_engine/algebra/include_algebra.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "geren_img/Camada.h"

void correcao_gamma ( Camada &camada, Camada &camada_aux, bool &preview, bool &ativado );

int main () {
    lito::Engine_SDL tela( "Processamento_imagem", 680, 680 );
	lito::Engine_OpenGl opengl;
	lito::Shader shader( "shader.vs", "shader.fs" );

    SDL_Event evento;
	bool loop = true;
	
	bool preview = false;

    printf( "Versão do OpenGl: %s\n", tela.obter_versao_opengl() );

	Camada camada_1( "Pinguim_1.jpg" );
	Camada camada_2( camada_1.img );

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL( tela.window, tela.contextoGL );
	ImGui_ImplOpenGL3_Init( "#version 130" );

	bool menu_imagem = false;
	bool menu_imagem_gamma = false;

	while ( loop ) {
		while ( SDL_PollEvent( &evento ) ) {
			
			ImGui_ImplSDL2_ProcessEvent( &evento );
			switch ( evento.type ) {
				case SDL_QUIT:
					loop = false;
				break;
				default: break;
			}
		}
		glViewport( ( (int)io.DisplaySize.x / 2 ) - ( (int)io.DisplaySize.y / 2 ), 0, (int)io.DisplaySize.y, (int)io.DisplaySize.y );

		glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		shader.usar();
		
		if ( !preview )
			camada_1.renderizar();
		else
			camada_2.renderizar();

		// Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame( tela.window );
        ImGui::NewFrame();

		ImGui::BeginMainMenuBar();
			if ( ImGui::BeginMenu( "Imagem", &menu_imagem ) ) {
				if ( ImGui::MenuItem( "Correção de gamma", nullptr, &menu_imagem_gamma ) )
					preview = true;

				if ( ImGui::MenuItem( "Negativo" ) ) {
					camada_1 = negativo( camada_1.img );
					camada_1.atualizar();
				}

				if ( ImGui::MenuItem( "Tons de cinza" ) ) {
					camada_2 = ( camada_1.img.tornar_cinza() );
					camada_1.atualizar();
					camada_2.atualizar();
				}

				if ( ImGui::MenuItem( "RGB" ) ) {
					camada_2 = ( camada_1.img.tornar_rgb() );
					camada_1.atualizar();
					camada_2.atualizar();
				}

				ImGui::EndMenu();
			}

		ImGui::EndMainMenuBar();

		if ( menu_imagem_gamma )
			correcao_gamma( camada_1, camada_2, preview, menu_imagem_gamma );
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		tela.swap_tela();
	}

	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void correcao_gamma ( Camada &camada, Camada &camada_aux, bool &preview, bool &ativado )
{
	static float val_gamma = 1.0f;
	static bool loop_inicial = true;
	auto preview_func = [ &camada, &camada_aux ] ( float val_gamma )
	{
		camada_aux = pow( camada.img, val_gamma );
		camada_aux.atualizar();
	};

	if ( !ImGui::Begin( "Correção Gamma", &ativado ) ) {
		ImGui::End();
		return;
	}

	if ( loop_inicial || ImGui::SliderFloat( "Gamma", &val_gamma, 0.1f, 2.9f, "ratio = %.3f" ) ) {
		preview_func( val_gamma );
		loop_inicial = false;
	}

	if ( ImGui::Button("Restaurar") ) {
		val_gamma = 1.0f;
		preview_func( val_gamma );
	}

	ImGui::SameLine();

	if ( ImGui::Button( "Aplicar" ) ) {
		camada = camada_aux;
		camada.atualizar();
		ativado = false;
	}

	ImGui::End();

	if ( !ativado ) {
		preview = false;
		loop_inicial = true;
	}
}