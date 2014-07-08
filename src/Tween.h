//
//  Tween.h
//
//  Created by lars berg on 7/6/14.
//

#pragma once

#include "ofMain.h"
#include "Easings.h"

namespace Tween
{
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
	
	template<class T>
	class Tween
	{
	public:
		Tween(T* _target, T _startVal, T _endVal, float _startTime, float _endTime):
		target(_target),
		startVal(_startVal),
		endVal(_endVal),
		startTime(_startTime),
		endTime(_endTime),
		onStart(NULL),
		onUpdate(NULL),
		onComplete(NULL),
		state(TWEEN_IDLE),
		progress(0),
		bLoop(false),
		bYoYo(false),
		bKill(true)
		{}
		
		~Tween()
		{}
		
		void update(float t)
		{
			//handle states
			switch (state)
			{
				case TWEEN_STARTED:
					if(t >= endTime)
					{
						//STOP it
						progress = 1;
						value = endVal;
						if(target != NULL)	*target = value;
						
						state = TWEEN_STOPPED;
						
						//callbacks
						if(onComplete != NULL)	onComplete(this, value);
						if(bYoYo)	swap(startVal, endVal);
						if(bLoop)	restart();
					}
					else
					{
						//UPDATE it
						updateValue(t);
						
						//on update callback
						if(onUpdate != NULL)	onUpdate(this, value);
					}
					break;
					
				case TWEEN_IDLE:
					
					//START the tween if it's time
					if(startTime <= t)
					{
						state = TWEEN_STARTED;
						
						updateValue(t);
						
						if(onStart != NULL)	onStart(this, value);
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
		
		void updateValue(float t)
		{
			progress = ofMap(t, startTime, endTime, 0, 1, true);
			value = lerp(startVal, endVal, ease(progress));
			if(target != NULL)	*target = value;
		}
		
		Tween<T>* pause()
		{
			state = TWEEN_PAUSED;
			return this;
		}
		
		Tween<T>* play()
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
		
		Tween<T>* restart()
		{
			float duration = endTime - startTime;
			startTime = ofGetElapsedTimeMillis();
			endTime = startTime + duration;
			
			state = TWEEN_IDLE;
			
			return this;
		}
		
		Tween<T>* loop(bool _bLoop=true)
		{
			bLoop = _bLoop;
			return this;
		}
		
		Tween<T>* yoyo(bool _bYoYo=true)
		{
			bYoYo = _bYoYo;
			return this;
		}
		
		Tween<T>* setEase(float (*e)(float))
		{
			ease = e;
			return this;
		}
		
		T* getTarget()
		{
			return target;
		}
		
		TweenState getState()
		{
			return state;
		}
		
	public:
		void (*onStart)(void* _tween, T _value);
		void (*onUpdate)(void* _tween, T _value);
		void (*onComplete)(void* _tween, T _value);
		
		bool bKill;
		float (*ease)(float);
		
		//this can be handy for custom callbacks
		void* userPointer;
		
	protected:
		float startTime, endTime, progress;
		T startVal, endVal, value;
		T* target;
		bool bLoop, bYoYo;
		
		TweenState state;
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
		
		//creating new tweens
		Tween<float>* addTween( float* target, float startVal, float endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<int>* addTween( int* target, int startVal, int endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<ofVec2f>* addTween( ofVec2f* target, ofVec2f startVal, ofVec2f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<ofVec3f>* addTween( ofVec3f* target, ofVec3f startVal, ofVec3f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<ofVec4f>* addTween( ofVec4f* target, ofVec4f startVal, ofVec4f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<ofFloatColor>* addTween( ofFloatColor* target, ofFloatColor startVal, ofFloatColor endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween<ofColor>* addTween( ofColor* target, ofColor startVal, ofColor endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		
		//adding existing tweens
		Tween<int>* addTween(Tween<int>* t);
		Tween<float>* addTween(Tween<float>* t);
		Tween<double>* addTween(Tween<double>* t);
		Tween<ofVec2f>* addTween(Tween<ofVec2f>* t);
		Tween<ofVec3f>* addTween(Tween<ofVec3f>* t);
		Tween<ofVec4f>* addTween(Tween<ofVec4f>* t);
		Tween<ofColor>* addTween(Tween<ofColor>* t);
		Tween<ofFloatColor>* addTween(Tween<ofFloatColor>* t);
		
		//removing tweens
		void remove(Tween<int>* t);
		void remove(Tween<float>* t);
		void remove(Tween<double>* t);
		void remove(Tween<ofVec2f>* t);
		void remove(Tween<ofVec3f>* t);
		void remove(Tween<ofVec4f>* t);
		void remove(Tween<ofColor>* t);
		void remove(Tween<ofFloatColor>* t);
		
		//getting tweens by target
		Tween<int>* getTween(int& target);
		Tween<float>* getTween(float& target);
		Tween<double>* getTween(double& target);
		Tween<ofVec2f>* getTween(ofVec2f& target);
		Tween<ofVec3f>* getTween(ofVec3f& target);
		Tween<ofVec4f>* getTween(ofVec4f& target);
		Tween<ofColor>* getTween(ofColor& target);
		Tween<ofFloatColor>* getTween(ofFloatColor& target);
		
	private:
		
		//tween vectors
		template <class T>
		void clearTweenVector(vector<T*>& tweenVector)
		{
			for(auto &it: tweenVector)
			{
				delete it;
			}
			tweenVector.clear();
		}
		
		template <class T>
		void updateTweenVector(vector<T*>& v, float time)
		{
			if(v.size() == 0)	return;
			
			//we want the most recent tweens to superceed any previous so we need to loop twice
			//first to set the values
			vector<int> dead;
			int i=0;
			for(auto &it: v)
			{
				it->update(time);
				
				if(it->getState() == TWEEN_STOPPED && it->bKill)
				{
					dead.push_back(i);
				}
				
				i++;
			}
			
			//bury the dead
			for(int i=dead.size()-1; i>=0; i--)
			{
				delete v[dead[i]];
				v.erase(v.begin() + dead[i]);
			}
		}
		
		//adding tweens
		template <class T>
		Tween<T>* addTween(vector< Tween<T>* >& v, Tween<T>* t)
		{
			v.push_back(t);
			return t;
		}
		
		template <class T>
		Tween<T>* addTween(vector< Tween<T>* >& v,
						   T* target,
						   T startVal,
						   T endVal,
						   float startTime,
						   float endTime,
						   float (*ease)(float) = Ease::Linear )
		{
			auto t = new Tween<T>(target, startVal, endVal, startTime, endTime);
			t->setEase(ease);
			
			return addTween(v, t);
		}
		
		//REMOVING TWEENS
		template <class T>
		void removeFromVector(vector<T*>& v, T* t, bool bDelete = true)
		{
			auto tIt = find (v.begin(), v.end(), t);
			if(tIt != v.end())
			{
				if(bDelete)	delete t;
				v.erase( tIt );
			}
		}
		
		//find tweens by target
		template <class T>
		Tween<T>* findTweenByTarget(vector<Tween<T>*>& v, T& t)
		{
			for(auto& it: v)
			{
				if(it->getTarget() == &t)
				{
					return it;
				}
			}
			
			return NULL;
		}
		
		// tween vectors
		vector< Tween<int>* > tweensi;
		vector< Tween<float>* > tweensf;
		vector< Tween<double>* > tweensd;
		vector< Tween<ofVec2f>* > tweensVec2f;
		vector< Tween<ofVec3f>* > tweensVec3f;
		vector< Tween<ofVec4f>* > tweensVec4f;
		vector< Tween<ofColor>* > tweensColor;
		vector< Tween<ofFloatColor>* > tweensColorf;
	};
}