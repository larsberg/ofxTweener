//
//  TweenManager.cpp
//  DraggableManager
//
//  Created by Quin Kennedy on 7/28/14.
//
//

#include "TweenManager.h"

namespace Tween
{
	TweenManager::TweenManager()
	{
		ofAddListener(ofEvents().update, this, &TweenManager::update);
	}
	
	TweenManager::~TweenManager()
	{
		ofRemoveListener(ofEvents().update, this, &TweenManager::update);
		
		clear();
	}
	
	
	void TweenManager::clear()
	{
        for(auto &it: tweens)
        {
            delete it;
        }
        tweens.clear();
	}
	void TweenManager::update(ofEventArgs& e)
	{
		update( ofGetElapsedTimeMillis() );
	}
	
	void TweenManager::update( float t)
	{
        if(tweens.size() == 0)	return;
        
        //we want the most recent tweens to superceed any previous so we need to loop twice
        //first to set the values
        vector<int> dead;
        int i=0;
        if (tweens.empty()){
            return;
        }
        for(list<Tween*>::iterator it = tweens.begin(); it != tweens.end();){
            (*it)->update(t);
            
            if ((*it)->bFinished){
                for(auto &it2:(*it)->_chainedTweens){
                    addTween(it2, (*it)->endTime);
                }
            }
            if((*it)->getState() == TWEEN_STOPPED && (*it)->bKill)
            {
                delete (*it);
                it = tweens.erase(it);
            } else {
                it++;
            }
        }
	}
	
	void TweenManager::remove(Tween* t, bool bDelete)
	{
        auto tIt = find (tweens.begin(), tweens.end(), t);
        if(tIt != tweens.end())
        {
            if(bDelete)	delete t;
            tweens.erase( tIt );
        }
	}
	
	Tween* TweenManager::getTween(void* target)
	{
        for(auto& it: tweens)
        {
            if(it->getTarget() == &target)
            {
                return it;
            }
        }
        
        return NULL;
	}
    
}