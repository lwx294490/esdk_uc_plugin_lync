#ifndef _UC_DEVICEMGR_H_
#define _UC_DEVICEMGR_H_
#include <map>

typedef std::map<TUP_UINT32,std::string> MAP_DEVICE;
//媒体设置
const unsigned int DEVCIE_SIZE = 10;//最多支持10个设备
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
	//麦克风管理
	int GetMicLevel(int& _level)const;
	int SetMicLevel(int _level)const;
	//扬声器管理
	int GetSpeakerLevel(int& _level)const;
	int SetSpeakerLevel(int _level)const;
	//获取麦克风设备列表
	int GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//获取扬声器设备列表
	int GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//获取视频设备列表
	int GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* _devList);
	//获取当前麦克风设备
	int GetCurrentMicDev(STDeviceParam* _device);
	//获取当前扬声器设备
	int GetCurrentSpeakerDev(STDeviceParam* _device);
	//获取当前视频设备
	int GetCurrentVideoDev(STDeviceParam* _device);
	//设置当前麦克风设备
	int SetCurrentMicDev(int _index);
	//设置当前扬声器设备
	int SetCurrentSpeakerDev(int _index);
	//设置当前视频设备
	int SetCurrentVideoDev(int _index);
private:
	UCDeviceMgr(void);
	~UCDeviceMgr(void);
private:
	MAP_DEVICE m_mapInDevice;		//麦克风列表
	MAP_DEVICE m_mapOutDevice;		//扬声器列表
	MAP_DEVICE m_mapVideoDevice;	//视频设备列表

	TUP_INT32 m_InDeviceSize;		//麦克风总数
	TUP_INT32 m_OutDeviceSize;		//扬声器总数
	TUP_INT32 m_VideoDeviceSize;	//视频设备总数

};

#endif


