#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	TWEEN::setTimeFunc( ofGetElapsedTimef );
	
	ofSetBackgroundAuto(false);
	ofSetDepthTest(true);
	
	//background
	c.set(0, 255, 255, 5);
	auto t = manager.addTween( c, ofColor(200, 30, 0, 5), 3, 1);
	t->loop(3);
	t->autoReverse();
	t->start();
	t->onStart(onStart, NULL);
	t->onComplete(onComplete, &count);

	//circling balls
	colors.resize(100);
	positions.resize(colors.size(), ofVec3f(0,-200,-200));
	
	for(int i=0; i<positions.size(); i++)
	{
		//space them horizontally
		float speed = ofRandom(.5, 5);
		positions[i].x = i * 80 - (positions.size() * .5 * 80.);
		
		//circling positions using Sinusoidal easings
		manager.addTween(positions[i].y, 200.f, speed, 0, TWEEN::Ease::Sinusoidal::InOut )->autoReverse()->loop()->start();
		manager.addTween(positions[i].z, 200.f, speed, 0, TWEEN::Ease::Sinusoidal::InOut )->autoReverse()->loop()->start(speed * .5);//you can set an initial delay
		
		//sphere color
		colors[i].set(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255), 255);
		ofColor randomColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255), 255);
		float randomPeriod = ofRandom(.35, 2);
		manager.addTween( colors[i], randomColor, randomPeriod )->start()->loop()->autoReverse();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{}

//--------------------------------------------------------------
void ofApp::draw()
{
	glClear( GL_DEPTH_BUFFER_BIT );
	ofBackgroundGradient(c, ofFloatColor(0,0,0,.15));
	
	camera.begin();
	
	ofEnableDepthTest();
	
	for(int i=0; i<positions.size(); i++)
	{
		ofSetColor(colors[i]);
		ofDrawSphere(positions[i], 35);
	}
	
	camera.end();
	
	ofDisableDepthTest();
	
	ofSetColor(255);
	ofDrawBitmapString( "background onComplete count: " + ofToString(count), 20, 30);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
	
}
