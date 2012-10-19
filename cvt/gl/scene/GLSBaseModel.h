/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2011, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_GLSBASEMODEL_H
#define CVT_GLSBASEMODEL_H

#include <cvt/gl/scene/GLSRenderable.h>
#include <cvt/gl/GLMesh.h>

namespace cvt {
	class GLSVistor;
	class GLSMaterial;

	class GLSBaseModel : public GLSRenderable {
		public:
			GLSBaseModel( GLMesh* mesh, GLSMaterial* material );
			~GLSBaseModel();

			GLMesh*		 mesh() { return _mesh; }
			GLSMaterial* material() { return _material; }
			bool		 visible() const { return _visible; }
			void		 setVisible( bool b ) { _visible = b; }

			void		 accept( GLSVisitor& visitor );
		private:
			bool		 _visible;
			GLMesh*		 _mesh;
			GLSMaterial* _material;
	};


	inline GLSBaseModel::GLSBaseModel( GLMesh* mesh, GLSMaterial* mat ) :
		_mesh( mesh ),
		_material( mat )
	{
	}

	inline GLSBaseModel::~GLSBaseModel()
	{
	}

}

#endif