#include "pa03.h"
double integrate1(Range rng)
{
	//Perform numerical integration of the function func(x)
	//INPUT: Range rng -- the lower and upper limits of the integration
	//                    and the number of intervals to integrate over
	//OUTPUT: Return the result of the integration
	int i;
	double answer = 0;

	for(i = 0; i < rng.intervals; i ++)
	{
		if(i == 0)
		{
			answer += func(rng.lowerlimit);
		}
		else if(i == 1)
		{
			answer += func((rng.lowerlimit) + ((rng.upperlimit - rng.lowerlimit) / rng.intervals));
		}
		else
		{
			answer += func((rng.lowerlimit) + i * ((rng.upperlimit - rng.lowerlimit) / rng.intervals));
		}
	}
	answer *= ((rng.upperlimit - rng.lowerlimit) / rng.intervals);

	return answer;		
}

void integrate2(RangeAnswer * rngans)
{
	double answer = integrate1(rngans -> rng);
	rngans -> answer = answer;
	//Perform numerical integration of the function func(x)
	//INPUT: RangeAnswer * rngans 
	//              -- the lower and upper limits of the integration
	//                 and the number of intervals to integrate over
	//OUTPUT: The result of the integration should be placed in rngans->answer

	//You should try to call integrate1 when implementing integrate2
}
