//
//  Tween.cpp
//
//  Created by lars berg on 7/6/14.
//

#include "Tween.h"


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
        for(auto &it: tweens)
        {
            it->update(t);
            
            if(it->getState() == TWEEN_STOPPED && it->bKill)
            {
                dead.push_back(i);
            }
            if (it->bFinished){
                for(auto &it2:it->_chainedTweens){
                    addTween(it2);
                }
            }
            
            i++;
        }
        
        //bury the dead
        for(int i=dead.size()-1; i>=0; i--)
        {
            delete tweens[dead[i]];
            tweens.erase(tweens.begin() + dead[i]);
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