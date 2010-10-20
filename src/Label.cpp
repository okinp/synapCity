/*
 *  Label.cpp
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#include "Label.h"
Label::Label()
{
	
}
Label::Label(Vec2i _pos)
{
	
	artworkTxt.setFont(Font(loadFile(cinder::app::App::get()->getResourcePath("etelkanarrowmediumpro.otf")), 20 ));
	artworkTxt.setColor(Color(1.0f,1.0f,1.0f));
	nameTxt.setFont(Font( loadFile(cinder::app::App::get()->getResourcePath("etelkanarrowlightpro.otf")), 11 ));
	nameTxt.setColor(Color(1.0f,1.0f,1.0f));
	primaryReadingsTxt.setFont(Font(loadFile(cinder::app::App::get()->getResourcePath( "etelkamonospacepro.otf")), 8));
	primaryReadingsTxt.setColor(Color(1.0f,1.0f,1.0f));
	
	userName = "Michael Zick Doherty";
	meditValue = string("M") + string("80");
	attentValue =  string("A") + string("67");
	artworkID =  "01";
	
	artworkTxt.addLine(artworkID);
	
	nameTxt.addLine(userName);
	
	primaryReadingsTxt.addLine(meditValue);
	primaryReadingsTxt.addLine(attentValue);
	
	readingsTexture = Texture( primaryReadingsTxt.render(true));
	nameTexture = Texture( nameTxt.render(true));
	artworkTexture = Texture(artworkTxt.render(true));
	
	pos = _pos;
	//vLines(Vec2i _pos, int _width, int _nLines, int _spacing, int _length);
	equalizer = vLines(Vec2i(artworkTexture.getWidth()+readingsTexture.getWidth()+4,readingsTexture.getHeight()-4)+pos, 2, 8, 2, readingsTexture.getHeight()-4);
	
	//Set equalizer
	for (int i=0; i<equalizer.nLines; i++) {
		float r = Rand::randFloat();
		setData(i, r);
	}

}
void Label::setArtworkID(int i)
{ 
	stringstream ss;
	ss << i;
	if (i<10){
		artworkID = string("0") + ss.str();
	} else {
		artworkID = ss.str();
	}
	updateContent();

}
void Label::setAttention(string attention)
{
	stringstream ss;
	ss << "A" << attention;
	
	attentValue = ss.str();
}
void Label::setMeditation(string meditation)
{

	stringstream ss;
	ss << "M" << meditation;
	meditValue = ss.str();
}
void Label::updateContent()
{
	//There seems to be no way to empty a TextLayout natively
	//so I moved the mLines que to public in the cinder source code.
	artworkTxt.mLines.clear();
	artworkTxt.addLine(artworkID);
	artworkTexture = Texture(artworkTxt.render(true));
}
void Label::draw()
{
	
	enableAlphaBlending();
	glColor3f(1.0f, 1.0f, 1.0f);
	
	//Draw equalizer
	//pushMatrices();
	//glTranslatef(pos.x, pos.y, 0);
	equalizer.draw();
	//popMatrices();

	//Draw artworkID, username and artworkID
	glEnable(GL_TEXTURE_2D);
	pushMatrices();
	readingsTexture = Texture( primaryReadingsTxt.render(true));
	nameTexture = Texture( nameTxt.render(true));
	artworkTexture = Texture(artworkTxt.render(true));
	ci::gl::draw( artworkTexture, Vec2i( 0, 0 )+ pos );
	ci::gl::draw(readingsTexture,Vec2i(2,4) + pos+Vec2i(artworkTexture.getWidth(),0));
	ci::gl::draw(nameTexture, pos + Vec2i(0,artworkTexture.getHeight()+equalizer.width));
    popMatrices();
	glDisable(GL_TEXTURE_2D);
	
	//Draw horizontal line
	Vec2i hLinePos = Vec2i(0, artworkTexture.getHeight())+pos;
	int hLineLength = artworkTexture.getWidth() + readingsTexture.getWidth() + equalizer.getWidth();
	glBegin(GL_QUADS);
	glVertex2f(hLinePos.x, hLinePos.y);
	glVertex2f(hLinePos.x + hLineLength + 5, hLinePos.y);
	glVertex2f(hLinePos.x + hLineLength + 5, hLinePos.y+equalizer.width);
	glVertex2f(hLinePos.x, hLinePos.y+equalizer.width);
	glEnd();
	 

}
// val needs to be in the range 0 to 1 (i.e percentage of max line length)
void Label::setData(int i, float val)
{
	equalizer.lines[i].val = val;

}