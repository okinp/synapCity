/*
 *  vLines.cpp
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#include "vLines.h"

vLines::vLines()
{
	
	nLines = 8;
	width = 3;
	spacing = 1;
	length =30;
	for (int i =0; i<nLines; i++) {
		line l = line(pos+Vec2i(i*(width+spacing),5),length);
		lines.push_back(l);
	}
}
vLines::vLines(Vec2i _pos, int _width, int _nLines, int _spacing, int _length)
{
	nLines = _nLines;
	width = _width;
	pos = _pos;
	spacing = _spacing;
	length = _length;
	
	for (int i =0; i<nLines; i++) {
		line l = line(pos+Vec2i(i*(width+spacing),5), length);
		l.setWidth(width);
		lines.push_back(l);
	}
}
void vLines::setSpacing(float _spacing)
{
	
}
void vLines::draw()
{
	for (int i=0; i<nLines; i++) {
		lines[i].draw();
	}
	
	
}
