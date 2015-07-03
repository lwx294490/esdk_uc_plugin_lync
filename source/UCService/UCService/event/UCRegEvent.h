#pragma once
#include "UCEvent.h"

class UCRegEvent : public UCEvent
{
public:
	UCRegEvent(void);
	virtual ~UCRegEvent(void);
public:
	virtual bool DoHandle(void);
public:
	int m_state;
	std::string m_stateDesc;

};
