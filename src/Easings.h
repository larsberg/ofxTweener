//
//  Easings.h
//  example
//
//  Created by lars berg on 2/4/15.
//
//

#pragma once

#include "ofMain.h"

namespace TWEEN
{	
	
	//UTILS
	template<class T>
	static T lerp(T a, T b, float k)
	{
		return a * (1. - k) + b * k; //	a + k * (b - a) was giving an error for ofColor...
	}
	
	template<>
	bool lerp<bool>(bool a, bool b, float k)
	{
		return k < 1 ? a : b;
	}
	
	template<class T>
	static T mapLinear( T x, T a1, T a2, T b1, T b2 )
	{
		if(a2 == a1)	return b1;
		
		return b1 + ( x - a1 ) * ( b2 - b1 ) / (a2 - a1);
	}
	
	
	//EASES
	typedef float (*EaseFunc)(float);
	
	namespace Ease
	{
		static float Linear(float k)
		{
			return CLAMP(k,0,1);
		}
		
		static float Zero(float k)
		{
			return 0;
		}
		
		static float One(float k)
		{
			return 1;
		}
		
		static float Floor(float k)
		{
			return floor(k);
		}
		
		namespace Quadratic
		{
			static float In( float k )
			{
				return k * k;
			}
			
			static float Out(float  k )
			{
				return k * ( 2 - k );
			}
			
			static float InOut(float k )
			{
				if ( ( k *= 2 ) < 1 ){ return 0.5 * k * k;}
				--k;
				return - 0.5 * ( k * ( k - 2 ) - 1 );
			}
		}
		
		namespace Cubic
		{
			static float In(float k )
			{
				return k * k * k;
			}
			static float Out(float k )
			{
				--k;
				return k * k * k + 1;
			}
			static float InOut(float k )
			{
				if ( ( k *= 2 ) < 1 ) return 0.5 * k * k * k;
				k-=2;
				return 0.5 * ( k * k * k + 2 );
			}
		}
		
		namespace Quartic
		{
			static float In(float k )
			{
				return k * k * k * k;
			}
			static float Out(float k )
			{
				--k;
				return 1 - ( k * k * k * k );
			}
			static float InOut(float k )
			{
				if ( ( k *= 2 ) < 1) return 0.5 * k * k * k * k;
				k -= 2;
				return - 0.5 * ( k * k * k * k - 2 );
			}
		}
		
		namespace Quintic
		{
			static float In(float k )
			{
				return k * k * k * k * k;
			}
			static float Out(float k )
			{
				--k;
				return k * k * k * k * k + 1;
			}
			static float InOut(float k )
			{
				if ( ( k *= 2 ) < 1 ) return 0.5 * k * k * k * k * k;
				k -= 2;
				return 0.5 * ( k * k * k * k * k + 2 );
			}
		}
		
		namespace Sinusoidal
		{
			static float In(float k )
			{
				return 1 - cos( k * PI / 2 );
			}
			static float Out(float k )
			{
				return sin( k * PI / 2 );
			}
			static float InOut(float k )
			{
				return 0.5 * ( 1 - cos( PI * k ) );
			}
		}
		
		namespace Exponential
		{
			static float In(float k )
			{
				return k == 0 ? 0 : pow( 1024, k - 1 );
			}
			static float Out(float k )
			{
				return k == 1 ? 1 : 1 - pow( 2, - 10 * k );
			}
			static float InOut(float k )
			{
				if ( k == 0 ) return 0;
				if ( k == 1 ) return 1;
				if ( ( k *= 2 ) < 1 ) return 0.5 * pow( 1024, k - 1 );
				return 0.5 * ( - pow( 2, - 10 * ( k - 1 ) ) + 2 );
			}
		}
		
		namespace Circular
		{
			static float In(float k )
			{
				return 1 - sqrt( 1 - k * k );
			}
			static float Out(float k )
			{
				--k;
				return sqrt( 1 - ( k * k ) );
			}
			static float InOut(float k )
			{
				if ( ( k *= 2 ) < 1) return - 0.5 * ( sqrt( 1 - k * k) - 1);
				k -= 2;
				return 0.5 * ( sqrt( 1 - k * k) + 1);
			}
		}
		
		namespace Elastic
		{
			static float In(float k )
			{
				float s, a, p;
				a = 0.1;
				p = 0.4;
				
				if ( k == 0 ) return 0;
				if ( k == 1 ) return 1;
				if ( !a || a < 1 ) { a = 1; s = p / 4; }
				else s = p * asin( 1 / a ) / ( 2 * PI );
				k -= 1;
				return - ( a * pow( 2, 10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) );
			}
			static float Out(float k )
			{
				float s, a, p;
				a = 0.1;
				p = 0.4;
				if ( k == 0 ) return 0;
				if ( k == 1 ) return 1;
				if ( !a || a < 1 ) { a = 1; s = p / 4; }
				else s = p * asin( 1 / a ) / ( 2 * PI );
				return ( a * pow( 2, - 10 * k) * sin( ( k - s ) * ( 2 * PI ) / p ) + 1 );
			}
			static float InOut(float k )
			{
				float s, a, p;
				a = 0.1;
				p = 0.4;
				
				if ( k == 0 ) return 0;
				if ( k == 1 ) return 1;
				if ( !a || a < 1 ) { a = 1; s = p / 4; }
				else s = p * asin( 1 / a ) / ( 2 * PI );
				if ( ( k *= 2 ) < 1 )
				{
					k -= 1;
					return - 0.5 * ( a * pow( 2, 10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) );
				}
				k -= 1;
				return a * pow( 2, -10 * k ) * sin( ( k - s ) * ( 2 * PI ) / p ) * 0.5 + 1;
			}
		}
		
		namespace Back
		{
			static float In(float k )
			{
				float s = 1.70158;
				return k * k * ( ( s + 1 ) * k - s );
			}
			static float Out(float k )
			{
				float s = 1.70158;
				--k;
				return k * k * ( ( s + 1 ) * k + s ) + 1;
			}
			static float InOut(float k )
			{
				float s = 1.70158 * 1.525;
				k *= 2;
				if ( k < 1 ) return 0.5 * ( k * k * ( ( s + 1 ) * k - s ) );
				k -= 2;
				return 0.5 * ( k * k * ( ( s + 1 ) * k + s ) + 2 );
			}
		}
		
		namespace Bounce
		{
			static float Out(float k )
			{
				if ( k < ( 1 / 2.75 ) ) {
					return 7.5625 * k * k;
				} else if ( k < ( 2 / 2.75 ) ) {
					k -= 1.5 / 2.75;
					return 7.5625 * k * k + 0.75;
				} else if ( k < ( 2.5 / 2.75 ) ) {
					k -= 2.25 / 2.75 ;
					return 7.5625 * k * k + 0.9375;
				} else {
					k -= 2.625 / 2.75;
					return 7.5625 * k * k + 0.984375;
				}
			}
			static float In(float k )
			{
				return 1 - Out( 1 - k );
			}
			static float InOut(float k )
			{
				if ( k < 0.5 ) return In( k * 2 ) * 0.5;
				return Out( k * 2 - 1 ) * 0.5 + 0.5;
			}
		}
	}
}