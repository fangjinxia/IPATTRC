#include "StdAfx.h"
#include "myMutex.h"


myMutex::myMutex(void)
{
#ifdef WIN32
	::InitializeCriticalSection(&fMutex);
#else
	pthread_mutex_init(&fMutex, NULL);
#endif
}


myMutex::~myMutex(void)
{
#ifdef WIN32
	::DeleteCriticalSection(&fMutex);
#else
	pthread_mutex_destroy(&fMutex);
#endif
}

void myMutex::lockMutex()
{
#ifdef WIN32
	::EnterCriticalSection(&fMutex);
#else
	pthread_mutex_lock(&fMutex);  
#endif
}


void myMutex::unlockMutex()
{
#ifdef WIN32
	::LeaveCriticalSection(&fMutex);
#else
	pthread_mutex_unlock(&fMutex);  
#endif
}
