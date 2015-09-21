using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Data;
using Microsoft.Win32;
using System.Runtime.InteropServices;
using System.Threading;

namespace LyncWpfApp
{
   public class WinOptionSettingViewModel
   {
       public ICommand OKCommand { get; set; }
       public ICommand CancelCommand { get; set; }
       public ICommand ApplyCommand { get; set; }
       public ICommand PlayCommand { get; set; }
       public ICommand OpenPathCommand { get; set; }
       public WinOptionSetting winOptionSetting { get; set; }
       //FrmToolBar FrmToolBar;   //2015/8/11
       int count = 10;
       public WinOptionSettingViewModel(WinOptionSetting window)
       {
           winOptionSetting = window;

           OKCommand = new DelegateCommand(OKCommandProcess);
           CancelCommand = new DelegateCommand(CancelCommandProcess);
           ApplyCommand = new DelegateCommand(ApplyCommandProcess);

           LoadSystDve();//加载系统设备
        }
       public WinOptionSettingViewModel()
       {
       }
       /// <summary>
       /// 加载系统设备
       /// </summary>
       void LoadSystDve()
       {
           UserConfigBusiness conf = new UserConfigBusiness();

           int iSizeSTDeviceListParam = Marshal.SizeOf(typeof(STDeviceListParam));
           int iSizeSTDeviceParam = Marshal.SizeOf(typeof(STDeviceParam));
           int iBufSize = (iSizeSTDeviceListParam + iSizeSTDeviceParam * (count - 1));
           byte[] pSTDeviceList = new byte[iBufSize];

           UCServiceRetvCode iRet = (UCServiceRetvCode)conf.GetMicDevList(0, 9, iBufSize, pSTDeviceList);

           Dictionary<int, string> dicMicrophone = new Dictionary<int, string>();
           if (iRet == UCServiceRetvCode.UC_SDK_Success)
           {
               IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTDeviceListParam);
               byte[] tempInfoByte = new byte[iSizeSTDeviceListParam];

               Marshal.Copy(pSTDeviceList, 0, tempInfoIntPtr, (int)iSizeSTDeviceListParam);
               STDeviceListParam head = (STDeviceListParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceListParam));

               for (int i = -1; i < head.iTotal - 1 && i < count - 1; i++)
               {
                   Marshal.Copy(pSTDeviceList, iSizeSTDeviceListParam + iSizeSTDeviceParam * i, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam item = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));
                   dicMicrophone.Add(item.index, item.name);
               }
               Marshal.Release(tempInfoIntPtr);
           }
           winOptionSetting.comMicrophone.ItemsSource = dicMicrophone;
           winOptionSetting.comMicrophone.SelectedValuePath = "Key";
           winOptionSetting.comMicrophone.DisplayMemberPath = "Value";
           winOptionSetting.comMicrophone.SelectedIndex = 0;

           pSTDeviceList = new byte[iBufSize];
           iRet = (UCServiceRetvCode)conf.GetSpeakerDevList(0, 9, iBufSize, pSTDeviceList);
           Dictionary<int, string> dicSpeakerDev = new Dictionary<int, string>();
           if (iRet == UCServiceRetvCode.UC_SDK_Success)
           {
               IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTDeviceListParam);
               byte[] tempInfoByte = new byte[iSizeSTDeviceListParam];

               Marshal.Copy(pSTDeviceList, 0, tempInfoIntPtr, (int)iSizeSTDeviceListParam);
               STDeviceListParam head = (STDeviceListParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceListParam));

               for (int i = -1; i < head.iTotal - 1 && i < count - 1; i++)
               {
                   Marshal.Copy(pSTDeviceList, iSizeSTDeviceListParam + iSizeSTDeviceParam * i, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam item = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));
                   dicSpeakerDev.Add(item.index, item.name);
               }
               Marshal.Release(tempInfoIntPtr);
           }
           winOptionSetting.comSpeaker.ItemsSource = dicSpeakerDev;
           winOptionSetting.comSpeaker.SelectedValuePath = "Key";
           winOptionSetting.comSpeaker.DisplayMemberPath = "Value";
           winOptionSetting.comSpeaker.SelectedIndex = 0;

           pSTDeviceList = new byte[iBufSize];
           iRet = (UCServiceRetvCode)conf.GetVideoDevList(0, 9, iBufSize, pSTDeviceList);
           Dictionary<int, string> dicVideoDev = new Dictionary<int, string>();
           if (iRet == UCServiceRetvCode.UC_SDK_Success)
           {
               IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTDeviceListParam);
               byte[] tempInfoByte = new byte[iSizeSTDeviceListParam];

               Marshal.Copy(pSTDeviceList, 0, tempInfoIntPtr, (int)iSizeSTDeviceListParam);
               STDeviceListParam head = (STDeviceListParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceListParam));

               for (int i = -1; i < head.iTotal - 1 && i < count - 1; i++)
               {
                   Marshal.Copy(pSTDeviceList, iSizeSTDeviceListParam + iSizeSTDeviceParam * i, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam item = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));
                   dicVideoDev.Add(item.index, item.name);
               }
               Marshal.Release(tempInfoIntPtr);
           }
           winOptionSetting.comCamera.ItemsSource = dicVideoDev;
           winOptionSetting.comCamera.SelectedValuePath = "Key";
           winOptionSetting.comCamera.DisplayMemberPath = "Value";
           winOptionSetting.comCamera.SelectedIndex = 0;
       }

       private void OKCommandProcess()
       {
           winOptionSetting.Close();
           ApplyCommandProcess();
       }
       private void CancelCommandProcess()
       {
           winOptionSetting.Close();
       }
       private void ApplyCommandProcess()
       {
           try
           {
               UCUserInfo user = new UCUserInfo();
               user.Camera = winOptionSetting.comCamera.SelectedIndex.ToString();
               user.Lang = winOptionSetting.comLang.SelectedIndex.ToString();
               user.MicPhone = winOptionSetting.comMicrophone.SelectedIndex.ToString();
               user.Password = winOptionSetting.txtPassword.Password.ToString();
               user.Port = winOptionSetting.txtPort.Text.ToString();
               user.Server = winOptionSetting.txtServer1.Text.ToString();
               user.Speaker = winOptionSetting.comSpeaker.SelectedIndex.ToString();
               user.UserID = winOptionSetting.txtAccount.Text.ToString();
               user.AutoStart = winOptionSetting.chkStart.IsChecked == true ? "1" : "0";
               user.Available = (bool)winOptionSetting.chkAvailable.IsChecked;
               user.Unavailable = (bool)winOptionSetting.chkUnavailable.IsChecked;
               user.Busy = (bool)winOptionSetting.chkBusy.IsChecked;
               user.Voicemail = (bool)winOptionSetting.chkVoicemail.IsChecked;
               user.AvailableCallNumber = winOptionSetting.txtAvailable.Text;
               user.UnavailableCallNumber = winOptionSetting.txtUnavailable.Text;
               user.BusyCallNumber = winOptionSetting.txtBusy.Text;
               user.VoicemailCallNumber = winOptionSetting.txtVoicemail.Text;
               user.SetFWDService = FrmToolBar.isSetFWDUnCond ? "1" : "0";

               XmlHelper.SetUserConfig(user);

               UserConfigBusiness conf = new UserConfigBusiness();
               conf.SetCurrentMicDev(winOptionSetting.comMicrophone.SelectedIndex);
               conf.SetCurrentVideoDev(winOptionSetting.comCamera.SelectedIndex);
               conf.SetCurrentSpeakerDev(winOptionSetting.comSpeaker.SelectedIndex);

               //modify by jinyeqing 2015/6/1   登陆时某些值为空要设置提示 (要求提示语言国际化)
               if (winOptionSetting.txtPort.Text.ToString() == "" || winOptionSetting.txtPort.Text.ToString() == null)
               {
                   Dialog.Show(StringHelper.FindLanguageResource("Portcannotbenull"), StringHelper.FindLanguageResource("error")); 
                   return;
               }
               if (winOptionSetting.txtPassword.Password.ToString() == "" || winOptionSetting.txtPassword.Password.ToString() == null)
               {
                   Dialog.Show(StringHelper.FindLanguageResource("Passwordcannotbenull"), StringHelper.FindLanguageResource("error")); 
                   return;
               }
               if (winOptionSetting.txtAccount.Text.ToString() == "" || winOptionSetting.txtAccount.Text.ToString() == null)
               {
                   Dialog.Show(StringHelper.FindLanguageResource("UserIDcannotbenull"), StringHelper.FindLanguageResource("error"));
                   return;
               }
               if (winOptionSetting.txtServer1.Text.ToString() == "" || winOptionSetting.txtServer1.Text.ToString() == null)
               {
                   Dialog.Show(StringHelper.FindLanguageResource("Servercannotbenull"), StringHelper.FindLanguageResource("error"));
                   return;
               }
               if (winOptionSetting.comLang.SelectedIndex.ToString() == "" || winOptionSetting.comLang.SelectedIndex.ToString() == null)
               {
                   Dialog.Show(StringHelper.FindLanguageResource("Languagecannotbenull"), StringHelper.FindLanguageResource("error"));
                   return;
               }
              // end modify 

               if (winOptionSetting.chkStart.IsChecked == true)
               {
                   RegistryKey runKey = Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run");
                   runKey.SetValue("LyncWpfApp.exe", System.Windows.Forms.Application.StartupPath + "\\LyncWpfApp.exe");
                   //如果Lync插件自启动，那么就算Lync设置了自启动也不能让它运行   modify by 00327190   2015/8/6
                   RegistryKey runKey1 = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run", true);
                   if (null != runKey1 && null != runKey1.GetValue("LyncWpfApp.exe"))
                   {
                       RegistryKey runKey2 = Registry.CurrentUser.OpenSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run", true);
                       if (null != runKey2 && null != runKey2.GetValue("Lync"))
                       {
                           runKey2.DeleteValue("Lync");
                       }
                   }      
               }
               else
               {
                   RegistryKey runKey = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Windows\CurrentVersion\Run", true);
                   runKey.DeleteValue("LyncWpfApp.exe");
               }
           }
           catch
           {
               LogManager.SystemLog.Info("DeleteSubKey");
           }        
       }
       public void SaveLyncAccountToConfig(string account)
       {
           try
           {
               UCUserInfo user = new UCUserInfo();
               user = XmlHelper.GetUserConfig();
               user.UserID = account;
               XmlHelper.SetUserConfig(user);
           }
           catch (System.Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
           }
       }
       public void StartLoadData()
       {
           try
           {
               UCUserInfo user = new UCUserInfo();
               user = XmlHelper.GetUserConfig();

               winOptionSetting.txtAccount.Text = user.UserID;
               winOptionSetting.comLang.SelectedIndex = Convert.ToInt32(user.Lang);

               winOptionSetting.txtPassword.Password = user.Password;
               winOptionSetting.txtPort.Text = user.Port;
               winOptionSetting.txtServer1.Text = user.Server;
              
               winOptionSetting.chkStart.IsChecked = user.AutoStart == "1" ? true : false;
               

               winOptionSetting.chkAvailable.IsChecked = user.Available;
               winOptionSetting.chkUnavailable.IsChecked = user.Unavailable;
               winOptionSetting.chkBusy.IsChecked = user.Busy;
               winOptionSetting.chkVoicemail.IsChecked = user.Voicemail;
               winOptionSetting.txtAvailable.Text = user.AvailableCallNumber;
               winOptionSetting.txtUnavailable.Text = user.UnavailableCallNumber;
               winOptionSetting.txtBusy.Text = user.BusyCallNumber;
               winOptionSetting.txtVoicemail.Text = user.VoicemailCallNumber;

               //设置呼叫前转信息
               if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
               {
                   return;
               }
               winOptionSetting.comMicrophone.SelectedIndex = GetMicrophone();
               winOptionSetting.comSpeaker.SelectedIndex = GetSpeaker();
               winOptionSetting.comCamera.SelectedIndex = GetCamera();

               int iRet = (int)UCServiceRetvCode.UC_SDK_Success;

               ForwardServiceType type = ForwardServiceType.FORWARD_UNCONDITION;
               STCallExData data = new STCallExData();
               MakeCallBusiness call = new MakeCallBusiness();

               //无条件前传
               iRet  = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radCallForwardUnCondEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               winOptionSetting.txtCallForwardUnCond.Text = data.Num;

               //遇忙前传
               type = ForwardServiceType.FORWARD_ONBUSY;
               data = new STCallExData();

               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radCallForwardBusyEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               winOptionSetting.txtCallForwardBusy.Text = data.Num;

               //无应答前传
               type = ForwardServiceType.FORWARD_NOREPLY;
               data = new STCallExData();

               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radCallForwardNoReplyEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               winOptionSetting.txtCallForwardNoReply.Text = data.Num;

               //离线前传
               type = ForwardServiceType.FORWARD_OFFLINE;
               data = new STCallExData();

               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radCallForwardOfflineEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               winOptionSetting.txtCallForwardOffline.Text = data.Num;

               //modify by 00327190   2015/7/30
               type = ForwardServiceType.VOICEMAIL_UNCONDITION;  //无条件语音邮箱前转
               data = new STCallExData();
               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radVoiceForwardUnCondEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               //winOptionSetting.txtVoiceForwardUnCond.Text = data.Num;   //2015/8/24

               // 无应答语音邮箱前转
               type = ForwardServiceType.VOICEMAIL_NOREPLY;  
               data = new STCallExData();
               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radVoiceForwardNoReplyEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               //winOptionSetting.txtVoiceForwardNoReply.Text = data.Num;   //2015/8/24

               // 遇忙语音邮箱前转
               type = ForwardServiceType.VOICEMAIL_ONBUSY;
               data = new STCallExData();
               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radVoiceForwardBusyEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               //winOptionSetting.txtVoiceForwardBusy.Text = data.Num;   //2015/8/24

               // 离线语音邮箱前转
               type = ForwardServiceType.VOICEMAIL_OFFLINE;
               data = new STCallExData();
               iRet = call.GetCallExService((int)type, ref data);
               if (iRet != (int)UCServiceRetvCode.UC_SDK_Success)
               {
                   LogManager.SystemLog.Error("GetCallExService error");
                   return;
               }
               winOptionSetting.radVoiceForwardOfflineEn.IsChecked = (string.IsNullOrEmpty(data.Num) ? false : true);
               //winOptionSetting.txtVoiceForwardOffline.Text = data.Num;   //2015/8/24

              
           }
           catch (System.Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
           }
       }
       private int GetMicrophone()
       {
           try
           {
               UserConfigBusiness conf = new UserConfigBusiness();

               int iSizeSTDeviceParam = Marshal.SizeOf(typeof(STDeviceParam));
               byte[] pSTDeviceParam = new byte[iSizeSTDeviceParam];

               UCServiceRetvCode iRet = (UCServiceRetvCode)conf.GetCurrentMicDev(pSTDeviceParam);
               if (iRet == UCServiceRetvCode.UC_SDK_Success)
               {
                   IntPtr tempInfoIntPtr = Marshal.AllocHGlobal(iSizeSTDeviceParam);

                   Marshal.Copy(pSTDeviceParam, 0, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam head = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));

                   if (head.index<0)
                   {
                       return 0;
                   }
                   else
                   {
                       return head.index;
                   }
               }
               else
               {
                   return 0;
               }
           }
           catch (Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
               return 0;
           }
       }
       private int GetSpeaker()
       {
           try
           {
               UserConfigBusiness conf = new UserConfigBusiness();

               int iSizeSTDeviceParam = Marshal.SizeOf(typeof(STDeviceParam));
               byte[] pSTDeviceParam = new byte[iSizeSTDeviceParam];

               UCServiceRetvCode iRet = (UCServiceRetvCode)conf.GetCurrentSpeakerDev(pSTDeviceParam);
               if (iRet == UCServiceRetvCode.UC_SDK_Success)
               {
                   IntPtr tempInfoIntPtr = Marshal.AllocHGlobal(iSizeSTDeviceParam);

                   Marshal.Copy(pSTDeviceParam, 0, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam head = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));

                   if (head.index < 0)
                   {
                       return 0;
                   }
                   else
                   {
                       return head.index;
                   }
               }
               else
               {
                   return 0;
               }
           }
           catch (Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
               return 0;
           }
       }
       private int GetCamera()
       {
           try
           {
               UserConfigBusiness conf = new UserConfigBusiness();

               int iSizeSTDeviceParam = Marshal.SizeOf(typeof(STDeviceParam));
               byte[] pSTDeviceParam = new byte[iSizeSTDeviceParam];

               UCServiceRetvCode iRet = (UCServiceRetvCode)conf.GetCurrentVideoDev(pSTDeviceParam);
               if (iRet == UCServiceRetvCode.UC_SDK_Success)
               {
                   IntPtr tempInfoIntPtr = Marshal.AllocHGlobal(iSizeSTDeviceParam);

                   Marshal.Copy(pSTDeviceParam, 0, tempInfoIntPtr, (int)iSizeSTDeviceParam);
                   STDeviceParam head = (STDeviceParam)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STDeviceParam));

                   if (head.index < 0)
                   {
                       return 0;
                   }
                   else
                   {
                       return head.index;
                   }
               }
               else
               {
                   return 0;
               }
           }
           catch (Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
               return 0;
           }
       }
   }
}
