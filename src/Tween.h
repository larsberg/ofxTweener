//
//  Tween.h
//  example
//
//  Created by lars berg on 2/4/15.
//
//

#pragma once

#include "Easings.h"
#include "TweenCallback.h"

namespace TWEEN
{
	static float (*tweenTimeFunc)() = ofGetElapsedTimef;
	
	static void setTimeFunc( float (*timeFunc)() )
	{
		tweenTimeFunc = timeFunc;
	}
	
	class Tween
	{
	public:
		
		Tween( float duration = 1, float delay = 0, EaseFunc ease = TWEEN::Ease::Linear);
		
		~Tween();
		
		Tween* clear();
		
		Tween* onStart(void(*onStartFunc)(void* ptr), void* user_ptr);
		
		Tween* onUpdate(void(*onUpdateFunc)(void* ptr), void* user_ptr);
		
		Tween* onComplete(void(*onCompleteFunc)(void* ptr), void* user_ptr);
		
		Tween* setEase(EaseFunc ease);
		
		Tween* delay( float delayAmount );
		
		Tween* start(float initialDelay=0);
		
		Tween* loop(int count = -1);
		
		Tween* autoReverse(bool reverseOnComplete = true);
		
		Tween* autoDelete(bool _deleteOnComplete);
		
		void update(float t);
		
		//chaining
		Tween* addChain(shared_ptr<Tween> chainedTween)
		{
			chains.push_back( chainedTween );
			return this;
		}
		
		//getters
		bool getDeleteOnComplete();
	
		bool getCompleted();
		
		//overwrite in TweenItem
		virtual void updateValue(float u)
		{}
		
		virtual void reverse()
		{}
		
	protected:
		TweenCallback _onStart;
		TweenCallback _onUpdate;
		TweenCallback _onComplete;
		
		list< shared_ptr<Tween> > chains;
		
		float startTime, endTime, _delay, _duration, elapsed;
		bool bStarted, bCompleted, bReverse, bPlaying, deleteOnComplete;
		
		EaseFunc easing;
		
		int repeat;
	};
}