#pragma once
#include <string>
//Listener for calling specific functions after a thread has finished execution

class IExecutionEvent
{
public:
	virtual void OnFinishedExecution() = 0;
};