#pragma once

#include "ofMain.h"
#include "ofxBlur.h"

class ofxCameraFilter {
protected:
	ofFbo preblur, postblur;
	ofxBlur blur;
	ofShader shader;
	
	float distortion, distortionSize;
	float aberrationAmount;
	float noiseAmount;
	float vignetteSharpness, vignetteSize;
public:
	ofxCameraFilter();
	void setup(int width, int height);
	void begin();
	void end();
	void draw();
	
	void setBlurScale(float scale);
	void setBlurRotation(float rotation);
	void setBlurBrightness(float brightness);
	void setDistortion(float distortion);
	void setDistortionSize(float distortionSize);
	void setAberrationAmount(float aberrationAmount);
	void setNoiseAmount(float noiseAmount);
	void setVignetteSharpness(float vignetteSharpness);
	void setVignetteSize(float vignetteSize);
};