#ifndef CAMADA_H
#define CAMADA_H

#include "Imagem.h"
#include <cstring>

enum class tipo_fundo { COM, SEM };

class Camada {
public:
    Imagem img;
    unsigned int id_img;

    unsigned int VAO;
    unsigned int EBO;

    Camada ( unsigned int larg, unsigned int alt, Img tipo = Img::BRANCO, lito::Vec_3f cor = lito::Vec_3f(1.0f, 1.0f, 1.0f)  )
    : img( larg, alt, tipo, cor )
    {
        iniciar();
    }

    Camada ( std::string caminho )
    : img( caminho )
    {
        iniciar();
    }

    Camada( const Imagem &n_img )
    : img( n_img )
    {
        iniciar();
    }

    void iniciar ();
    void atualizar ();
    void renderizar ();

    Camada& operator = ( const Camada &camada );
    Camada& operator = ( const Imagem &camada );

    //Camada& redimensionar ( unsigned int nova_larg, unsigned int nova_alt );
};

#endif