#pragma once

#define stringify(text) # text

string cameraFilterSource = stringify(
uniform float distortion;
uniform float distortionSize;
uniform float aberrationAmount;
uniform float vignetteSharpness;
uniform float vignetteSize;
uniform float noiseAmount;
uniform vec2 imageSize;
uniform float imageRadius;

// configurable
const int aberrationSteps = 32;

// setup per-frame
uniform float time;
uniform sampler2DRect preblur;
uniform sampler2DRect postblur;

// pre-computed
const float HALF_PI = 3.1415926 / 2.;
const float aberrationWeight = 2. / float(aberrationSteps);

float GetHueComponent(float hue) {
	if (hue < 0.) {
		hue += 1.;
	} else if (hue > 1.) {
		hue -= 1.;
	}
	if ((6. * hue) < 1.) {
		return 6. * hue;
	} else if ((2. * hue) < 1.) {
		return 1.;
	} else if ((3. * hue) < 2.) {
		return ((2. / 3.) - hue) * 6.;
	} else {
		return 0.;
	}
}

vec3 HueToRGB(float hue) {
	return vec3(
		GetHueComponent(hue - (1./3.)),
		GetHueComponent(hue),
		GetHueComponent(hue + (1./3.))
	);
}

float rand(vec2 coord){
    return fract(sin(dot(coord, vec2(12.9898,78.233))) * 43758.5453);
}

void main(void) {
	vec2 tc = gl_TexCoord[0].st;

	vec2 imageCenter = imageSize / 2.;
	vec2 P = (tc / imageCenter) - 1.; // to normalized image coordinates
	P /= distortionSize;
	vec2 Pp = P / (1. - distortion * dot(P, P));
	P *= distortionSize;
	tc = (Pp + 1.) * imageCenter;  // back to pixel coordinates

	vec2 fromCenter = tc - imageCenter;
	float radius = sqrt(dot(fromCenter, fromCenter));
	float normalizedRadius = radius / imageRadius;
	
	vec3 aberration = vec3(0., 0., 0.);
	float aberrationScale = aberrationAmount / float(aberrationSteps);
	for(int i = 0; i < aberrationSteps; i++) {
		vec2 curCoord = imageCenter + fromCenter * (1. - aberrationScale * float(i));
		vec3 curColor = texture2DRect(postblur, curCoord).rgb;
		float curHue = float(i) / float(aberrationSteps);
		aberration += curColor * HueToRGB(1. - curHue); // 1. - switches the red/blue
	}
	aberration *= aberrationWeight;

	float vignette = sin(clamp((normalizedRadius - vignetteSize) * vignetteSharpness, -HALF_PI, HALF_PI));
	vignette = .5 - (vignette * .5); // scale from -1 to 1 onto 1 to 0

	float noise = rand((tc / imageSize) * time) * noiseAmount;
	
	vec3 original = texture2DRect(preblur, tc).rgb;

	vec3 finalColor = ((original + aberration) * vignette) + noise;
	gl_FragColor = vec4(finalColor, 1.);
}
);