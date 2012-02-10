#pragma once

#include "ofMain.h"

#include "ofxCameraFilter.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofxCameraFilter filter;
};
