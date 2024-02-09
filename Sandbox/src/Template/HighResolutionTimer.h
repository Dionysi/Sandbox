#pragma once
#ifdef _WIN32
#include <windows.h>
#endif


/*
* Wrapper class around the standard library's high resolution clock.
*/
class HighResolutionTimer
{

private:
#ifdef _WIN32
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartTiming;
#endif


public:
	/*
	* Starts the timer. You may directly call any
	* of the "Elapsed" functions to get a timing
	* result.
	*/
	HighResolutionTimer();

	/*
	* Restarts the timer.
	*/
	void Restart();

	/*
	* Retrieve the elapsed time since the last call to Start in seconds.
	*/
	double ElapsedSeconds();
	/*
	* Retrieve the elapsed time since the last call to Start in microseconds.
	*/
	long long ElapsedMicroSeconds();
	/*
	* Retrieve the elapsed time since the last call to Start in milliseconds.
	*/
	long long ElapsedMilliSeconds();
};
