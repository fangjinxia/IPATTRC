#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>  
#endif // WIN32

class myMutex
{
public:
#ifdef WIN32
	CRITICAL_SECTION fMutex;
#else
	pthread_mutex_t fMutex;
#endif

public:
	myMutex(void);
	~myMutex(void);

	void lockMutex();
	void unlockMutex();
};

