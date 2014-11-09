//
//  Tweener.h
//
//  Created by lars berg on 10/22/14.
//

#pragma once

#include "ofMain.h"
#include "Easings.h"


namespace Tween
{
	//TYPES
	typedef float (*EaseFunc)(float);
	
	enum TweenState
	{
		TWEEN_STARTED = 0,
		TWEEN_STOPPED = 1,
		TWEEN_PAUSED = 2,
		TWEEN_IDLE = 3
	};
	
	class Tween;
	class EventArgs
	{
	public:
		EventArgs(Tween* t)
		{
			tween = t;
		}
		Tween* tween;
	};
	
	//UTILS
	template<class T>
	static T lerp(T a, T b, float k)
	{
		return a * (1. - k) + b * k; //	a + k * (b - a) was giving an error for ofColor...
	}
	
	template<class T>
	static T mapLinear(T x, T a1, T a2, T b1, T b2, bool clamp = true )
	{
		T denom = a2 - a1;
		if(denom == 0)	return b1;
		
		T val = b1 + ( x - a1 ) * ( b2 - b1 ) / ( a2 - a1 );
		
		if(clamp)	val = max(b1, min(b2, val));
		
		return val;
	};
	
	//TWEEN
	class Tween
	{
	public:
		Tween(float duration, float delay, EaseFunc ease);
		
		Tween* onStart(void(*onStartFunc)(void* tween));
		
		Tween* onUpdate(void(*onUpdateFunc)(void* tween));
		
		Tween* onComplete(void(*onCompleteFunc)(void* tween));
		
		template <typename ArgumentsType, class ListenerClass>
		Tween* addUpdateListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP)
		{
			ofAddListener(onUpdateEvent, listener, listenerMethod, prio);
			return this;
		}
		
		template <typename ArgumentsType, class ListenerClass>
		Tween* addStartListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP)
		{
			ofAddListener(onStartEvent, listener, listenerMethod, prio);
			return this;
		}
		
		template <typename ArgumentsType, class ListenerClass>
		Tween* addCompleteListener(ListenerClass  * listener, void (ListenerClass::*listenerMethod)(ArgumentsType&), int prio=OF_EVENT_ORDER_AFTER_APP)
		{
			ofAddListener(onCompleteEvent, listener, listenerMethod, prio);
			return this;
		}
		
		Tween* setUserPtr(void* ptr);
		
		Tween* start();
		
		Tween* stop();
		
		Tween* pause();
		
		Tween* pause(float pauseTime);
		
		Tween* unpause();
		
		Tween* setRepeat(int count = -1 );
		
		Tween* loop(int count = -1 );
		
		Tween* yoyo(bool bYoyo=true);
		
		Tween* addChain(shared_ptr<Tween> chainedTween);
		
		Tween* setPersist(bool bPersist);
		
		// updates every frame
		void update(float t = ofGetElapsedTimeMillis());
		
		//overwritten by TweenItem
		
		virtual void updateValue(){}
		virtual void startItem(){}
		virtual void reverse(){}
		virtual void handleRepeat(){}
		virtual void* getTarget(){return NULL;}
		virtual void* getItem(){return NULL;}
		
		//attributes
		float duration, startTime, endTime, pauseTime, delay, progress;
		EaseFunc ease;
		bool persist, bReverse;
		int repeatCount;

		//	callbacks
		void (*_onStart)(void* _tween);
		void (*_onUpdate)(void* _tween);
		void (*_onComplete)(void* _tween);
		
		//	ofEvents
		ofEvent<EventArgs> onCompleteEvent;
		ofEvent<EventArgs> onUpdateEvent;
		ofEvent<EventArgs> onStartEvent;
		
		vector<void*> updateListeners;
		vector<void*> updateMethods;
		
		shared_ptr<EventArgs> eventArgs;

		//	user pointer is useful for events(cast void* to class*)
		void* userPointer;
		
		//	udpating, started, stopped, paused & idle
		TweenState state;
		
		//	these tweens will be started on completion
		list< shared_ptr<Tween> > chains;
	};
	
	//
	template<class T>
	class TweenItem : public Tween
	{
	public:
		TweenItem( T& target, T endVal, float duration, float delay = 0, EaseFunc ease=Ease::Linear) :
		Tween(duration, delay, ease),
		ptr( &target ),
		endVal( endVal ),
		startVal(target)
		{}
		
		void updateValue()
		{
			value = lerp(startVal, endVal, ease(progress));
			if(ptr != NULL)	*ptr = value;
		}
		
		void startItem()
		{
			if(ptr != NULL)	startVal = *ptr;
		}
		
		void handleRepeat()
		{
			if(ptr != NULL)	*ptr = startVal;
			start();
		}
		
		void reverse()
		{
			swap(startVal, endVal);
		}
		
		void* getTarget()
		{
			return (void*)ptr;
		}
		
		void* getItem(){
			return (void*)this;
		}
		
		T getValue()
		{
			return value;
		}
		
	
		T value, startVal, endVal;
		T* ptr;
	};
	
	template<>
	class TweenItem<bool> : public Tween
	{
	public:
		TweenItem( bool& target, bool endVal, float duration, float delay = 0, EaseFunc ease=Ease::Linear) :
		Tween(duration, delay, ease),
		ptr( &target ),
		endVal( endVal ),
		startVal(target)
		{}
		
		void updateValue()
		{
//			value = lerp(startVal, endVal, ease(progress));
			if(progress == 1) value = endVal;
			if(ptr != NULL)	*ptr = value;
		}
		
		void startItem()
		{
			if(ptr != NULL)	startVal = *ptr;
		}
		
		void handleRepeat()
		{
			if(ptr != NULL)	*ptr = startVal;
			start();
		}
		
		void reverse()
		{
			swap(startVal, endVal);
		}
		
		void* getTarget()
		{
			return (void*)ptr;
		}
		
		void* getItem(){
			return (void*)this;
		}
		
		bool getValue()
		{
			return value;
		}
		
		
		bool value, startVal, endVal, *ptr;
	};
}