/*void async_work_group_image_copy( __local float4* buf, __read_only image2d_t input, const sampler_t sampler, int4 xywh )
{
	const int lx = get_local_id( 0 );
	const int ly = get_local_id( 1 );
	const int lw = get_local_size( 0 );
	const int lh = get_local_size( 1 );
	const int width = get_image_width( input );
	const int height = get_image_height( input );

	int offsety = xywh.z * ly; // y-offset to buf for this work-item
	int incy = xywh.z * lh; // x-offset to buf for this work item

	for( int y = ly; y < xywh.w; y += lh ) {
		for( int x = lx, offsetx = lx; x < xywh.z; x += lw, offsetx += lw ) {
			buf[ offsety + offsetx ] = read_imagef( input, sampler, xywh.xy + ( int2 ) ( x, y ) );
		}
		offsety += incy;
	}
}*/


__kernel void boxfilter( __write_only image2d_t out,  __read_only image2d_t in, const int r, __local float4* buf )
{
	const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;
	const int width = get_image_width( out );
	const int height = get_image_height( out );
	const int lx = get_local_id( 0 );
    const int ly = get_local_id( 1 );
    const int lw = get_local_size( 0 );
    const int lh = get_local_size( 1 );
	const int r2 = r * 2;
    const int bstride = lw + r2;
	const int2 base = ( int2 )( get_group_id( 0 ) * lw - r, get_group_id( 1 ) * lh - r );
	int2 coord, mincoord, maxcoord;
	float size;
	float4 value;

	for( int y = ly; y < lh + r2; y += lh ) {
		for( int x = lx; x < lw + r2; x += lw ) {
			buf[ mul24( y, bstride ) + x ] = read_imagef( in, sampler, base + ( int2 )( x, y ) );
		}
	}

	barrier( CLK_LOCAL_MEM_FENCE );

	coord.x = get_global_id( 0 );
	coord.y = get_global_id( 1 );

	if( coord.x >= width || coord.y >= height )
		return;

#define BUF( x, y ) ( buf[ mul24( ( y ) + r, bstride ) + ( x ) + r ] )

	mincoord.x = max( 0, coord.x - r );
	mincoord.y = max( 0, coord.y - r );
	maxcoord.x = min( width - 1, coord.x + r );
	maxcoord.y = min( height - 1, coord.y + r );

	size = ( maxcoord.x - mincoord.x + 1 ) * ( maxcoord.y - mincoord.y + 1 );
	mincoord -= coord;
	maxcoord -= coord;

	value = 0;
	for( int y = mincoord.y; y <= maxcoord.y; y++ )
		for( int x = mincoord.x; x <= maxcoord.x; x++ )
			value += BUF( lx + x, ly + y );
	value /= ( float4 ) size;

	write_imagef( out, coord, value );
}
