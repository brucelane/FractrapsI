#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FractrapsIApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
	Vec3i		    iResolution;           // viewport resolution (in pixels)
	float			iGlobalTime;           // shader playback time (in seconds)
	Vec2i			iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
	gl::GlslProg	mShader;

};

void FractrapsIApp::setup()
{
	try {
		iResolution = Vec3i( 1024, 768, 1 );
		iGlobalTime = 1;
		iMouse =  getMousePos();
		// load and compile the shader
		mShader = gl::GlslProg( loadAsset("FractrapsI_vert.glsl"), loadAsset("FractrapsI_frag.glsl") );
	}
	catch( const std::exception &e ) {
		// if anything went wrong, show it in the output window
		console() << e.what() << std::endl;
	}
}

void FractrapsIApp::mouseDown( MouseEvent event )
{
}

void FractrapsIApp::update()
{
	iMouse =  getMousePos();
}

void FractrapsIApp::draw()
{
		// clear the window
	gl::clear();

	mShader.bind();
	mShader.uniform("iGlobalTime",iGlobalTime++);
	mShader.uniform("iResolution",iResolution);
	mShader.uniform("iMouse", iMouse);

	gl::drawSolidRect( Rectf( getWindowBounds() ), false );

	// unbind textures and shader
	mShader.unbind();
}

CINDER_APP_BASIC( FractrapsIApp, RendererGl )
