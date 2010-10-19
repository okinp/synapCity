/*
 *  jsonReader.h
 *  synapcityViz
 *
 *  Created by Nikolas Psaroudakis on 9/26/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#ifndef JSON_READ_
#define JSON_READ_

#include "json.h"
#include "cinder/app/App.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "cinder/DataSource.h"
#include "cinder/Url.h"
#include "cinder/Buffer.h"
#include "cinder/Stream.h"
#include "time.h"
//#include <boost/thread.hpp">


using namespace std;
struct eegData {
	int id;
	int user_id;
	int artwork_id;
	string session_created;
	string dateOfReading;
	float time_offset;
	float signalQuality;
	float eSenseAttention;
	float eSenseMeditation;
	float eegLowAlpha;
	float eegHighAlpha;
	float eegLowBeta;
	float eegHighBeta;
	float eegLowGamma;
	float eegHighGamma;
	float eegDelta;
	float eegTheta;
};
class jsonRead {
public:
	jsonRead();
	~jsonRead();
	string readData();
//	boost::thread threadedRead(); 
	vector<eegData> parseJson(string& s);
	static bool local;
	vector<eegData> scrapedData; 
	
	
	Json::Value mRoot;
	Json::Reader mReader;
	int numClusters;
	string mResult;
	istringstream mInStream; 
	//cinder::DataSource dataURL;
	time_t start,end;
};
#endif