#include <iostream>
#include "engines/Engine_OpenGl.h"
#include "engines/Engine_SDL.h"
#include "shaders/Shader.h"
#include "camera/Camera.h"

#include "fisica/fisica.h"

struct Triangulo_ponto {
	lito::Vec_2f pos;
	lito::Vec_3f cor;

	Triangulo_ponto( lito::Vec_2f Pos, lito::Vec_3f Cor ) : pos(Pos), cor(Cor) {}
};

int main () {
    lito::Engine_SDL tela( "Testes", 500, 500 );
	lito::Engine_OpenGl opengl;
	lito::Shader shader( "../shaders/shader.vs", "../shaders/shader.fs" );
	lito::Shader shader_2( "../shaders/shader_2.vs", "../shaders/shader_2.fs" );
	
	SDL_Event evento;
	bool loop = true;

	printf( "Versão do OpenGl: %s\n", tela.obter_versao_opengl() );

	Triangulo_ponto triangulo[3] =
	{
		Triangulo_ponto{ lito::Vec_2f(-0.5f, -0.25f ), lito::Vec_3f( 1.0f, 0.0f, 0.0f ) },
		Triangulo_ponto{ lito::Vec_2f( 0.5f, -0.25f ), lito::Vec_3f( 0.0f, 1.0f, 0.0f ) },
		Triangulo_ponto{ lito::Vec_2f( 0.0f,  0.5f  ), lito::Vec_3f( 0.0f, 0.0f, 1.0f ) }
	};

	lito::Vertex_array_config config[2] =
	{
		lito::Vertex_array_config( GL_FLOAT, 2, lito::Attrib_config::FLOAT ),
		lito::Vertex_array_config( GL_FLOAT, 3, lito::Attrib_config::FLOAT )
	};

	unsigned int novaVAO;
	unsigned int novaVBO;
	unsigned int tamanho_dados = sizeof(float) * 5;
	unsigned int tamanho = tamanho_dados * 3;

	float tempo = 0;

	lito::Matriz_4f matriz_modelo;

	novaVAO = criar_vertice_buffer( triangulo, config, 2, 3 );

	lito::Vertex_array_config config_aabb[1] =
	{
		lito::Vertex_array_config( GL_FLOAT, 2, lito::Attrib_config::FLOAT ),
	};

	unsigned int EBO_config[6] = { 0, 1, 2
	                             , 2, 3, 0 };

	lito::AABB_2d<float> aabb_1( lito::Vec_2f( -0.5f, 0.0f ), 0.25f, 0.25f );
	//lito::AABB_2d<float> aabb_2( lito::Vec_2f( +0.5f, 0.0f ), 0.25f, 0.25f );
	lito::Circulo_2d<float> aabb_2( lito::Vec_2f( +0.5f, 0.0f ), 0.25f );

	unsigned int VAO_1;
	unsigned int VAO_2;
	unsigned int EBO;

	int x;
	int y;

	VAO_1 = lito::criar_vertice_buffer( aabb_1._array_val, config_aabb, 1, 4 );
	VAO_2 = lito::criar_vertice_buffer( aabb_2._array_val, config_aabb, 1, 4 );

	EBO = lito::criar_element_buffer( EBO_config, 6 );

	lito::Vec_2f pos_mouse( 0.0f, 0.0f );
	lito::Vec_2f pos_ant_mouse( 0.0f, 0.0f );
	lito::Vec_2f vec_direcao( 0.0f, 0.0f );

	while ( loop ) {

		while ( SDL_PollEvent( &evento ) ) {
			
			if ( evento.type == SDL_QUIT ) {
				loop = false;
			}
		}

		pos_ant_mouse = pos_mouse;
		SDL_GetMouseState( &x, &y );

		pos_mouse._x = -1.0f + ( 1.0f / 500.0f ) + ( ( 2.0f / 500.0f ) * (float)x );
		pos_mouse._y = +1.0f - ( 1.0f / 500.0f ) - ( ( 2.0f / 500.0f ) * (float)y );

		vec_direcao = pos_mouse - aabb_2._pos;
		aabb_2._pos += vec_direcao;
		aabb_2._quadri_envol.inf_dir += vec_direcao;
		aabb_2._quadri_envol.sup_dir += vec_direcao;
		aabb_2._quadri_envol.sup_esq += vec_direcao;
		aabb_2._quadri_envol.inf_esq += vec_direcao;

		lito::atualizar_vertice_buffer( VAO_2, aabb_2._array_val, 0, sizeof(float), 8 );


		matriz_modelo = lito::rotacionar( lito::Ori_transf::xy, tempo );
		tempo += 0.01f;

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		#if 0
		glBindVertexArray( novaVAO );
		shader.usar();

		mudarMatriz4( shader, "matriz_modelo", matriz_modelo._val );

		glDrawArrays( GL_TRIANGLES, 0, 3 );
		#else
		shader_2.usar();

		if ( lito::teste_colisao( aabb_1, aabb_2 ) )
			mudarVec3_fv( shader_2, "cor", lito::Vec_3f( 1.0f, 0.0f, 0.0f ).coord );
		else
			mudarVec3_fv( shader_2, "cor", lito::Vec_3f( 0.0f, 1.0f, 0.0f ).coord );

		glBindVertexArray( VAO_1 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0 );
		
		glBindVertexArray( VAO_2 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0 );
		#endif

		tela.swap_tela();
	}
    
    return 0;
}