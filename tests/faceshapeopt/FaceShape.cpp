#include "FaceShape.h"
#include <cvt/util/Exception.h>

namespace cvt {
	FaceShape::FaceShape() : _ptsize( 0 ), _pcsize( 0 ), _lsize( 0 ),  _lines( NULL )
	{
		_transform.identity();
	}

	FaceShape::~FaceShape()
	{
		if( _lines )
			delete[] _lines;
	}

	void FaceShape::drawMean( GFX* g, const Matrix3f& transform )
	{
		Vector2f pts[ 2 ];
		size_t i1, i2;

		g->color().set( 1.0f, 1.0f, 1.0f, 1.0f );
		for( size_t i = 0; i < _lsize; i++ ) {
			i1 = _lines[ i * 2 ];
			i2 = _lines[ i * 2 + 1 ];
			pts[ 0 ].x = _mean[ i1 * 2 ];
			pts[ 0 ].y = _mean[ i1 * 2 + 1 ];
			pts[ 1 ].x = _mean[ i2 * 2 ];
			pts[ 1 ].y = _mean[ i2 * 2 + 1 ];
			pts[ 0 ] = transform * pts[ 0 ];
			pts[ 1 ] = transform * pts[ 1 ];
			g->drawLines( pts, 1 );
		}
	}

	void FaceShape::drawCurrent( GFX* g )
	{
		Vector2f pts[ 2 ];
		size_t i1, i2;

		g->color().set( 1.0f, 1.0f, 1.0f, 1.0f );
		for( size_t i = 0; i < _lsize; i++ ) {
			i1 = _lines[ i * 2 ];
			i2 = _lines[ i * 2 + 1 ];
			pts[ 0 ].x = _pts[ i1 * 2 ];
			pts[ 0 ].y = _pts[ i1 * 2 + 1 ];
			pts[ 1 ].x = _pts[ i2 * 2 ];
			pts[ 1 ].y = _pts[ i2 * 2 + 1 ];
			g->drawLines( pts, 1 );
		}
	}


	void FaceShape::load( const char* path )
	{
		FILE* f;
		f = fopen( path, "rb" );
		if( !f )
			throw CVTException( "Could not open file!" );
		uint32_t tmp;
		fread( &tmp, sizeof( uint32_t ), 1, f );
		_ptsize = tmp;
		fread( &tmp, sizeof( uint32_t ), 1, f );
		_pcsize = tmp;

		_mean = Eigen::VectorXf::Zero( _ptsize * 2 );
		_pc = Eigen::MatrixXf::Zero( _ptsize * 2, _pcsize );
		_p = Eigen::VectorXf::Zero( _pcsize );
		_pts = Eigen::VectorXf::Zero( _ptsize * 2 );

		for( size_t i = 0; i < _ptsize * 2; i++ )
			fread( &_mean( i ), sizeof( float ), 1, f );

		for( size_t c = 0; c < _pcsize; c++ ) {
			for( size_t i = 0; i < _ptsize * 2; i++ )
				fread( &_pc( i, c ), sizeof( float ), 1, f );
		}
		fread( &tmp, sizeof( uint32_t ), 1, f );
		_lsize = tmp;
		_lines = new uint32_t[ _lsize * 2 ];
		for( size_t i = 0; i < _lsize * 2; i++ )
			fread( &_lines[ i ], sizeof( uint32_t ), 1, f );
		fclose( f );
		updateCurrent();
	}


	void FaceShape::updateCurrent()
	{
		Vector2f pt;
		_pts = _mean + _pc * _p;
		for( size_t i = 0; i < _ptsize; i++ ) {
			pt.x = _pts[ i * 2 ];
			pt.y = _pts[ i * 2 + 1 ];
			pt = _transform * pt;
			_pts[ i * 2 ] = pt.x;
			_pts[ i * 2 + 1 ] = pt.y;
		}
	}
}
