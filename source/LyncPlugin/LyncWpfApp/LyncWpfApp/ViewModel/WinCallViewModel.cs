 using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using System.Windows.Controls;
using System.Data;
using System.Windows;
using System.Windows.Threading;
using System.Threading;
using Microsoft.Lync.Model;
using Microsoft.Lync.Model.Group;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace LyncWpfApp
{
    public class WinCallViewModel
    {
         WinCall winCall;
         WinLync winlync;         
         //WinCallReceive wincallreceive;
         //TimingMessageBox WinMess;
         public bool flag = false;
         public bool flag1 = false;
         [DllImport("user32.dll", EntryPoint = "ShowWindow", SetLastError = true)]
         static extern bool ShowWindow(IntPtr hWnd, uint nCmdShow);
         [DllImport("user32.dll", EntryPoint = "DestroyWindow", SetLastError = true)]
         static extern bool DestroyWindow(IntPtr hWnd);
         public static object lockObject = new object();
        public ICommand VideoCommand { get; set; }
        public ICommand CallSuspendCommand { get; set; }
        public ICommand HoldDownCommand { get; set; }
        public ICommand SetMicPhoneCommand { get; set; }
        public ICommand AddContactCommand { get; set; }
        public ICommand MuteCommand { get; set; }
        public ICommand HoldDownOneCommand { get; set; }
        public ICommand ReInviteOneCommand { get; set; }
        public ICommand RemoveCommand { get; set; }
        public ICommand OpenDialCommand { get; set; }
        public ICommand SetVolCommand { get; set; }
        public ICommand BlindTransCallCommand { get; set; }
        public int a = 1;
       
        public bool StrTemp;
        public int uiSize ;
        public byte[] pSTContactList ;

        public bool isVideo = false;

        public bool IsVideo
        {
            get
            {
                return isVideo;
            }
            set
            {
                isVideo = value;
                winCall.SetButCallSuspEnable(isVideo);
            }
        }
        MakeCallBusiness call = new MakeCallBusiness();
        List<UCContact> contactList;
        ConfMemberEventCB callBackConfMemberEventCB;
        CallEventCB callBackVideoCallEventCB;
        CallReservedEventCB callReservedEventCB;
        CallTransEventCB callTransEventCB;  //modify by jinyeqing 6/3       
       
        public WinCallViewModel(WinCall window, string str)
        {
            try
            {
                //if (SingletonObj.LoginInfo.LyncName != str.Split(';')[0] && str.Split(';').Length != 1)
                //{
                //    this.flag = false;
                //}
                //else
                //{
                //    this.flag = true;
                //}
                //StrTemp = winlync.strTempBool.ToString();                
                callBackConfMemberEventCB = new ConfMemberEventCB(callBackConfMemberEventCBProcess);
                callBackVideoCallEventCB = new CallEventCB(callBackVideoCallEventCBProcess);
                callReservedEventCB = new CallReservedEventCB(callReservedEventCBProcess);
                callTransEventCB = new CallTransEventCB(callTransEventCBProcess);
                //modify by jinyeqing 2015/5/22   jiaji 说要把这三个事件回调函数放之前  （上下顺序倒了一下  下面的注释了）              
                call.SetConfMemEventCallBack(callBackConfMemberEventCB);

                call.SetVideoCallEventCallBack(callBackVideoCallEventCB);

                call.SetCallReservedEventCallBack(callReservedEventCB);

                call.SetCallTransEventCallBack(callTransEventCB);
                //modify by jinyeqing 2015/5/22   jiaji 说要把这三个事件回调函数放之前  （上下顺序倒了一下  下面的注释了）
                winCall = window;

                VideoCommand = new DelegateCommand(VideoCommandProcess);
                CallSuspendCommand = new DelegateCommand(CallSuspendCommandProcess);
                HoldDownCommand = new DelegateCommand(HoldDownCommandProcess);
                SetMicPhoneCommand = new DelegateCommand(SetMicPhoneCommandProcess);
                AddContactCommand = new DelegateCommand(AddContactCommandProcess);

                HoldDownOneCommand = new DelegateCommand(HoldDownOneCommandProcess);
                ReInviteOneCommand = new DelegateCommand(ReInviteOneCommandProcess);

                MuteCommand = new DelegateCommand(MuteCommandProcess);
                RemoveCommand = new DelegateCommand(RemoveCommandProcess);
                OpenDialCommand = new DelegateCommand(OpenDialCommandProcess);
                SetVolCommand = new DelegateCommand(SetVolCommandProcess);
                BlindTransCallCommand = new DelegateCommand(BlindTransCallCommandProcess);
                this.winlync = winCall.lync;   //modify by 00327190 2015/7/16
                try
                {

                    lock (WinCall.lockObject)
                    {                       
                       
                        try
                        {
                            LogManager.SystemLog.Info("WinCallViewModel Monitor.Enter");
                            contactList = new List<UCContact>();

                            string[] listStr = str.Split(';');
                            foreach (string con in listStr)
                            {
                                if (str.IndexOf("VideoCall") > -1 && contactList.Count == 2)
                                {
                                    break;
                                }
                                if (con == "VideoCall")
                                {
                                    IsVideo = true;
                                    continue;
                                }
                                UCContact uc = new UCContact();
                                uc.UserName = con;

                                if (contactList.Exists(x => x.UserName == uc.UserName))
                                {
                                    continue;
                                }

                                if (uc.UserName.IndexOf("@") != -1)
                                {
                                    uc.UCMemberType = MemberType.UC_ACCOUNT;
                                }
                                else  //如果是纯数字，则再分能不能查到对应的UC用户  2015/9/21
                                {
                                    StringBuilder ucName = new StringBuilder(100);
                                    call.GetUCAccountByPhoneNo(uc.UserName, ucName);
                                    if (ucName.ToString() == "")  //纯话机   2015/9/21
                                    {
                                        uc.UCMemberType = MemberType.UC_IPPHONE;
                                    }
                                    else
                                    {
                                        uc.UCMemberType = MemberType.UC_ACCOUNT;
                                        uc.UserName = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);                                       
                                    }
                                    //uc.UCMemberType = MemberType.UC_IPPHONE;
                                }
                                if (contactList.Count == 0)
                                {
                                    if (IsVideo)
                                    {
                                        //2015/8/24    UTF8 转码UNICODE
                                        //byte[] buffer1 = Encoding.Default.GetBytes(str);
                                        //byte[] buffer2 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer1, 0, buffer1.Length);
                                        //string strBuffer = Encoding.Default.GetString(buffer2, 0, buffer2.Length);
                                        winCall.Title = (uc.UserName == SingletonObj.LoginInfo.LyncName ? str.Split(';')[2].ToString() : uc.UserName);
                                    }
                                    else
                                    {
                                        //2015/8/24    UTF8 转码UNICODE
                                        //byte[] buffer1 = Encoding.Default.GetBytes(str);
                                        //byte[] buffer2 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer1, 0, buffer1.Length);
                                        //string strBuffer = Encoding.Default.GetString(buffer2, 0, buffer2.Length);
                                        winCall.Title = (uc.UserName == SingletonObj.LoginInfo.LyncName ? str.Split(';')[1].ToString() : uc.UserName);
                                    }
                                    uc.IsLeader = true;
                                    uc.Mute = MemStatusInCall.CONF_MEM_INCONF;
                                }
                                else
                                {
                                    uc.Mute = MemStatusInCall.CONF_MEM_INVITING;
                                }
                                uc.Online = GetContactAvailability((int)uc.UCMemberType, StringHelper.GetSubString(uc.UserName));
                                contactList.Add(uc);
                            }

                            bool isConf = false;
                            if (contactList.Count > 2)
                            {
                                isConf = true;
                                StrTemp = isConf;
                            }
                            winCall.Render(contactList, isConf);                         
                        }
                        finally
                        {
                            LogManager.SystemLog.Info("WinCallViewModel Monitor.Exit");
                        }
                        //call.SetConfMemEventCallBack(callBackConfMemberEventCB);

                        //call.SetVideoCallEventCallBack(callBackVideoCallEventCB);

                        //call.SetCallReservedEventCallBack(callReservedEventCB);
                    }

                   

                  
                }
                catch (System.Exception ex)
                {
                    LogManager.SystemLog.Error(ex.ToString());
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
           
        }
        public void OpenDialCommandProcess()
        {
            if (winCall.lync.winTwoDail == null)
            {
                winCall.lync.winTwoDail = new WinTwoDail(winCall.lync);
                winCall.lync.winTwoDail.Show();
            }
            //modify by 00327190  2015/7/23  如果已经打开，再次按此按钮则显示画面    
            //Click the button to show the window again if the window was opened  already
            else
            {
                Window frm = winCall.lync.winTwoDail;
                frm.Focus();
                //获取该界面句柄       //Get handle of the interface 
                IntPtr hwnd = new WindowInteropHelper(winCall.lync.winTwoDail).Handle;
                //显示窗体   //show the window 
                ShowWindow(hwnd, 1);
            }
        }
        public void HoldDownOneCommandProcess()
        {
            Thread thread = new Thread(new ThreadStart(HoldDownOneCommandThread));
            thread.Start();
        }
        void HoldDownOneCommandThread()
        {
            lock (WinCall.lockObject)
            {
              
                try
                {
                    LogManager.SystemLog.Info("HoldDownOneCommandProcess Monitor.Enter");
                    int index = winCall.GetSelectListIndex();
                    if (index < 0)
                    {
                        return;
                    }
                    call.ModifyMemberStatusInCall((int)MemberStatusInCall.EndCallMember, (int)contactList[index].UCMemberType, new StringBuilder(StringHelper.GetSubString(contactList[index].UserName)));
                    contactList[index].Mute = MemStatusInCall.CONF_MEM_HANGUP;
                    //winCall.Render(contactList);
                }
                finally
                {
                    LogManager.SystemLog.Info("HoldDownOneCommandProcess Monitor.Exit");
                }
            }
          
        }
        public void ReInviteOneCommandProcess()
        {
            Thread thread = new Thread(new ThreadStart(ReInviteOneCommandThread));
            thread.Start();
        }
        void ReInviteOneCommandThread()
        {
            lock (WinCall.lockObject)
            {
               
                try
                {
                    LogManager.SystemLog.Info("ReInviteOneCommandProcess Monitor.Enter");
                    int index = winCall.GetSelectListIndex();
                    if (index < 0)
                    {
                        return;
                    }
                    call.ModifyMemberStatusInCall((int)MemberStatusInCall.ReInviteMember, (int)contactList[index].UCMemberType, new StringBuilder(StringHelper.GetSubString(contactList[index].UserName)));
                    contactList[index].Mute = MemStatusInCall.CONF_MEM_INVITING;
                    //winCall.Render(contactList);
                }
                finally
                {
                    LogManager.SystemLog.Info("ReInviteOneCommandProcess Monitor.Exit");

                }
            }
           
        }

        public void MuteCommandProcess()
        {
            Thread thread = new Thread(new ThreadStart(MuteCommandThread));
            thread.Start();
        }
        void MuteCommandThread()
        {
            lock (WinCall.lockObject)
            {
               
                try
                {
                    LogManager.SystemLog.Info("MuteCommandProcess Monitor.Enter");
                    int index = winCall.GetSelectListIndex();
                    if (index < 0)
                    {
                        return;
                    }
                    bool mute = contactList[index].Mute == MemStatusInCall.CONF_MEM_MUTE;
                    contactList[index].Mute = mute ? MemStatusInCall.CONF_MEM_UnMute : MemStatusInCall.CONF_MEM_MUTE;
                    //winCall.Render(contactList);

                    if (mute)
                    {
                        call.ModifyMemberStatusInCall((int)MemberStatusInCall.UnMuteMember, (int)contactList[index].UCMemberType, new StringBuilder(StringHelper.GetSubString(contactList[index].UserName)));
                    }
                    else
                    {
                        call.ModifyMemberStatusInCall((int)MemberStatusInCall.MuteMember, (int)contactList[index].UCMemberType, new StringBuilder(StringHelper.GetSubString(contactList[index].UserName)));
                    }
                }
                finally
                {
                    LogManager.SystemLog.Info("MuteCommandProcess Monitor.Exit");
                }
            }
           
        }
        public void RemoveCommandProcess()
        {
            Thread thread = new Thread(new ThreadStart(RemoveCommandThread));
            thread.Start();
        }
        void RemoveCommandThread()
        {
            lock (WinCall.lockObject)
            {
              
                try
                {
                    LogManager.SystemLog.Info("RemoveCommandProcess Monitor.Enter");
                    int index = winCall.GetSelectListIndex();
                    if (index < 0)
                    {
                        return;
                    }
                    string name = StringHelper.GetSubString(contactList[index].UserName);
                    if (index > 0)  //modify by jinyeqing    
                    {
                        LogManager.SystemLog.Info(string.Format("index={0} and contactList[index]={1} ", index, contactList[index].UserName));
                        call.DeleteMemberInCall((int)contactList[index].UCMemberType, new StringBuilder(name));
                        contactList.RemoveAt(index);
                        winCall.Render(contactList);
                        winCall.DecreaseContactWinSize(contactList);
                    }
                }
                finally
                {
                    LogManager.SystemLog.Info("RemoveCommandProcess Monitor.Exit");
                }
            }
          
        }
        private void SetMicPhoneCommandProcess()
        {
            if (winCall.imgMic.Source.ToString().IndexOf("Unmic") > 0)
            {
                UpdateImage.UpdateData(winCall.imgMic, "/Image/call/Mic_2.png");
                call.UnMuteMic();
            }
            else
            {
                UpdateImage.UpdateData(winCall.imgMic, "/Image/call/Unmic_2.png");
                call.MuteMic();
            }
        }

        public void AcceptVideoCall()   //视频被呼叫
        {
            IsVideo = true;
            STVideoWindow stLocalWnd = new STVideoWindow();
            STVideoWindow stRemoteWnd = new STVideoWindow();
            winCall.GetVideoPlayPara(ref stLocalWnd, ref stRemoteWnd);
            call.AcceptVideoCall(ref stLocalWnd, ref stRemoteWnd);
            winCall.SetVideoImage();           
            winCall.SetVideoLocalRemoteSize();
        }
        private void VideoCommandProcess()
        {
            try
            {
                IsVideo = true;
                if (winCall.imgVideo.Source.ToString().IndexOf("unvideo") == -1)
                {
                    winCall.SetWinSize();
                    if (winCall.video == null)
                    {
                        winCall.SetUCVideo();
                    }
                    //2015/7/27
                    if (winlync.isConnected == true)
                    {
                        winCall.btnVideo.IsEnabled = false;
                    }
                    STVideoWindow stLocalWnd = new STVideoWindow();
                    STVideoWindow stRemoteWnd = new STVideoWindow();
                    winCall.GetVideoPlayPara(ref stLocalWnd, ref stRemoteWnd);
                    call.MakeVideoCall(ref stLocalWnd, ref stRemoteWnd);
                    winCall.SetVideoImage();
                    winCall.SetVideoLocalRemoteSize();
                }
                else
                {
                    winCall.isreturn = false;
                    // "强制变为false";
                    call.HangupVideoCall();
                }
              
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }


        private void CallSuspendCommandProcess()
        {
            if (winCall.imgCallSuspend.Source.ToString().IndexOf("CallHold") > 0)
            {
                UpdateImage.UpdateData(winCall.imgCallSuspend, "/Image/call/Resume_1.png");
                call.holdCall();
                if (winCall.strtemp.Split(';')[0] != "VideoCall" && winCall.strtemp.Split(';')[0] !="Call")  //直接人名打头的情况   2015/8/5
                {

                    //主被叫呼叫保持时的加人按钮的状态   modify by 00327190 2015/7/16
                    if (SingletonObj.LoginInfo.LyncName != winCall.strtemp.Split(';')[0] && winCall.strtemp.Split(';').Length != 1)   //被叫   //之前是str.Split(';')[0]    2015/7/30
                    {
                       
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnVideo.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = false;
                        if (winCall.lync.isConnected == true)   //语音升级视频下，如果按保持呼叫按钮 winCall.lync.Ishold = true;  //2015/8/18
                        {
                            winCall.lync.Ishold = true;
                        }
                    }
                    else
                    {
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnVideo.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = false;
                        if (winCall.lync.isConnected == true)   //语音升级视频下，如果按保持呼叫按钮 winCall.lync.Ishold = true;  //2015/8/18
                        {
                            winCall.lync.Ishold = true;
                        }
                    }
                }
                else     //视频情况下   2015/8/5
                {
                    if (SingletonObj.LoginInfo.LyncName != winCall.strtemp.Split(';')[1] && winCall.strtemp.Split(';').Length != 1)   //被叫   //之前是str.Split(';')[0]    2015/7/30
                    {
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnVideo.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = false;
                        winCall.lync.Ishold = true;

                    }
                    else
                    {
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnVideo.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = false;
                        winCall.lync.Ishold = true;
                    }
                }

            }
            else
            {
                UpdateImage.UpdateData(winCall.imgCallSuspend, "/Image/call/CallHold_1.png");
                call.resumeCall();
                //主被叫取消呼叫保持时的加人按钮的状态   modify by 00327190 2015/7/16
                if (winCall.strtemp.Split(';')[0] != "VideoCall" && winCall.strtemp.Split(';')[0] != "Call")  //语音情况下   2015/8/5
                {
                    if (SingletonObj.LoginInfo.LyncName != winCall.strtemp.Split(';')[0] && winCall.strtemp.Split(';').Length != 1)   //被叫  //被叫   //之前是str.Split(';')[0]    2015/7/30
                    {
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = true;
                        winCall.lync.Ishold = false;  //8/18
                        //话机联动状态下,视频按钮不能使用
                        //If you are in phone joint,you can not use the Video button
                        if (winlync.toolBar.JointType == PhoneJointType.IPPhone_Device)
                        {
                            winCall.btnVideo.IsEnabled = false;
                            UpdateImage.UpdateData(winCall.imgVideo, "/Image/call/video_3.png");
                        }
                        else
                        {
                            winCall.btnVideo.IsEnabled = true;
                        }
                    }
                    else
                    {
                        winCall.btnAddContact.IsEnabled = true;
                        winCall.btnBlindTransCall.IsEnabled = true;
                        winCall.lync.Ishold = false;  //8/18
                        //话机联动状态下,视频按钮不能使用
                        //If you are in phone joint,you can not use the Video button
                        if (winlync.toolBar.JointType == PhoneJointType.IPPhone_Device)
                        {
                            winCall.btnVideo.IsEnabled = false;
                            UpdateImage.UpdateData(winCall.imgVideo, "/Image/call/video_3.png");
                        }
                        else
                        {
                            winCall.btnVideo.IsEnabled = true;
                        }
                    }
                }
                else    //视频或者开始为Call情况下   2015/8/5
                {
                    if (SingletonObj.LoginInfo.LyncName != winCall.strtemp.Split(';')[1] && winCall.strtemp.Split(';').Length != 1)   //被叫  //被叫   //之前是str.Split(';')[0]    2015/7/30
                    {
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = true;
                        winCall.lync.Ishold = false;  //8/5 

                        //话机联动状态下,视频按钮不能使用
                        //If you are in phone joint,you can not use the Video button
                        if (winlync.toolBar.JointType == PhoneJointType.IPPhone_Device)
                        {
                            winCall.btnVideo.IsEnabled = false;
                            UpdateImage.UpdateData(winCall.imgVideo, "/Image/call/video_3.png");
                        }
                        else
                        {
                            winCall.btnVideo.IsEnabled = true;
                        }
                    }
                    else
                    {
                        winCall.btnAddContact.IsEnabled = true;
                        winCall.btnBlindTransCall.IsEnabled = true;
                        winCall.lync.Ishold = false;   //8/5
                        //话机联动状态下,视频按钮不能使用
                        //If you are in phone joint,you can not use the Video button
                        if (winlync.toolBar.JointType == PhoneJointType.IPPhone_Device)
                        {
                            winCall.btnVideo.IsEnabled = false;
                            UpdateImage.UpdateData(winCall.imgVideo, "/Image/call/video_3.png");
                        }
                        else
                        {
                            winCall.btnVideo.IsEnabled = true;
                        }
                    }
                }
            }
        }
        private void HoldDownCommandProcess()
        {
            if (winCall.lync.isHave == true)
            {
                call.RejectVideoCall();                 
                Thread.Sleep(1000);                             
            }
            call.hangupCall();
            winCall.Close();
            if (winCall.lync.isHave == true)
            {
                //强制关闭Receive界面                 
                DestroyWindow(winCall.lync.hwnd);
                winCall.lync.isHave = false;
            }
            winCall.lync.Ishold = false;   //2015/8/18 
            winCall.lync.IsBlindTrans = false;   //2015/8/18
        }
        void AddContactCommandProcess()
        {
            if (winCall.lync.winAllContact == null)
            {
                winCall.lync.winAllContact = new WinAllContact(winCall.lync);
                winCall.lync.winAllContact.AddContactChanged = GetSelectContact;
                winCall.lync.winAllContact.Show();
            }
          
        }
        void GetSelectContact(DataTable dt)
        {
            Thread thread = new Thread(new ParameterizedThreadStart(GetSelectContactFun));
            thread.Priority = ThreadPriority.AboveNormal;
            thread.Start(dt);

        }
        /// <summary>
        /// 增加新的与会人
        /// </summary>
        /// <param name="obj"></param>
        void GetSelectContactFun(object obj)
        {
            DataTable dt1 = (DataTable)obj;
            //modifty by 00327190  做校验，防止已经通话中的人再次入会
            for (int i = 0; i < contactList.Count; i++)
            {
                for (int j = 0; j < dt1.Rows.Count; j++)
                {
                    string b = dt1.Rows[j]["Url"].ToString().Trim();
                    if (b != "" && b != null)     //UC帐号和话机联动账号添加，url不空
                    {
                        string a = contactList[i].UserName.ToString().Trim();                       
                        //string c = a.Substring(0, a.Length - 10).ToString().Trim();   //这个是截取 @lync1.com之前的字符串的方法                        
                        if (String.Compare(a, b) == 0 || a.Equals(b) || a == b)
                        {
                            string message = (a) + " " + StringHelper.FindLanguageResource("theconferencehassameperson");
                            winCall.OpenDialogTiming(message, "error", 2);
                            dt1.Rows[j].Delete();
                           // return;
                        }
                    }
                    else   //话机添加（没有对应UC账号），url为空，只能根据phone比较
                    {

                        string a = contactList[i].UserName.ToString().Trim();
                        string d = dt1.Rows[j]["phone"].ToString().Trim();
                        if (String.Compare(a, d) == 0 || a.Equals(d) || a == d)
                        {
                            string message = (a)+ " " +StringHelper.FindLanguageResource("theconferencehassameperson");                           
                            winCall.OpenDialogTiming(message, "error", 2);
                            dt1.Rows[j].Delete();
                            //return;
                        }

                    }
                   
                }

            }
            dt1.AcceptChanges();
            int count = dt1.Rows.Count + contactList.Count;          
            if (dt1.Rows.Count != 0)
            {
                if (count <= 20)   //多于20个人就不添加了 (应该是原先列表加上新加的人数大于20才不添加)
                {
                    lock (WinCall.lockObject)
                    {
                       
                        if (StrTemp == true)   //为conference 时，走这个接口 
                        {
                            try
                            {

                                LogManager.SystemLog.Info("GetSelectContactFun Monitor.Enter");
                                DataTable dt = (DataTable)obj;
                                int type = 0;
                                foreach (DataRow dr in dt1.Rows)
                                {
                                    string str = dr["Url"].ToString() == "" ? dr["Phone"].ToString() : dr["Url"].ToString();
                                    string userName = "";
                                    if (str.IndexOf("sip") > -1)
                                    {
                                        str = str.Substring(str.IndexOf(":") + 1);
                                    }
                                    STConfMember ST = new STConfMember();
                                    StringBuilder ucName = new StringBuilder(100);
                                    // if (call.GetUCAccount(str, ucName) == 0)   //回调成功   modify by 00327190   之前没有if判断，现在只有能成功才可以入会 
                                    //{
                                    if (dr["Name"].ToString() == "")
                                    {
                                        call.GetUCAccount(str, ucName);
                                        if (ucName.ToString() != "")
                                        {
                                            userName = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                                            type = 0;
                                            str = userName.ToString();
                                            //2015/8/6
                                            ST.membertype = type;
                                            ST.account = ucName.ToString();
                                        }
                                        else
                                        {
                                            userName = str;
                                            type = 1;
                                            //2015/8/6
                                            ST.membertype = type;
                                            ST.account = str;
                                        }
                                    }
                                    else
                                    {
                                        userName = str;
                                        type = 0;
                                        //2015/8/6
                                        ST.membertype = type;
                                        ST.account = str.Replace(StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName), "");
                                    }

                                    UCContact uc = new UCContact();

                                    uc.UCMemberType = (MemberType)type;
                                    uc.Mute = MemStatusInCall.CONF_MEM_INVITING;
                                    uc.UserName = userName;
                                    uc.Online = GetContactAvailability(type, StringHelper.GetSubString(uc.UserName));//查询uc状态

                                    contactList.Add(uc);

                                    call.InviteMemberInCall(type, new StringBuilder(StringHelper.GetSubString(str)));

                                    //}
                                    //else
                                    //{
                                    //    string message = StringHelper.FindLanguageResource("error") + (str);
                                    //    winCall.OpenDialogTiming(message, "error", 3);
                                    //}
                                }
                                IEnumerable<UCContact> noduplicates = contactList.Distinct(new ContactCompar());
                                List<UCContact> temp = new List<UCContact>();
                                foreach (var contact in noduplicates)
                                {
                                    temp.Add(contact);
                                }
                                contactList = temp;
                                winCall.Render(contactList);
                                winCall.IsEnableChanged();


                            }

                            finally
                            {
                                LogManager.SystemLog.Info("GetSelectContactFun Monitor.Exit");
                            }
                        }
                        else   ////为call 时，点呼转多人，走这个接口 
                        {
                            StrTemp = true;
                            LogManager.SystemLog.Info("GetSelectContactFun Monitor.Enter");
                            DataTable dt = (DataTable)obj;
                            int type = 0;

                            STConfMemList ST1 = new STConfMemList();
                            ST1.stConfMem = new STConfMember[dt.Rows.Count];
                            ST1.size = dt.Rows.Count;
                            for (int i = 0; i < dt1.Rows.Count; i++)
                            {
                                DataRow dr = dt.Rows[i];
                                STConfMember ST = new STConfMember();

                                string str = dr["Url"].ToString() == "" ? dr["Phone"].ToString() : dr["Url"].ToString();
                                string userName = "";
                                if (str.IndexOf("sip") > -1)
                                {
                                    str = str.Substring(str.IndexOf(":") + 1);
                                }
                                StringBuilder ucName = new StringBuilder(100);
                                if (dr["Name"].ToString() == "")
                                {
                                    call.GetUCAccount(str, ucName);
                                    if (ucName.ToString() != "")
                                    {
                                        userName = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);  
                                        type = 0;
                                        str = userName.ToString();
                                        ST.membertype = type;
                                        ST.account = ucName.ToString();
                                    }
                                    else
                                    {
                                        userName = str;
                                        type = 1;
                                        ST.membertype = type;
                                        ST.account = str;
                                    }
                                }
                                else
                                {
                                    userName = str;
                                    type = 0;
                                    ST.membertype = type;
                                    ST.account = str.Replace(StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName), "");
                                }

                                ST1.stConfMem[i] = ST;
                                ST1.size = i + 1;
                                UCContact uc = new UCContact();
                                uc.UCMemberType = (MemberType)type;
                                uc.Mute = MemStatusInCall.CONF_MEM_INVITING;
                                uc.UserName = userName;
                                uc.Online = GetContactAvailability(type, StringHelper.GetSubString(uc.UserName));//查询uc状态
                                contactList.Add(uc);

                            }
                            int iSizeSTContact = Marshal.SizeOf(typeof(STConfMember));
                            int iSizeSTContactList = Marshal.SizeOf(typeof(STConfMemList));
                            uiSize = iSizeSTContactList + (dt.Rows.Count - 1) * iSizeSTContact;
                            pSTContactList = StructToBytes(ST1);
                            if (call.UC_SDK_TransCallToConf(pSTContactList, uiSize) == 0)
                            {
                                IEnumerable<UCContact> noduplicates = contactList.Distinct(new ContactCompar());
                                List<UCContact> temp = new List<UCContact>();
                                foreach (var contact in noduplicates)
                                {
                                    temp.Add(contact);
                                }
                                contactList = temp;
                                winCall.Render(contactList);
                                //winCall.IsConf();
                                winCall.IsEnableChanged();
                            }
                            else
                            {
                                DialogShow.Show(StringHelper.FindLanguageResource("error"), StringHelper.FindLanguageResource("error"), 2);
                                return;
                            }
                        }
                    }

                }
                else
                {
                    winCall.OpenDialogTiming("somanypeople", "error", 2);
                    winCall.lync.setBtn();  //2015/8/17   之前由于视频转移导入的添加界面OK键使得加人键禁用原因
                    return;
                }
            }
            else
            {
                //winCall.OpenDialogTiming("PleaseAddOneAccountFirst", "error", 2);
                //return;
            }
           
            winCall.lync.setBtn();
        }

        
        //struct转换为byte[]
        public static byte[] StructToBytes(STConfMemList structObj)
        {           
            int iSizeSTContact = Marshal.SizeOf(typeof(STConfMember));
            int iSizeSTContactList = Marshal.SizeOf(typeof(STConfMemList));
            int uiSize = iSizeSTContactList + (structObj.size - 1) * iSizeSTContact;
            IntPtr buffer = Marshal.AllocHGlobal(uiSize);
            try
            {
                Marshal.StructureToPtr(structObj, buffer, false);
                byte[] bytes = new byte[uiSize];
                Marshal.Copy(buffer, bytes, 0, uiSize);
                return bytes;
            }
            finally
            {
                Marshal.FreeHGlobal(buffer);
            }
        }
    


        public void Slider_ValueChanged(double newValue, string type)
        {
            if (type == "MicPhone")
            {
                call.SetMicLevel((int)newValue);                       
            }
            else
            {
                call.SetSpkerLevel((int)newValue);               
            }
        }
        public int Slider_GetValue(string type)
        {
            int newValue = 0;
            if (type == "MicPhone")
            {
                call.GetMicLevel(ref newValue);
            }
            else
            {
                call.GetSpkerLevel(ref newValue);
            }
            return newValue;
        }
        private void SetVolCommandProcess()
        {
            if (winCall.imgVol.Source.ToString().IndexOf("Spker") > 0)
            {
                UpdateImage.UpdateData(winCall.imgVol, "/Image/call/Unspker_2.png");
                call.MuteSpker();
            }
            else
            {
                UpdateImage.UpdateData(winCall.imgVol, "/Image/call/Spker_2.png");
                call.UnMuteSpker();
            }
        }

        /// <summary>
        /// 该函数用于呼叫盲转，当终端已经处于通话状态时，直接转移
        /// </summary>
        private void BlindTransCallCommandProcess()
        {
            if (winCall.lync.winAllContact == null)
            {
                winCall.lync.winAllContact = new WinAllContact(winCall.lync,true);
                winCall.lync.winAllContact.AddContactChanged = GetBlindContact;
                winCall.lync.winAllContact.Show();
                winCall.lync.IsBlindTrans = true;
            }

        }

        /// <summary>
        /// 盲转处理函数
        /// </summary>
        /// <param name="dt"></param>
        private void GetBlindContact(DataTable dt)
        {
            int type = 0;
            foreach (DataRow dr in dt.Rows)
            {
                string str = dr["Url"].ToString() == "" ? dr["Phone"].ToString() : dr["Url"].ToString();
                string userName = "";
                if (str.IndexOf("sip") > -1)
                {
                    str = str.Substring(str.IndexOf(":") + 1);
                }
                StringBuilder ucName = new StringBuilder(100);
                if (dr["Name"].ToString() == "")
                {
                    call.GetUCAccount(str, ucName);
                    if (ucName.ToString() != "")
                    {
                        userName = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                        type = 0;
                        str = userName.ToString();
                    }
                    else
                    {
                        userName = str;
                        type = 1;
                    }
                }
                else
                {
                    userName = str;
                    type = 0;
                }

                userName = StringHelper.GetSubString(str);

                int iRet = call.BlindTransCall(type, userName);
                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    winCall.lync.IsTransfer = true;
                    LogManager.SystemLog.Error("BlindTransCall error");
                    winCall.OpenDialog("BlindTransCallFail", "error");                    
                    winCall.lync.setBtn();   //2015/8/18
                }
                break;
            }
        }
        private void callBackVideoCallEventCBProcess(ref STCallParam _callParam)//视频呼叫回调
        {
            string acc = _callParam.ucAcc;
            CallStatus st = (CallStatus)_callParam.callStatus;

            if (st == CallStatus.CALL_VIDEO_REQ)
            {
                winCall.ShowReceiveWin(_callParam);
            }
            else if (st == CallStatus.CALL_VIDEO_CLOSE)
            {
                //2015/7/27
                if (winCall.lync.isConnected == true)   //语音升级视频
                {
                    if (winCall.lync.toolBar.JointType == PhoneJointType.PC_Device)
                    {
                        winCall.VideoClose(); 
                    }
                }
                CloseVideo();               
            }
                //modify by 00327190   2015/7/27
            else if (st == CallStatus.CALL_VIDEO_CONNECTED)
            {
                winCall.VideoConnected();                

            }

        }
      
        void CloseVideo()
        {
            winCall.CloseWinVideo();
            
        }
        private void callBackConfMemberEventCBProcess(ref STConfParam _avParam)
        {            
            LogManager.SystemLog.Info("callBackConfMemberEventCBProcess Monitor.Enter");
            ParameterizedThreadStart para = new ParameterizedThreadStart(StartUpdateCallWin);
            Thread thread = new Thread(para);
            thread.Priority = ThreadPriority.Highest;   //之前是Highest  2015/8/11 
            thread.Start(_avParam);
        }
               

        void StartUpdateCallWin(object avParam)
        {

            lock (WinCall.lockObject)
            {
                //this.flag1 = false;              
                try
                {
                    if (contactList != null)  //modify by 00327190   2015/8/10
                    {
                        LogManager.SystemLog.Info("StartUpdateCallWin Monitor.Enter");
                        STConfParam _avParam = new STConfParam();
                        _avParam = (STConfParam)avParam;
                        LogManager.SystemLog.Info("Start ConfMemberEventCB");
                        string str = _avParam.callerAcc_;
                        if (str == "")
                        {
                            if (_avParam.memStatus == (int)MemStatusInCall.CONF_MEM_SPK)
                            {
                                foreach (UCContact uc1 in contactList)
                                {
                                    uc1.IsSpeaker = false;
                                }
                            }
                            LogManager.SystemLog.Info("End ConfMemberEventCB1");
                            return;
                        }
                        else
                        {

                            if (contactList.FindIndex((x) => { return StringHelper.GetSubString(x.UserName) == str; }) == -1)
                            {
                                UCContact uc = new UCContact();
                                if (_avParam.memType == (int)MemberType.UC_IPPHONE)
                                {
                                    uc.UserName = str;
                                }
                                else
                                {
                                    uc.UserName = str + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                                }
                                uc.Mute = (MemStatusInCall)_avParam.memStatus;
                                uc.UCMemberType = (MemberType)_avParam.memType;
                                uc.Online = GetContactAvailability(_avParam.memType, str);
                                //if 是modify by jinyeqing   之前是没有的
                                if (_avParam.memStatus != (int)MemStatusInCall.CONF_MEM_DEL)
                                {
                                    contactList.Add(uc);
                                }
                                winCall.Render(contactList);
                                //winCall.AddContactWinSize(contactList);
                                LogManager.SystemLog.Info("End ConfMemberEventCB2");
                                return;
                            }
                            else if (!winCall.IsConf())//修改呼叫三人会议，一人未接，被叫者不是会议状态的bug
                            {
                                winCall.Render(contactList);
                            }
                        }
                        UCContact ucFrist = contactList.First((x) => { return StringHelper.GetSubString(x.UserName) == str; });
                        if (ucFrist != null)
                        {
                            if ((_avParam.memStatus == (int)MemStatusInCall.CONF_MEM_DEL || _avParam.memStatus == (int)MemStatusInCall.CONF_MEM_QUIT)
                                && contactList.FindIndex((x) => { return x.IsLeader == true && StringHelper.GetSubString(x.UserName) == str; }) != -1)
                            {
                                //临时注释掉 会议主席离会时，关闭会议的处理，只更新状态
                                //winCall.CloseCallInThread();
                                ucFrist.Mute = (MemStatusInCall)_avParam.memStatus;
                                return;
                            }
                            switch (_avParam.memStatus)
                            {
                                case (int)MemStatusInCall.CONF_MEM_SPK:
                                    foreach (UCContact uc1 in contactList)
                                    {
                                        uc1.IsSpeaker = false;
                                    }
                                    ucFrist.IsSpeaker = true;
                                    break;
                                //case (int)MemStatusInCall.CONF_MEM_QUIT:
                                case (int)MemStatusInCall.CONF_MEM_DEL:
                                    contactList.Remove(ucFrist);
                                    winCall.Render(contactList);
                                    //  winCall.AddContactWinSize(contactList);
                                    break;
                                default:
                                    ucFrist.Mute = (MemStatusInCall)_avParam.memStatus;
                                    break;
                            }
                        }
                    }
                }
                finally
                {
                    LogManager.SystemLog.Info("End ConfMemberEventCB3");
                    LogManager.SystemLog.Info("StartUpdateCallWin Monitor.Exit");
                }
                //this.flag1 = true;
            }
        }
        UCContactAvailability GetContactAvailability(int _AccountType, string _Account)
        {
            UCContactAvailability state;
            int _Status = 0;
            call.GetContactStatus(_AccountType, _Account, ref _Status);

            state = (UCContactAvailability)_Status;
            return state;
        }
        public void InsertCallHistory()
        {
            Thread thread = new Thread(new ThreadStart(InsertCallHistoryThread));
            thread.Start();
        }
        void InsertCallHistoryThread()
        {
            lock (WinCall.lockObject)
            {
               
                try
                {
                    LogManager.SystemLog.Info("InsertCallHistory Monitor.Enter");
                    string lyncName = "";
                    if (SingletonObj.LoginInfo == null)
                    {
                        return;
                    }
                    else
                    {
                        lyncName = SingletonObj.LoginInfo.LyncName;
                    }
                    HistoryQueryBusiness query = new HistoryQueryBusiness();
                    string url = "";
                    string name = "";
                    List<UCContact> contactList = winCall.listContact.ItemsSource as List<UCContact>;
                    if (contactList == null || contactList.Count == 0)
                    {
                        return;
                    }
                    UCContact uc = contactList.Find((x) => { return x.UserName != lyncName; });
                    if (uc == null)
                    {
                        return;
                    }
                    name = StringHelper.GetSubString(uc.UserName);
                    if (uc.UCMemberType == MemberType.UC_IPPHONE)
                    {
                        url = name;
                    }
                    else
                    {
                        url = StringHelper.GetLyncUrl(name);
                    }

                    int dt = winCall.GetAllSeconds();
                    query.InsertCallHistory(winCall.callType, url == "" ? name : url, name, dt);
                }
                finally
                {
                    LogManager.SystemLog.Info("InsertCallHistory Monitor.Exit");
                }
            }
          
        }

        public void InsertConfHistory()
        {
            Thread thread = new Thread(new ThreadStart(InsertConfHistoryThread));
            thread.Start();
        }
        void InsertConfHistoryThread()
        {
            lock (WinCall.lockObject)
            {
               
                try
                {
                    LogManager.SystemLog.Info("InsertConfHistory Monitor.Enter");
                    if (SingletonObj.LoginInfo == null)
                    {
                        return;
                    }

                    List<UCContact> contactList = winCall.listContact.ItemsSource as List<UCContact>;
                    if (contactList == null || contactList.Count == 0)
                    {
                        return;
                    }

                    HistoryQueryBusiness query = new HistoryQueryBusiness();
                    int _duration = winCall.GetAllSeconds();

                    string str = "";
                    StringBuilder _historyID = new StringBuilder(100);
                    for (int index = 0; index < contactList.Count; index++)
                    {
                        if (contactList[index].IsLeader)
                        {
                            str = contactList[index].UserName;
                            string strSIP = "";
                            if (contactList[index].UCMemberType == MemberType.UC_IPPHONE)
                            {
                                strSIP = str;
                            }
                            else
                            {
                                strSIP = "sip:" + str;
                            }
                            query.InsertConvHistory(strSIP, str, _duration, _historyID);
                            break;
                        }
                    }
                    for (int index = 0; index < contactList.Count; index++)
                    {
                        if (!contactList[index].IsLeader)
                        {
                            str = StringHelper.GetSubString(contactList[index].UserName);
                            string url = StringHelper.GetLyncUrl(str);

                            query.InsertConvHistoryPart(_historyID.ToString(), url == "" ? str : url, str);
                        }
                    }
                }
                finally
                {
                    LogManager.SystemLog.Info("InsertConfHistory Monitor.Exit");
                }
            }
           
        }

        public void HangupVideoCall()
        {
            call.HangupVideoCall();
            //winCall.CloseWinVideo();   //2015/5/26
        }
        public void RejectVideoCall()
        {
            call.RejectVideoCall();
        }

        /// <summary>
        /// 呼叫转移事件回调函数
        /// </summary>
        /// <param name="type">呼叫转移类型，0表示盲转</param>
        /// <param name="reslut">呼叫转移结果，1表示成功</param>
        private void callReservedEventCBProcess(int type, int reslut)
        {
            LogManager.SystemLog.Info(string.Format("callReservedEventCBProcess.type = {0},reslut ={1}", type, reslut));

            Thread threadUCContactStateChanged = new Thread(new ThreadStart(() 
                =>
                {
                    if (type == 0)//盲转
                    {
                        if (reslut == 1)
                        {
                            LogManager.SystemLog.Error("BlindTransCall success");
                            winCall.OpenDialog("BlindTransCallSucc", "success");
                            winCall.CloseWinThread();
                        }
                        else
                        {
                            LogManager.SystemLog.Error("BlindTransCall error");
                            winCall.OpenDialog("BlindTransCallFail", "error");
                            winCall.lync.setBtn();   //2015/8/18
                        }
                    }
                }));

            threadUCContactStateChanged.Priority = ThreadPriority.AboveNormal;
            threadUCContactStateChanged.Start();            
        }

        /// <summary>
        /// 盲转呼叫转移事件回调函数
        /// </summary>
        /// <param name="type">呼叫转移类型，0表示盲转</param>
        /// <param name="reslut">呼叫转移结果，1表示成功</param>
        private void callTransEventCBProcess(int type, int reslut)
        {
            LogManager.SystemLog.Info(string.Format("callTransEventCBProcess.type = {0},reslut ={1}", type, reslut));

            Thread threadUCContactStateChanged = new Thread(new ThreadStart(()
                =>
            {
                if (type == 0)//盲转
                {
                    if (reslut == 0)
                    {
                        LogManager.SystemLog.Error("BlindTransCall success");
                        winCall.OpenDialogTiming("BlindTransCallSucc", "success", 2);
                        winCall.CloseWinThread();
                    }
                    else 
                    {
                        LogManager.SystemLog.Error("BlindTransCall error");                        
                        winCall.OpenDialogTiming("BlindTransCallFail", "error", 2);
                        //转移失败时视频按钮，加人按钮，呼叫保持按钮恢复原状态
                        winCall.lync.setBtn();   //2015/8/10                     
                    }
                }
            }));

            threadUCContactStateChanged.Priority = ThreadPriority.AboveNormal;
            threadUCContactStateChanged.Start();
        }
               
    }
}
