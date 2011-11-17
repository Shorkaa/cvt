#include <cvt/gfx/ifilter/BoxFilter.h>

#include <cvt/cl/kernel/prefixsum/prefixsum_boxfilter.h>

namespace cvt {
	static ParamInfoTyped<Image*> pin( "Input", true );
	static ParamInfoTyped<Image*> pout( "Output", false );
	static ParamInfoTyped<int>	  pradius( "Radius", false );

	static ParamInfo * _params[ 3 ] = {
		&pin,
		&pout,
		&pradius
	};

	BoxFilter::BoxFilter() :
		IFilter( "BoxFilter", _params, 3, IFILTER_CPU | IFILTER_OPENCL ),
		_clprefixsum_boxfilter( _prefixsum_boxfilter_source, "prefixsum_boxfilter" )
	{
	}

	void BoxFilter::apply( Image& dst, const Image& src, const int radius ) const
	{
		// FIXME: hardcoded work-group size
		_clprefixsum_boxfilter.setArg( 0, dst );
		_clprefixsum_boxfilter.setArg( 1, src );
		_clprefixsum_boxfilter.setArg( 2, radius );
		_clprefixsum_boxfilter.run( CLNDRange( Math::pad( src.width(), 32 ), Math::pad( src.height(), 32 ) ), CLNDRange( 32, 32 ) );
	}

	void BoxFilter::apply( const ParamSet* set, IFilterType t ) const
	{
		Image * in = set->arg<Image*>( 0 );
		Image * out = set->arg<Image*>( 2 );
		int radius = set->arg<int>( 3 );


		switch ( t ) {
			case IFILTER_OPENCL:
				this->apply( *out, *in, radius );
				break;
			default:
				throw CVTException( "Not implemented" );
		}
	}

}