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
	int PlayLogin(void);			//���ŵ�¼�ɹ���	
	int StartPlayIncomingCall(void) ;	
	int EndPlayIncoming(void) ;
	int StartPlayRingBack(void);//���Ż�����
	int EndPlayRingBack(void) ;
	int StartPlayHoldCall(void) ;//////���б�������
	int EndPlayHoldCall(void) ;
private:
	UCPlayMgr(void);
	~UCPlayMgr(void);
private:
	std::string m_curPath;
	TUP_INT32 m_tupIncomingHandle;
	TUP_INT32 m_tupRingBackHandle;
	TUP_INT32 m_tupHoldCallHandle;
};
#endif


