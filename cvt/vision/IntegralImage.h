/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_INTEGRAL_IMAGE_H
#define CVT_INTEGRAL_IMAGE_H

#include <cvt/gfx/Image.h>
#include <cvt/util/Flags.h>
#include <cvt/vision/Patch.h>

namespace cvt
{
    enum IntImgFlagTypes {
		SUMMED_AREA = ( 1 << 0 ),
		SQUARED_SUMMED_AREA = ( 1 << 1 )
	};

	CVT_ENUM_TO_FLAGS( IntImgFlagTypes, IntegralImageFlags )

	class IntegralImage
	{
		public:
            IntegralImage( const Image & img, IntegralImageFlags flags = SUMMED_AREA );
            IntegralImage( IntegralImageFlags flags = SUMMED_AREA );
            
            ~IntegralImage();

            void    update( const Image & img );
            float   area( const Recti & r ) const;
            float   sqrArea( const Recti & r ) const;

            /**
             * normalized cross correlation:
             * calculates the normalized cross correlation of the Rectangle rOther from other
             * with pos in this image
             */
            float   ncc( const Image & img,
                         const Image & otherI,
                         const IntegralImage & otherII,
                         const Recti & rOther,
                         const Vector2i & pos ) const;

            /**
             * compute normalized cross correlation of the patch with
             * this image at position pos
             */
            float   ncc( const Image & img, const Patch & patch, const Vector2i & pos ) const;

            const Image & sumImage()	const { return _sum; };
            const Image & sqrSumImage() const { return _sqrSum; };
            IntegralImageFlags flags()  const { return _flags; };

            static inline float area( const Image & img, const Recti & r );

            static inline float area( const float * p, size_t w, size_t h, size_t stride );
            static inline float area( const float * ptr, size_t x, size_t y, size_t w, size_t h, size_t stride );

        private:
            Image              _sum;
            Image              _sqrSum;
            IntegralImageFlags _flags;

	};

    inline float IntegralImage::area( const Image & img, const Recti & r )
    {
        size_t stride;
        const float * p = img.map<float>( &stride );

        int xOffset, yOffset;

        yOffset = r.y - 1;
        xOffset = r.x - 1;

        float sum = p[ ( yOffset + r.height ) * stride + xOffset + r.width ];

        if( yOffset >= 0 ){
            if( xOffset >= 0 ){ // +a
                sum += p[ yOffset * stride + xOffset ];
                sum -= p[ ( yOffset + r.height ) * stride + xOffset ];
            }

            xOffset = Math::min( xOffset + r.width, ( int )img.width() - 1 );
            sum -= p[ yOffset * stride + xOffset ];
        } else {
            yOffset = yOffset + r.height;
            if( xOffset >= 0 ){ // -c
                sum -= p[ yOffset * stride + xOffset ];
            }
        }

        img.unmap( p );
        return sum;
    }

    inline float IntegralImage::area( const float * p, size_t w, size_t h, size_t stride )
    {
        w--; h--;
        return  p[ stride * h + w ]
               -p[ w - stride ]
               -p[ stride * h - 1 ]
               +p[ -stride - 1 ];
    }

    inline float IntegralImage::area( const float* ptr, size_t x, size_t y, size_t w, size_t h, size_t widthstep )
    {
		const float* p = ptr + y * widthstep + x;
        w--; h--;
        return  p[ widthstep * h + w ]
               -p[ w - widthstep ]
               -p[ widthstep * h - 1 ]
               +p[ -widthstep - 1 ];
    }

}

#endif
