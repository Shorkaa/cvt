/*
 * File:   Inserter.h
 * Author: sebi
 *
 * Created on July 13, 2011, 3:55 PM
 */

#ifndef INSERTER_H
#define	INSERTER_H

#include <cvt/vision/Feature2D.h>
#include <vector>

namespace cvt {

    template <class ContType>
    struct Inserter {

        Inserter( ContType & c ) : _c( c ) {}

        static void insertPoint( float x, float y );

      private:
        ContType & _c;

        Inserter( const Inserter & );
        Inserter & operator=( const Inserter & );
    };

    template<>
    inline void Inserter<std::vector<Feature2Df> >::insertPoint(float x, float y )
    {
        _c.push_back( Feature2Df( x, y ) );
    }

}


#endif	/* INSERTER_H */

