#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	c.set(70, 255, 90);
	tweens.addTween(&c, c, ofColor(0, 255, 230, 255), 1000, 100, Tween::Ease::Bounce::Out)->yoyo()->loop();
	
	
	//	for(int i=0; i<100; i++)
	//	{
	//		tweens.addTween(&c, c, ofColor(ofRandom(250), ofRandom(250), ofRandom(250), 255), 100, 110 * i, Tween::Ease::Sinusoidal::InOut);//->yoyo()->loop();
	//	}
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(c);
	
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
