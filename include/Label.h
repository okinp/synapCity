/*
 *  Label.h
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#pragma once
#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/Rand.h"
#include "vLines.h"
#include "cinder/app/App.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


using namespace ci;
using namespace gl;
using namespace std;
class	Label {
public:
	Label();
	Label(Vec2i _pos);
	void draw();
	void setData(int i, float val);
	void setArtworkID(int i);
	void setUserName(string name);
	void setAttention(string attention);
	void setMeditation(string meditation);
	void updateContent();
	
	ci::Vec2i pos;
	//string data;
	//vector <int> data;
	TextLayout nameTxt;
	TextLayout artworkTxt;
	TextLayout primaryReadingsTxt;
	
	Texture	nameTexture;
	Texture	artworkTexture;
	Texture	readingsTexture;
	
	string userName;
	string meditValue;
	string attentValue;
	string artworkID;

	vLines equalizer;
	 

};