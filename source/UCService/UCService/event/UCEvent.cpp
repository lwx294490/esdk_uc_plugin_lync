//lint -e1762
//lint -e818
#include "StdAfx.h"
#include "UCEvent.h"



const std::string BOOK_CONF_NUM = "600000";//‘§‘ºª·“È∫≈

UCEvent::UCEvent()
{
}
UCEvent::~UCEvent()
{
}

EventType UCEvent::GetEventType(void)
{
	return m_EventType;
}
