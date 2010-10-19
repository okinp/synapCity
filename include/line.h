/*
 *  line.h
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#pragma once
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
using namespace ci;
class line {
public:
	line();
	line(Vec2i _pos, int _maxHeight);
	void setValue(float _val);
	void setWidth(float _wdt);
	void setMaxHeight(int _maxHeight);
	void draw();
	float width;
	float maxHeight;
	float val;
	Vec2i pos;
	

};