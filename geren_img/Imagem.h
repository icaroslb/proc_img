#ifndef IMAGEM_H
#define IMAGEM_H

#include "../lito_engine/algebra/Vec_4.h"
#include "../lito_engine/engines/Engine_OpenGl.h"
#include "../lito_engine/io/Leitor_imagem.h"

enum class Img{ BRANCO, PRETO, TRANSPARENTE, COR };

class Imagem {
public:
    union {
        lito::Vec_3f *data_rgb;
        float *data_c;
    };

    int larg;
    int alt;
    int tamanho;

    lito::Canais canal;

    Imagem ( int larg, int alt, Img tipo = Img::BRANCO, lito::Vec_3f cor = lito::Vec_3f(1.0f, 1.0f, 1.0f) )
    : larg( larg )
    , alt( alt )
    , tamanho( larg * alt )
    , canal( lito::Canais::RGB )
    {
        switch ( tipo )
        {
        case Img::BRANCO:
            data_rgb = new lito::Vec_3f[tamanho]{ lito::Vec_3f( 1.0f, 1.0f, 1.0f ) };
        break;
        case Img::PRETO:
            data_rgb = new lito::Vec_3f[tamanho]{ lito::Vec_3f( 0.0f, 0.0f, 0.0f ) };
        break;
        case Img::COR:
            data_rgb = new lito::Vec_3f[tamanho]{ cor };
        break;
        case Img::TRANSPARENTE:
            data_rgb = new lito::Vec_3f[tamanho]{ lito::Vec_3f( 0.0f, 0.0f, 0.0f ) };
        break;
        default: break;
        }
    }

    Imagem ( std::string caminho )
    {
        int num_canais;
        canal = lito::Canais::RGB;
        data_c = lito::carregar_imagem( caminho, larg, alt, num_canais, canal );
        tamanho = larg * alt;
    }

    Imagem ( const Imagem &img )
    {
        data_c = nullptr;
        canal = img.canal;
        larg = img.larg;
        alt = img.alt;
        tamanho = img.tamanho;

        *this = img;
    }

    lito::Vec_3f& operator () ( int x, int y );

    Imagem& tornar_cinza ();
    Imagem& tornar_rgb ();

    Imagem operator + ( const Imagem &img ) const;
    Imagem operator - ( const Imagem &img ) const;
    Imagem operator * ( const Imagem &img ) const;

    Imagem& operator = ( const Imagem &img );
    Imagem& operator += ( const Imagem &img );
    Imagem& operator -= ( const Imagem &img );
    Imagem& operator *= ( const Imagem &img );

    Imagem operator + ( float c ) const;
    Imagem operator - ( float c ) const;
    Imagem operator * ( float c ) const;
    Imagem operator / ( float c ) const;

    Imagem& operator = ( float c );
    Imagem& operator += ( float c );
    Imagem& operator -= ( float c );
    Imagem& operator *= ( float c );
    Imagem& operator /= ( float c );

    ~Imagem()
    {
            delete [] data_c;
    }
};

Imagem operator + ( float c , const Imagem &img );
Imagem operator - ( float c , const Imagem &img );
Imagem operator * ( float c , const Imagem &img );

Imagem log ( const Imagem &img );
Imagem pow ( const Imagem &img, float c );

Imagem negativo ( const Imagem &img );

#endif