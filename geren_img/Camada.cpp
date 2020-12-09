#include "Camada.h"

void Camada::iniciar ()
{
    glGenTextures( 1, &id_img );
    glBindTexture( GL_TEXTURE_2D, id_img );
	
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if ( img.canal == lito::Canais::RGB )
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, img.larg, img.alt, 0, GL_RGB, GL_FLOAT, img.data_rgb );
    else
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, img.larg, img.alt, 0, GL_LUMINANCE, GL_FLOAT, img.data_c );
    glGenerateMipmap( GL_TEXTURE_2D );

    float altura_img = ( (float)img.alt / (float)img.larg );
    float alt_vert = altura_img / 2.0f;

    float vertices_img[] = { -1.0f, -altura_img, 0.0f, 0.0f,
	                          1.0f, -altura_img, 1.0f, 0.0f,
	                          1.0f,  altura_img, 1.0f, 1.0f,
	                         -1.0f,  altura_img, 0.0f, 1.0f };
    unsigned int indices_img[] = { 0, 1, 3,
	                               1, 2, 3 };
    int divisoes_img[] = { 2, 2 };

    lito::Vertex_array_config config[2] =
	{
		lito::Vertex_array_config( GL_FLOAT, 2, lito::Attrib_config::FLOAT ),
		lito::Vertex_array_config( GL_FLOAT, 2, lito::Attrib_config::FLOAT )
	};

    VAO = lito::criar_vertice_buffer( vertices_img, config, 2, 4 );
	EBO = lito::criar_element_buffer( indices_img, 6 );
}
/*==================================================*/
//Camada& Camada::redimensionar ( unsigned int nova_larg, unsigned int nova_alt )
//{
//    lito::Vec_4d *aux_data = new lito::Vec_4d[nova_larg*nova_alt]{ lito::Vec_4d( 0.0, 0.0, 0.0, 0.0 ) };
//    unsigned int larg_dif;
//    unsigned int alt_dif;
//
//    if ( nova_larg < larg )
//        larg_dif = nova_larg;
//    else
//        larg_dif = larg;
//
//    if ( nova_alt < alt )
//        alt_dif = nova_alt;
//    else
//        alt_dif = alt;
//
//
//    for ( int i = 0; i < alt_dif; i++ ) {
//        memcpy( &(aux_data[i*nova_larg]), &((*this)( i, 0 )), sizeof(lito::Vec_4d) * larg_dif );
//    }
//
//    delete [] data;
//
//    data = aux_data;
//}
/*==================================================*/
void Camada::atualizar ()
{
    glBindTexture( GL_TEXTURE_2D, id_img );

    if ( img.canal == lito::Canais::RGB )
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, img.larg, img.alt, GL_RGB, GL_FLOAT, img.data_rgb );
    else
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, img.larg, img.alt, GL_LUMINANCE, GL_FLOAT, img.data_c );
}
/*==================================================*/
void Camada::renderizar ()
{
    glBindVertexArray( VAO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	
    glBindTexture( GL_TEXTURE_2D, id_img );

    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, 6 );
}
/*==================================================*/
Camada& Camada::operator = ( const Camada &camada )
{
    img = camada.img;

    return *this;
}
/*==================================================*/
Camada& Camada::operator = ( const Imagem &imagem )
{
    img = imagem;

    return *this;
}
/*==================================================*/