using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows;

namespace LyncWpfApp
{
    public class LogInBusiness
    {
        static public Action<SignInState,StringBuilder> GetUCStateChanged;
        static ClientSignInNotifyCB clientSignInNotifyCB = new ClientSignInNotifyCB(ClientSignInNotifyCBMethod);//设置呼叫事件回调
        static public Action<int, STContact> StatusChanged;
        static StatusChangedCB statusChangedCB = new StatusChangedCB(StatusChangedCBMethod);//设置状态回调函数
        static public Action<STMsgAVSessionClosedParam> AVSessionClosed;
        static AVSessionClosedCB avSessionClosedCB = new AVSessionClosedCB(AVSessionClosedCBMethod);
        static public Action AVSessionConnected;
        static AVSessionConnectedCB avSessionConnectedCB = new AVSessionConnectedCB(AVSessionConnectedCBMethod);
        static public Action<STAudioVideoParam> AVSessAdded;
        static AVSessAddedCB avSessAddedCB = new AVSessAddedCB(AVSessAddedCBMethod);

        //modify 

        public int Login(string name, string pwd, string server1, string langID)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start Login"));
                int iRet = UCInterface.UC_SDK_Init();
                UCInterface.UC_SDK_SetLoginEventCB(clientSignInNotifyCB);
                UCInterface.UC_SDK_SetCallEventCallBack(avSessionClosedCB, avSessionConnectedCB, avSessAddedCB);
                UCInterface.UC_SDK_SetStatusChangedCB(statusChangedCB);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start Login error {0}", iRet));
                    return iRet;
                }

                iRet = UCInterface.UC_SDK_SignInByPWD(name, pwd, server1, langID);

                LogManager.SystemLog.Debug(string.Format("End Login"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }

        }
        public int UnInit()//释放资源
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_UnInit"));
            int iRet = UCInterface.UC_SDK_UnInit();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_UnInit error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_UnInit"));
            return iRet;
        }
        public int SignOut()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SignOut"));
            int iRet = UCInterface.UC_SDK_SignOut();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_SignOut error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SignOut"));
            return iRet;
        }
        static private void ClientSignInNotifyCBMethod(int _state, StringBuilder _reason)
        {
            SignInState st = (SignInState)_state;
            if (GetUCStateChanged != null)
            {
                GetUCStateChanged(st, _reason);
            }
        }
        static private void StatusChangedCBMethod(int _state, ref STContact _contact)
        {
            if (StatusChanged != null)
            {
                StatusChanged(_state, _contact);
            }
            LogManager.SystemLog.Debug(string.Format("StatusChangedCBMethod name = {0}", _contact.ucAcc_));
        }
        static void AVSessionClosedCBMethod(ref STMsgAVSessionClosedParam _avParam)
        {
            if (AVSessionClosed != null)
            {
                AVSessionClosed(_avParam);
            }
        }
        static void AVSessionConnectedCBMethod()
        {
            if (AVSessionConnected != null)
            {
                AVSessionConnected();
            }
        }
        static void AVSessAddedCBMethod(ref STAudioVideoParam _avParam)
        {
            if (AVSessAdded != null)
            {
                AVSessAdded(_avParam);
            }
        }
        public int GetPhoneJointDevType(ref int _pDevType)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetPhoneJointDevType"));
            int iRet = UCInterface.UC_SDK_GetPhoneJointDevType(ref _pDevType);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_GetPhoneJointDevType error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetPhoneJointDevType"));
            return iRet;
        }
        public int SetPhoneJointDevType(int _pDevType)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetPhoneJointDevType"));
            int iRet = UCInterface.UC_SDK_SetPhoneJointDevType(_pDevType);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_SetPhoneJointDevType error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetPhoneJointDevType"));
            return iRet;
        }

        public int SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack)
        {           
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetPhoneJointEventCallBack"));
            int iRet = UCInterface.UC_SDK_SetPhoneJointEventCallBack(pjEventCallBack);          
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_SetPhoneJointEventCallBack error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetPhoneJointEventCallBack"));
            return iRet;
        }

        public int PubSelfStatus(int _Status, StringBuilder _Desc)
        {           
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_PubSelfStatus"));            
            int iRet = UCInterface.UC_SDK_PubSelfStatus(_Status, _Desc);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("Start UC_SDK_PubSelfStatus error {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_PubSelfStatus"));
            return iRet;
        }
    }
}
