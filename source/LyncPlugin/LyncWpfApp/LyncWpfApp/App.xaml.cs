using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Windows;
using System.Threading;
using System.Diagnostics;
using System.Globalization;
using System.IO;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        static WinLync win;
        public App()
        {
            Startup += new StartupEventHandler(App_Startup);
        }

        void App_Startup(object sender, StartupEventArgs e)
        {
            LogManager.SystemLog.Debug("Start App_Startup");
            win = new WinLync();
            this.MainWindow = win;
            win.Show();
            LogManager.SystemLog.Debug("End App_Startup");
        }

        public static class EntryPoint
        {
            [STAThread]
            public static void Main(string[] args)
            {
               App app = new App();
               app.Run();
            }
        }
        protected override void OnStartup(StartupEventArgs e)
        {
            log4net.Config.XmlConfigurator.Configure();
            LogManager.SystemLog.Debug("Start OnStartup");
            string str = Process.GetCurrentProcess().ProcessName;
            Process[] processes;
            //Get the list of current active processes.
            processes = System.Diagnostics.Process.GetProcesses();
            foreach (Process p in processes)
            {
                if (p.ProcessName == str)
                {
                    if (p.Id != Process.GetCurrentProcess().Id)
                    {
                        Environment.Exit(0);
                    }                  
                }
            }


            //载入语言
            LoadLanguage();
            base.OnStartup(e);

            LogManager.SystemLog.Debug("End OnStartup");
        }

        /// <summary>
        /// 程序启动时根据CultureInfo载入不同的语言
        /// 如：中文 currentCultureInfo.Name = zh-CN
        /// 程序自动载入zh-CN.xaml
        /// </summary>
        private void LoadLanguage()
        {
            LogManager.SystemLog.Debug("Start LoadLanguage");
            CultureInfo currentCultureInfo = CultureInfo.CurrentCulture;
            string name = currentCultureInfo.Name;
            LogManager.SystemLog.Debug(string.Format("Start LoadLanguage name = {0}", name));
            UCUserInfo user = new UCUserInfo();
            user = XmlHelper.GetUserConfig();
            if (user.Lang =="0")//语系地区
            {
                name = "zh-CN";
            }
            else if (user.Lang == "1")
            {
                name = "en-US";
            }
            else if (user.Lang == "2")
            {
                name = "pt-BR";//葡萄牙
            }
            LogManager.SystemLog.Info(string.Format("Start LoadLanguage = {0}", name));
            List<ResourceDictionary> langRdList = new List<ResourceDictionary>();
            try
            {
                langRdList.Add(
                System.Windows.Application.LoadComponent(
                new Uri("/Resources/Language/" + name + ".xaml", UriKind.Relative)) as ResourceDictionary);

                string[] strFiles = Directory.GetFiles(System.Windows.Forms.Application.StartupPath.Substring(0, System.Windows.Forms.Application.StartupPath.IndexOf("\\bin")) + "\\Resources\\Style");
                foreach (string strFile in strFiles)
                {
                    langRdList.Add(System.Windows.Application.LoadComponent(
                     new Uri("/Resources/Style/" + strFile.Substring(strFile.LastIndexOf("\\") + 1), UriKind.Relative)) as ResourceDictionary);
                }
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
            if (langRdList.Count > 0)
            {
                if (this.Resources.MergedDictionaries.Count > 0)
                {
                    this.Resources.MergedDictionaries.Clear();
                }
                foreach (ResourceDictionary langRd in langRdList)
                {
                    this.Resources.MergedDictionaries.Add(langRd);
                }
            }
            LogManager.SystemLog.Debug("End LoadLanguage");
        }
    }
}
