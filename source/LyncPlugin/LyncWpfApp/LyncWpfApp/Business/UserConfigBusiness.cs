using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    public class UserConfigBusiness
    {
        public int GetMicDevList(int _fromIndex, int _toIndex, int _size,byte[] devList)//该函数用于获取麦克风设备列表
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetMicDevList"));
                int iRet = UCInterface.UC_SDK_GetMicDevList(_fromIndex,  _toIndex,  _size,devList);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetMicDevList error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetMicDevList"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, byte[] devList)//该函数用于获取扬声器设备列表
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetSpeakerDevList"));
                int iRet = UCInterface.UC_SDK_GetSpeakerDevList(_fromIndex, _toIndex, _size, devList);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetSpeakerDevList error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetSpeakerDevList"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetVideoDevList(int _fromIndex, int _toIndex, int _size, byte[] devList)//该函数用于获取视频设备列表
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetVideoDevList"));
                int iRet = UCInterface.UC_SDK_GetVideoDevList(_fromIndex, _toIndex, _size, devList);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetVideoDevList error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetVideoDevList"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetCurrentMicDev(byte[] device)//该函数用于获取当前麦克风设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetCurrentMicDev"));
                int iRet = UCInterface.UC_SDK_GetCurrentMicDev(device);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetCurrentMicDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetCurrentMicDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetCurrentSpeakerDev(byte[] device)//该函数用于获取当前扬声器设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetCurrentSpeakerDev"));
                int iRet = UCInterface.UC_SDK_GetCurrentSpeakerDev(device);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetCurrentSpeakerDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetCurrentSpeakerDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetCurrentVideoDev(byte[] device)//该函数用于获取当前视频设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetCurrentVideoDev"));
                int iRet = UCInterface.UC_SDK_GetCurrentVideoDev(device);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetCurrentVideoDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetCurrentVideoDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int SetCurrentMicDev(int index)//该函数用于设置当前麦克风设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCurrentMicDev"));
                int iRet = UCInterface.UC_SDK_SetCurrentMicDev(index);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_SetCurrentMicDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCurrentMicDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int SetCurrentSpeakerDev(int index)//该函数用于设置当前扬声器设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCurrentSpeakerDev"));
                int iRet = UCInterface.UC_SDK_SetCurrentSpeakerDev(index);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_SetCurrentSpeakerDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCurrentSpeakerDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int SetCurrentVideoDev(int index)//该函数用于设置当前视频设备
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCurrentVideoDev"));
                int iRet = UCInterface.UC_SDK_SetCurrentVideoDev(index);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_SetCurrentVideoDev error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCurrentVideoDev"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int OpenPortal(int _type)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_OpenPortal"));
                int iRet = UCInterface.UC_SDK_OpenPortal(_type);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_OpenPortal error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_OpenPortal"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        public int GetContactInfo(StringBuilder _Account, ref  STContact _pContactInfo)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetContactInfo"));
                int iRet = UCInterface.UC_SDK_GetContactInfo(_Account, ref _pContactInfo);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetContactInfo error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetContactInfo"));
                return iRet;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Debug(ex.ToString());
                return -1;
            }
        }
        
    }
}
