#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	float w = ofGetWidth(), h = ofGetHeight();
	
	ofVec2f p0( w - 200, 200 );
	ofVec2f p1( w - 200, h - 200 );
	ofVec2f p2( 200, h - 200 );
	ofVec2f p3( 200, 200);
	
	auto t0 = tweenManager.addTween( pos0, p0, p1, 1, 0, TWEEN::Ease::Elastic::Out );
	auto t1 = tweenManager.addTween( pos0, p1, p2, 1, 0, TWEEN::Ease::Elastic::Out );
	auto t2 = tweenManager.addTween( pos0, p2, p3, 1, 0, TWEEN::Ease::Elastic::Out );
	auto t3 = tweenManager.addTween( pos0, p3, p0, 1, 0, TWEEN::Ease::Elastic::Out );
	
	// chain each tween off another
	t0->addChain( t1 );
	t1->addChain( t2 );
	t2->addChain( t3 );
	t3->addChain( t0 );
	
	//loop the chain by preventing the manager from deleting them when they complete
	t0->autoDelete( false );
	t1->autoDelete( false );
	t2->autoDelete( false );
	t3->autoDelete( false );
	
	t0->start();
	
	
	//some other tweens
	color.set( ofRandom(1),ofRandom(1),ofRandom(1) );
	auto colorTween = tweenManager.addTween(color, ofFloatColor(ofRandom(1),ofRandom(1),ofRandom(1)), 1 );
	
	radius = 30;
	auto radiusTween = tweenManager.addTween(radius, 100.f, .5, 0, TWEEN::Ease::Quintic::InOut );
	
	colorTween->addChain( radiusTween )->autoReverse()->autoDelete( false )->start();
	radiusTween->addChain( colorTween )->autoReverse()->autoDelete( false );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor( color );
	ofDrawSphere( pos0, radius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
