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
		update( tweenTimeFunc() );
	}
	
	void Manager::update(float t)
	{
		for (list< shared_ptr<Tween> >::reverse_iterator rit=tweens.rbegin(); rit!=tweens.rend(); ++rit) {
			
			// update the tween
			(*rit)->update(t);
			
			//remove stopped tweens
			if( (*rit)->getCompleted() && (*rit)->getDeleteOnComplete() )
			{
				tweens.remove(*rit);
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