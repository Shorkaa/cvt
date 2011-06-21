#ifndef CVT_ITRANSFORM_H
#define CVT_ITRANSFORM_H

#include <cvt/gfx/IFilter.h>
#include <cvt/util/Plugin.h>
#include <cvt/util/PluginManager.h>

namespace cvt {
	class ITransform : public IFilter {
		public:
			ITransform();
			~ITransform();
			void apply( const ParamSet* attribs, IFilterType iftype ) const;

			static void apply( Image& dst, const Image& src, const Matrix3f& transform, bool fill = false, const Color& color = Color::WHITE );

		private:
			static void applyFC1( Image& dst, const Image& src, const Matrix3f& transform, bool fill, const Color& color );
			static void applyFC4( Image& dst, const Image& src, const Matrix3f& transform, bool fill, const Color& color );
			static void applyU8C1( Image& dst, const Image& src, const Matrix3f& transform, bool fill, const Color& color );
			static void applyU8C4( Image& dst, const Image& src, const Matrix3f& transform, bool fill, const Color& color );

			ITransform( const ITransform& t );
	};
}

#endif
