//
//  Manager.h
//  example
//
//  Created by lars berg on 2/5/15.
//
//

#pragma once

#include "TweenItem.h"

namespace TWEEN
{
	class Manager
	{
	public:
		
		Manager();
		~Manager();
		
		template<class T>
		static shared_ptr<Tween> makeTween( T& target, T startVal, T endVal, float duration = 1000, float delay = 0, EaseFunc ease=Ease::Linear )
		{
			return shared_ptr<Tween>( new TweenItem<T>( &target, startVal, endVal, duration, delay, ease) );
		}
		
		template<class T>
		shared_ptr<Tween> addTween( T& target, T endVal, float duration = 1000, float delay = 0, EaseFunc ease=Ease::Linear )
		{
			auto t = makeTween( target, target, endVal, duration, delay, ease);
			return addTween(t);
		}
		
		template<class T>
		shared_ptr<Tween> addTween( T& target, T startVal, T endVal, float duration, float delay, EaseFunc ease )
		{
			auto t = makeTween( target, startVal, endVal, duration, delay, ease);
			return addTween(t);
		}
		
		shared_ptr<Tween> addTween(shared_ptr<Tween> t);
		
		void setGetCurrentTimeMethod( float (*timeFunc)() );
		
		void update( ofEventArgs& e );

		void update( float t );
		
		void remove( shared_ptr<Tween> t );
		
		void clear();
		
		list< shared_ptr<Tween> > tweens;
	};
}