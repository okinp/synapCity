#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"
#include "cinder/Rand.h"
#include "clusterSystem.h"
#include "cinder/Channel.h"


using namespace ci;
using namespace ci::app;
using namespace std;

/*
   ALL CREDIT for this code goes to KYLE MCDONALD and his original OF version
   posted here http://www.openframeworks.cc/forum/viewtopic.php?f=12&t=2860
*/

int totalNumberParticles = 10000;
int totalNumberClusters = 10;

class synapcityVizApp : public AppBasic {
 public:	
	void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
	
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event);
	void mouseUp( MouseEvent event);
	void mouseDrag( MouseEvent event );
	bool showInfo;
	clusterSystem theClusters;
	
	Surface mySurface;
	
};

void synapcityVizApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(1280,800);
	//settings->setFullScreen( true );
	cout << "prepare";
	
}

void synapcityVizApp::setup(){
	
	Rand::randomize();
	
	showInfo = false;
	Url url( "http://dl.dropbox.com/u/2569433/nebula.png" );
	mySurface = loadImage( loadUrl( url ) );
	
	// instead of sending 1 surface send array of surfaces
	theClusters.setup(mySurface);
	


}
void synapcityVizApp::update() {
	theClusters.showInfo = showInfo;
	theClusters.update();
	
	
}

void synapcityVizApp::draw()
{
	cinder::gl::clear();
	cinder::gl::enableAlphaBlending();
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	theClusters.draw();
}

	
void synapcityVizApp::keyDown( KeyEvent event )
{
if (event.getChar()=='i') {
	showInfo = !showInfo;
}
	if( event.getChar() == 'R' ) {
		theClusters.repForce++;	
	}
	if( event.getChar() == 'r' ) {
		if(theClusters.repForce > 1)	
		theClusters.repForce--;	
	}
	if( event.getChar() == 'T' ) {
		theClusters.repForce2++;	
	}
	if( event.getChar() == 't' ) {
		if(theClusters.repForce2 > 1)	
			theClusters.repForce2--;	
	}
	if( event.getChar() == 'A' ) {
		theClusters.attForce++;	
	}
	if( event.getChar() == 'a' ) {
		if(theClusters.attForce > 1)	
		theClusters.attForce--;	
	}
	if( event.getChar() == 'N' ) {
		theClusters.neighbor++;	
	}
	if( event.getChar() == 'n' ) {
		if(theClusters.neighbor > 1)
		theClusters.neighbor--;	
	}
	if( event.getChar() == 'O' ) {
		theClusters.lineOpacity = theClusters.lineOpacity + 0.001;	
	}
	if( event.getChar() == 'o' ) {
		if(theClusters.lineOpacity > 0)
			theClusters.lineOpacity= theClusters.lineOpacity - 0.001;	
	}
	
	
	cout << "rep " << theClusters.repForce  << "rep2 " << theClusters.repForce2 << " att " << theClusters.attForce << " Neigh " << theClusters.neighbor << endl;
	

}

void synapcityVizApp::mouseDown( MouseEvent event )
{
		//cout << getMousePos() << endl;
	theClusters.mouseOn = true;
	theClusters.mouseLoc = getMousePos();
}

void synapcityVizApp::mouseUp( MouseEvent event )
{
	theClusters.mouseOn = false;

}

void synapcityVizApp::mouseDrag( MouseEvent event )
{
	theClusters.mouseLoc = getMousePos();
	
}
// This line tells Cinder to actually create the application
CINDER_APP_BASIC( synapcityVizApp, RendererGl )
