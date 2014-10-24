//
//  TweenManager.h
//
//  Created by lars berg on 10/24/14.
//
#pragma once

#include "ofMain.h"

#include "Tween.h"

namespace Tween
{	
	class Manager
	{
	public:
		Manager()
		{
			ofAddListener(ofEvents().update, this, &Manager::update);
		}
		~Manager()
		{
			ofRemoveListener(ofEvents().update, this, &Manager::update);
		}
		
		template<class T>
		static shared_ptr<Tween> makeTween(T& target, T endVal, float duration, float delay, EaseFunc ease)
		{
			return shared_ptr<Tween>(new TweenItem<T>(target, endVal, duration, delay, ease));
		}
		
		template<class T>
		shared_ptr<Tween> addTween(T& target, T endVal, float duration, float delay = 0, EaseFunc ease=Ease::Linear)
		{
			auto t = makeTween( target, endVal, duration, delay, ease);
			return addTween(t);
		}
		
		template<class T>
		shared_ptr<Tween> addTween(T* target, T endVal, float duration, float delay = 0, EaseFunc ease=Ease::Linear)
		{
			return addTween(*target, endVal, duration, delay, ease);
		}
		
		shared_ptr<Tween> addTween(shared_ptr<Tween> t){
			tweens.push_back(t);
			return t;
		}
		
		void update(ofEventArgs& e)
		{
			update(ofGetElapsedTimeMillis());
		}
		
		void update(float t)
		{
			for(auto it = tweens.begin(); it != tweens.end(); it++)
			{
				(*it)->update(t);
				
				//if it's stopped erase it
				if( (*it)->state == TWEEN_STOPPED && !(*it)->persist )
				{
					tweens.erase(it);
				}
			}
		}
		
		void remove(shared_ptr<Tween> t)
		{
			auto tIt = find (tweens.begin(), tweens.end(), t);
			if(tIt != tweens.end())
			{
				tweens.erase( tIt );
			}
		}
		
		shared_ptr<Tween> getTween(void* target)
		{
			for(auto& i: tweens)
			{
				if(i->getTarget() == &target)
				{
					return i;
				}
			}
			
			shared_ptr<Tween> ptr;
			return ptr;
		}
		
		list< shared_ptr<Tween> > tweens;
	};
}