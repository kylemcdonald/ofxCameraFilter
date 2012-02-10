#include "ofApp.h"

void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	filter.setup(640, 480);
	
	ofSetCircleResolution(64);
	grid.setMode(OF_PRIMITIVE_LINES);
	for(int y = 0; y < ofGetHeight(); y += 16) {
		for(int x = 0; x < ofGetWidth(); x += 16) {
			grid.addVertex(ofVec2f(x, 0));
			grid.addVertex(ofVec2f(x, ofGetHeight()));
			grid.addVertex(ofVec2f(0, y));
			grid.addVertex(ofVec2f(ofGetWidth(), y));
		}
	}
}

void ofApp::update() {	
	cam.update();
	if(cam.isFrameNew()) {
		filter.begin();
		cam.draw(0, 0);
		grid.draw();
		filter.end();
	}
}

void ofApp::draw() {
	ofBackground(0);	
	filter.draw();
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}
