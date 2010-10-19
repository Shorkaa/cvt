#ifndef CVTGFX_H
#define CVTGFX_H

#include <cvt/util/Rect.h>
#include <cvt/gfx/Color.h>

namespace cvt {
	class GFX {
		public:
			GFX();
			//GFX( const GFX& g );
			virtual ~GFX();

			void setDefault();
			void setColor( const Color& c ) { color = c; };
			Color& getColor() { return color; };

			virtual void fillRect( const Recti& rect ) = 0;
			virtual void fillRect( int x, int y, int width, int height ) = 0;

		protected:
			Color color;
	};
}

#endif
