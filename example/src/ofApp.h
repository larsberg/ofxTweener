#pragma once

#include "ofMain.h"
#include "Tweener.h"

class ofApp : public ofBaseApp
{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	static void onStart(void* ptr)
	{
		cout <<"on start! " << ofGetElapsedTimef() << endl;
	}
	
	static void onUpdate(void* ptr)
	{
		cout <<"on update: " << ofGetElapsedTimef() << endl;
	}
	
	static void onComplete(void* ptr)
	{
		cout <<"on complete: " << ofGetElapsedTimef() << endl;
		int& counter = (int&)(*ptr);
		counter++;
	}
	
	ofColor c;
	int count;
	ofEasyCam camera;
	
	vector<ofColor> colors;
	vector<ofVec3f> positions;

	ofFloatColor backgroundColor;
	
	TWEEN::Manager manager;
};
