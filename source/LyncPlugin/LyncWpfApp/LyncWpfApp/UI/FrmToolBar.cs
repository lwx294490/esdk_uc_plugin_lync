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
        AddInToolBarWiewModel toolBarWiewModel;
        public  PhoneJointEventCB phoneJointEventCB;
        LogInBusiness log = new LogInBusiness();
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
            UCServiceRetvCode iRet = (UCServiceRetvCode)log.SetPhoneJointDevType((int)PhoneJointType.PC_Device);
            if (iRet != UCServiceRetvCode.UC_SDK_Success)
            {
                Dialog.Show(StringHelper.FindLanguageResource("ConfigPhoneJointDevFail"), StringHelper.FindLanguageResource("error"));
            }
        }

        void BtnIP_Click(object sender, EventArgs e)
        {
            UCServiceRetvCode iRet = (UCServiceRetvCode)log.SetPhoneJointDevType((int)PhoneJointType.IPPhone_Device);
            if (iRet != UCServiceRetvCode.UC_SDK_Success)
            {
                Dialog.Show(StringHelper.FindLanguageResource("ConfigPhoneJointDevFail"), StringHelper.FindLanguageResource("error"));
            }
        }

        void BtnSetting_Click(object sender, EventArgs e)
        {
            if (WinOptionSetting.isHave == false)
            {
                setting = new WinOptionSetting(Lync);
                setting.Show();
            }
        }

        void BtnHisitory_Click(object sender, EventArgs e)
        {
            if (WinHisitory.isHave == false)
            {
                history = new WinHisitory(Lync);
                history.Show();
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

        void PhoneJointEventCBMethod(int _state)
        {
            LogManager.SystemLog.Debug(Enum.GetName(typeof(EM_PhoneJointStatusType),_state));

            EM_PhoneJointStatusType stateType = (EM_PhoneJointStatusType)_state;

            if (stateType == EM_PhoneJointStatusType.STATUS_START_SUCC && type != PhoneJointType.IPPhone_Device)
            {
                string str = System.Windows.Forms.Application.StartupPath;
                BtnPC.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PC_2.png");
                BtnIP.Image = Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\PHONE_3.png");
                type = PhoneJointType.IPPhone_Device;

                if (SingletonObj.LoginInfo==null||SingletonObj.LoginInfo.UserID==null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() => 
                { 
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStartSucess"), StringHelper.FindLanguageResource("StatusStartSucess")); 
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
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStopSucess"), StringHelper.FindLanguageResource("StatusStopSucess"));
                }));
            }
            else if (stateType == EM_PhoneJointStatusType.STATUS_START_FAILED)
            {
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStartFailed"), StringHelper.FindLanguageResource("StatusStartFailed"));
                }));
            }
            else if (stateType == EM_PhoneJointStatusType.STATUS_STOP_FAILED)
            {
                if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                {
                    return;
                }
                System.Windows.Application.Current.Dispatcher.Invoke(new Action(() =>
                {                    
                    Dialog.Show(StringHelper.FindLanguageResource("StatusStopFailed"), StringHelper.FindLanguageResource("StatusStopFailed"));
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
            STCallExData data = new STCallExData();
            int iRet = 0;

            if (!isSetVoiceMailUnCond)
            {
                data.Num = "152";
                iRet = call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);

                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    LogManager.SystemLog.Error("SetCallExService error");
                    isSetVoiceMailUnCond = false;
                    Dialog.Show(StringHelper.FindLanguageResource("FWDMailFail"), StringHelper.FindLanguageResource("FWDMailFail"));
                    return;
                }
                else
                {
                    isSetVoiceMailUnCond = true;
                    Dialog.Show(StringHelper.FindLanguageResource("FWDMailSuccess"), StringHelper.FindLanguageResource("FWDMailSuccess"));
                }
            }
            else
            {
                iRet = call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);

                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    LogManager.SystemLog.Error("SetCallExService error");
                    isSetVoiceMailUnCond = true;
                    Dialog.Show(StringHelper.FindLanguageResource("CancelFWDMailFail"), StringHelper.FindLanguageResource("CancelFWDMailFail"));
                    return;
                }
                else
                {
                    isSetVoiceMailUnCond = false;
                    Dialog.Show(StringHelper.FindLanguageResource("CancelFWDMailSuccess"), StringHelper.FindLanguageResource("CancelFWDMailSuccess"));
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
                string str = System.Windows.Forms.Application.StartupPath;
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
                        Dialog.Show(StringHelper.FindLanguageResource("FWDSuccess"), StringHelper.FindLanguageResource("FWDSuccess"));
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
                        Dialog.Show(StringHelper.FindLanguageResource("CancelFWDSuccess"), StringHelper.FindLanguageResource("CancelFWDSuccess"));
                    }
                    else
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("CancelFWDFailed"), StringHelper.FindLanguageResource("error"));
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
                }
                else
                {
                    isSetFWDUnCond = false;
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
    }
}
