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
using System.Drawing;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinOptionSetting.xaml
    /// </summary>
    public partial class WinOptionSetting : Window
    {
        WinLync lync;
        public static bool isHave = false;
        //FrmToolBar toolBar;        
        public System.Windows.Forms.Button btnFWD;
        public System.Windows.Forms.Button BtnFWD
        {
            get { return btnFWD; }
        }
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
                        if (IsValidPhoneNumber(data.Num) == false)
                        {
                            DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                            return;
                        }
                        else if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("PhoneNumberNullError"), StringHelper.FindLanguageResource("error"));
                            string str = System.Windows.Forms.Application.StartupPath;                           
                            lync.toolBar.BtnFWD.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_2.png");                          
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                            if (iRet == 0)
                            {
                                string str = System.Windows.Forms.Application.StartupPath;
                                lync.toolBar.BtnFWD.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_3.png");
                                //2015/8/11  一旦设置了无条件前转，则其他前转全部设置为关闭
                                data.Num = string.Empty;
                                call.SetCallExService((int)ForwardServiceType.FORWARD_NOREPLY, data);
                                call.SetCallExService((int)ForwardServiceType.FORWARD_OFFLINE, data);
                                call.SetCallExService((int)ForwardServiceType.FORWARD_ONBUSY, data);
                            }
                          
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;                      
                        iRet += call.SetCallExService((int)ForwardServiceType.FORWARD_UNCONDITION, data);
                        if (iRet == 0)
                        {
                            string str = System.Windows.Forms.Application.StartupPath;
                            lync.toolBar.BtnFWD.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\MobilePhone_2.png");
                        }
                    }
                }
                else if (buttonName == "btnCallForwardNoReply")
                {
                    //不回复呼叫前转
                    this.lync.toolBar.GetFWDInfo();
                    if (lync.toolBar.isSetFWDUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radCallForwardNoReplyEn.IsChecked)
                        {
                            data.Num = this.txtCallForwardNoReply.Text.Trim();
                            if (IsValidPhoneNumber(data.Num) == false)
                            {
                                DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                                return;
                            }
                            else if (string.IsNullOrEmpty(data.Num))
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
                }
                else if (buttonName == "btnCallForwardBusy")
                {
                    //遇忙呼叫前转
                    this.lync.toolBar.GetFWDInfo();
                    if (lync.toolBar.isSetFWDUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radCallForwardBusyEn.IsChecked)
                        {
                            data.Num = this.txtCallForwardBusy.Text.Trim();
                            if (IsValidPhoneNumber(data.Num) == false)
                            {
                                DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                                return;
                            }
                            else if (string.IsNullOrEmpty(data.Num))
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
                }
                else if (buttonName == "btnCallForwardOffline")
                {
                    //离线呼叫前转
                    this.lync.toolBar.GetFWDInfo();
                    if (lync.toolBar.isSetFWDUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radCallForwardOfflineEn.IsChecked)
                        {
                            data.Num = this.txtCallForwardOffline.Text.Trim();
                            if (IsValidPhoneNumber(data.Num) == false)
                            {
                                DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                                return;
                            }
                            else if (string.IsNullOrEmpty(data.Num))
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
                }
                else if (buttonName == "btnCallForwardDND")   //DND取消了  2015/8/11
                {
                    //离线呼叫前转
                    if ((bool)this.radCallForwardDNDEn.IsChecked)
                    {
                        data.Num = this.txtCallForwardDND.Text.Trim();
                        if (IsValidPhoneNumber(data.Num) == false)
                        {
                            DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                            return;
                        }
                        else if (string.IsNullOrEmpty(data.Num))
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
                    Dialog.Show(StringHelper.FindLanguageResource("FWDFailed"), StringHelper.FindLanguageResource("error"));
                }
                else
                {
                    Dialog.Show(StringHelper.FindLanguageResource("FWDSuccess"), StringHelper.FindLanguageResource("Success"));
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
                        //data.Num = this.txtVoiceForwardUnCond.Text.Trim();
                        data.Num ="1";
                        if (string.IsNullOrEmpty(data.Num))
                        {
                            Dialog.Show(StringHelper.FindLanguageResource("MailNumberNullError"), StringHelper.FindLanguageResource("error"));
                            string str = System.Windows.Forms.Application.StartupPath;
                            lync.toolBar.BtnMail.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_2.png"); 
                            return;
                        }
                        else
                        {
                            iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                            if (iRet == 0)
                            {
                                string str = System.Windows.Forms.Application.StartupPath;
                                lync.toolBar.BtnMail.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_3.png");
                                //2015/8/11  一旦设置了无条件前转，则其他前转全部设置为关闭
                                data.Num = string.Empty;
                                call.SetCallExService((int)ForwardServiceType.VOICEMAIL_NOREPLY, data);
                                call.SetCallExService((int)ForwardServiceType.VOICEMAIL_OFFLINE, data);
                                call.SetCallExService((int)ForwardServiceType.VOICEMAIL_ONBUSY, data);
                            }
                        }
                    }
                    else
                    {
                        data.Num = string.Empty;
                        iRet += call.SetCallExService((int)ForwardServiceType.VOICEMAIL_UNCONDITION, data);
                        if (iRet == 0)
                        {
                            string str = System.Windows.Forms.Application.StartupPath;
                            lync.toolBar.BtnMail.Image = System.Drawing.Image.FromFile(str.Substring(0, str.IndexOf("bin")) + "\\Image\\sms_2.png");
                        }
                    }
                }
                else if (buttonName == "btnVoiceForwardNoReply")
                {
                    //无应答转语音邮箱
                    this.lync.toolBar.GetMailFrwInfo();
                    if (lync.toolBar.isSetVoiceMailUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radVoiceForwardNoReplyEn.IsChecked)
                        {
                            //data.Num = this.txtVoiceForwardNoReply.Text.Trim();
                            data.Num = "1";
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
                }
                else if (buttonName == "btnVoiceForwardBusy")
                {
                    //遇忙转语音邮箱
                    this.lync.toolBar.GetMailFrwInfo();
                    if (lync.toolBar.isSetVoiceMailUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radVoiceForwardBusyEn.IsChecked)
                        {
                            //data.Num = this.txtVoiceForwardBusy.Text.Trim();
                            data.Num = "1";
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
                }
                else if (buttonName == "btnVoiceForwardOffline")
                {
                    //离线转语音邮箱
                    this.lync.toolBar.GetMailFrwInfo();
                    if (lync.toolBar.isSetVoiceMailUnCond1 == true)  //如果设置了无条件前转，则不能设置其他前转
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("Cannottransfer"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    else
                    {
                        if ((bool)this.radVoiceForwardOfflineEn.IsChecked)
                        {
                            //data.Num = this.txtVoiceForwardOffline.Text.Trim();
                            data.Num = "1";
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
                }
                else if (buttonName == "btnVoiceForwardDND")  //DND不做了  2015/8/11
                {
                    //离线呼叫前转
                    if ((bool)this.radVoiceForwardDNDEn.IsChecked)
                    {
                        //data.Num = this.txtVoiceForwardDND.Text.Trim();
                        data.Num = "1";
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
                    Dialog.Show(StringHelper.FindLanguageResource("FWDMailFail"), StringHelper.FindLanguageResource("error"));
                }
                else
                {
                    Dialog.Show(StringHelper.FindLanguageResource("FWDMailSuccess"), StringHelper.FindLanguageResource("Success"));
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }

        private void radCallForwardUnCondEn_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardUnCond != null)
            {
                if ((bool)radCallForwardUnCondDis.IsChecked)
                {
                    this.txtCallForwardUnCond.Text = string.Empty;
                    this.txtCallForwardUnCond.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardUnCond.IsEnabled = true;
                }
            }

        }

        private void radCallForwardUnCondDis_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardUnCond != null)
            {
                if ((bool)radCallForwardUnCondDis.IsChecked)
                {
                    this.txtCallForwardUnCond.Text = string.Empty;
                    this.txtCallForwardUnCond.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardUnCond.IsEnabled = true;
                }
            }
        }

        private void radCallForwardNoReplyEn_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardNoReply != null)
            {
                if ((bool)radCallForwardNoReplyDis.IsChecked)
                {
                    this.txtCallForwardNoReply.Text = string.Empty;
                    this.txtCallForwardNoReply.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardNoReply.IsEnabled = true;
                }
            }
        }

        private void radCallForwardNoReplyDis_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardNoReply != null)
            {
                if ((bool)radCallForwardNoReplyDis.IsChecked)
                {
                    this.txtCallForwardNoReply.Text = string.Empty;
                    this.txtCallForwardNoReply.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardNoReply.IsEnabled = true;
                }
            }
        }

        private void radCallForwardBusyEn_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardBusy != null)
            {
                if ((bool)radCallForwardBusyDis.IsChecked)
                {
                    this.txtCallForwardBusy.Text = string.Empty;
                    this.txtCallForwardBusy.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardBusy.IsEnabled = true;
                }
            }
        }

        private void radCallForwardBusyDis_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardBusy != null)
            {
                if ((bool)radCallForwardBusyDis.IsChecked)
                {
                    this.txtCallForwardBusy.Text = string.Empty;
                    this.txtCallForwardBusy.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardBusy.IsEnabled = true;
                }
            }
        }

        private void radCallForwardOfflineEn_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardOffline != null)
            {
                if ((bool)radCallForwardOfflineDis.IsChecked)
                {
                    this.txtCallForwardOffline.Text = string.Empty;
                    this.txtCallForwardOffline.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardOffline.IsEnabled = true;
                }
            }
        }

        private void radCallForwardOfflineDis_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardOffline != null)
            {
                if ((bool)radCallForwardOfflineDis.IsChecked)
                {
                    this.txtCallForwardOffline.Text = string.Empty;
                    this.txtCallForwardOffline.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardOffline.IsEnabled = true;
                }
            }
        }

        private void radCallForwardDNDEn_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardDND != null)
            {
                if ((bool)radCallForwardDNDDis.IsChecked)
                {
                    this.txtCallForwardDND.Text = string.Empty;
                    this.txtCallForwardDND.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardDND.IsEnabled = true;
                }
            }
        }

        private void radCallForwardDNDDis_Checked(object sender, RoutedEventArgs e)
        {
            if (txtCallForwardDND != null)
            {
                if ((bool)radCallForwardDNDDis.IsChecked)
                {
                    this.txtCallForwardDND.Text = string.Empty;
                    this.txtCallForwardDND.IsEnabled = false;
                }
                else
                {
                    this.txtCallForwardDND.IsEnabled = true;
                }
            }
        }

        private void radVoiceForwardUnCondEn_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardUnCond != null)
            //{
            //    if ((bool)radVoiceForwardUnCondDis.IsChecked)
            //    {
            //        this.txtVoiceForwardUnCond.Text = string.Empty;
            //        this.txtVoiceForwardUnCond.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardUnCond.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardUnCondDis_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardUnCond != null)
            //{
            //    if ((bool)radVoiceForwardUnCondDis.IsChecked)
            //    {
            //        this.txtVoiceForwardUnCond.Text = string.Empty;
            //        this.txtVoiceForwardUnCond.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardUnCond.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardNoReplyEn_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardNoReply != null)
            //{
            //    if ((bool)radVoiceForwardNoReplyDis.IsChecked)
            //    {
            //        this.txtVoiceForwardNoReply.Text = string.Empty;
            //        this.txtVoiceForwardNoReply.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardNoReply.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardNoReplyDis_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardNoReply != null)
            //{
            //    if ((bool)radVoiceForwardNoReplyDis.IsChecked)
            //    {
            //        this.txtVoiceForwardNoReply.Text = string.Empty;
            //        this.txtVoiceForwardNoReply.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardNoReply.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardBusyEn_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardBusy != null)
            //{
            //    if ((bool)radVoiceForwardBusyDis.IsChecked)
            //    {
            //        this.txtVoiceForwardBusy.Text = string.Empty;
            //        this.txtVoiceForwardBusy.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardBusy.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardBusyDis_Checked(object sender, RoutedEventArgs e)
        {
        //    if (txtVoiceForwardBusy != null)
        //    {
        //        if ((bool)radVoiceForwardBusyDis.IsChecked)
        //        {
        //            this.txtVoiceForwardBusy.Text = string.Empty;
        //            this.txtVoiceForwardBusy.IsEnabled = false;
        //        }
        //        else
        //        {
        //            this.txtVoiceForwardBusy.IsEnabled = true;
        //        }
        //    }
        }

        private void radVoiceForwardOfflineEn_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardOffline != null)
            //{
            //    if ((bool)radVoiceForwardOfflineDis.IsChecked)
            //    {
            //        this.txtVoiceForwardOffline.Text = string.Empty;
            //        this.txtVoiceForwardOffline.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardOffline.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardOfflineDis_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardOffline != null)
            //{
            //    if ((bool)radVoiceForwardOfflineDis.IsChecked)
            //    {
            //        this.txtVoiceForwardOffline.Text = string.Empty;
            //        this.txtVoiceForwardOffline.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardOffline.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardDNDEn_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardDND != null)
            //{
            //    if ((bool)radVoiceForwardDNDDis.IsChecked)
            //    {
            //        this.txtVoiceForwardDND.Text = string.Empty;
            //        this.txtVoiceForwardDND.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardDND.IsEnabled = true;
            //    }
            //}
        }

        private void radVoiceForwardDNDDis_Checked(object sender, RoutedEventArgs e)
        {
            //if (txtVoiceForwardDND != null)
            //{
            //    if ((bool)radVoiceForwardDNDDis.IsChecked)
            //    {
            //        this.txtVoiceForwardDND.Text = string.Empty;
            //        this.txtVoiceForwardDND.IsEnabled = false;
            //    }
            //    else
            //    {
            //        this.txtVoiceForwardDND.IsEnabled = true;
            //    }
            //}
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
