using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Data;
using System.Globalization;
using System.Threading;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinOptionSetting.xaml
    /// </summary>
    public partial class WinOptionSetting : Window
    {
        WinLync lync;
        public static bool isHave = false;
        public WinOptionSetting(WinLync lync)
        {
            this.lync = lync;
            InitializeComponent();
            tabOptionSetting.TabStripPlacement = Dock.Left;

            WinOptionSettingViewModel model = new WinOptionSettingViewModel(this);
            this.DataContext = model;
            model.StartLoadData();
            this.Closed += new EventHandler(WinOptionSetting_Closed);
            isHave = true;
            WinLync.lyncCounter++;
        }

        void WinOptionSetting_Closed(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            isHave = false;
            lync.toolBar.Setting = null;
        }

        private void btnOpenPath_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = StringHelper.FindLanguageResource("SelectFile");
            openFileDialog.FileName = string.Empty;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            DialogResult result = openFileDialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.Cancel)
            {
                return;
            }
            (dataGrid1.DataContext as DataTable).Rows[dataGrid1.SelectedIndex][2] = openFileDialog.FileName;
         }

        private void OpenSelfMgr_Portal_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            UserConfigBusiness conf = new UserConfigBusiness();
            UCServiceRetvCode iRet = (UCServiceRetvCode)conf.OpenPortal((int)PortalType.SelfMgr_Portal);
            if (iRet == UCServiceRetvCode.UC_SDK_NotLogin)
            {
                Dialog.Show(StringHelper.FindLanguageResource("NoLogin"), StringHelper.FindLanguageResource("error"));
            }
        }

        private void BookConf_Portal_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (SingletonObj.LoginInfo == null)
            {
                return;
            }
            UserConfigBusiness conf = new UserConfigBusiness();
            conf.OpenPortal((int)PortalType.BookConf_Portal);
        }

        private void OpenSelfMgr_Portal_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)
        {
            OpenSelfMgr_Portal.FontWeight = FontWeights.Bold;
        }

        private void OpenSelfMgr_Portal_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
        {
            OpenSelfMgr_Portal.FontWeight = FontWeights.Normal;
        }

        private void BookConf_Portal_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)
        {
            BookConf_Portal.FontWeight = FontWeights.Bold;
        }

        private void BookConf_Portal_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
        {
            BookConf_Portal.FontWeight = FontWeights.Normal;
        }

        private void CallForward_Click(object sender, RoutedEventArgs e)
        {
            if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
            {
                Dialog.Show(StringHelper.FindLanguageResource("NoUCAccount"), StringHelper.FindLanguageResource("SettingUC"));
                return;
            }
            try
            {
                MakeCallBusiness call = new MakeCallBusiness();
                STCallExData data = new STCallExData();
                int iRet = 0;

                string buttonName = (sender as System.Windows.Controls.Button).Name;

                if (buttonName == "btnCallForwardUnCond")
                {
                    //无条件呼叫前传
                    if ((bool)this.radCallForwardUnCondEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardUnCond.Text.Trim();

                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                    }
                }
                else if (buttonName == "btnCallForwardNoReply")
                {
                    //不回复呼叫前转
                    if ((bool)this.radCallForwardNoReplyEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardNoReply.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_NOREPLY, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_NOREPLY, data);
                    }
                }
                else if (buttonName == "btnCallForwardBusy")
                {
                    //遇忙呼叫前转
                    if ((bool)this.radCallForwardBusyEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardBusy.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_ONBUSY, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_ONBUSY, data);
                    }
                }
                else if (buttonName == "btnCallForwardOffline")
                {
                    //离线呼叫前转
                    if ((bool)this.radCallForwardOfflineEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardOffline.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_OFFLINE, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_OFFLINE, data);
                    }
                }
                else if (buttonName == "btnCallForwardDND")
                {
                    //离线呼叫前转
                    if ((bool)this.radCallForwardDNDEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardDND.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                    }
                }

                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    LogManager.SystemLog.Error("SetCallExService error");                   
                }
                else
                {
                    Dialog.Show(StringHelper.FindLanguageResource("FWDSuccess"), StringHelper.FindLanguageResource("FWDSuccess"));
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }

        //语音信箱转移
        private void MailForward_Click(object sender, RoutedEventArgs e)
        {
            if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
            {
                Dialog.Show(StringHelper.FindLanguageResource("NoUCAccount"), StringHelper.FindLanguageResource("SettingUC"));
                return;
            }
            try
            {
                MakeCallBusiness call = new MakeCallBusiness();
                STCallExData data = new STCallExData();
                int iRet = 0;

                string buttonName = (sender as System.Windows.Controls.Button).Name;

                if (buttonName == "btnVoiceForwardUnCond")
                {
                    //无条件转语音邮箱
                    if ((bool)this.radVoiceForwardUnCondEn.IsChecked)
                    {
                        data.Num = this.txtVoiceForwardUnCond.Text.Trim();

                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                    }
                }
                else if (buttonName == "btnVoiceForwardNoReply")
                {
                    //无应答转语音邮箱
                    if ((bool)this.radVoiceForwardNoReplyEn.IsChecked)
                    {
                        data.Num = this.txtVoiceForwardNoReply.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_NOREPLY, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_NOREPLY, data);
                    }
                }
                else if (buttonName == "btnVoiceForwardBusy")
                {
                    //遇忙转语音邮箱
                    if ((bool)this.radVoiceForwardBusyEn.IsChecked)
                    {
                        data.Num = this.txtVoiceForwardBusy.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_ONBUSY, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_ONBUSY, data);
                    }
                }
                else if (buttonName == "btnVoiceForwardOffline")
                {
                    //离线转语音邮箱
                    if ((bool)this.radVoiceForwardOfflineEn.IsChecked)
                    {
                        data.Num = this.txtVoiceForwardOffline.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_OFFLINE, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_OFFLINE, data);
                    }
                }
                else if (buttonName == "btnVoiceForwardDND")
                {
                    //离线呼叫前转
                    if ((bool)this.radVoiceForwardDNDEn.IsChecked)
                    {
                        data.Num = this.txtVoiceForwardDND.Text.Trim();
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                    }
                }

                if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
                {
                    LogManager.SystemLog.Error("SetCallExService error");
                    //modify by jinyeqing 
                    Dialog.Show(StringHelper.FindLanguageResource("SetCallExServiceerror"), StringHelper.FindLanguageResource("error"));
                }
                else
                {
                    Dialog.Show(StringHelper.FindLanguageResource("FWDMailSuccess"), StringHelper.FindLanguageResource("FWDMailSuccess"));
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }



    }
}
