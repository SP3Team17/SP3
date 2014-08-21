#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <exception>
#include <ctime>
#include <cstdlib>

//Math Namespace
namespace Math
{
	const float	EPSILON    = 0.00001f; //Used for error checking
	const float	PI         = 3.1415926535897932384626433832795f;
	const float TWO_PI     = PI * 2.0f;
	const float HALF_PI    = PI / 2.0f;
	const float QUARTER_PI = PI / 4.0f;

	inline float FAbs(float value)
	{
		return (value < 0) ? -value : value;
	}

	//Converts from degrees to radians
	inline float DegreeToRadian(float value)
	{
		return value * PI / 180.0f;
	}

	//Converts from radians to degrees
	inline float RadianToDegree(float value)
	{
		return value * 180.0f / PI;
	}

	//Keeps a value between a min and max point. If it goes to low, it will 
	//become the max. If the value gets too high, it will become the min.
	template<typename T>
	T Wrap(T val, T minVal, T maxVal)
	{
		if (val < minVal)
			return maxVal;
		
		else if (val > maxVal)
			return minVal;

		return val;
	}

	//Keeps a value between a min and max point. If it goes to low, it will 
	//become the min. If the value gets too high, it will become the max.
	template<typename T>
	T Clamp(T val, T minVal, T maxVal)
	{
		if (val < minVal)
			return minVal;
		
		else if (val > maxVal)
			return maxVal;

		return val;
	}

	//Returns the smaller of the two values
	template<typename T>
	T Min(T x, T y)
	{
		return (x < y) ? x : y;
	}

	//Returns the larger of the two values
	template<typename T>
	T Max(T x, T y)
	{
		return (x > y) ? x : y;
	}

	//Initialize Random Number Generator
	inline void InitRNG(void)
	{
		srand (static_cast<unsigned> (time(0)));
	}
	
	//Return a random integer
	inline unsigned RandInt(void)
	{
		return rand();
	}
	
	//Return a random integer between min and max
	inline int RandIntMinMax (int min, int max)
	{
		int num = rand() % (max - min + 1);
		return (num + min);
	}
	
	//Return a random float
	inline float RandFloat (void)
	{
		return rand() / static_cast <float> (RAND_MAX);
	}

	//Return a random float between min and max
	inline float RandFloatMinMax (float min, float max)
	{
		float num = (max - min) * RandFloat ();
		return (num + min);
	}
}

//Class DivideByZero:
//Exception for divide by zero
class DivideByZero : public std::exception
{
public:
	const char* what() {return "Divide By Zero";}
};

#endif 
