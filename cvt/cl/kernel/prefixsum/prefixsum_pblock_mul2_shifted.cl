__kernel void prefixsum_pblock_mul2_shifted( __write_only image2d_t out,  __read_only image2d_t in1, __read_only image2d_t in2, const float2 shift, __local float4* buf )
{
    const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_LINEAR;
	const int lx = get_local_id( 0 );
	const int ly = get_local_id( 1 );
    const int lw = get_local_size( 0 );
//    const int lh = get_local_size( 1 );
	const int width = get_image_width( out );
	const int height = get_image_height( out );
	int2 coord = { get_global_id( 0 ), get_global_id( 1 ) };
	float2 coordf = { get_global_id( 0 ), get_global_id( 1 ) };
	int lid = mul24( lw, ly ) + lx;
	float4 tmp;


	tmp  = read_imagef( in1, sampler, coord );
	tmp *= read_imagef( in2, sampler, coordf + shift );
	buf[ lid ] = tmp;

	// assume lw == lh
	for( int offset = 1; offset < lw; offset <<= 1 )
	{
		barrier( CLK_LOCAL_MEM_FENCE );
		if( lx >= offset )
			tmp += buf[ lid - offset ];
		barrier( CLK_LOCAL_MEM_FENCE );
		buf[ lid ] = tmp;

		barrier( CLK_LOCAL_MEM_FENCE );
		if( ly >= offset )
			tmp += buf[ lid - mul24( lw, offset ) ];
		barrier( CLK_LOCAL_MEM_FENCE );
		buf[ lid ] = tmp;
	}

	if( coord.x < width && coord.y < height )
		write_imagef( out, coord, tmp );
}
