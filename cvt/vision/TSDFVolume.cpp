#include <cvt/vision/TSDFVolume.h>
#include <cvt/cl/kernel/TSDFVolume/TSDFVolume.h>

namespace cvt
{

	TSDFVolume::TSDFVolume( const Matrix4f& gridtoworld, size_t width, size_t height, size_t depth, float truncation ) :
		_width( width ),
		_height( height ),
		_depth( depth ),
		_trunc( truncation ),
		_g2w( gridtoworld ),
		_clvolume( sizeof( cl_float2 ) * width * height * depth ),
		_clproj( sizeof( float ) * 12 ),
		_clvolclear( _TSDFVolume_source, "TSDFVolume_clear" ),
		_clvoladd( _TSDFVolume_source, "TSDFVolume_add" )
	{

	}

	void TSDFVolume::clear( float weight )
	{
		/* clear the volume */
		_clvolclear.setArg( 0, _clvolume );
		_clvolclear.setArg( 1, ( int ) _width);
		_clvolclear.setArg( 2, ( int ) _height );
		_clvolclear.setArg( 3, ( int ) _depth);
		_clvolclear.setArg( 4, weight );
		// FIXME: maybe 8 x 8 x ? for the local range is better
		_clvolclear.run( CLNDRange( Math::pad16( _width ), Math::pad16( _height ), _depth ), CLNDRange( 16, 16, 1 ) );
	}


	void TSDFVolume::addDepthMap( const Matrix4f& proj, const Image& depthmap, float scale )
	{
		// update projection matrix
		Matrix4f projall = proj * _g2w;
		_clproj.write( ( void* ) projall.ptr() );

		// add depthmap
		_clvoladd.setArg( 0, _clvolume );
		_clvoladd.setArg( 1, ( int ) _width );
		_clvoladd.setArg( 2, ( int ) _height );
		_clvoladd.setArg( 3, ( int ) _depth );
		_clvoladd.setArg( 4, depthmap );
		_clvoladd.setArg( 5, scale );
		_clvoladd.setArg( 6, _clproj );
		_clvoladd.setArg( 7, _trunc );
		_clvoladd.run( CLNDRange( Math::pad16( _width ), Math::pad16( _height ), _depth ), CLNDRange( 16, 16, 1 ) );
	}

	void TSDFVolume::addDepthMap( const Matrix3f& intrinsics, const Matrix4f& extrinsics, const Image& depthmap, float scale )
	{
		Matrix4f proj = intrinsics.toMatrix4();
		proj *= extrinsics;
		addDepthMap( proj, depthmap, scale );
	}


	void TSDFVolume::saveRaw( const String& path ) const
	{
		float* ptr = ( float* ) _clvolume.map();
		float* origptr = ptr;
		size_t n = _width * _height * _depth;

		FILE* f;
		f = fopen( path.c_str(),"wb");
		while( n-- ) {
			fwrite( ptr, sizeof( float ), 1, f );
			ptr += 2;
		}
		fclose( f );

		_clvolume.unmap( origptr );
	}
}
