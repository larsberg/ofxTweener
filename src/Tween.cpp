//
//  Tween.cpp
//  example
//
//  Created by lars berg on 2/4/15.
//
//

#include "Tween.h"


namespace TWEEN
{
	
	Tween::Tween( float duration, float delay, EaseFunc ease) :
	easing( ease ),
	bStarted( false ),
	bCompleted( false ),
	bReverse( false ),
	bPlaying( false ),
	deleteOnComplete(true),
	elapsed( 0 ),
	repeat( 0 ),
	_duration( duration ),
	_delay( delay )
	{}
	
	Tween::~Tween()
	{}
	
	Tween* Tween::clear()
	{
		_onStart.clear();
		_onUpdate.clear();
		_onComplete.clear();
		chains.clear();
		
		return this;
	}
	
	Tween* Tween::onStart(void(*onStartFunc)(void* ptr), void* user_ptr)
	{
		_onStart.set(onStartFunc, user_ptr);
		
		return this;
	}
	
	Tween* Tween::onUpdate(void(*onUpdateFunc)(void* ptr), void* user_ptr)
	{
		_onUpdate.set(onUpdateFunc, user_ptr);
		
		return this;
	}
	
	Tween* Tween::onComplete(void(*onCompleteFunc)(void* ptr), void* user_ptr)
	{
		_onComplete.set(onCompleteFunc, user_ptr);
		
		return this;
	}
	
	Tween* Tween::setEase(EaseFunc ease)
	{
		easing = ease;
		
		return this;
	}
	
	Tween* Tween::autoDelete(bool _deleteOnComplete)
	{
		deleteOnComplete = _deleteOnComplete;
		
		return this;
	}
	
	Tween* Tween::delay( float delayAmount )
	{
		startTime -= _delay;
		_delay = delayAmount;
		startTime += _delay;
		endTime = startTime + _duration;
		
		return this;
	}
	
	Tween* Tween::loop(int count)
	{
		repeat = count;
		
		return this;
	}
	
	Tween* Tween::autoReverse(bool reverseOnComplete)
	{
		bReverse = reverseOnComplete;
		
		return this;
	}
	
	
	bool Tween::getDeleteOnComplete()
	{
		return deleteOnComplete;
	}
	
	bool Tween::getCompleted()
	{
		return bCompleted;
	}
	
	Tween* Tween::start(float initialDelay)
	{
		bPlaying = true;
		bCompleted = false;
		
		startTime = tweenTimeFunc() + _delay + initialDelay;
		endTime = startTime + _duration;
		
		cout << "tweenTimeFunc(): " << tweenTimeFunc() << endl;
		cout << "startTime: " << startTime << endl;
		cout << "endTime: " << endTime << endl;
		
		return this;
	}
	
	void Tween::update(float t)
	{
		//if it's not ready return
		if ( !bPlaying || t < startTime )
		{
			return;
		}
		
		//on start callback
		if(!bStarted)
		{
			bStarted = true;
			bCompleted = false;
			_onStart.call();
		}
		
		//progress
		elapsed = (t - startTime) / _duration;
		
		//update
		if(!bCompleted)
		{
			if(elapsed >= 1)
			{
				//complete it
				updateValue( 1 );
				bCompleted = true;
				
				//loop
				if(repeat != 0)
				{
					if(repeat > 0) repeat--;
					
					bStarted = bCompleted = false;
					startTime = endTime + _delay;
					endTime = startTime + _duration;
				}
				
				//autoReverse
				if(bReverse)
				{
					reverse();
				}
				
				//start any chains
				for(auto& c: chains)
				{
					cout << "c->start();" << endl;
					c->start();
				}
				
				//complete callback
				_onComplete.call();
			}
			else
			{
				//update it
				updateValue( easing(elapsed) );
				_onUpdate.call();
			}
		}
	}
}