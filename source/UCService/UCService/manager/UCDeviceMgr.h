#ifndef _UC_DEVICEMGR_H_
#define _UC_DEVICEMGR_H_
#include <map>

typedef std::map<TUP_UINT32,std::string> MAP_DEVICE;
//ý������
const unsigned int DEVCIE_SIZE = 10;//���֧��10���豸
const std::string SETTING_MEDIA_AUDIOINPUTDEVICE = "AudioInputDevice";
const std::string SETTING_MEDIA_AUDIOOUTPUTDEVICE = "AudioOutputDevice";
const std::string SETTING_MEDIA_VIDEODEVICE = "VideoDevice";

class UCDeviceMgr
{
public:
	static inline UCDeviceMgr& Instance()
	{
		static UCDeviceMgr inst;
		return inst;
	}
public:
	void Init(void);
	void Uninit(void);
public:
	//��˷����
	int GetMicLevel(int& _level)const;
	int SetMicLevel(int _level)const;
	//����������
	int GetSpeakerLevel(int& _level)const;
	int SetSpeakerLevel(int _level)const;
	//��ȡ��˷��豸�б�
	int GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//��ȡ�������豸�б�
	int GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//��ȡ��Ƶ�豸�б�
	int GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//��ȡ��ǰ��˷��豸
	int GetCurrentMicDev(STDeviceParam* _device);
	//��ȡ��ǰ�������豸
	int GetCurrentSpeakerDev(STDeviceParam* _device);
	//��ȡ��ǰ��Ƶ�豸
	int GetCurrentVideoDev(STDeviceParam* _device);
	//���õ�ǰ��˷��豸
	int SetCurrentMicDev(int _index);
	//���õ�ǰ�������豸
	int SetCurrentSpeakerDev(int _index);
	//���õ�ǰ��Ƶ�豸
	int SetCurrentVideoDev(int _index);
private:
	UCDeviceMgr(void);
	~UCDeviceMgr(void);
private:
	MAP_DEVICE m_mapInDevice;		//��˷��б�
	MAP_DEVICE m_mapOutDevice;		//�������б�
	MAP_DEVICE m_mapVideoDevice;	//��Ƶ�豸�б�

	TUP_INT32 m_InDeviceSize;		//��˷�����
	TUP_INT32 m_OutDeviceSize;		//����������
	TUP_INT32 m_VideoDeviceSize;	//��Ƶ�豸����

};

#endif


