using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;

namespace WpfSendMessage
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        static string[] argList;
        public App()
        {
            Startup += new StartupEventHandler(App_Startup);
        }

        void App_Startup(object sender, StartupEventArgs e)
        {
            MainWindow win = new MainWindow(argList);
            this.MainWindow = win;
            win.Show();
        }

        public static class EntryPoint
        {
            [STAThread]
            public static void Main(string[] args)
            {
                argList = args;
                App app = new App();
                app.Run();
            }
        }
    }
}
