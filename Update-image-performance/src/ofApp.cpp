#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	oriImg.loadImage("lena.jpg");
	newImg.setFromPixels(oriImg.getPixels());
	repeatNum = 100;
	costTime = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	oriImg.draw(0, 0);
	newImg.draw(oriImg.getWidth() + 10, 0);

	string debugStr = "";
	debugStr += "FPS: " + ofToString(ofGetFrameRate()) + '\n';
	debugStr += "cost time: " + ofToString(costTime) + '\n';
	debugStr += "repeat number(key 3/4): " + ofToString(repeatNum);
	ofDrawBitmapStringHighlight(debugStr, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		int startTime = ofGetElapsedTimeMillis();
		for (int k = 0; k < repeatNum; k++) {
			for (int y = 0; y < oriImg.getHeight(); y++) {
				for (int x = 0; x < newImg.getWidth(); x++) {
					newImg.setColor(x, y, ofColor(newImg.getColor(x, y).r));
				}
			}
		}

		newImg.update();

		costTime = ofGetElapsedTimeMillis() - startTime;

		ofLogNotice(ofToString(costTime));
	}

	if (key == '2') {
		int startTime = ofGetElapsedTimeMillis();

		unsigned char * p = newImg.getPixels().getData();

		for (int k = 0; k < repeatNum; k++) {
			for (int y = 0; y < oriImg.getHeight(); y++) {
				for (int x = 0; x < newImg.getWidth(); x++) {
					int ind = x + y*newImg.getWidth();
					p[ind * 3]     = p[ind * 3];	// r
					p[ind * 3 + 1] = p[ind * 3];	// g
					p[ind * 3 + 2] = p[ind * 3];	// b
				}
			}
		}
		newImg.update();

		costTime = ofGetElapsedTimeMillis() - startTime;

		ofLogNotice(ofToString(costTime));
	}

	if (key == '3') {
		repeatNum -= 10;
		if (repeatNum < 0) repeatNum = 10;
	}
	if (key == '4') {
		repeatNum += 10;
	}
}