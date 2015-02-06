//
//  Manager.cpp
//  example
//
//  Created by lars berg on 2/5/15.
//
//

#include "TweenManager.h"


namespace TWEEN
{
	
	Manager::Manager()
	{
		ofAddListener(ofEvents().update, this, &Manager::update);
	}
	Manager::~Manager()
	{}
	
	shared_ptr<Tween> Manager::addTween(shared_ptr<Tween> t)
	{
		tweens.push_back(t);
		return t;
	}
	
	void Manager::setGetCurrentTimeMethod( float (*timeFunc)() )
	{
		setTimeFunc( timeFunc );
	}
	
	void Manager::update(ofEventArgs& e)
	{
		update( tweenTimeFunc() );
	}
	
	void Manager::update(float t)
	{
		for(auto it = tweens.begin(); it != tweens.end(); it++)
		{
			(*it)->update(t);
			
			//remove stopped tweens
			if( (*it)->getCompleted() && (*it)->getDeleteOnComplete() )
			{
				tweens.erase(it);
			}
		}
	}
	
	void Manager::remove(shared_ptr<Tween> t)
	{
		auto tIt = find( tweens.begin(), tweens.end(), t );
		if(tIt != tweens.end())
		{
			tweens.erase( tIt );
		}
	}
	
	void Manager::clear()
	{
		tweens.clear();
	}
}