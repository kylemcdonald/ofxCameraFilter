#include "ofApp.h"

void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);
	filter.setup(640, 480);
}

void ofApp::update() {
	filter.begin();
	ofSetColor(255);
	ofTranslate(ofGetWidth() / 2, ofGetHeight() /2);
	ofRotate(ofGetElapsedTimef() * 20);
	int n = 13;
	for(int i = 0; i < n; i++) {
		float theta = ofMap(i, 0, n, 0, 360);
		ofPushMatrix();
		ofRotate(theta);
		ofTranslate(50 + 150 * ofNoise(ofGetElapsedTimef() + i), 0);
		if(i% 6 < 3) {
			ofFill();
		} else {
			ofNoFill();
		}
		if(i % 2 == 0) {
			ofCircle(0, 0, 32);
		} else {
			ofRect(-16, -16, 32, 32);
		}
		ofPopMatrix();
	}
	filter.end();
}

void ofApp::draw() {
	ofBackground(0);
	filter.draw();
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}