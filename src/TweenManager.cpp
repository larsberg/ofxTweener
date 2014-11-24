//
//  TweenManager.cpp
//
//  Created by lars berg on 10/24/14.
//

#include "TweenManager.h"


namespace Tween
{
	Manager::Manager()
	{
		ofAddListener(ofEvents().update, this, &Manager::update);
		
		id = ofRandom(1000000);
	}
	
	Manager::~Manager()
	{
		ofRemoveListener(ofEvents().update, this, &Manager::update);
	}
	
	shared_ptr<Tween> Manager::addTween(shared_ptr<Tween> t)
	{
		tweens.push_back(t);
		return t;
	}
	
	void Manager::update(ofEventArgs& e)
	{
		update(ofGetElapsedTimeMillis());
	}
	
	void Manager::update(float t)
	{
		for(auto it = tweens.begin(); it != tweens.end(); it++)
		{
			(*it)->update(t);
			
			//remove stopped tweens
			if( (*it)->state == TWEEN_STOPPED && !(*it)->persist )
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
		for(auto& t: tweens)	t->stop();
		
		tweens.clear();
	}
	
	shared_ptr<Tween> Manager::getTween(void* target)
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
}