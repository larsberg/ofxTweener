//
//  TweenEventArgs.h
//  DraggableManager
//
//  Created by Quin Kennedy on 7/28/14.
//
//

#pragma once
#include "ofMain.h"

namespace Tween
{
	class Tween;
	
	class TweenEventArgs
	{
	public:
		TweenEventArgs(Tween* t=NULL)
		{
			tween = t;
		}
		Tween* tween;
	};
}
