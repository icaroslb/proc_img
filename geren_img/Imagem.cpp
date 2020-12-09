#include "Imagem.h"

lito::Vec_3f& Imagem::operator () ( int x, int y )
{
    return data_rgb[ ( x * larg ) + y ];
}
/*==================================================*/
Imagem& Imagem::tornar_cinza ()
{
    if ( canal == lito::Canais::CINZA )
        return *this;
    canal = lito::Canais::CINZA;

    float *novo_data_cinza = new float [tamanho];

    for ( int i = 0; i < tamanho; i++ )
            novo_data_cinza[i] = ( 0.298936f * data_rgb[i]._x )
                               + ( 0.587043f * data_rgb[i]._y )
                               + ( 0.114021f * data_rgb[i]._z );
    
    delete [] data_rgb;

    data_c = novo_data_cinza;

    return *this;
}
/*==================================================*/
Imagem& Imagem::tornar_rgb ()
{
    if ( canal == lito::Canais::RGB )
        return *this;
    canal = lito::Canais::RGB;

    lito::Vec_3f *novo_data_rgb = new lito::Vec_3f [tamanho];

    for ( int i = 0; i < tamanho; i++ )
            novo_data_rgb[i] = data_c[i];
    
    delete [] data_c;

    data_rgb = novo_data_rgb;

    return *this;
}
/*==================================================*/
Imagem Imagem::operator + ( const Imagem &img ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] + img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] + img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem Imagem::operator - ( const Imagem &img ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] - img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] - img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem Imagem::operator * ( const Imagem &img ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] * img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] * img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem& Imagem::operator = ( const Imagem &img )
{
    if ( data_c != nullptr )
        delete [] data_c;
    
    if ( img.canal == lito::Canais::RGB ) {
        if ( canal != lito::Canais::RGB )
            canal = lito::Canais::RGB;

        data_rgb = new lito::Vec_3f[tamanho];
        memcpy( (void*)data_rgb, img.data_rgb, sizeof(lito::Vec_3f) * img.tamanho );
    } else {
        if ( canal != lito::Canais::CINZA )
            canal = lito::Canais::CINZA;

        data_c = new float[tamanho];
        memcpy( data_c, img.data_c, sizeof(float) * img.tamanho );
    }
    
    return *this;
}
/*==================================================*/
Imagem& Imagem::operator += ( const Imagem &img )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] += img.data_rgb[i];
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] += img.data_c[i];
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator -= ( const Imagem &img )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] -= img.data_rgb[i];
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] -= img.data_c[i];
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator *= ( const Imagem &img )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] *= img.data_rgb[i];
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] *= img.data_c[i];
    }

    return *this;
}
/*==================================================*/
Imagem Imagem::operator + ( float c ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] + c;
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] + c;
    }

    return resul;
}
/*==================================================*/
Imagem Imagem::operator - ( float c ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] - c;
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] - c;
    }

    return resul;
}
/*==================================================*/
Imagem Imagem::operator * ( float c ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] * c;
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] * c;
    }

    return resul;
}
/*==================================================*/
Imagem Imagem::operator / ( float c ) const
{
    Imagem resul( larg, alt );

    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = data_rgb[i] / c;
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = data_c[i] / c;
    }

    return resul;
}
/*==================================================*/
Imagem& Imagem::operator = ( float c )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] = c;
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] = c;
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator += ( float c )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] += c;
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] += c;
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator -= ( float c )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] -= c;
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] -= c;
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator *= ( float c )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] *= c;
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] *= c;
    }

    return *this;
}
/*==================================================*/
Imagem& Imagem::operator /= ( float c )
{
    if ( canal == lito::Canais::RGB ) {
        for ( int i = 0; i < tamanho; i++ )
            data_rgb[i] /= c;
    } else {
        for ( int i = 0; i < tamanho; i++ )
            data_c[i] /= c;
    }

    return *this;
}
/*==================================================*/
Imagem operator + ( float c , const Imagem &img )
{
    Imagem resul( img.larg, img.alt );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = c + img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = c + img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem operator - ( float c , const Imagem &img )
{
    Imagem resul( img.larg, img.alt );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = c - img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = c - img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem operator * ( float c , const Imagem &img )
{
    Imagem resul( img.larg, img.alt );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = c * img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = c * img.data_c[i];
    }

    return resul;
}
/*==================================================*/
Imagem log ( const Imagem &img )
{
    Imagem resul( img.larg, img.alt );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = log( img.data_rgb[i] );
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = log( img.data_c[i] );
    }


    return resul;
}
/*==================================================*/
Imagem pow ( const Imagem &img, float c )
{
    Imagem resul( img.larg, img.alt );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = pow( img.data_rgb[i], c );
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = pow( img.data_c[i], c );
    }


    return resul;
}
/*==================================================*/
Imagem negativo ( const Imagem &img ) {
    Imagem resul( img );

    if ( img.canal == lito::Canais::RGB ) {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_rgb[i] = lito::Vec_3f( 1.0f, 1.0f, 1.0f ) - img.data_rgb[i];
    } else {
        for ( int i = 0; i < resul.tamanho; i++ )
            resul.data_c[i] = 1.0f - img.data_c[i];
    }

    return resul;
}