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
		Manager();
		~Manager();
		
		template<class T>
		static shared_ptr<Tween> makeTween(T& target, T endVal, float duration = 1000, float delay = 0, EaseFunc ease=Ease::Linear)
		{
			return shared_ptr<Tween>(new TweenItem<T>(target, endVal, duration, delay, ease));
		}
		
		template<class T>
		shared_ptr<Tween> addTween(T& target, T endVal, float duration = 1000, float delay = 0, EaseFunc ease=Ease::Linear)
		{
			auto t = makeTween( target, endVal, duration, delay, ease);
			return addTween(t);
		}
		
		template<class T>
		shared_ptr<Tween> addTween(T* target, T startVal, T endVal, float duration, float delay, EaseFunc ease=Ease::Linear)
		{
			return addTween(*target, startVal, endVal, duration, delay, ease);
		}
		
		shared_ptr<Tween> addTween(shared_ptr<Tween> t);
		
		void update(ofEventArgs& e);
		
		void update(float t = ofGetElapsedTimeMillis());
		
		void remove(shared_ptr<Tween> t);
		
		void clear();
		
		shared_ptr<Tween> getTween(void* target);
		
		list< shared_ptr<Tween> > tweens;
		int id;
	};
}