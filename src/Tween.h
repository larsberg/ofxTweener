//
//  Tween.h
//
//  Created by lars berg on 7/6/14.
//

#pragma once

#include "ofMain.h"
#include "Easings.h"

#include <iostream>     // std::cout

namespace Tween
{
	enum TweenState
	{
		TWEEN_STARTED = 0,
		TWEEN_STOPPED = 1,
		TWEEN_PAUSED = 2,
		TWEEN_IDLE = 3
	};
    
    class TweenManager;
	
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
		
		virtual void updateValue(float start_t, float end_t, float t)
		{}
        
        virtual void reachedEnd()
		{}
        
        void added(float currentTime)
		{
            addedTime = currentTime;
            startTime = currentTime + delay;
            endTime = startTime + duration;
        }
		
	public:
		Tween():
		ease(Ease::Linear)
		{}
		
		void (*onStart)(void* _tween);
		void (*onUpdate)(void* _tween);
		void (*onComplete)(void* _tween);
		
		bool bKill;
		float (*ease)(float);
		
		//this can be handy in custom callbacks
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
					}
					break;
					
				case TWEEN_IDLE:
					
					//START the tween if it's time
					if(startTime <= t)
					{
						state = TWEEN_STARTED;
						
						updateValue(startTime, endTime, t);
						
						if(onStart != NULL)	onStart(this);
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
			startTime = bLoop ? endTime : ofGetElapsedTimeMillis();
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
        }
        
        void reachedEnd(){
            progress = 1;
            value = endVal;
            if(target != NULL)	*target = value;
            
            state = TWEEN_STOPPED;
            
            //callbacks
            if(onComplete != NULL)	onComplete(this);
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
		
		T getValue()
		{
			return value;
		}
	};
	
	template<class T>
	class ControlPoint
	{
	public:

		ControlPoint(float _u, T _value, float (*_ease)(float)):
		u(_u), value(_value), ease(_ease)
		{}
		
		
		static bool compareControlPoints( ControlPoint<T> a, ControlPoint<T> b)
		{
			return a.u < b.u;
		}
		
		float u;
		T value;
		float (*ease)(float);
	};
    
	template<class T>
    class TweenCurve : public Tween
	{
        friend TweenManager;
		
	public:
		TweenCurve(T* _target, T _startVal, T _endVal, float _delay, float _duration, float(*_ease)(float)=Ease::Linear)
		{
            target = _target;
            startVal = _startVal;
            endVal = _endVal;
			
			addPoint(0, startVal);
			addPoint(1, startVal);
			
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
			ease = _ease;
        }
		
		void addPoint(float u, T value)
		{
			controlPoints.push_back(ControlPoint<T>(u, value, ease));
			sort(controlPoints.begin(), controlPoints.end(), ControlPoint<T>::compareControlPoints);
		}
		
		void addPoint(float u, T value, float(*_ease)(float))
		{
			controlPoints.push_back(ControlPoint<T>(u, value, _ease));
			sort(controlPoints.begin(), controlPoints.end(), ControlPoint<T>::compareControlPoints);
		}
		
		T sample(float _u)
		{
			
//			T sampleValue = lerp(startVal, endVal, ease(u));
			
			//find our lower and upper values
			ControlPoint<T>* lowVal = &controlPoints[0];
			ControlPoint<T>* hiVal = &controlPoints[0];
			
			for(int i=0; i<controlPoints.size()-1; i++)
			{
				if(controlPoints[i].u <= _u)
				{
					lowVal = &controlPoints[i];
				}
				if(controlPoints[i+1].u >= _u)
				{
					hiVal = &controlPoints[i+1];
					break;
				}
			}
			
			//find a mapped sample and lerp our out value
			float sampleVal = ofMap(_u, lowVal->u, hiVal->u, 0.f, 1.f, true );
			return lerp(lowVal->value, hiVal->value, lowVal->ease(sampleVal));
		}
		
	protected:
		vector< ControlPoint<T> > controlPoints;
		
		T startVal, endVal, value;
		T* target;
        
        
        void reachedEnd()
		{
            progress = 1;
            value = endVal;
            if(target != NULL)	*target = value;
            
            state = TWEEN_STOPPED;
            
            //callbacks
            if(onComplete != NULL)	onComplete(this);
            if(bYoYo)	swap(startVal, endVal);
            if(bLoop)	restart();
        }
		
		void updateValue(float start_t, float end_t, float t)
		{
			progress = ofMap(t, start_t, end_t, 0, 1, true);
			value = sample(progress);
			
			if(target != NULL)	*target = value;

		}
        
    public:
		~TweenCurve()
		{}
		
        void* getTarget()
        {
            return (void*)target;
        }
		
		T getValue()
		{
			return value;
		}
	};
	
	
	/**
	 *
	 * Tween manger for adding, updating and removing tweens
	 *
	 */
	class TweenManager
	{
	public:
		TweenManager();
		
		~TweenManager();
		
		void clear();
		
		void update(ofEventArgs& e);
		
		void update( float t = ofGetElapsedTimeMillis() );
        
        template<class T>
        static Tween* makeTween( T* target, T startVal, T endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear ){
			auto t = new TweenItem<T>(target, startVal, endVal, delay, duration);
			t->setEase(ease);
            return t;
        };
		
		//adding existing tweens
		Tween* addTween(Tween* t){
            tweens.push_back(t);
            t->added(ofGetElapsedTimeMillis());
            return t;
        }
        
        template<class T>
        Tween* addTween( T* target, T startVal, T endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear ){
            Tween* t = TweenManager::makeTween(target, startVal, endVal, duration, delay, ease);
            return addTween(t);
        }
        
        template<class T>
        Tween* addTween( T* target, T startVal, T endVal, float duration, float (*ease)(float) ){
            Tween* t = TweenManager::makeTween(target, startVal, endVal, duration, 0, ease);
            return addTween(t);
        }
		
		//removing tweens
		void remove(Tween* t, bool bDelete = true);
		
		//getting tweens by target
		Tween* getTween(void* target);
		
	private:
		
		// tween vectors
		vector< Tween* > tweens;
	};
}