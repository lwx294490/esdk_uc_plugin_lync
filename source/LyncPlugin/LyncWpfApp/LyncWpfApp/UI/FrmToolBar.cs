using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Lync.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using System.Windows;


namespace LyncWpfApp
{
    public partial class FrmToolBar : Form
    {
        public Action toolCallClick;
        public Action toolCallOver;
      
        
        public WinLync Lync
        {
            get;
            set;
        }
        public PictureBox PictureBoxProgress
        {
            get { return pictureBox; }
        }
        public Label LabState
        {
            get { return labState; }
        }


        public Button BtnHisitory
        {
            get { return btnHsitory; }
        }

        public Button BtnSetting
        {
            get { return btnSetting; }
        }

        public Button BtnDail
        {
            get { return btnDail; }
        }

        public Button BtnIP
        {
            get { return btnIP; }
        }
        public Button BtnPC
        {
            get { return btnPC; }
        }
        public Button BtnFWD
        {
            get { return btnFWD; }
        }
        public Button BtnMail
        {
            get { return btnMail; }
        }
        PhoneJointType type;
        public LyncWpfApp.PhoneJointType JointType
        {
            get { return type; }
            set { type = value; }
        }
        WinHisitory history;
        public WinHisitory History
        {
            get { return history; }
            set { history = value; }
        }
        WinOptionSetting setting;
        public WinOptionSetting Setting
        {
            get { return setting; }
            set { setting = value; }
        }
        [DllImport("user32.dll", EntryPoint = "ShowWindow", SetLastError = true)]
        static extern bool ShowWindow(IntPtr hWnd, uint nCmdShow);
        AddInToolBarWiewModel toolBarWiewModel;
        public  PhoneJointEventCB phoneJointEventCB;
        LogInBusiness log = new LogInBusiness();
        public bool isSetFWDUnCond1 = false;//是否设置了无条件呼叫前转  
        public bool isSetVoiceMailUnCond1 = false;//是否设置了语音邮箱呼叫前转
        static public bool isSetFWDUnCond = false;//是否设置了无条件呼叫前转        
        static public bool isSetVoiceMailUnCond = false;//是否设置了语音邮箱呼叫前转

        MakeCallBusiness call = new MakeCallBusiness();     

        public FrmToolBar(WinLync lync)
        {
            InitializeComponent();
            phoneJointEventCB = new PhoneJointEventCB(PhoneJointEventCBMethod);
            this.Visible = false;
            this.TopMost = true;
            SetButtonVisible(false);

            BtnHisitory.FlatAppearance.BorderSize = 0;
            BtnHisitory.FlatStyle = FlatStyle.Flat;
            BtnSetting.FlatAppearance.BorderSize = 0;
            BtnSetting.FlatStyle = FlatStyle.Flat;
            BtnDail.FlatAppearance.BorderSize = 0;
            BtnDail.FlatStyle = FlatStyle.Flat;
            BtnIP.FlatAppearance.BorderSize = 0;
            BtnIP.FlatStyle = FlatStyle.Flat;
            BtnPC.FlatAppearance.BorderSize = 0;
            BtnPC.FlatStyle = FlatStyle.Flat;
            BtnFWD.FlatAppearance.BorderSize = 0;
            BtnFWD.FlatStyle = FlatStyle.Flat;
            BtnMail.FlatAppearance.BorderSize = 0;
            BtnMail.FlatStyle = FlatStyle.Flat;
            BtnDail.Click += new EventHandler(BtnDail_Click);
            BtnHisitory.Click += new EventHandler(BtnHisitory_Click);
            BtnSetting.Click += new EventHandler(BtnSetting_Click);
            BtnIP.Click += new EventHandler(BtnIP_Click);
            BtnPC.Click += new EventHandler(BtnPC_Click);
            BtnFWD.Click += new EventHandler(BtnFWD_Click);
            BtnMail.Click += new EventHandler(BtnMail_Click);
            LabState.MouseEnter += new EventHandler(LabState_MouseEnter);
            LabState.MouseLeave += new EventHandler(LabState_MouseLeave);
            this.Lync = lync;
            labState.TabIndex = 1;
            labState.Focus();
            toolBarWiewModel = new AddInToolBarWiewModel(this);              
        }

        void LabState_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
        }

        void LabState_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
        }

        void BtnPC_Click(object sender, EventArgs e)
        {
            //通话时不能更改话机联动状态
            //You can't change joint type in a call
            if (Lync.winCall != null)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannotdothisincall"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            else if (Lync.isHave == true)   //通话未接通时也不许更改话机联动状态
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannotdothisincall"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            else
            {
                UCServiceRetvCode iRet = (UCServiceRetvCode)log.SetPhoneJointDevType((int)PhoneJointType.PC_Device);
                if (iRet != UCServiceRetvCode.UC_SDK_Success)
                {
                    Dialog.Show(StringHelper.FindLanguageResource("ConfigPhoneJointDevFail"), StringHelper.FindLanguageResource("error"));
                }
            }
        }

        void BtnIP_Click(object sender, EventArgs e)
        {
            //通话时不能更改话机联动状态
            //You can't change joint type in a call
            if (Lync.winCall != null)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannotdothisincall"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            else if (Lync.isHave == true)   //通话未接通时也不许更改话机联动状态
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannotdothisincall"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            else
            {
                UCServiceRetvCode iRet = (UCServiceRetvCode)log.SetPhoneJointDevType((int)PhoneJointType.IPPhone_Device);
                if (iRet != UCServiceRetvCode.UC_SDK_Success)
                {
                    Dialog.Show(StringHelper.FindLanguageResource("ConfigPhoneJointDevFail"), StringHelper.FindLanguageResource("error"));
                }
            }
        }

        void BtnSetting_Click(object sender, EventArgs e)
        {
            if (WinOptionSetting.isHave == false)
            {
                setting = new WinOptionSetting(Lync);
                setting.Show();
            }
            //modify by 00327190  2015/7/14  如果已经打开，再次按此按钮则显示画面  
            //Click the button to show the window again if the window was opened  already
            else      
            {
                Window frm = setting;
                frm.Focus();
                //获取该界面句柄  //Get handle of the interface 
                IntPtr hwnd = new WindowInteropHelper(setting).Handle;
                //显示窗体    //show the window 
                ShowWindow(hwnd, 1);
            }
        }

        void BtnHisitory_Click(object sender, EventArgs e)
        {
            if (WinHisitory.isHave == false)
            {
                history = new WinHisitory(Lync);
                history.Show();
            }
            //modify by 00327190  2015/7/14  如果已经打开，再次按此按钮则显示画面  (Focus是被覆盖的情况，ShowWindow是最小化后显示的情况)  
            //Click the button to show the window again if the window was opened  already
            else   
            {
                Window frm = history;
                frm.Focus();
                //获取该界面句柄       //Get handle of the interface 
                IntPtr hwnd = new WindowInteropHelper(history).Handle;
                //显示窗体   //show the window 
                ShowWindow(hwnd, 1);
            }
        }

        void BtnDail_Click(object sender, EventArgs e)
        {
            if (Lync.winDial == null)
            {
                WinDail dial = new WinDail(Lync);
                Lync.winDial = dial;
                dial.Show();
            }
            else
            {
                IntPtr hwnd = new WindowInteropHelper(Lync.winDial).Handle;
                ShowWindow(hwnd, 1);//显示窗体
            }

        }

        public void SetButtonVisible(bool isVisable)
        {
            int devType = 0;
            int iRet = 0;
            if (isVisable)
            {
                LogInBusiness log = new LogInBusiness();
                iRet = log.GetPhoneJointDevType(ref devType);
            }
            BtnHisitory.Visible = isVisable;
            BtnDail.Visible = isVisable;
            BtnFWD.Visible = isVisable;
            BtnMail.Visible = isVisable;
            BtnPC.Visible = isVisable && iRet != (int)UCServiceRetvCode.UC_SDK_NoRight;
            BtnIP.Visible = isVisable && iRet != (int)UCServiceRetvCode.UC_SDK_NoRight;
            //获取设置前传结果
            GetFWDInfo();
        }

        void btnCall_MouseEnter(object sender, EventArgs e)
        {
            if (null != toolCallOver)
            {
                toolCallOver();
            }
        }

        private void btnCall_Click(object sender, EventArgs e)
        {
            if (null != toolCallClick && Lync.winCall == null)
            {
                toolCallClick();
                toolBarWiewModel.startContextCall(WinLync.SelectedUserList);
            }
        }

        private void btnDail_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            btnDail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\DialPad_2.png");
        }

        private void btnDail_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            btnDail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\DialPad_1.png");
        }

        private void btnHsitory_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            btnHsitory.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\his_2.png");
        }

        private void btnHsitory_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            btnHsitory.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\his_1.png");
        }

        private void btnSetting_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            btnSetting.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\set_2.png");
        }

        private void btnSetting_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            btnSetting.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\set_1.png");
        }
        public void SetBtnImage(int devType)
        {
            type = (PhoneJointType)devType;
            if (type == PhoneJointType.IPPhone_Device)
            {
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_1.png");
            }
            else
            {
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_1.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");
            }
        }


        void PhoneJointEventCBMethod(ref PJStatusParam _pj)
        {
            LogManager.SystemLog.Debug(Enum.GetName(typeof(EM_PhoneJointStatusType), _pj.PJ_Status));
            string user = _pj.ucCalleeAcc;
            EM_PhoneJointStatusType stateType = (EM_PhoneJointStatusType)_pj.PJ_Status;           
            if (stateType == EM_PhoneJointStatusType.STATUS_START_SUCC && type != PhoneJointType.IPPhone_Device)
            {
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_3.png");
                type = PhoneJointType.IPPhone_Device;

                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStartSucess"), StringHelper.FindLanguageResource("Success"));
                }));

            }             
            else if (stateType == EM_PhoneJointStatusType.STATUS_STOP_SUCC && type != PhoneJointType.PC_Device)
            {
                type = PhoneJointType.PC_Device;
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_3.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");

                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStopSucess"), StringHelper.FindLanguageResource("Success"));
                }));
            }
            else if (stateType == EM_PhoneJointStatusType.STATUS_START_FAILED && type != PhoneJointType.IPPhone_Device)   //2015/8/6  && 后面是新加的
            {         
                //modify by 00327190 2015/7/13  设置话机联动失败时也应该将图片置为相应的状态
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_3.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStartFailed"), StringHelper.FindLanguageResource("error"));
                }));
            }
            else if (stateType == EM_PhoneJointStatusType.STATUS_STOP_FAILED && type != PhoneJointType.PC_Device)   //2015/8/6  && 后面是新加的
            {
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStopFailed"), StringHelper.FindLanguageResource("error"));
                }));
            }
                //modify by 00327190  2015/7/30  话机注销上报消息  
            else if (stateType == EM_PhoneJointStatusType.STATUS_OFFLINE)
            {
                type = PhoneJointType.PC_Device;
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_3.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusOffline"), StringHelper.FindLanguageResource("StatusOffline"));
                }));
            }
            //modify by 00327190  2015/7/30  话机上线上报消息 
            else if (stateType == EM_PhoneJointStatusType.STATUS_ONLINE && type == PhoneJointType.IPPhone_Device)   //9/17
            {
                type = PhoneJointType.PC_Device;
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_3.png");
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("Statusonline"), StringHelper.FindLanguageResource("Statusonline"));
                }));
            }
        }

        private void btnIP_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            if (type == PhoneJointType.IPPhone_Device)
            {
                btnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_3.png");
            }
            else
            {
                btnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");
            }
        }

        private void btnIP_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            if (type == PhoneJointType.IPPhone_Device)
            {
                btnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_1.png");
            }
            else
            {
                btnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_2.png");
            }
        }

        private void btnPC_MouseEnter(object sender, EventArgs e)
        {
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            if (type == PhoneJointType.IPPhone_Device)
            {
                btnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
            }
            else
            {
                btnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_3.png");
            }
        }

        private void btnPC_MouseLeave(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            if (type == PhoneJointType.IPPhone_Device)
            {
                btnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
            }
            else
            {
                btnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_1.png");
            }
        }
        private string SetFWDService()
        {
            return Lync.GetLyncPhoneNumber();
        }

        private void btnFWD_MouseEnter(object sender, EventArgs e)
        {
            GetFWDInfo();   //modify by 00327190 2015/7/29   先查询 
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            if (!isSetFWDUnCond)
            {
                btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_2.png");
            }
            else
            {
                btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_3.png");
            }
        }

        private void btnFWD_MouseLeave(object sender, EventArgs e)
        {
            GetFWDInfo();   //modify by 00327190 2015/7/29   先查询 
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;         
            if (!isSetFWDUnCond)
            {
                btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_2.png");
            }
            else
            {
                btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_1.png");
            }
        }

        private void btnMail_MouseEnter(object sender, EventArgs e)
        {
            GetMailFrwInfo();  //7/30  先查询语音邮箱配置  
            WinLync.lyncCounter++;
            string str = System.Windows.Forms.Application.StartupPath;
            if (isSetVoiceMailUnCond)
            {
                btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_3.png");
            }
            else
            {
                btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_2.png");
            }
        }

        private void btnMail_MouseLeave(object sender, EventArgs e)
        {
            GetMailFrwInfo();  //7/30  先查询语音邮箱配置  
            WinLync.lyncCounter--;
            string str = System.Windows.Forms.Application.StartupPath;
            if (isSetVoiceMailUnCond)
            {
                btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_1.png");
            }
            else
            {
                btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_2.png");
            }
        }

        /// <summary>
        /// 语音邮箱呼叫前传
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void BtnMail_Click(object sender, EventArgs e)
        {
            //语音邮箱
            //通话时不能更改话机联动状态
            //You can't change joint type in a call
            if (Lync.winCall != null)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Cannotchangemailincall"), StringHelper.FindLanguageResource("error"), 2);
                return;
            }
            else
            {
                GetMailFrwInfo();  //7/30  先查询语音邮箱配置  
                UserConfigBusiness conf = new UserConfigBusiness();
                STContact con = new STContact();
                int iRet = conf.GetContactInfo(new StringBuilder(SingletonObj.LoginInfo.UserID), ref con);
                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    LogManager.SystemLog.Error("GetContactInfo error");
                    return;
                }
                //7/30
                STCallExData data = new STCallExData();
                //int iRet = 0;
                if (!isSetVoiceMailUnCond)
                {
                    //if (string.IsNullOrEmpty(con.email_))
                    //{
                    //    LogManager.SystemLog.Warn("email_ is null");
                    //    Dialog.Show(StringHelper.FindLanguageResource("NoVoicemail"), StringHelper.FindLanguageResource("error"));
                    //    return;
                    //}
                    //data.Num = con.email_;   //2015/8/13
                    data.Num = "1";
                    LogManager.SystemLog.Info(string.Format("email_ is {0}", data.Num));
                    
                    iRet = call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);

                    if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                    {
                        LogManager.SystemLog.Error("SetCallExService error");
                        isSetVoiceMailUnCond = false;
                        Dialog.Show(StringHelper.FindLanguageResource("FWDMailFail"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        GetMailFrwInfo();
                        if (isSetVoiceMailUnCond == true)
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("FWDMailSuccess"), StringHelper.FindLanguageResource("Success"));
                        }
                        else
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("FWDMailFail"), StringHelper.FindLanguageResource("error"));
                        }

                    }
                }
                else
                {
                    iRet = call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);

                    if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                    {
                        LogManager.SystemLog.Error("SetCallExService error");
                        isSetVoiceMailUnCond = true;
                        Dialog.Show(StringHelper.FindLanguageResource("CancelFWDMailFail"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        GetMailFrwInfo();
                        if (!isSetVoiceMailUnCond)
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("CancelFWDMailSuccess"), StringHelper.FindLanguageResource("Success"));
                        }
                        else
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("CancelFWDMailFail"), StringHelper.FindLanguageResource("error"));
                        }

                    }

                }
            }
        }
        /// <summary>
        /// 设置呼叫前传
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void BtnFWD_Click(object sender, EventArgs e)
        {
            try
            {
                //通话时不能更改话机联动状态
                //You can't change joint type in a call
                if (Lync.winCall != null)
                {
                    DialogShow.Show(StringHelper.FindLanguageResource("CannotchangeFWDincall"), StringHelper.FindLanguageResource("error"), 2);
                    return;
                }
                else
                {                  
                    GetFWDInfo();                  
                    UserConfigBusiness conf = new UserConfigBusiness();
                    STContact con = new STContact();
                    int iRet = conf.GetContactInfo(new StringBuilder(SingletonObj.LoginInfo.UserID), ref con);
                    if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                    {
                        LogManager.SystemLog.Error("GetContactInfo error");
                        return;
                    }

                    STCallExData data = new STCallExData();

                    if (!isSetFWDUnCond)
                    {
                        if (string.IsNullOrEmpty(con.mobile_))
                        {
                            LogManager.SystemLog.Warn("user mobile is null");
                            Dialog.Show(StringHelper.FindLanguageResource("NoMoblePhone"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        data.Num = con.mobile_;
                        LogManager.SystemLog.Info(string.Format("user mobile is {0}", data.Num));
                        iRet = call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);

                        if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                        {
                            LogManager.SystemLog.Error("SetCallExService error");
                            return;
                        }

                        //查询设置结果
                        GetFWDInfo();

                        if (isSetFWDUnCond)
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("FWDSuccess"), StringHelper.FindLanguageResource("Success"));
                        }
                        else
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("FWDFailed"), StringHelper.FindLanguageResource("error"));
                        }
                    }
                    else
                    {
                        iRet = call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);

                        if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                        {
                            LogManager.SystemLog.Error("SetCallExService error");
                            return;
                        }

                        //查询设置结果
                        GetFWDInfo();

                        if (!isSetFWDUnCond)
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("CancelFWDSuccess"), StringHelper.FindLanguageResource("Success"));
                        }
                        else
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("CancelFWDFailed"), StringHelper.FindLanguageResource("error"));
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
       /// <summary>
       /// 查询呼叫前传信息
       /// </summary>
        public void GetFWDInfo()
        { 
            try
            {
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }

                int type = (int)ForwardServiceType.FORWARD_UNCONDITION;
                STCallExData data = new STCallExData();

                call.GetCallExService(type, ref data);

                if ((ForwardServiceType)type == ForwardServiceType.FORWARD_UNCONDITION && !string.IsNullOrEmpty(data.Num))
                {
                    isSetFWDUnCond = true;
                    isSetFWDUnCond1 = true;
                }
                else
                {                    
                    isSetFWDUnCond = false;
                    isSetFWDUnCond1 = false;
                }
                string str = System.Windows.Forms.Application.StartupPath;
                if (!isSetFWDUnCond)
                {
                    btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_2.png");
                }
                else
                {
                    btnFWD.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_1.png");
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }


        /// <summary>
        /// 查询语音邮箱前传信息
        /// </summary>
        public void GetMailFrwInfo()
        {
            try
            {
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }

                int type = (int)ForwardServiceType.VOICEMAIL_UNCONDITION;
                STCallExData data = new STCallExData();

                call.GetCallExService(type, ref data);

                if ((ForwardServiceType)type == ForwardServiceType.VOICEMAIL_UNCONDITION && !string.IsNullOrEmpty(data.Num))
                {
                    isSetVoiceMailUnCond = true;
                    isSetVoiceMailUnCond1 = true;
                  
                }
                else
                {
                    isSetVoiceMailUnCond = false;
                    isSetVoiceMailUnCond1 = false;
                }
                string str = System.Windows.Forms.Application.StartupPath;
                if (!isSetVoiceMailUnCond)
                {
                    btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_2.png");
                }
                else
                {
                    btnMail.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms.png");
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
    }
}
