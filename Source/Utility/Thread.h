#pragma once

#ifdef WIN32
#include<Windows.h>
#else
//#include<pthread.h>
#endif

class Thread
{
public:
	Thread();
	virtual ~Thread();
};

