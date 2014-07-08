//
//  Tween.cpp
//
//  Created by lars berg on 7/6/14.
//

#include "Tween.h"


namespace Tween
{
	TweenManager::TweenManager()
	{
		ofAddListener(ofEvents().update, this, &TweenManager::update);
	}
	
	TweenManager::~TweenManager()
	{
		ofRemoveListener(ofEvents().update, this, &TweenManager::update);
		
		clear();
	}
	
	
	void TweenManager::clear()
	{
		clearTweenVector( tweensi );
		clearTweenVector( tweensf );
		clearTweenVector( tweensd );
		clearTweenVector( tweensVec2f );
		clearTweenVector( tweensVec3f );
		clearTweenVector( tweensVec4f );
		clearTweenVector( tweensColorf );
		clearTweenVector( tweensColor );
	}
	void TweenManager::update(ofEventArgs& e)
	{
		update( ofGetElapsedTimeMillis() );
	}
	
	void TweenManager::update( float t)
	{
		updateTweenVector( tweensi, t );
		updateTweenVector( tweensf, t );
		updateTweenVector( tweensd, t );
		updateTweenVector( tweensVec2f, t );
		updateTweenVector( tweensVec3f, t );
		updateTweenVector( tweensVec4f, t );
		updateTweenVector( tweensColor, t );
		updateTweenVector( tweensColorf, t );
	}
	
	
	//ADDING NEW TWEENS
	Tween<float>* TweenManager::addTween( float* target, float startVal, float endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensf, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<int>* TweenManager::addTween( int* target, int startVal, int endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensi, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<ofVec2f>* TweenManager::addTween( ofVec2f* target, ofVec2f startVal, ofVec2f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensVec2f, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<ofVec3f>* TweenManager::addTween( ofVec3f* target, ofVec3f startVal, ofVec3f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensVec3f, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<ofVec4f>* TweenManager::addTween( ofVec4f* target, ofVec4f startVal, ofVec4f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensVec4f, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<ofFloatColor>* TweenManager::addTween( ofFloatColor* target, ofFloatColor startVal, ofFloatColor endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensColorf, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween<ofColor>* TweenManager::addTween( ofColor* target, ofColor startVal, ofColor endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweensColor, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	
	
	Tween<int>* TweenManager::addTween(Tween<int>* t){	return addTween(tweensi, t);}
	Tween<float>* TweenManager::addTween(Tween<float>* t){	return addTween(tweensf, t);}
	Tween<double>* TweenManager::addTween(Tween<double>* t){	return addTween(tweensd, t);}
	Tween<ofVec2f>* TweenManager::addTween(Tween<ofVec2f>* t){	return addTween(tweensVec2f, t);}
	Tween<ofVec3f>* TweenManager::addTween(Tween<ofVec3f>* t){	return addTween(tweensVec3f, t);}
	Tween<ofVec4f>* TweenManager::addTween(Tween<ofVec4f>* t){	return addTween(tweensVec4f, t);}
	Tween<ofColor>* TweenManager::addTween(Tween<ofColor>* t){	return addTween(tweensColor, t);}
	Tween<ofFloatColor>* TweenManager::addTween(Tween<ofFloatColor>* t){	return addTween(tweensColorf, t);}
	
	void TweenManager::remove(Tween<int>* t)
	{
		removeFromVector(tweensi, t);
	}
	void TweenManager::remove(Tween<float>* t)
	{
		removeFromVector(tweensf, t);
	}
	void TweenManager::remove(Tween<double>* t)
	{
		removeFromVector(tweensd, t);
	}
	void TweenManager::remove(Tween<ofVec2f>* t)
	{
		removeFromVector(tweensVec2f, t);
	}
	void TweenManager::remove(Tween<ofVec3f>* t)
	{
		removeFromVector(tweensVec3f, t);
	}
	void TweenManager::remove(Tween<ofVec4f>* t)
	{
		removeFromVector(tweensVec4f, t);
	}
	void TweenManager::remove(Tween<ofColor>* t)
	{
		removeFromVector(tweensColor, t);
	}
	void TweenManager::remove(Tween<ofFloatColor>* t)
	{
		removeFromVector(tweensColorf, t);
	}
	
	
	
	Tween<int>* TweenManager::getTween(int& target)
	{
		return findTweenByTarget(tweensi, target);
	}
	Tween<float>* TweenManager::getTween(float& target)
	{
		return findTweenByTarget(tweensf, target);
	}
	Tween<double>* TweenManager::getTween(double& target)
	{
		return findTweenByTarget(tweensd, target);
	}
	Tween<ofVec2f>* TweenManager::getTween(ofVec2f& target)
	{
		return findTweenByTarget(tweensVec2f, target);
	}
	Tween<ofVec3f>* TweenManager::getTween(ofVec3f& target)
	{
		return findTweenByTarget(tweensVec3f, target);
	}
	Tween<ofVec4f>* TweenManager::getTween(ofVec4f& target)
	{
		return findTweenByTarget(tweensVec4f, target);
	}
	Tween<ofColor>* TweenManager::getTween(ofColor& target)
	{
		return findTweenByTarget(tweensColor, target);
	}
	Tween<ofFloatColor>* TweenManager::getTween(ofFloatColor& target)
	{
		return findTweenByTarget(tweensColorf, target);
	}

}