#include "StdAfx.h"
#include "Log.h"
#include "UCDeviceMgr.h"
#include "UCRegMgr.h"
#include "UCConfigMgr.h"

UCDeviceMgr::UCDeviceMgr(void):m_InDeviceSize(0),m_OutDeviceSize(0),m_VideoDeviceSize(0)
{
	try
	{
		m_mapInDevice.clear();
		m_mapOutDevice.clear();
		m_mapVideoDevice.clear();
	}
	catch(...)
	{
	}
}

UCDeviceMgr::~UCDeviceMgr(void)
{	
	try
	{
		m_mapInDevice.clear();
		m_mapOutDevice.clear();
		m_mapVideoDevice.clear();
		m_InDeviceSize = 0;
		m_OutDeviceSize = 0;
		m_VideoDeviceSize = 0;
	}
	catch(...)
	{
	}
}

void UCDeviceMgr::Init(void)
{
	m_mapInDevice.clear();
	m_InDeviceSize = 0;
	m_mapOutDevice.clear();
	m_OutDeviceSize = 0;
	m_mapVideoDevice.clear();
	m_VideoDeviceSize = 0;

	//获取输入设备
	TUP_UINT32 uiSize = DEVCIE_SIZE;
	CALL_S_DEVICEINFO* pstDevice = new CALL_S_DEVICEINFO[DEVCIE_SIZE];
	TUP_RESULT tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_MIC);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_devices mic failed.");
	}
	if(uiSize>DEVCIE_SIZE)
	{
		uiSize = DEVCIE_SIZE;
	}
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{
		m_mapInDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
	}
	m_InDeviceSize = uiSize;
	SAFE_DELETE_ARRAY(pstDevice);

	//获取输出设备
	uiSize = DEVCIE_SIZE;
	pstDevice = new CALL_S_DEVICEINFO[DEVCIE_SIZE];
	tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_SPEAK);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_devices speaker failed.");
	}
	else
	{
		if(uiSize>DEVCIE_SIZE)
		{
			uiSize = DEVCIE_SIZE;
		}
		for(TUP_UINT32 i=0;i<uiSize;i++)
		{
			m_mapOutDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
		}
		m_OutDeviceSize = uiSize;
	}

	SAFE_DELETE_ARRAY(pstDevice);

	//获取视频设备
	uiSize = DEVCIE_SIZE;
	pstDevice = new CALL_S_DEVICEINFO[DEVCIE_SIZE];
	tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_VIDEO);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_devices video failed.");
	}
	else
	{
		if(uiSize>DEVCIE_SIZE)
		{
			uiSize = DEVCIE_SIZE;
		}
		for(TUP_UINT32 i=0;i<uiSize;i++)
		{
			m_mapVideoDevice[pstDevice[i].ulIndex] = pstDevice[i].strName;
		}
		m_VideoDeviceSize = uiSize;		
	}
	SAFE_DELETE_ARRAY(pstDevice);
	return;
}
void UCDeviceMgr::Uninit(void)
{
	m_mapInDevice.clear();
	m_InDeviceSize = 0;
	m_mapOutDevice.clear();
	m_OutDeviceSize = 0;
	m_mapVideoDevice.clear();
	m_VideoDeviceSize = 0;
}

int UCDeviceMgr::GetMicLevel(int& level)const
{	
	level = 0;
	TUP_UINT32 uiLevel = 0;
	TUP_RESULT tRet = tup_call_media_get_mic_volume(&uiLevel);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_mic_volume failed.");
		return UC_SDK_Failed;
	}
	level = (int)uiLevel;
	return UC_SDK_Success;

}
int UCDeviceMgr::SetMicLevel(int level)const
{
	TUP_RESULT tRet = tup_call_media_set_mic_volume(CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER,level);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_speak_volume failed.");
		return UC_SDK_Failed;
	}	
	return UC_SDK_Success;
}


int UCDeviceMgr::GetSpeakerLevel(int& level)const
{
	TUP_UINT32 uiLevel = 0;
	TUP_RESULT tRet = tup_call_media_get_speak_volume(&uiLevel);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_speak_volume failed.");
		return UC_SDK_Failed;
	}
	level = (int)uiLevel;
	return UC_SDK_Success;
}
int UCDeviceMgr::SetSpeakerLevel(int level)const
{
	TUP_RESULT tRet = tup_call_media_set_speak_volume(CALL_E_AO_DEV_SPEAKER,level);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_set_speak_volume failed.");
		return UC_SDK_Failed;
	}

	return UC_SDK_Success;
}

//获取麦克风设备列表
int UCDeviceMgr::GetMicDevList(int _fromIndex, int _toIndex, STDeviceListParam* _pMicDevList)
{
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex");
		return UC_SDK_InvalidPara;
	}

	_pMicDevList->iTotal = m_mapInDevice.size();
	if(_fromIndex >= _pMicDevList->iTotal)
	{
		ERROR_LOG("_fromIndex is too large.");
		return UC_SDK_InvalidPara;
	}		
	_pMicDevList->iFrom = _fromIndex;

	if(_toIndex >= _pMicDevList->iTotal)
	{
		_pMicDevList->iTo = _pMicDevList->iTotal-1;
	}
	else
	{
		_pMicDevList->iTo = _toIndex;
	}	

	for(int i=_pMicDevList->iFrom;i<=_pMicDevList->iTo;i++)
	{
		int j = i-_pMicDevList->iFrom;
		std::string utf8StrName = m_mapInDevice[i];
		std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
		TUP_UINT32 index  = i;
		_pMicDevList->deviceList[j].index = index;
		memcpy_s(_pMicDevList->deviceList[j].name,STRING_LENGTH,name.c_str(),name.length());
		_pMicDevList->deviceList[j].iscertified = 0;
		_pMicDevList->deviceList[j].isactive = 0;
		_pMicDevList->deviceList[j].type = 0;
	}

	return UC_SDK_Success;
}
//获取扬声器设备列表
int UCDeviceMgr::GetSpeakerDevList(int _fromIndex, int _toIndex, STDeviceListParam* _pSpeakerDevList)
{
	//UC_SDK_GetSpeakerDevList()调用GetSpeakerDevList()前，已经对入参数值和字节大小进行判断。这里仅进行简单判断
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex");
		return UC_SDK_InvalidPara;
	}
	_pSpeakerDevList->iTotal = m_mapOutDevice.size();
	if(_fromIndex >= _pSpeakerDevList->iTotal)
	{
		ERROR_LOG("_fromIndex is too large.");
		return UC_SDK_InvalidPara;
	}		
	_pSpeakerDevList->iFrom = _fromIndex;

	if(_toIndex >= _pSpeakerDevList->iTotal)
	{
		_pSpeakerDevList->iTo = _pSpeakerDevList->iTotal-1;
	}
	else
	{
		_pSpeakerDevList->iTo = _toIndex;
	}	

	for(int i=_pSpeakerDevList->iFrom;i<=_pSpeakerDevList->iTo;i++)
	{
		int j = i-_pSpeakerDevList->iFrom;
		std::string utf8StrName = m_mapOutDevice[i];
		std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
		TUP_UINT32 index  = i;
		_pSpeakerDevList->deviceList[j].index = index;
		memcpy_s(_pSpeakerDevList->deviceList[j].name,STRING_LENGTH,name.c_str(),name.length());
		_pSpeakerDevList->deviceList[j].iscertified = 0;
		_pSpeakerDevList->deviceList[j].isactive = 0;
		_pSpeakerDevList->deviceList[j].type = 0;
	}
	return UC_SDK_Success;
}
//获取视频设备列表
int UCDeviceMgr::GetVideoDevList(int _fromIndex, int _toIndex, STDeviceListParam* pVideoDevList)
{
	//UC_SDK_GetVideoDevList()调用GetVideoDevList()前，已经对入参数值和字节大小进行判断。这里仅进行简单判断
	if (_fromIndex < 0 || _toIndex < 0 || _fromIndex > _toIndex)
	{
		ERROR_LOG("_fromIndex < 0 or _toIndex < 0 or fromIndex > toIndex");
		return UC_SDK_InvalidPara;
	}

	pVideoDevList->iTotal = m_mapVideoDevice.size();
	if(_fromIndex >= pVideoDevList->iTotal)
	{
		ERROR_LOG("_fromIndex is too large.");
		return UC_SDK_InvalidPara;
	}		
	pVideoDevList->iFrom = _fromIndex;

	if(_toIndex >= pVideoDevList->iTotal)
	{
		pVideoDevList->iTo = pVideoDevList->iTotal-1;
	}
	else
	{
		pVideoDevList->iTo = _toIndex;
	}	

	for(int i=pVideoDevList->iFrom;i<=pVideoDevList->iTo;i++)
	{
		int j = i-pVideoDevList->iFrom;
		std::string utf8StrName = m_mapVideoDevice[i];
		std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
		TUP_UINT32 index  = i;
		pVideoDevList->deviceList[j].index = index;
		memcpy_s(pVideoDevList->deviceList[j].name,STRING_LENGTH,name.c_str(),name.length());
		pVideoDevList->deviceList[j].iscertified = 0;
		pVideoDevList->deviceList[j].isactive = 0;
		pVideoDevList->deviceList[j].type = 0;
	}
	
	return UC_SDK_Success;
}
//获取当前麦克风设备
int UCDeviceMgr::GetCurrentMicDev(STDeviceParam* _pDevice)
{
	TUP_UINT32 uiIndex = 0;
	TUP_RESULT tRet = tup_call_media_get_mic_index(&uiIndex);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_mic_index Failed.");
		return UC_SDK_Failed;
	}
	if(uiIndex >= m_mapInDevice.size())
	{
		ERROR_LOG("uiIndex is Invalid .");
		return UC_SDK_Failed;
	}

	std::string utf8StrName = m_mapInDevice[uiIndex];
	std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
	_pDevice->index = uiIndex;
	memcpy_s(_pDevice->name,STRING_LENGTH,name.c_str(),name.length());
	_pDevice->iscertified = 0;
	_pDevice->isactive = 0;
	_pDevice->type = 0;

	return UC_SDK_Success;
}
//获取当前扬声器设备
int UCDeviceMgr::GetCurrentSpeakerDev(STDeviceParam* _pDevice)
{
	TUP_UINT32 uiIndex = 0;
	TUP_RESULT tRet = tup_call_media_get_speak_index(&uiIndex);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_speak_index Failed.");
		return UC_SDK_Failed;
	}
	if(uiIndex >= m_mapOutDevice.size())
	{
		ERROR_LOG("uiIndex is Invalid .");
		return UC_SDK_Failed;
	}

	std::string utf8StrName = m_mapOutDevice[uiIndex];
	std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
	_pDevice->index = uiIndex;
	memcpy_s(_pDevice->name,STRING_LENGTH,name.c_str(),name.length());
	_pDevice->iscertified = 0;
	_pDevice->isactive = 0;
	_pDevice->type = 0;

	return UC_SDK_Success;
}
//获取当前视频设备
int UCDeviceMgr::GetCurrentVideoDev(STDeviceParam* _pDevice)
{
	TUP_UINT32 uiIndex = 0;
	TUP_RESULT tRet = tup_call_media_get_video_index(&uiIndex);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_get_video_index Failed.");
		return UC_SDK_Failed;
	}
	if(uiIndex >= m_mapVideoDevice.size())
	{
		ERROR_LOG("uiIndex is Invalid .");
		return UC_SDK_Failed;
	}

	std::string utf8StrName = m_mapVideoDevice[uiIndex];
	std::string name = eSDKTool::utf8str2unicodestr(utf8StrName);
	_pDevice->index = uiIndex;
	memcpy_s(_pDevice->name,STRING_LENGTH,name.c_str(),name.length());
	_pDevice->iscertified = 0;
	_pDevice->isactive = 0;
	_pDevice->type = 0;

	return UC_SDK_Success;
}
//设置当前麦克风设备
int UCDeviceMgr::SetCurrentMicDev(int _index)
{
	if((unsigned int)_index >= m_mapInDevice.size())
	{
		ERROR_LOG("Index is Invalid .");
		return UC_SDK_Failed;
	}
	TUP_RESULT tRet = tup_call_media_set_mic_index(_index);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_set_mic_index Failed.");
		return UC_SDK_Failed;
	}

	char chIndex[DEVCIE_SIZE] = {0};
	_itoa_s(_index,chIndex,10);
	(void)ConfigMgr::Instance().SaveUserConfig(SETTING_MEDIA_AUDIOINPUTDEVICE,chIndex);

	return UC_SDK_Success;
}
//设置当前扬声器设备
int UCDeviceMgr::SetCurrentSpeakerDev(int _index)
{
	if((unsigned int)_index >= m_mapOutDevice.size())
	{
		ERROR_LOG("Index is Invalid .");
		return UC_SDK_Failed;
	}
	TUP_RESULT tRet = tup_call_media_set_speak_index(_index);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_set_speak_index Failed.");
		return UC_SDK_Failed;
	}

	char chIndex[DEVCIE_SIZE] = {0};
	_itoa_s(_index,chIndex,10);
	(void)ConfigMgr::Instance().SaveUserConfig(SETTING_MEDIA_AUDIOOUTPUTDEVICE,chIndex);	
	
	return UC_SDK_Success;
}
//设置当前视频设备
int UCDeviceMgr::SetCurrentVideoDev(int _index)
{
	if((unsigned int)_index >= m_mapVideoDevice.size())
	{
		ERROR_LOG("Index is Invalid .");
		return UC_SDK_Failed;
	}
	TUP_RESULT tRet = tup_call_media_set_video_index(_index);
	if(tRet != TUP_SUCCESS)
	{
		ERROR_LOG("tup_call_media_set_video_index Failed.");
		return UC_SDK_Failed;
	}

	char chIndex[DEVCIE_SIZE] = {0};
	_itoa_s(_index,chIndex,10);
	(void)ConfigMgr::Instance().SaveUserConfig(SETTING_MEDIA_VIDEODEVICE,chIndex);	
	
	return UC_SDK_Success;
}


