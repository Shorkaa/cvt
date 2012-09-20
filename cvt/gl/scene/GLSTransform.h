/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_GLSTRANSFORM_H
#define CVT_GLSTRANSFORM_H

#include <cvt/math/Matrix.h>

namespace cvt {
	class GLSTransformable
	{
		public:
			GLSTransformable( const Matrix4f& mat );
			~GLSTransformable();

			const Matrix4f& transformation() const;
			Matrix4f&		transformation();
			void			setTransformation( const Matrix4f& t );

		protected:
			Matrix4f	_transformation;
	};

	inline GLSTransformable::GLSTransformable( const Matrix4f& mat ) : GLSNode( GLSNODE_TRANSFORMATION ), _transformation( mat )
	{
	}

	inline GLSTransformable::~GLSTransformable()
	{
	}

	inline void GLSTransformable::setTransformation( const Matrix4f& t )
	{
		_transformation = t;
	}

	inline const Matrix4f& GLSTransformable::transformation() const
	{
		return _transformation;
	}

	inline Matrix4f& GLSTransformable::transformation()
	{
		return _transformation;
	}
}

#endif
