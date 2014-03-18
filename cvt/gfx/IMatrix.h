#ifndef IMATRIX_H
#define IMATRIX_H

#include <cvt/gfx/Image.h>
namespace cvt{

    class Image;
    class IMatrix
    {
        public:
            IMatrix(){}
            ~IMatrix();
            static Matrix4f contrastMatrix(float rscale, float gscale, float bscale);
            static Matrix4f saturationMatrix(float s);
            static Matrix4f brightnessMatrix(float roffset, float goffset, float boffset);
            static Matrix4f XYZconversionMatrix();
            static Matrix4f invXYZconversionMatrix();
            static void colorTransform(Image& dst, const Image& src, const Matrix4f& mat);
        protected:
        private:
    };
}
#endif // IMATRIX_H
