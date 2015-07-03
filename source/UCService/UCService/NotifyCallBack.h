#pragma once

class CNotifyCallBack
{
private:
	CNotifyCallBack(void);
	~CNotifyCallBack(void);
public:
	static TUP_BOOL IMNotify(IM_E_EVENT_ID eventID, void *body);
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *data);
};
