/*
 *  cluster.cpp
 *  eegParticles
 *
 *  Created by Nikolas Psaroudakis on 9/25/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */
#include "cinder/Utilities.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Timer.h"
#include "cinder/Rand.h"
#include "cluster.h"
#include "cinder/gl/gl.h"



Texture* cluster::tex = NULL ;
float cluster::maxVelocity = 1.2f;
int cluster::meditThres = 40;
bool cluster::showPanels = true;
cluster::cluster(Vec2f _pos, float _radius, int _w, int _h, const Surface &mySurface)
{
	showInfo = true;
	//if (tex==NULL) {
	//	tex = new gl::Texture( loadImage( ci::app::App::get()->loadResource("particle.png"))); 
	//}
	Rand::randomize();
	mCentre = _pos;
	mRadius = _radius;
	
	
	float padding = 10;
	float maxVelocity = .05;
	
	
	for(int i = 0; i < totalNumberParticles/totalNumberClusters; i++) {
		float x = Rand::randFloat(padding, _w - padding);
		float y = Rand::randFloat(padding, _h - padding);
		float xv = Rand::randFloat(-maxVelocity, maxVelocity);
		float yv = Rand::randFloat(-maxVelocity, maxVelocity);
		Particle particle(x, y, xv, yv);
		// select a random color from the surface
		ColorA8u myColor = mySurface.getPixel( Vec2i(Rand::randInt(0, 600 ),Rand::randInt(0, 600 )));
		//if black we should skip that
		particle.updateColor(myColor);
		this->add(particle);
		
	}
	
	/*
	 while (this->size() < totalNumberParticles/totalNumberClusters ) {
	 float r = Rand::randFloat(0.0f, (float) mRadius);
	 float theta = Rand::randFloat(0.0f, (float) 2*PI);
	 Particle p = Particle(mCentre.x+r*cos(theta), mCentre.y+r*sin(theta), Rand::randFloat(-maxVelocity, maxVelocity),Rand::randFloat(-maxVelocity, maxVelocity));
	 this->add(p);
	 }
	 */
	setTimeStep(0.2);
	//glDisable(GL_TEXTURE_2D);
	//centerAttraction = 2;
	//particleNeighborhood = 7;
	//centerRepulsion = 2;
	theLabel = Label(mCentre+Vec2i(60,60));
	increasing = false;
	
	aTimer = ci::Timer();
}
cluster::~cluster()
{
	
}
void cluster::setCentre(Vec2f _mCentre)
{
	mCentre = _mCentre;
}
void cluster::setAttention(float _mAttn)
{
	mAttn = _mAttn;
}
void cluster::setMeditation(float _mMedit)
{
	mMedit = _mMedit;
}
void cluster::setColor(Vec3f _color)
{
	mColor = _color;
	
}

void cluster::drawForces()
{
	
}

vector<Particle> cluster::getParticles() {
	return particles;
}

void cluster::draw()
{	
	//Randomly updating the equalizer in the label
	//To be removed
	if (aTimer.isStopped()) {
		aTimer.start();
	} else if (aTimer.getSeconds()>=1){
		for (int i=0; i<theLabel.equalizer.nLines; i++) {
			theLabel.setData(i, Rand::randFloat());
		}
		aTimer.stop();
		aTimer = ci::Timer();
	}
	int n = particles.size();
	
	glBegin(GL_POINTS);
	for(int i = 0; i < n; i++){
		glColor4f(particles[i].mColor);
		particles[i].draw();
	}
	glEnd();
	
	
	
	if (showInfo) {
		theLabel.draw();
	}
	
}

void cluster::updateInfo()
{
	
	
}
void cluster::setParams()
{
	
	
}
void cluster::setCenterAttraction(float v)
{
	
}
void cluster::setParticleNeighborhood(float v)
{
	
}
void cluster::setCenterRepulsion(float v)
{
	
}




