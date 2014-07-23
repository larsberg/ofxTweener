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
		clearTweenVector( tweens );
	}
	void TweenManager::update(ofEventArgs& e)
	{
		update( ofGetElapsedTimeMillis() );
	}
	
	void TweenManager::update( float t)
	{
		updateTweenVector( tweens, t );
	}
	
	
	//ADDING NEW TWEENS
	Tween* TweenManager::addTween( float* target, float startVal, float endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( int* target, int startVal, int endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( ofVec2f* target, ofVec2f startVal, ofVec2f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( ofVec3f* target, ofVec3f startVal, ofVec3f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( ofVec4f* target, ofVec4f startVal, ofVec4f endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( ofFloatColor* target, ofFloatColor startVal, ofFloatColor endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	Tween* TweenManager::addTween( ofColor* target, ofColor startVal, ofColor endVal, float duration, float delay, float (*ease)(float))
	{
		return addTween( tweens, target, startVal, endVal, ofGetElapsedTimeMillis()+delay, ofGetElapsedTimeMillis()+delay+duration, ease);
	}
	
	
	Tween* TweenManager::addTween(Tween* t){	return addTween(tweens, t);}
	
	void TweenManager::remove(Tween* t)
	{
		removeFromVector(tweens, t);
	}
	
	
	
	Tween* TweenManager::getTween(void* target)
	{
		return findTweenByTarget(tweens, target);
	}

}