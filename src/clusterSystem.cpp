/*
 *  clusterSystem.cpp
 *  eegParticles
 *
 *  Created by Nikolas Psaroudakis on 9/25/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#include "clusterSystem.h"
#include "cinder/app/AppBasic.h"


extern int totalNumberClusters;
int clusterSystem::binPower = 2;
clusterSystem::clusterSystem()
{
	mouseOn = false;
	showInfo = false;
	increasing = false;
	firstTime = true;
	repForce = 1;
	repForce2 = 91;
	attForce = 1;
	neighbor = 41;
	//rep 1rep2 91 att 1 Neigh 19
	
	
	cnt =0;
 }
clusterSystem::~clusterSystem()
{
	
}
void clusterSystem::setup(string (&images)[10])
{
	mPerlin = Perlin();
	
	int binPower = 4;
	
	particleSystem.setup(getWindowWidth(), getWindowHeight(), binPower);
	
	
	float kParticles = 1;
	float padding = 10;
	float maxVelocity = .05;
	
	timeStep = 0.5;
	lineOpacity = 0.02f;
	pointOpacity = 0.05f;
	
	particleNeighborhood = 12;
	particleRepulsion = 2;

	centerAttraction = 7;

	
	
	//int sz = 0;
	int cntA =0;
	int cntB =0;
	int cnt =0;
	Rand  randGen;
	cluster *cl;
	cout << "cluster begin";
	//Positioning of clusters
	
	/*272,356
	646,208
	577,646
	137,622
	466,497
	189,107
	919,115
	390,153
	615,358
	834,513
	 */
	vector<Vec2i> container;
	container.push_back(Vec2i(272,356));
	container.push_back(Vec2i(646,208));
	container.push_back(Vec2i(577,646));
	container.push_back(Vec2i(137,622));
	container.push_back(Vec2i(466,497));
	container.push_back(Vec2i(189,107));
	container.push_back(Vec2i(919,115));
	container.push_back(Vec2i(390,153));
	container.push_back(Vec2i(615,358));
	container.push_back(Vec2i(834,513));
	
	

	/*
	while (clusters.size() < totalNumberClusters) {
		if (cnt < 5 ){
			cl = new cluster(Vec2f(getWindowWidth()/10+cntA*getWindowWidth()/5, getWindowHeight()/4), 30,getWindowWidth(),getWindowHeight());
			
			
			cntA++;
		} else {
			cl = new cluster(Vec2f(getWindowWidth()/10+cntB*getWindowWidth()/5, 3*getWindowHeight()/4), 30,getWindowWidth(),getWindowHeight());
			cntB++;
		}
	*/
			// pass in a surface for each cluster
		for (int i = 0; i < container.size(); i++) {
			
			//cout << "imasj " << _rootUrl + images[i] << endl;
			
			
			//Url url( _rootUrl + images[i] );
			
			Surface mySurface = loadImage(cinder::app::App::get()->getResourcePath(images[i]));
			
			cl = new cluster(container[i], 30,getWindowWidth(),getWindowHeight(), mySurface);
			cl->setup(getWindowWidth(),getWindowHeight(), binPower);
			cl->setColor(Vec3f(Rand::randFloat(0, 1),Rand::randFloat(0,1),Rand::randFloat(0,1)));
			cl->theLabel.setArtworkID(i+1);
			clusters.push_back(*cl);
			cnt++;
			 //*/
		}
			 
		
		
	//}
	cout << clusters.size() << endl;
	 

}
void clusterSystem::update()
{	
	cnt++;
	clIter = clusters.begin();
	while (clIter!=clusters.end()) {
		(clIter)->showInfo = showInfo;
		(clIter)->setTimeStep(0.8);
		++clIter;
	}
	 
	//mySurface = &mySurface;
	particleSystem.setTimeStep(timeStep);

}
void clusterSystem::draw()
{
	////////////
	gl::clear();
	gl::enableAdditiveBlending();
	glColor4f(1.0f, 1.0f, 1.0f,lineOpacity);
	
	
	
	
	particleSystem.setupForces();
	
	
	// apply per-particle forces
	//glBegin(GL_POINTS);
	
	
	
	for(int i = 0; i < particleSystem.size(); i++) {
		//float temp = particleSystem.size() / 5;
		Particle& cur = particleSystem[i];
		glColor3f(cur.mColor);
		
		//glBegin(GL_LINES);
		particleSystem.addRepulsionForce(cur.x,cur.y, neighbor, repForce);
		cur.addDampingForce(0.1);
		
		//glEnd();
		
	}
	
	
	
	
	//particleSystem.addAttractionForce(800, 500, getWindowWidth(), attForce);
	
	//glColor4f(1.0f, 1.0f, 1.0f, 0.4);
	//console() << mouse.y/482 << endl;
	

	
	/////////////////////
	
	
	
	
	clIter =clusters.begin();
	int kk = 0;
	

	while (clIter!=clusters.end()) {
				
		//(clIter)->setParticleNeighborhood(4);
		(clIter)->setupForces();	// apply per-particle forces
		//(clIter)->addRepulsionForce((clIter)->mCentre.x+((clIter)->mMedit),(clIter)->mCentre.y,(clIter)->mMedit*3 , repForce2);
			
					
		for (int i=0; i< (clIter)->size(); i++) {
			Particle& cur = (*(clIter))[i];
			
			//glColor4f(cur.mColor,0.2f);
			Color shit(cur.mColor);
			glColor4f(shit.r, shit.g, shit.b,lineOpacity);

			glBegin(GL_LINES);

			//..cout << " cur " << i << " " << (*clIter)->mMedit << endl;
			//(*clIter)->addRepulsionForce(cur, 5,  3);
			
			(clIter)->addRepulsionForce(cur, neighbor+(clIter)->mMedit/50, repForce);
			cur.bounceOffWalls(0, 0, getWindowWidth(), getWindowHeight());	
			cur.addDampingForce(0.5);
			
		}
			
		
			glEnd();	
			(clIter)->addAttractionForce((clIter)->mCentre.x,(clIter)->mCentre.y,getWindowWidth(),attForce);
			
		//if(kk == 2) { 
			
			//(clIter)->addAttractionForce(mouseLoc.x,mouseLoc.y,200, 6);
			gl::pushMatrices();
			gl::translate(Vec3f(getWindowWidth() * 0.5, getWindowHeight() * 0.5, 0.0));
			gl::rotate(Vec3f(0, 0, (clIter)->mMedit));
		
			//gl::drawSolidCircle(Vec2f::zero(), 80, 4);
			//cout << cos(toRadians((clIter)->mMedit)) << endl;
		
		
		// get Perlin noise value based on my location and
		// elapsed seconds and turn this noise value into an angle.
		float nX = mouseLoc.x * 0.005f;
		float nY = mouseLoc.y * 0.005f;
		float nZ = app::getElapsedSeconds() * 0.1f;
		float noise = mPerlin.fBm( nX, nY, nZ );
		float angle = noise * 15.0f;
		Vec2f noiseVector( cos( angle ), sin( angle ) );
		
		//cout << nois;
		Vec2f mVel = noiseVector * 40;
		Vec2f mLoc = Vec2f(mouseLoc.x,mouseLoc.y);
		mLoc += mVel;
			
		//(clIter)->addRepulsionForce(mLoc.x,mLoc.y, (clIter)->mMedit/7+40, 30);
		glBegin(GL_LINES);
		(clIter)->addRepulsionForce(mLoc.x,mLoc.y, repForce2, 30);
		glEnd();
		
				
		
		
		//if(kk == 2) {
			// get Perlin noise value based on my location and
			// elapsed seconds and turn this noise value into an angle.
			float nX2 = (clIter)->mCentre.x * 0.005f;
			float nY2 = (clIter)->mCentre.y * 0.005f;
			float nZ2 = app::getElapsedSeconds() * 0.1f;
			float noise2 = mPerlin.fBm( nX2, nY2, nZ2 );
			float angle2 = noise2 * 15.0f;
			Vec2f noiseVector2( cos( angle2 ), sin( angle2 ) );
			
			//cout << nois;
			Vec2f mVel2 = noiseVector2 * 40;
			Vec2f mLoc2 = Vec2f((clIter)->mCentre.x,(clIter)->mCentre.y);
			mLoc2 += mVel2;
			
			
			(clIter)->addAttractionForce(mLoc2.x,mLoc2.y,getWindowWidth(),attForce);
			
			
		//}
		
		
		//	(clIter)->addRepulsionForce(mouseLoc.x+ (cos( toRadians((clIter)->mMedit) )*100),mouseLoc.y+ (sin( toRadians((clIter)->mMedit) )*100), (clIter)->mMedit/7+40, 30);
			gl::popMatrices();
			
		//}
		
		++clIter;
		kk++;
	}

	
	getJsonAndApplyForces();
	
	
	//gl::clear();
	//gl::enableAdditiveBlending();
	//gl::enableAlphaBlending();
	//glColor4f(1.0f, 0.2f, 1.0f, 0.4);

	glBegin(GL_POINTS);
	//particleSystem.update();
	//glPointSize(10); 
		
	clIter = clusters.begin();
	while (clIter!=clusters.end()) {
		(clIter)->update();
		
		(clIter)->draw();
		
		++clIter;
	}
	//particleSystem.draw();
	gl::disableAlphaBlending();

	//renderTextInfo();
	 
	 
		
}
void clusterSystem::renderTextInfo()
{
	//Render FPS
	glColor3f(1.0f, 1.0f, 1.0f);
	gl::drawString( toString((int) ci::app::App::get()->getAverageFps()) + " fps", Vec2f(32.0f, 52.0f));

	
}

void clusterSystem::getJsonAndApplyForces()
{  
	if (cnt%10==0) {
	string ss= theReader.readData();
	if (firstTime) {
		//cout << "DAMN " << endl;
		outData = theReader.parseJson(ss);
		clIter = clusters.begin();
		for (int i=0; i< outData.size(); i++) {
			
			//medit = 0;
			//attn = 0;

		}
		firstTime = false;
	}
	
	//simulateDataChange();
		clIter = clusters.begin();
		
		cnt++;
		clIter = clusters.begin();
		while (clIter!=clusters.end()) {
		///int artworkID = outData[i].artwork_id - 1 ;
		
		//float x =clusters[artworkID]->mCentre.x;
		//float y = clusters[artworkID]->mCentre.y;
		//float medit = outData[i].eSenseMeditation;
		//float attn = outData[i].eSenseAttention;
		//float scale = 300.0f;
		//clusters[artworkID]->mMedit = medit;
		//clusters[artworkID]->mAttn = attn;
		//clusters[artworkID]->centerAttraction = 
		//clusters[artworkID]->applyForces();
		(clIter)->updateInfo();
		
		if ((clIter)->mMedit < 0 ) {
			(clIter)->increasing = true;
		} 
		else if ((clIter)->mMedit > 360) {
			//(clIter)->increasing = false;
			(clIter)->mMedit = 0;
			//increasing = false;
		}
		if ((clIter)->increasing == true) {
			//outData[i].eSenseMeditation++;
			(clIter)->mMedit = (clIter)->mMedit + 30;
		} else {
			(clIter)->mMedit = (clIter)->mMedit - 1;
		}
		++clIter;
		
	}
	 

	}
	
	
}
	 
void clusterSystem::simulateDataChange()
{
	clIter = clusters.begin();

	
		for (int i=0; i< outData.size(); i++)
		{
			int artworkID = outData[i].artwork_id - 1;
			//
						//cout << "eben " << outData[i].eSenseMeditation << endl;
		}
		
}
