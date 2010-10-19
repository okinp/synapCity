/*
 *  vLines.h
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */


#pragma once
#include "cinder/Vector.h"
#include "line.h"
#include <vector>

using namespace ci;
class vLines {
public:
	vLines();
	vLines(Vec2i _pos, int _width, int _nLines, int _spacing, int _length);
	void draw();
	void setHeight();
	void setSpacing(float _spacing);
	Vec2i pos;
	int nLines;
	int spacing;
	int width;
	int length;
	std::vector <line> lines;
};