using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LyncWpfApp
{
    public class MakeCallBusiness
    {
        /// <summary>
        /// 插件呼叫管理模块的发起上下文呼叫业务接口
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="contactNum"></param>
        /// <param name="isVideo"></param>
        public int startContextCall()     //modify by jinyeqing 2015/6/2 之前是返回值是空值 现在返回INT 
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_MakeCall"));
            int iRet = UCInterface.UC_SDK_MakeCall();
            if (iRet != 0)
            {              
                LogManager.SystemLog.Error(string.Format("UC_SDK_MakeCall = {0}", iRet));              
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_MakeCall"));   
            return iRet;
        }

        /// <summary>
        /// 增加成员
        /// </summary>
        /// <param name="sipUri"></param>
        public int insertMember(int type, StringBuilder sipUri)  //modify by jinyeqing 2015/6/9 之前是返回值是空值 现在返回INT 
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InsertMember"));
            int iRet = UCInterface.UC_SDK_AddCallMember(type, StringHelper.GetSubString(sipUri.ToString()));
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_InsertMember = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_InsertMember"));
            return iRet;
        }
        
        /// <summary>
        /// 通话保持
        /// </summary>
        public void holdCall()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_HoldCall"));
            int iRet = UCInterface.UC_SDK_HoldCall();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_HoldCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_HoldCall"));
        }
        /// <summary>
        /// 通话恢复
        /// </summary>
        public void resumeCall()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_ResumeCall"));
            int iRet = UCInterface.UC_SDK_ResumeCall();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_ResumeCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_ResumeCall"));
        }
        /// <summary>
        /// 结束通话
        /// </summary>
        public void hangupCall()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_HangupCall"));
            int iRet = UCInterface.UC_SDK_HangupCall();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_HangupCall = {0}", iRet));

            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_HangupCall"));

        }
        public void SendDTMF(char tone)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SendDTMF"));
            int iRet = UCInterface.UC_SDK_SendDTMF(tone);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SendDTMF = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SendDTMF"));
        }
        public void MuteMic()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_MuteMic"));
            int iRet = UCInterface.UC_SDK_MuteMic();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_MuteMic = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_MuteMic"));
        }
        public void UnMuteMic()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_UnMuteMic"));
            int iRet = UCInterface.UC_SDK_UnMuteMic();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_UnMuteMic = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_UnMuteMic"));
        }
        public void MakeVideoCall(ref STVideoWindow stLocalWnd, ref STVideoWindow stRemoteWnd)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_MakeVideoCall"));
            int iRet = UCInterface.UC_SDK_MakeVideoCall(stLocalWnd.hWnd, stLocalWnd.left, stLocalWnd.top, stLocalWnd.width, stLocalWnd.height,
                                                        stRemoteWnd.hWnd, stRemoteWnd.left, stRemoteWnd.top, stRemoteWnd.width, stRemoteWnd.height);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_MakeVideoCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_MakeVideoCall"));
        }
        public void InviteMemberInCall(int memberType, StringBuilder lyncAccount)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InviteMemberInCall"));
            int iRet = UCInterface.UC_SDK_InviteMemberInCall(memberType, lyncAccount);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_InviteMemberInCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_InviteMemberInCall"));
        }

        public int UC_SDK_TransCallToConf(byte[] _pContactList, int size)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InviteMemberInCall"));
            int iRet = UCInterface.UC_SDK_TransCallToConf(_pContactList, size);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_TransCallToConf = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_TransCallToConf"));
            return iRet;
        }

        public void DeleteMemberInCall(int memberType, StringBuilder lyncAccount)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_DeleteMemberInCall"));
            int iRet = UCInterface.UC_SDK_DeleteMemberInCall(memberType, lyncAccount);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_DeleteMemberInCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_DeleteMemberInCall"));
        }
        public void ModifyMemberStatusInCall(int operateType, int memberType, StringBuilder lyncAccount)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_ModifyMemberStatusInCall lyncAccount = {0}", lyncAccount.ToString()));
            int iRet = UCInterface.UC_SDK_ModifyMemberStatusInCall(operateType, memberType, lyncAccount);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_ModifyMemberStatusInCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_ModifyMemberStatusInCall"));
        }

        public void GetMicLevel(ref int level)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetMicLevel"));
            int iRet = UCInterface.UC_SDK_GetMicLevel(ref level);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetMicLevel = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetMicLevel"));
        }
        public void SetMicLevel(int level)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetMicLevel"));
            int iRet = UCInterface.UC_SDK_SetMicLevel(level);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetMicLevel = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetMicLevel"));
        }
        public void MuteSpker()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_MuteSpker()"));
            int iRet = UCInterface.UC_SDK_MuteSpker();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_MuteSpker = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_MuteSpker"));
        }
        public void UnMuteSpker()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_UnMuteSpker"));
            int iRet = UCInterface.UC_SDK_UnMuteSpker();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_UnMuteSpker = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_UnMuteSpker"));
        }
        public void SetSpkerLevel(int level)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetSpkerLevel"));
            int iRet = UCInterface.UC_SDK_SetSpkerLevel(level);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetSpkerLevel = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetSpkerLevel"));
        }
        public void GetSpkerLevel(ref int level)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetSpkerLevel"));
            int iRet = UCInterface.UC_SDK_GetSpkerLevel(ref level);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetSpkerLevel = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetSpkerLevel"));
        }

        public void SetVideoCallEventCallBack(CallEventCB callEventCallBack)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCallEventCallBack2"));
            int iRet = UCInterface.UC_SDK_SetVideoCallEventCallBack(callEventCallBack);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetCallEventCallBack2 = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCallEventCallBack2"));
        }
        public void SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetConfMemEventCallBack"));
            int iRet = UCInterface.UC_SDK_SetConfMemEventCallBack(confMemEventCallBack);
            if (iRet != 0)  
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetConfMemEventCallBack = {0}", iRet));              
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetConfMemEventCallBack"));
        }

        public void AcceptVideoCall(ref STVideoWindow stLocalWnd, ref STVideoWindow stRemoteWnd)//接听视频呼叫
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_AcceptVideoCall"));
            int iRet = UCInterface.UC_SDK_AcceptVideoCall(stLocalWnd.hWnd, stLocalWnd.left, stLocalWnd.top, stLocalWnd.width, stLocalWnd.height,
                                                        stRemoteWnd.hWnd, stRemoteWnd.left, stRemoteWnd.top, stRemoteWnd.width, stRemoteWnd.height);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_AcceptVideoCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_AcceptVideoCall"));
        }
        public void RejectVideoCall()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_RejectVideoCall"));
            int iRet = UCInterface.UC_SDK_RejectVideoCall();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_RejectVideoCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_RejectVideoCall"));
        }
        public void HangupVideoCall()
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_HangupVideoCall"));
            int iRet = UCInterface.UC_SDK_HangupVideoCall();
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_HangupVideoCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_HangupVideoCall"));
        }
        public void ForwardCall(int iMemberType, string pMember)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_ForwardCall"));
            int iRet = UCInterface.UC_SDK_ForwardCall(iMemberType, pMember);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_ForwardCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_ForwardCall"));
        }
        public void GetUCAccount(string phoneNum, StringBuilder _UCAcc)  //modify by jinyeqing 2015/6/9 之前是返回值是空值 现在返回INT 
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetUCAccount"));
            int iRet = UCInterface.UC_SDK_GetUCAccount(phoneNum, _UCAcc);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetUCAccount = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetUCAccount"));           
        }
        //modify byjinyeqing  2015/6/10   
        public string  GetUCAccountByPhoneNo(string phoneNum, StringBuilder _UCAcc)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetUCAccount"));
            int iRet = UCInterface.UC_SDK_GetUCAccount(phoneNum, _UCAcc);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetUCAccount = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetUCAccount"));
            string UCAcc = _UCAcc.ToString().Trim();
            return UCAcc;
        }
        //endmodify 
        public void GetContactStatus(int _AccountType, string _Account, ref int _Status)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetContactStatus"));
            int iRet = UCInterface.UC_SDK_GetContactStatus(_AccountType, _Account, ref _Status);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetContactStatus = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetContactStatus"));
        }
        public int SetCallExService(int iMemberType,  STCallExData pMember)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCallExService"));
            int iRet = UCInterface.UC_SDK_SetCallExService(iMemberType,ref pMember);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetCallExService = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCallExService"));
            return iRet;
        }

        public int GetCallExService(int _type, ref STCallExData _CallExData)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetCallExService"));
            int iRet = UCInterface.UC_SDK_GetCallExService( _type, ref _CallExData);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetCallExService = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetCallExService"));
            return iRet;
        }

        public int BlindTransCall(int iMemberType, string pMember)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_BlindTransCall"));
            int iRet = UCInterface.UC_SDK_BlindTransCall(iMemberType, pMember);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_BlindTransCall = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_BlindTransCall"));
            return iRet;
        }

        /// <summary>
        /// 该函数用于呼叫企业通讯录
        /// </summary>
        /// <param name="strSearchKey">查询关键字。为空时表示查询所有列表</param>
        /// <param name="_fromIndex">查询起始序列号。要求返回的数据</param>
        /// <param name="_toIndex">查询截止序列号。要求返回的数据,注意最多查询100</param>
        /// <param name="_pContactList">返回的数据STContactList*</param>
        /// <returns>0</returns>
        public int GetEntContactList(string strSearchKey, int _fromIndex, int _toIndex, byte[] _pContactList)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_GetEntContactList"));
            int iRet = UCInterface.UC_SDK_GetEntContactList(strSearchKey, _fromIndex, _toIndex, _pContactList);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_GetEntContactList = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_GetEntContactList"));
            return iRet;
        }

        /// <summary>
        /// 该函数用于设置呼叫转移事件回调函数
        /// </summary>
        /// <param name="crEventCallBack"></param>
        public void SetCallReservedEventCallBack(CallReservedEventCB crEventCallBack)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCallReservedEventCallBack"));
            int iRet = UCInterface.UC_SDK_SetCallReservedEventCallBack(crEventCallBack);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetCallReservedEventCallBack = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCallReservedEventCallBack"));
        }

        /// <summary>
        /// 该函数用于设置盲转呼叫事件回调函数
        /// </summary>
        /// <param name="crEventCallBack"></param>
        public void SetCallTransEventCallBack(CallTransEventCB CallTransCallBack)
        {
            LogManager.SystemLog.Debug(string.Format("Start UC_SDK_SetCallReservedEventCallBack"));
            int iRet = UCInterface.UC_SDK_SetCallTransEventCallBack(CallTransCallBack);
            if (iRet != 0)
            {
                LogManager.SystemLog.Error(string.Format("UC_SDK_SetCallTransEventCallBack = {0}", iRet));
            }
            LogManager.SystemLog.Debug(string.Format("End UC_SDK_SetCallTransEventCallBack"));
        }
    }
} 
