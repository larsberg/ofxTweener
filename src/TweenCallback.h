//
//  TweenCallback.h
//  example
//
//  Created by lars berg on 2/4/15.
//
//

#pragma once

#include "Easings.h"


namespace TWEEN
{	
	class TweenCallback
	{
	public:
		TweenCallback( void(*_callback)(void*) = NULL, void* _userPointer = NULL);
		
		~TweenCallback();
		
		void set( void(*_callback)(void*), void* _userPointer);
		
		void set( void(*_callback)(void*) );
		
		void clear();
		
		void call();
		
		void (*callback)(void*);
		void* userPointer;
	};
}