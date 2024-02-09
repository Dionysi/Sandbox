#include "stdfax.h"
#include "HighResolutionTimer.h"

HighResolutionTimer::HighResolutionTimer()
{
	Restart();
}

void HighResolutionTimer::Restart()
{
#ifdef _WIN32
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_StartTiming);
#endif
}

double HighResolutionTimer::ElapsedSeconds()
{
#ifdef _WIN32
	return (double)ElapsedMicroSeconds() / 1'000'000.0;
#endif
}

long long HighResolutionTimer::ElapsedMicroSeconds()
{
#ifdef _WIN32
	LARGE_INTEGER endTiming;
	QueryPerformanceCounter(&endTiming);

	// Convert elapsed time to microseconds.
	LONGLONG elapsed = (endTiming.QuadPart - m_StartTiming.QuadPart) * 1'000'000;
	return elapsed / m_Frequency.QuadPart;
#endif
}

long long HighResolutionTimer::ElapsedMilliSeconds()
{
#ifdef _WIN32
	// Rather than re-calculating the timing in MicroSeconds for performance sake,
	// we convert the micro seconds timing to milliseconds to maintain precision.
	return ElapsedMicroSeconds() / 1000;
#endif
}
