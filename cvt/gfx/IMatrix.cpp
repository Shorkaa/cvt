#include "IMatrix.h"
#include <cvt/gfx/Image.h>
#include <cvt/gfx/IMapScoped.h>
#include <cvt/util/SIMD.h>
#include <cvt/util/ScopedBuffer.h>

using namespace cvt;


Matrix4f IMatrix::contrastMatrix(float rscale, float gscale, float bscale){
    Matrix4f mat = Matrix4f(rscale,0,0,0,
                            0,gscale,0,0,
                            0,0,bscale,0,
                            0,0,0,1);
    return mat;
}

Matrix4f IMatrix::saturationMatrix(float s){
    Matrix4f mat = Matrix4f(lumaR - lumaR * s + s,  lumaG - lumaG * s,      lumaB - lumaB * s,       0,
                            lumaR - lumaR * s,      lumaG - lumaG * s + s,  lumaB - lumaB * s,       0,
                            lumaR - lumaR * s,      lumaG - lumaG * s,      lumaB - lumaB * s + s,   0,
                            0,                      0,                      0,                       1);
    return mat;
}

Matrix4f IMatrix::brightnessMatrix(float roffset, float goffset, float boffset){
    Matrix4f mat = Matrix4f(1,0,0,roffset,
                            0,1,0,goffset,
                            0,0,1,boffset,
                            0,0,0,1);
    return mat;
}

Matrix4f IMatrix::XYZconversionMatrix(){
    //values according to CIE standards for converting RGB to XYZ
    Matrix4f mat = Matrix4f(0.4124, 0.3576, 0.1805, 0,
                            0.2126, 0.7152, 0.0722, 0,
                            0.0193, 0.1192, 0.9505, 0,
                            0,      0,      0,      1);
/*
    Matrix4f mat = Matrix4f(0.4124, 0.2126, 0.0193, 0,
                            0.3576, 0.7152, 0.1192, 0,
                            0.1805, 0.0722, 0.9505, 0,
                            0,      0,      0,      1);*/
    return mat;
}

Matrix4f IMatrix::invXYZconversionMatrix(){
    Matrix4f mat = Matrix4f( 3.2406, -1.5372, -0.4986,   0,
                            -0.9689,  1.8758,  0.0415,   0,
                             0.0557, -0.2040,  1.0570,   0,
                             0,       0,       0,        1);
                             /*
    Matrix4f mat = Matrix4f( 3.2406, -0.9689,  0.0557,   0,
                            -1.5372,  1.8758, -0.2040,   0,
                            -0.4986,  0.0415,  1.0570,   0,
                             0,       0,       0,        1);
                             */
    return mat;
}

void IMatrix::colorTransform(Image& dst, const Image& src, const Matrix4f& mat){

	IMapScoped<float> mapdst( dst );
	IMapScoped<const float> mapsrc( src );
    SIMD* simd = SIMD::instance();

    for(int i;i<src.height();i++){
        simd->colorTransformation(mapdst.ptr(), mapsrc.ptr(), mat, src.width());
        mapsrc++;
        mapdst++;
    }

}

