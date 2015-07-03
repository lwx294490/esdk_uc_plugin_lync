using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Windows;
using Microsoft.Lync.Model;
using Microsoft.Lync.Model.Group;

namespace LyncWpfApp
{
    public class WinCallReceiveViewModel
    {
        WinCallReceive winCallReceive;
        public ICommand AnswerCommand { get; set; }
        public ICommand DeclineCommand { get; set;}
        public ICommand FinishCommand { get; set; }
        bool isVideo = false;
        public bool isAnswerMessage = false;
        CallReceiveBusiness callBusiness = new CallReceiveBusiness();
        public WinCallReceiveViewModel(WinCallReceive window, bool video)
        {
            winCallReceive = window;
            isVideo = video;
            AnswerCommand = new DelegateCommand(AnswerCommandProcess);
            DeclineCommand = new DelegateCommand(DeclineCommandProcess);
            FinishCommand = new DelegateCommand(FinishCommandProcess);
        }
        private void FinishCommandProcess()
        {
            if ("" == winCallReceive.txtOtherPhone.Text)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            MakeCallBusiness bus = new MakeCallBusiness();
            bus.ForwardCall((int)MemberType.UC_IPPHONE, winCallReceive.txtOtherPhone.Text.ToString());
            winCallReceive.Close();
        }
        private void AnswerCommandProcess()
        {
            try
            {
                //if (!isVideo)
                //{                                                     
                //    callBusiness.AnswerCall();
                //}

                winCallReceive.isCloseButton = false;
                isAnswerMessage = false;
                winCallReceive.Close();
                if (winCallReceive.lync.timer == null || !winCallReceive.lync.timer.Enabled)
                {
                    WinCall call;
                    if (isVideo)
                    {
                        call = new WinCall(winCallReceive.lync, "VideoCall;" + winCallReceive.callName + ";" + SingletonObj.LoginInfo.LyncName);
                        call.callType = CallHistoryType.HISTORY_CALL_ANSWERED;
                    }
                    else
                    {
                        call = new WinCall(winCallReceive.lync, winCallReceive.callName + ";" + SingletonObj.LoginInfo.LyncName);
                        call.callType = CallHistoryType.HISTORY_CALL_ANSWERED;
                    }
                    winCallReceive.lync.winCall = call;
                    call.Show();
                    winCallReceive.lync.UCAVSessionConnected();
                }
                else
                {
                    winCallReceive.lync.winCall.model.IsVideo = true;
                    winCallReceive.lync.winCall.SetWinSize();
                    if (winCallReceive.lync.winCall.video == null)
                    {
                        winCallReceive.lync.winCall.SetUCVideo();
                    }
                    winCallReceive.lync.winCall.model.AcceptVideoCall();
                }
                if (!isVideo)
                {
                    callBusiness.AnswerCall();
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
           
        }

       

        private void DeclineCommandProcess()
        {
            isAnswerMessage = false;
            if (!isVideo)
            {
                callBusiness.RejectCall();
            }
            else
            {
                MakeCallBusiness bus = new MakeCallBusiness();
                bus.RejectVideoCall();
            }
            winCallReceive.isCloseButton = false;
            if (winCallReceive.Visibility == Visibility.Visible )
            {
                winCallReceive.Close();
            }         
            string name = StringHelper.GetSubString(winCallReceive.callName);
            string url = StringHelper.GetLyncUrl(name);
           
            HistoryQueryBusiness query = new HistoryQueryBusiness();
            query.InsertCallHistory(CallHistoryType.HISTORY_CALL_MISSED, url, name, -1);
        }
    }
}
