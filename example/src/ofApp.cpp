#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

	ofSetBackgroundAuto(false);
	ofSetDepthTest(true);
	
	//background
	c.set(70, 255, 90);
	auto t = tweenManager.addTween( c, ofColor(155,5), 3000, 100, Tween::Ease::Bounce::Out);
	
	t->addCompleteListener(this, &ofApp::onCompleteEvent);
	
	//circling balls
	colors.resize(100);
	positions.resize(colors.size(), ofVec3f(0,-200,-200));
	
	for(int i=0; i<positions.size(); i++)
	{
		//position
		float speed = ofRandom(200, 2000);
		positions[i].x = i * 80 - (positions.size() * .5 * 80.);
//		tweenManager.addTween( positions[i].y, 200.f, speed, 0, Tween::Ease::Sinusoidal::InOut);
		tweenManager.addTween(&positions[i].y, 200.f, speed, 0, Tween::Ease::Sinusoidal::InOut)->yoyo()->loop();
		tweenManager.addTween(&positions[i].z, 200.f, speed, 0, Tween::Ease::Sinusoidal::InOut)->yoyo()->loop()->delayStart(speed * .5);
		
		//color
		colors[i].set(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255), 255);
		tweenManager.addTween(&colors[i],
						ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255), 255),
						ofRandom(400, 2000))->setRepeat()->yoyo();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	glClear( GL_DEPTH_BUFFER_BIT );
	ofBackgroundGradient(ofFloatColor(0.1,0.11,0.13,.05), ofFloatColor(0,0,0,.05));
	
	camera.begin();
	
	ofEnableDepthTest();
	
	for(int i=0; i<positions.size(); i++)
	{
		ofSetColor(colors[i]);
		ofDrawSphere(positions[i], 35);
	}
	
	camera.end();
	
	
	//draw tween curve
	ofPushMatrix();
	ofTranslate(0, 50);
	
	//	background rectangle
	ofSetColor(0, 0, 0, 30);
	ofDrawRectangle(0,-50,400,100);
	
	ofPopMatrix();
	
}

//TWEEN EVENTS


void ofApp::onComplete(void* tween)
{
	cout << "tween has completed!" << endl;
}


void ofApp::onUpdateFloatCurve(void* tween)
{
	if(ofGetElapsedTimef() < 10)
	{
//		auto t = (Tween::TweenCurve<float>*)tween;
//		cout << "TweenCurve is updating and it's value is " << t->getValue() << endl;
	}
}

////ofEvent callbacks
//void onCompleteEvent(Tween::TweenEventArgs& e)
//{
//	cout << "ofEvent on complete" << endl;
//}

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
