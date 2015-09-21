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
            //2015/7/27   为空和数字校验
            if ("" == winCallReceive.txtOtherPhone.Text.Trim())
            {
                DialogShow.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            if (IsValidPhoneNumber(winCallReceive.txtOtherPhone.Text)==false)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            if (winCallReceive.UcPhoneNo == winCallReceive.txtOtherPhone.Text || winCallReceive.UcPhoneNo1 == winCallReceive.txtOtherPhone.Text)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannottansfer"), StringHelper.FindLanguageResource("error"), 2);
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
                //winCallReceive.lync.isHave = false;
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
                callBusiness.RejectCall();  //超时不做这个动作，只关界面   2015/7/28
            }
            else
            {
                MakeCallBusiness bus = new MakeCallBusiness();
                bus.RejectVideoCall();
            }
            winCallReceive.isCloseButton = false;

            //7/27 
            winCallReceive.lync.setBtn();   //先设置图形
            //if (winCallReceive.lync.toolBar.JointType == PhoneJointType.PC_Device)
            //{
            //    if (winCallReceive.lync.winCall.btnVideo.IsEnabled == false)
            //    {
            //        winCallReceive.lync.winCall.btnVideo.IsEnabled = true;
            //        UpdateImage.UpdateData(winCallReceive.lync.winCall.imgVideo, "/Image/call/video_1.png");
            //    }                
                                         
            //}

            if (winCallReceive.Visibility == Visibility.Visible )
            {
                winCallReceive.Close();
                winCallReceive.lync.isHave = false;
            }         
            string name = StringHelper.GetSubString(winCallReceive.callName);
            string url = StringHelper.GetLyncUrl(name);
           
            HistoryQueryBusiness query = new HistoryQueryBusiness();
            query.InsertCallHistory(CallHistoryType.HISTORY_CALL_MISSED, url, name, -1);
        }

      

        /// <summary>
        /// 校验是否为纯数字
        /// werther the number is right or not 
        /// </summary>
        /// <param name="dialContent"></param>
        public bool IsValidPhoneNumber(string phoneNumber)
        {
            if (string.IsNullOrEmpty(phoneNumber))
            {
                return false;
            }

            phoneNumber = phoneNumber.Trim();

            foreach (char ch in phoneNumber)
            {
                if ((ch >= '0' && ch <= '9') || ch == '*' || ch == '#')
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

    }
}
