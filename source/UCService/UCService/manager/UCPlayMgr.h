#ifndef _UC_TONE_PLAY_
#define _UC_TONE_PLAY_

class UCPlayMgr
{
public:
	static inline UCPlayMgr& Instance()
	{
		static UCPlayMgr inst;
		return inst;
	}
	int PlayLogin(void);			//播放登录成功音	
	int StartPlayIncomingCall(void) ;	
	int EndPlayIncoming(void) ;
	int StartPlayRingBack(void);//播放回铃音
	int EndPlayRingBack(void) ;
private:
	UCPlayMgr(void);
	~UCPlayMgr(void);
private:
	std::string m_curPath;
	TUP_INT32 m_tupIncomingHandle;
	TUP_INT32 m_tupRingBackHandle;
};
#endif


