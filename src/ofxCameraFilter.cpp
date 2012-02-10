#include "ofxCameraFilter.h"

#include "CameraFilter.frag.h"

ofxCameraFilter::ofxCameraFilter()
:distortion(.08)
,distortionSize(1.12)
,aberrationAmount(.08)
,vignetteSharpness(8.)
,vignetteSize(.8)
,noiseAmount(.1) {
}

void ofxCameraFilter::setup(int width, int height) {
ofSetLogLevel(OF_LOG_VERBOSE);
	preblur.allocate(width, height);
	postblur.allocate(width, height);
	blur.setup(width, height, 16, .1, 1, .8);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, cameraFilterSource);
	shader.linkProgram();
}

void ofxCameraFilter::begin() {
	preblur.begin();
	ofClear(0, 255);
}

void ofxCameraFilter::end() {
	preblur.end();
	
	blur.begin();
	ofClear(0, 255);
	ofSetColor(255);
	preblur.draw(0, 0);
	blur.end();
	
	postblur.begin();
	ofClear(0, 255);
	ofSetColor(255);
	blur.draw();
	postblur.end();
}

void ofxCameraFilter::draw() {
	ofPushStyle();
	shader.begin();
	shader.setUniformTexture("preblur", preblur.getTextureReference(), 1);
	shader.setUniformTexture("postblur", postblur.getTextureReference(), 2);
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform2f("imageSize", preblur.getWidth(), preblur.getHeight());
	shader.setUniform1f("imageRadius", ofDist(0, 0, preblur.getWidth(), preblur.getHeight()) / 2.);
	shader.setUniform1f("distortion", distortion);
	shader.setUniform1f("distortionSize", distortionSize);
	shader.setUniform1f("aberrationAmount", aberrationAmount);
	shader.setUniform1f("vignetteSharpness", vignetteSharpness);
	shader.setUniform1f("vignetteSize", vignetteSize);
	shader.setUniform1f("noiseAmount", noiseAmount);
	ofSetColor(255);
	preblur.draw(0, 0);
	shader.end();
}

void ofxCameraFilter::setBlurScale(float scale) {
	blur.setScale(scale);
}

void ofxCameraFilter::setBlurRotation(float rotation) {
	blur.setRotation(rotation);
}

void ofxCameraFilter::setBlurBrightness(float brightness) {
	blur.setBrightness(brightness);
}

void ofxCameraFilter::setDistortion(float distortion) {
	this->distortion = distortion;
}

void ofxCameraFilter::setDistortionSize(float distortionSize) {
	this->distortionSize = distortionSize;
}

void ofxCameraFilter::setAberrationAmount(float aberrationAmount) {
	this->aberrationAmount = aberrationAmount;
}

void ofxCameraFilter::setNoiseAmount(float noiseAmount) {
	this->noiseAmount = noiseAmount;
}

void ofxCameraFilter::setVignetteSharpness(float vignetteSharpness) {
	this->vignetteSharpness = vignetteSharpness;
}

void ofxCameraFilter::setVignetteSize(float vignetteSize) {
	this->vignetteSize = vignetteSize;
}
