//
//  Tween.h
//
//  Created by lars berg on 7/6/14.
//

#pragma once

#include "ofMain.h"
#include "Easings.h"
#include "TweenEventArgs.h"

namespace Tween
{
    class TweenManager;
    
	enum TweenState
	{
		TWEEN_STARTED = 0,
		TWEEN_STOPPED = 1,
		TWEEN_PAUSED = 2,
		TWEEN_IDLE = 3
	};
	
	template<class T>
	static T lerp(T a, T b, float k)
	{
		//return	a + k * (b - a);//this was giving an error for ofColor...
		return a * (1. - k) + b * k;
	}
    
    class Tween{
		friend TweenManager;
    private:
        float startTime, endTime;
	protected:
        float duration, delay, addedTime;
		float progress;
		bool bLoop, bYoYo, bFinished;
		
		TweenState state;
        vector<Tween*> _chainedTweens;
		
		virtual void updateValue(float start_t, float end_t, float t){}
        
        virtual void reachedEnd(){}
        
        void added(float currentTime){
            addedTime = currentTime;
            startTime = currentTime + delay;
            endTime = startTime + duration;
        }
		
	public:
		void (*onStart)(void* _tween);
		void (*onUpdate)(void* _tween);
		void (*onComplete)(void* _tween);
        ofEvent<TweenEventArgs> onCompleteEvent;
        ofEvent<TweenEventArgs> onUpdateEvent;
        ofEvent<TweenEventArgs> onStartEvent;
        TweenEventArgs* eventArgs;
		
		bool bKill;
		float (*ease)(float);
		
		//this can be handy for custom callbacks
		void* userPointer;
        
		void update(float t)
		{
            bFinished = false;
			//handle states
			switch (state)
			{
				case TWEEN_STARTED:
					if(t >= endTime)
					{
						//STOP it
                        reachedEnd();
                        bFinished = true;
					}
					else
					{
						//UPDATE it
						updateValue(startTime, endTime, t);
						
						//on update callback
						if(onUpdate != NULL)	onUpdate(this);
                        ofNotifyEvent(onUpdateEvent, *eventArgs, this);
					}
					break;
					
				case TWEEN_IDLE:
					
					//START the tween if it's time
					if(startTime <= t)
					{
						state = TWEEN_STARTED;
                        updateValue(startTime, endTime, t);
						
						if(onStart != NULL)	onStart(this);
                        ofNotifyEvent(onStartEvent, *eventArgs, this);
					}
					
					break;
					
				case TWEEN_STOPPED:
					//do nothing
					break;
					
				case TWEEN_PAUSED:
					//do nothing
					break;
					
				default:
					break;
			}
		}
		
		Tween* pause()
		{
			state = TWEEN_PAUSED;
			return this;
		}
		
		Tween* play()
		{
			if (state == TWEEN_PAUSED)
			{
				float duration = endTime - startTime;
				startTime = ofGetElapsedTimeMillis() - progress * duration;
				endTime = startTime + duration;
				
				state = TWEEN_STARTED;
			}
			
			return this;
		}
		
		Tween* restart()
		{
			float duration = endTime - startTime;
			startTime = ofGetElapsedTimeMillis();
			endTime = startTime + duration;
			
			state = TWEEN_IDLE;
			
			return this;
		}
		
		Tween* loop(bool _bLoop=true)
		{
			bLoop = _bLoop;
			return this;
		}
		
		Tween* yoyo(bool _bYoYo=true)
		{
			bYoYo = _bYoYo;
			return this;
		}
		
		Tween* setEase(float (*e)(float))
		{
			ease = e;
			return this;
		}
        
        virtual void* getTarget(){return NULL;}
		
		TweenState getState()
		{
			return state;
		}
		
		Tween* setOnUpdate(void (*_onUpdate)(void* _tween))
		{
			onUpdate = _onUpdate;
			return this;
		}
		
		Tween* setOnStart(void (*_onStart)(void* _tween))
		{
			onStart = _onStart;
			return this;
		}
		
		Tween* setOnComplete(void (*_onComplete)(void* _tween))
		{
			onComplete = _onComplete;
			return this;
		}
        
        template <typename ArgumentsType, class ListenerClass>
        Tween* addUpdateListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP){
            ofAddListener(onUpdateEvent, listener, listenerMethod, prio);
            return this;
        }
        
        template <typename ArgumentsType, class ListenerClass>
        Tween* addStartListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP){
            ofAddListener(onStartEvent, listener, listenerMethod, prio);
            return this;
        }
        
        template <typename ArgumentsType, class ListenerClass>
        Tween* addCompleteListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP){
            ofAddListener(onCompleteEvent, listener, listenerMethod, prio);
            return this;
        }
        
        Tween* addChained(Tween* tween){
            _chainedTweens.push_back(tween);
            return this;
        }
        
        Tween* clearChained(){
            _chainedTweens.clear();
            return this;
        }
    };
    
	template<class T>
    class TweenItem : public Tween
	{
        friend TweenManager;
	protected:
		T startVal, endVal, value;
		T* target;
        
		TweenItem(T* _target, T _startVal, T _endVal, float _delay, float _duration)
		{
            target = _target;
            startVal = _startVal;
            endVal = _endVal;
            delay = _delay;
            duration = _duration;
            onStart = NULL;
            onUpdate = NULL;
            onComplete = NULL;
            state = TWEEN_IDLE;
            progress = 0;
            bLoop = false;
            bYoYo = false;
            bKill = true;
            bFinished = false;
            eventArgs = new TweenEventArgs();
        }
        
        void reachedEnd(){
            progress = 1;
            value = endVal;
            if(target != NULL)	*target = value;
            
            state = TWEEN_STOPPED;
            
            //callbacks
            if(onComplete != NULL)	onComplete(this);
            ofNotifyEvent(onCompleteEvent, *eventArgs, this);
            if(bYoYo)	swap(startVal, endVal);
            if(bLoop)	restart();
        }
		
		void updateValue(float start_t, float end_t, float t)
		{
			progress = ofMap(t, start_t, end_t, 0, 1, true);
			value = lerp(startVal, endVal, ease(progress));
			if(target != NULL)	*target = value;
		}
        
    public:
		~TweenItem()
		{}
		
        void* getTarget()
        {
            return (void*)target;
        }
	};
}

#include "TweenManager.h"