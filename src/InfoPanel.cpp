
#include "InfoPanel.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

using namespace ci;

InfoPanel::InfoPanel()
{
	mState		= true;
	mOpacity	= 1.0f;
	mFadeTime	= 500;
	mMedit =0;
	mAttn = 0;
}
void InfoPanel::setReadings(int medit, int attn)
{
	mMedit	= medit;
	mAttn	= attn;
}
void InfoPanel::createTexture()
{
	TextLayout layout;
	std::stringstream ss;
	//std::stringstream ssB;
	layout.setFont( Font( "ArialMT", 14 ) );
	layout.setColor( Color( 1.0f, 0.6f, 0.0f ) );
	ss << "Meditation: ";
	//cout << ss.str();
	layout.addLine( ss.str());
	ss.str(""); 
	ss << mMedit;
	layout.setColor(Color(1.0f,1.0f,1.0f));
	layout.append(ss.str());
	//layout.addLine( "Meditation: %d",mMedit) );
	ss.str("");
	ss << "  Attention: ";
	layout.setColor( Color( 1.0f, 0.6f, 0.0f ) );
	layout.addLine(ss.str());
	ss.str("");
	ss << mAttn;
	layout.setColor(Color(1.0f,1.0f,1.0f));
	layout.append(ss.str());
	mTexture = gl::Texture( layout.render( true ) );
}


void InfoPanel::update( Vec2f aWindowDim, float aCounter )
{
	if( mState ){
		if( aCounter == mFadeTime ){
			toggleState();
		}
		mOpacity -= ( mOpacity - 1.0f ) * 0.1f;
	} else {
		mOpacity -= ( mOpacity - 0.0f ) * 0.1f;	
	}
	
	if( mOpacity > 0.01f ){
		render( aWindowDim );
	}
}


void InfoPanel::render( Vec2f aWindowDim )
{
	float x = aWindowDim.x - mTexture.getWidth() - 40.0f;
	float y = aWindowDim.y - mTexture.getHeight() - 25.0f;

	glColor4f( 1, 1, 1, mOpacity );
	gl::draw( mTexture, Vec2f( x, y ) );
}


void InfoPanel::toggleState()
{
	mState = ! mState;
}

