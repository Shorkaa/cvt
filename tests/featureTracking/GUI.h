#ifndef FEATURE_GUI_H
#define FEATURE_GUI_H

#include <cvt/gui/Application.h>
#include <cvt/gui/Window.h>
#include <cvt/gui/Slider.h>
#include <cvt/gui/WidgetLayout.h>
#include <cvt/gui/Moveable.h>
#include <cvt/gui/ImageView.h>
#include <cvt/gui/Button.h>
#include <cvt/gui/Label.h>
#include <cvt/gfx/GFXEngineImage.h>

#include <list>

namespace cvt
{

	class Gui : public Window
	{
		public:
			Gui();

			void updateImage( const cvt::Image & img,
                              const std::vector<Vector2f> & tracked );

			void observeFastThresholdSlider( const Delegate<void ( uint8_t )> & delegate );
			void observeFastSADThresholdSlider( const Delegate<void ( float )> & delegate );
            void observeOctaveSlider( const Delegate<void ( size_t )> & delegate );
            void observeScaleSlider( const Delegate<void ( float )> & delegate );
            void observeMaxFeatureSlider( const Delegate<void ( size_t )> & delegate );
            void observeNonMaxSuppression( const Delegate<void (ToggleButton *)> & delegate );
            void observeMaxDescDistanceSlider( const Delegate<void (size_t)> & delegate );
            void observeMatchRadiusSlider( const Delegate<void (size_t)> & delegate );
            void observeKLTSSDSlider( const Delegate<void (float)> & delegate );
            void observeGridSizeSlider( const Delegate<void (size_t)> & delegate );

            void setFPS( float fps );

		private:
			ImageView		_imgView;
			Moveable		_imgMov;
			Button			_quit;

			Slider<uint8_t> _fastThreshSlider;
            Label           _fastThreshLabel;
			
			Slider<float>	_fastSADThreshSlider;
            Label           _fastSADThreshLabel;

            Slider<size_t>  _octaveSlider;
            Label           _octaveLabel;

            Slider<float>   _scaleSlider;
            Label           _scaleLabel;

            Slider<size_t>  _maxFeatureSlider;
            Label           _maxFeatureLabel;

            ToggleButton    _nonMaxSuppression;

            Label           _fpsLabel;

            Slider<size_t>  _maxDescDistanceSlider;
            Label           _maxDescLabel;

            Slider<size_t>  _matchRadiusSlider;
            Label           _matchRadiusLabel;
            
			Slider<float>   _kltSSDSlider;
            Label           _kltSSDSliderLabel;
			
			Slider<size_t>  _gridSizeSlider;
            Label           _gridSizeSliderLabel;


            void updateFastSliderLabel( uint8_t thresh );
            void updateFastSADSliderLabel( float thresh );
            void updateOctaveLabel( size_t v );
            void updateScaleLabel( float v );
            void updateMaxFeatureLabel( size_t v );
            void updateMaxDescDistanceLabel( size_t v );
            void updateMatchRadiusLabel( size_t v );
            void updateKLTSSDSliderLabel( float v );
            void updateGridSizeSliderLabel( size_t v );
	};

	inline Gui::Gui():
		Window( "Feature Tracking GUI" ),
		_imgView(),
		_imgMov( &_imgView ),
		_quit( "Quit" ),
		_fastThreshSlider( 10, 120, 25 ),
        _fastThreshLabel( "FAST threshold:" ),
		_fastSADThreshSlider( 0.0f, 1.0f, 0.7f ),
        _fastSADThreshLabel( "FAST-SAD threshold:" ),
        _octaveSlider( 1, 5, 3 ),
        _octaveLabel( "Octaves: " ),
        _scaleSlider( 0.3f, 0.9f, 0.6f ),
        _scaleLabel( "Scale Factor: " ),
        _maxFeatureSlider( 50, 3000, 1000 ),
        _maxFeatureLabel( "Max Features: " ),
        _nonMaxSuppression( "Non Max Suppression", true ),
        _fpsLabel( "FPS: 0.0f" ),
        _maxDescDistanceSlider( 0, 256, 50 ),
        _maxDescLabel( "Max Desc. Dist.: 50" ),
        _matchRadiusSlider( 5, 100, 30 ),
        _matchRadiusLabel( "Match Radius: 30" ),
        _kltSSDSlider( 0.0f, 255.0f, 10.0f ),
        _kltSSDSliderLabel( "KLT-SSD THRESH: 0" ),
        _gridSizeSlider( 1, 200, 20 ),
        _gridSizeSliderLabel( "GridSize: 0" )
	{
		setSize( 960, 720 );

		_imgMov.setSize( 640, 480 );
		addWidget( &_imgMov );

		Delegate<void ()> qDel( &Application::exit );
		_quit.clicked.add( qDel );

        Delegate<void ( uint8_t )> threshChange( this, &Gui::updateFastSliderLabel );
        observeFastThresholdSlider( threshChange );
        
		Delegate<void ( float )> fastsadthresh( this, &Gui::updateFastSADSliderLabel );
        observeFastSADThresholdSlider( fastsadthresh );

        Delegate<void ( size_t )> octaveChange( this, &Gui::updateOctaveLabel );
        observeOctaveSlider( octaveChange );

        Delegate<void ( float )> scaleChange( this, &Gui::updateScaleLabel );
        observeScaleSlider( scaleChange );

        Delegate<void ( size_t )> maxFeatChange( this, &Gui::updateMaxFeatureLabel );
        observeMaxFeatureSlider( maxFeatChange );

        Delegate<void ( size_t )> maxDDChange( this, &Gui::updateMaxDescDistanceLabel );
        observeMaxDescDistanceSlider( maxDDChange );
        
		Delegate<void ( size_t )> matchRadiusChange( this, &Gui::updateMatchRadiusLabel );
        observeMatchRadiusSlider( matchRadiusChange );
		
		Delegate<void ( float )> kltssdthreshchange( this, &Gui::updateKLTSSDSliderLabel );
        observeKLTSSDSlider( kltssdthreshchange );
		
		Delegate<void ( size_t )> grid( this, &Gui::updateGridSizeSliderLabel );
        observeGridSizeSlider( grid );

        WidgetLayout wl;
        size_t h = 10;
		wl.setAnchoredRight( 10, 100 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_quit, wl );

        h += 30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_fastThreshSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_fastThreshLabel, wl );
        updateFastSliderLabel( 25 );
        
		h += 30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_fastSADThreshSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_fastSADThreshLabel, wl );
        updateFastSliderLabel( 25 );

        h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_octaveSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_octaveLabel, wl );
        updateOctaveLabel( 3 );

        h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_scaleSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_scaleLabel, wl );
        updateScaleLabel( 0.6f );

        h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_maxFeatureSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_maxFeatureLabel, wl );
        updateMaxFeatureLabel( 1000 );

        h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_maxDescDistanceSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_maxDescLabel, wl );

        h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_matchRadiusSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_matchRadiusLabel, wl );
        
		h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_kltSSDSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_kltSSDSliderLabel, wl );
		
		h+=30;
        wl.setAnchoredRight( 10, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_gridSizeSlider, wl );
        wl.setAnchoredRight( 160, 150 );
        addWidget( &_gridSizeSliderLabel, wl );

        h+=30;
        wl.setAnchoredRight( 10, 300 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_nonMaxSuppression, wl );

        h+=30;
        wl.setAnchoredRight( 160, 150 );
		wl.setAnchoredBottom( h, 20 );
		addWidget( &_fpsLabel, wl );
        

		setVisible( true );
	}

	inline void Gui::observeFastThresholdSlider( const Delegate<void ( uint8_t )> & delegate )
	{
	   	_fastThreshSlider.valueChanged.add( delegate );
	}

	inline void Gui::observeFastSADThresholdSlider( const Delegate<void ( float )> & delegate )
	{
	   	_fastSADThreshSlider.valueChanged.add( delegate );
	}

    inline void Gui::observeOctaveSlider( const Delegate<void ( size_t )> & delegate )
	{
	   	_octaveSlider.valueChanged.add( delegate );
	}

    inline void Gui::observeScaleSlider( const Delegate<void ( float )> & delegate )
    {
        _scaleSlider.valueChanged.add( delegate );
    }

    inline void Gui::observeMaxFeatureSlider( const Delegate<void ( size_t )> & delegate )
    {
        _maxFeatureSlider.valueChanged.add( delegate );
    }

    inline void Gui::observeNonMaxSuppression( const Delegate<void (ToggleButton *)> & delegate )
    {
        _nonMaxSuppression.toggled.add( delegate );
    }

    inline void Gui::observeMaxDescDistanceSlider( const Delegate<void (size_t)>& delegate )
    {
        _maxDescDistanceSlider.valueChanged.add( delegate );
    }

    inline void Gui::observeMatchRadiusSlider( const Delegate<void (size_t)>& delegate )
    {
        _matchRadiusSlider.valueChanged.add( delegate );
    }
    
	inline void Gui::observeKLTSSDSlider( const Delegate<void (float)>& delegate )
    {
        _kltSSDSlider.valueChanged.add( delegate );
    }

	inline void Gui::observeGridSizeSlider( const Delegate<void (size_t)>& delegate )
    {
        _gridSizeSlider.valueChanged.add( delegate );
    }

    inline void Gui::updateFastSliderLabel( uint8_t thresh )
    {
        String title( "FAST threshold: " );
        title += thresh;
        _fastThreshLabel.setLabel( title );
    }
    
	inline void Gui::updateFastSADSliderLabel( float thresh )
    {
        String title;

		title.sprintf( "F-SAD threshold: %0.2f", thresh );
        _fastSADThreshLabel.setLabel( title );
    }

    inline void Gui::updateOctaveLabel( size_t v )
    {
        String title( "Octaves: " );
        title += v;
        _octaveLabel.setLabel( title );
    }

    inline void Gui::updateScaleLabel( float v )
    {
        String title;
        title.sprintf( "Scale Factor: %0.2f", v );
        _scaleLabel.setLabel( title );
    }

    inline void Gui::updateMaxFeatureLabel( size_t v )
    {
        String title( "Max Features: " );
        title += v;
        _maxFeatureLabel.setLabel( title );
    }

    inline void Gui::updateMaxDescDistanceLabel( size_t v )
    {
        String title( "Max Desc. Dist.: " );
        title += v;
        _maxDescLabel.setLabel( title );
    }

    inline void Gui::updateMatchRadiusLabel( size_t v )
    {
        String title( "Match Radius: " );
        title += v;
        _matchRadiusLabel.setLabel( title );
    }

    inline void Gui::updateKLTSSDSliderLabel( float v )
    {
        String title;
		title.sprintf( "klt-SSD-THRESH: %0.2f", v );
        _kltSSDSliderLabel.setLabel( title );
    }
    
	inline void Gui::updateGridSizeSliderLabel( size_t v )
    {
        String title( "Grid Size: " );
        title += v;
        _gridSizeSliderLabel.setLabel( title );
    }

    inline void Gui::setFPS( float fps )
    {
        String title;
        title.sprintf( "FPS: %0.2f", fps );
        _fpsLabel.setLabel( title );
    }

	inline void Gui::updateImage( const cvt::Image & img,
                                  const std::vector<Vector2f> & tracked
                                  )
	{
        Image out( img );
        {
            GFXEngineImage ge( out );
            GFX g( &ge );
            
            g.color() = Color::GREEN;
            std::vector<Vector2f>::const_iterator tIter = tracked.begin();
            const std::vector<Vector2f>::const_iterator tEnd = tracked.end();
            while( tIter != tEnd ){
                g.fillRect( tIter->x-1, tIter->y-1, 3, 3 );
                tIter++;
            }
		}

		_imgView.setImage( out );
	}
}


#endif
