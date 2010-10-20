/*
 *  cluster.h
 *  eegParticles
 *
 *  Created by Nikolas Psaroudakis on 9/25/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#pragma once 

#include "particleSystem.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/Channel.h"
#include "Label.h"
#include "cinder/Timer.h"

#define PI 3.14159265

using namespace ci;
using namespace std;

//using namespace ci::app;
using namespace gl;
extern int totalNumberParticles;
extern int totalNumberClusters;

class cluster : public ParticleSystem {

	
public:
	cluster(Vec2f _pos, float _radius, int _w, int _h,const ci::Surface &mySurface);
	~cluster();
	void setCentre(Vec2f _mCentre);
	void setAttention(float _mAttn);
	void setMeditation(float _mMedit);
	///
	void setCenterAttraction(float v);
	void setParticleNeighborhood(float v); 
	void setCenterRepulsion(float v);							 
	///
	void setParams();
	void setColor(Vec3f _color);
	void updateInfo();
	void applyForces();
	void draw();
	void drawForces();
	vector<Particle> getParticles();
	
	//static int maxParticles;
	static float maxVelocity;
	static Texture* tex;
	Channel32f mChannel;
	Vec2f mCentre;
	float mAttn;
	float mMedit;
	static int meditThres;
	static bool showPanels;
	Vec3f mColor;
	
	bool showInfo;
	bool increasing;
	
	float centerAttraction;
	float particleNeighborhood;
	float centerRepulsion;
	float mRadius;
	Label theLabel;
private:
	Timer aTimer;
	

};