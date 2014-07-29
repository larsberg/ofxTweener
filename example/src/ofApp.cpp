#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//background
	c.set(70, 255, 90);
	auto t = tweens.addTween(&c, ofColor(0,0,0, 5), ofColor(255, 5), 3000, 100, Tween::Ease::Bounce::Out)->yoyo()->loop();
	t->setOnComplete(onComplete);
	
	//balls
	colors.resize(20);
	positions.resize(colors.size());
	
	for(int i=0; i<positions.size(); i++)
	{
		//position
		float speed = ofRandom(200, 1000);
		positions[i].x = i * 80 - (positions.size() * .5 * 80.);
		tweens.addTween(&positions[i].y, -200.f, 200.f, speed, 0, Tween::Ease::Sinusoidal::InOut)->yoyo()->loop();
		tweens.addTween(&positions[i].z, -200.f, 200.f, speed, speed * .5, Tween::Ease::Sinusoidal::InOut)->yoyo()->loop();
		
		//color
		tweens.addTween(&colors[i],
						ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)),
						ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)),
						ofRandom(400, 4000))->loop();
	}

	ofSetBackgroundAuto(false);
	ofSetDepthTest(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	glClear( GL_DEPTH_BUFFER_BIT );
	ofBackgroundGradient(c, ofFloatColor(0,0,0,.1));
	
	camera.begin();
	
	for(int i=0; i<positions.size(); i++)
	{
		ofSetColor(colors[i]);
		ofDrawSphere(positions[i], 15);
	}
	
	camera.end();
	
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
