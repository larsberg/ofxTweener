//
//  Tweener.cpp
//
//  Created by lars berg on 10/22/14.
//

#include "Tweener.h"

namespace Tween
{

	Tween::Tween(float duration, float delay, EaseFunc ease) :
	duration(duration),
	delay(delay),
	startTime(ofGetElapsedTimeMillis() + delay),
	endTime(startTime + duration),
	progress(0),
	ease(ease),
	_onStart(NULL),
	_onUpdate(NULL),
	_onComplete(NULL),
	userPointer(NULL),
	state(TWEEN_STOPPED),
	persist(false),
	repeatCount(0),
	bReverse(false),
	eventArgs(shared_ptr<EventArgs>(new EventArgs(this))),
	startDelay(0)
	{}
	
	Tween* Tween::onStart(void(*onStartFunc)(void* tween))
	{
		_onStart = onStartFunc;
		return this;
	}
	
	Tween* Tween::onUpdate(void(*onUpdateFunc)(void* tween))
	{
		_onUpdate = onUpdateFunc;
		return this;
	}
	
	Tween* Tween::onComplete(void(*onCompleteFunc)(void* tween))
	{
		_onComplete = onCompleteFunc;
		return this;
	}
	
	Tween* Tween::setUserPtr(void* ptr)
	{
		userPointer = ptr;
		return this;
	}
	
	Tween* Tween::start()
	{
		startTime = ofGetElapsedTimeMillis() + delay + startDelay;
		endTime = startTime + duration;
		state = TWEEN_IDLE;
		startDelay = 0;
		
		return this;
	}
	
	Tween* Tween::stop()
	{
		state = TWEEN_STOPPED;
		if(_onComplete != NULL)	_onComplete((void*)this);

		for(auto& c: chains)
		{
			c->unpause();
		}
		
		return this;
	}
	
	Tween* Tween::delayStart(float t)
	{
		startDelay = t;
//		startTime += t;
//		endTime += t;
		return this;
	}
	
	Tween* Tween::unpause()
	{
		startTime = ofGetElapsedTimeMillis() - pauseTime;
		endTime = startTime + duration;
		state = TWEEN_IDLE;
		
		return this;
	}
	
	Tween* Tween::pause()
	{
		if(state != TWEEN_PAUSED)
		{
			pauseTime = ofGetElapsedTimeMillis() - startTime - delay;
			state = TWEEN_PAUSED;
		}
		
		return this;
	}
	
	Tween* Tween::addChain(shared_ptr<Tween> chainedTween)
	{
		chainedTween->pause();
		chains.push_back( chainedTween );
		return this;
	}
	
	Tween* Tween::setPersist(bool bPersist)
	{
		persist = bPersist;
		return this;
	}
	
	
	Tween* Tween::setRepeat(int count)
	{
		repeatCount = count;
		return this;
	}
	
	Tween* Tween::yoyo(bool bYoyo)
	{
		bReverse = bYoyo;
		return this;
	}
	
	
	void Tween::update(float t )
	{
		switch (state)
		{
			case TWEEN_IDLE:
				
				if(startTime <= t)
				{
					//set the state
					state = TWEEN_STARTED;
			
					// this is a virtual void that the TweenItem uses
					// to set the startValue to the value of our target
					startItem();

					//update the values
					progress = ofMap(t, startTime, endTime, 0, 1, true);
					updateValue();
					
					//callback
					if(_onUpdate != NULL)	_onUpdate((void*)this);
				}
				
				break;
				
			case TWEEN_STARTED:

				progress = ofMap(t, startTime, endTime, 0, 1, true);
				
				updateValue();
				
				if(_onUpdate != NULL)	_onUpdate((void*)this);
				
				ofNotifyEvent(onUpdateEvent, *eventArgs, this);
				
				if(endTime <= t)
				{
					if(repeatCount == 0)
					{
						stop();
					}
					else
					{
						if(bReverse)	reverse();
						
						if(repeatCount > 0)	repeatCount--;
						
						handleRepeat();
					}
					
				}
				
				break;
						
			default:
				break;
		}
	}
}