//
//  TweenItem.h
//  example
//
//  Created by lars berg on 2/5/15.
//
//

#pragma once

#include "Tween.h"

namespace TWEEN
{
	template<class T>
	class TweenItem : public Tween
	{
	public:
		TweenItem( T* _target, T _startVal, T _endVal, float duration = 1, float delay = 0, EaseFunc ease = TWEEN::Ease::Linear) :
		Tween( duration, delay, ease ),
		_target( _target ),
		startValue( _startVal ),
		endValue( _endVal )
		{}
		
		~TweenItem()
		{}
		
		void updateValue(float u)
		{
			if(_target != NULL)	*_target = lerp( startValue, endValue, u);
		}
		
		void reverse()
		{
			swap(startValue, endValue);
		}
		
		T* _target;
		T startValue, endValue;
	};
}
