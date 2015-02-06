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
	t->loop(11);
	t->autoReverse();
	t->start();
	t->onStart(onStart, NULL);
	t->onComplete(onComplete, &count);

	//circling balls
	colors.resize(100);
	positions.resize(colors.size(), ofVec3f(-100,-100,0));
	
	float xSpacing = 40;
	float xOffset = .5 * positions.size() * xSpacing;
	for(int i=0; i<positions.size(); i++)
	{
		//space them out
		float speed = ofRandom(.5, 5);
		positions[i].z = i * xSpacing - xOffset;
		
		//circling using Sinusoidal easings
		manager.addTween(positions[i].x, 100.f, speed, 0, TWEEN::Ease::Sinusoidal::InOut )->autoReverse()->loop()->start();
		
		float initialDelay = speed * .5;
		manager.addTween(positions[i].y, 100.f, speed, 0, TWEEN::Ease::Sinusoidal::InOut )->autoReverse()->loop()->start( initialDelay );
		
		//sphere color
		ofColor randomColor( ofRandom(255), ofRandom(255), ofRandom(255), 255 );
		colors[i].set( ofRandom(255), ofRandom(255), ofRandom(255), 255 );
		
		float randomPeriod = ofRandom(.35, 2);
		
		manager.addTween( colors[i], randomColor, randomPeriod )->start()->loop()->autoReverse();
	}
	
	//bool
	manager.addTween(booleanValue, false, true, 2, 0, TWEEN::Ease::Linear )->autoReverse()->loop()->start();
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
	ofDrawBitmapString( ofToString("bool: ") + (booleanValue? "true" : "false" ), 20, 50);
	
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
