/*
 *  jsonReader.cpp
 *  synapcityViz
 *
 *  Created by Nikolas Psaroudakis on 9/26/10.
 *  Copyright 2010 New York University. All rights reserved.
 *
 */

#include "jsonRead.h"
bool jsonRead::local = true;
jsonRead::jsonRead()
{
	/*
	 numClusters = 10;
	 for (int i=0; i< numClusters; i++)
	 {
	 attn.push_back(0);
	 medit.push_back(0);
	 }
	 */
	time (&start);
	
}
jsonRead::~jsonRead()
{
	
}
/*
boost::thread jsonRead::threadedRead()
{
	boost::thread  threadA = boost::thread(readData());
	threadA.join();
	return threadA;
}
 */
string jsonRead::readData()
{
	time (&end);
	double diff = difftime(end,start);
	if (diff >= 0){
		//cout << "TimeDiff " << diff << endl;
		if (local) {
			//string path = cinder::app::App::get()->getResourcePath("readingOrig.json");
			string path = cinder::app::App::get()->getResourcePath("mathias_wave.json");
			ifstream infile(path.c_str());
			string mRes((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
			mResult = mRes;
		/*	
		} else {
			//mResult = "NOT LOCAL";
			string theURL="http://172.0.0.1:1234/buffer/1/readings.json";
			string user = "synapcity";
			string pass = "acclair";
			cinder::IStreamUrlRef urlRef = cinder::loadUrlStream(theURL,user,pass); 
			mResult="";
			if(urlRef)
			{        
				while (urlRef->getFileName().size() > 1 && urlRef->isEof() == false)
				{
					std::string currentLine = urlRef->readLine();            
					mResult+=currentLine;
				}
			}
		*/
		 }
		//Fix JSON DOM
		mResult = "{\"output\":" + mResult;
		mResult+="}";
		time (&start);
	}
//	cout << mResult.size() << endl;
	return mResult;
	
}
vector<eegData> jsonRead::parseJson(string& s)
{
	scrapedData.clear();
	string result;
	bool wasSuccessfull = mReader.parse(s,mRoot);
	if (!wasSuccessfull)
	{
		result="JSON PARSING FAILED";
		cout << result << endl;
		return scrapedData;
	} else {
		//cout << "JSON PARSING SUCCESS" << endl;
	}
	Json::Value rootOut = mRoot["output"];
	for (int i=0; i<rootOut.size(); ++i) {
		Json::Value elemOut = rootOut[i];
		//string val = elemOut.get()
		//elemOut = elemOut["reading"]["id"];
		eegData dataIn;
		dataIn.id = elemOut["reading"]["id"].asInt();
		dataIn.user_id = elemOut["reading"]["user_id"].asInt();
		dataIn.artwork_id = elemOut["reading"]["artwork_id"].asInt();
		dataIn.session_created = elemOut["reading"]["session_created"].asString();
		dataIn.dateOfReading = elemOut["reading"]["dateOfReading"].asString();
		dataIn.time_offset = elemOut["reading"]["time_offset"].asDouble();
		dataIn.signalQuality = elemOut["reading"]["signalQuality"].asDouble();
		dataIn.eSenseAttention = elemOut["reading"]["eSenseAttention"].asDouble();
		dataIn.eSenseMeditation  = elemOut["reading"]["eSenseMeditation"].asDouble();
		dataIn.eegLowAlpha  = elemOut["reading"]["eegLowAlpha"].asDouble();
		dataIn.eegHighAlpha  = elemOut["reading"]["eegHighAlpha"].asDouble();
		dataIn.eegLowBeta  = elemOut["reading"]["eegLowBeta"].asDouble();
		dataIn.eegHighBeta  = elemOut["reading"]["eegHighBeta"].asDouble();
		dataIn.eegLowGamma  = elemOut["reading"]["eegLowGamma"].asDouble();
		dataIn.eegHighGamma  = elemOut["reading"]["eegHighGamma"].asDouble();
		dataIn.eegDelta  = elemOut["reading"]["eegDelta"].asDouble();
		dataIn.eegTheta  = elemOut["reading"]["eegTheta"].asDouble();
		scrapedData.push_back(dataIn);
	}
	return scrapedData;
}

