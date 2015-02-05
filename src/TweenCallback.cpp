//
//  TweenCallback.cpp
//  example
//
//  Created by lars berg on 2/4/15.
//
//

#include "TweenCallback.h"


namespace TWEEN
{
	TweenCallback::TweenCallback( void(*_callback)(void*), void* _userPointer ) :
	callback(_callback),
	userPointer(_userPointer)
	{}
	
	TweenCallback::~TweenCallback()
	{}
	
	void TweenCallback::set( void(*_callback)(void*), void* _userPointer)
	{
		callback = _callback;
		userPointer = _userPointer;
	}
	
	void TweenCallback::set( void(*_callback)(void*) )
	{
		callback = _callback;
	}
	
	void TweenCallback::clear()
	{
		callback = NULL;
		userPointer = NULL;
	}
	
	void TweenCallback::call()
	{
		if(callback != NULL)
		{
			callback(userPointer);
		}
	}
}