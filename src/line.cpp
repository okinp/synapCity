/*
 *  line.cpp
 *  synapcityLabel
 *
 *  Created by Nikolas Psaroudakis on 10/16/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#include "line.h"
#include <iostream>

line::line()
{
	maxHeight = 50;
	width = 5;
	pos = Vec2i(0,0);
	val = 1.0f;
}
line::line(Vec2i _pos, int _maxHeight)
{
	pos=_pos;
	maxHeight = _maxHeight;
	width = 3;
	val =1;
}
void line::setValue(float _val)
{
	val = _val;
}
void line::setWidth(float _wdt)
{
	width = _wdt;
}
void line::setMaxHeight(int _maxHeight)
{
	maxHeight = _maxHeight;
}
void line::draw()
{	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x+width, pos.y);
	glVertex2f(pos.x+width, pos.y - val*maxHeight);
	glVertex2f(pos.x, pos.y - val*maxHeight);
	glEnd();
}