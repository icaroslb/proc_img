#ifndef FISICA_H
#define FISICA_H

#include <cmath>

#include "../algebra/algebra_vetor.h"

#include "../envoltorios/Poligono_convexo_2d.h"
#include "../envoltorios/Circulo_2d_copy.h"

namespace lito {

template <class T> bool teste_colisao ( const Vec_2<T> &p_1_1, const Vec_2<T> &p_1_2
                                      , const Vec_2<T> &p_2_1, const Vec_2<T> &p_2_2
                                      , const Vec_2<T> &normal, T &dist );
#if 0
template <class T> bool teste_colisao ( const AABB_2d<T> &aabb_1, const AABB_2d<T> &aabb_2 );
template <class T> bool teste_colisao ( const Circulo_2d<T> &circ_1, const Circulo_2d<T> &circ_2 );
template <class T> bool teste_colisao ( const AABB_2d<T> &aabb, const Circulo_2d<T> &circ );
template <class T> bool teste_colisao ( const Circulo_2d<T> &circ, const AABB_2d<T> &aabb );
template <class T> bool teste_colisao ( const AABB_2d<T> &aabb, const Vec_2<T> &pos );
template <class T> bool teste_colisao ( const Circulo_2d<T> &circ, const Vec_2<T> &pos );
#endif
template <class T> bool teste_colisao ( Poligono_convexo_2d<T> *p_1, Poligono_convexo_2d<T> *p_2 );
template <class T> bool teste_colisao ( Poligono_convexo_2d<T> *p, const Vec_2d<T> &ponto );

template <class T> Vec_2<T> colisao ( const Vec_2<T> &v, const Vec_2<T> &normal, T alfa, T beta );
template <class T> Vec_3<T> colisao ( const Vec_3<T> &v, const Vec_3<T> &normal, T alfa, T beta );
template <class T> Vec_4<T> colisao ( const Vec_4<T> &v, const Vec_4<T> &normal, T alfa, T beta );

#include "fisica.inl"

}

#endif
