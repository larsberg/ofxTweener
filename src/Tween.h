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
    
    class TweenManager;
	
	template<class T>
	static T lerp(T a, T b, float k)
	{
		//return	a + k * (b - a);//this was giving an error for ofColor...
		return a * (1. - k) + b * k;
	}
    
    class Tween{
		
	protected:
		float startTime, endTime, progress;
		bool bLoop, bYoYo;
		
		TweenState state;
        vector<Tween*> _chainedTweens;
		
		virtual void updateValue(float t){}
        
        virtual void reachedEnd(){}
		
	public:
		void (*onStart)(void* _tween);
		void (*onUpdate)(void* _tween);
		void (*onComplete)(void* _tween);
		
		bool bKill;
		float (*ease)(float);
		
		//this can be handy for custom callbacks
		void* userPointer;
        
		void update(float t)
		{
			//handle states
			switch (state)
			{
				case TWEEN_STARTED:
					if(t >= endTime)
					{
						//STOP it
                        reachedEnd();
					}
					else
					{
						//UPDATE it
						updateValue(t);
						
						//on update callback
						if(onUpdate != NULL)	onUpdate(this);
					}
					break;
					
				case TWEEN_IDLE:
					
					//START the tween if it's time
					if(startTime <= t)
					{
						state = TWEEN_STARTED;
						
						updateValue(t);
						
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
        
		TweenItem(T* _target, T _startVal, T _endVal, float _startTime, float _endTime)
		{
            target = _target;
            startVal = _startVal;
            endVal = _endVal;
            startTime = _startTime;
            endTime = _endTime;
            onStart = NULL;
            onUpdate = NULL;
            onComplete = NULL;
            state = TWEEN_IDLE;
            progress = 0;
            bLoop = false;
            bYoYo = false;
            bKill = true;
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
		
		void updateValue(float t)
		{
			progress = ofMap(t, startTime, endTime, 0, 1, true);
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
		Tween* addTween( float* target, float startVal, float endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( int* target, int startVal, int endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( ofVec2f* target, ofVec2f startVal, ofVec2f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( ofVec3f* target, ofVec3f startVal, ofVec3f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( ofVec4f* target, ofVec4f startVal, ofVec4f endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( ofFloatColor* target, ofFloatColor startVal, ofFloatColor endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		Tween* addTween( ofColor* target, ofColor startVal, ofColor endVal, float duration, float delay=0, float (*ease)(float) = Ease::Linear );
		
		//adding existing tweens
		Tween* addTween(Tween* t);
		
		//removing tweens
		void remove(Tween* t);
		
		//getting tweens by target
		Tween* getTween(void* target);
		
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
		
		void updateTweenVector(vector<Tween*>& v, float time)
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
		Tween* addTween(vector< Tween* >& v, Tween* t)
		{
			v.push_back(t);
			return t;
		}
		
		template <class T>
		Tween* addTween(vector< Tween* >& v,
						   T* target,
						   T startVal,
						   T endVal,
						   float startTime,
						   float endTime,
						   float (*ease)(float) = Ease::Linear )
		{
			auto t = new TweenItem<T>(target, startVal, endVal, startTime, endTime);
			t->setEase(ease);
			
			return addTween(v, t);
		}
		
		//REMOVING TWEENS
		void removeFromVector(vector<Tween*>& v, Tween* t, bool bDelete = true)
		{
			auto tIt = find (v.begin(), v.end(), t);
			if(tIt != v.end())
			{
				if(bDelete)	delete t;
				v.erase( tIt );
			}
		}
		
		//find tweens by target
		Tween* findTweenByTarget(vector<Tween*>& v, void* t)
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
		vector< Tween* > tweens;
	};
}