//
//  TweenManager.h
//  DraggableManager
//
//  Created by Quin Kennedy on 7/28/14.
//
//

#pragma once

#include "Tween.h"

namespace Tween{
    
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
		
		//removing tweens
		void remove(Tween* t, bool bDelete = true);
		
		//getting tweens by target
		Tween* getTween(void* target);
		
	private:
		
		// tween vectors
		vector< Tween* > tweens;
	};
}