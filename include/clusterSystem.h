/*
 *  clusterSystem.h
 *  eegParticles
 *
 *  Created by Nikolas Psaroudakis on 9/25/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#ifndef _CLUSTER_SYSTEM_
#define _CLUSTER_SYSTEM_

#include "cluster.h"
#include "jsonRead.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/Perlin.h"
#include "cinder/Surface.h"
#include <sstream>
#include <iostream>
#include <stdlib.h> 
#include <string>




using namespace std;
using namespace ci;
using namespace ci::app;
using namespace ci::gl;


class clusterSystem {
public:
	clusterSystem();
	~clusterSystem();
	void setup(string (&images)[10]);// const ci::Surface &mySurface);
	void update();
	void draw();
	bool showInfo;
	bool mouseOn;
	Vec2i mouseLoc;
	int repForce;
	int repForce2;

	int attForce;
	int neighbor;
	float lineOpacity, pointOpacity;
	//Surface	mySurface;
private:
	void getJsonAndApplyForces();
	void renderTextInfo();
	vector <cluster> clusters;
	vector <cluster>::iterator clIter;
	//static int numClusters;
	static int binPower;
	jsonRead theReader;
	vector<eegData> outData;
	
	Particle& operator[](unsigned i);

	//Simulation functs and vars
	void simulateDataChange();
	bool increasing;
	bool firstTime;
	
	long int cnt;
	
	ParticleSystem particleSystem;//
	float timeStep;
	
	float particleNeighborhood, particleNeighborhood2, particleRepulsion,particleRepulsion2;
	float centerAttraction,centerAttraction2;
	
	Perlin mPerlin;
};
#endif