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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Threading;

namespace WpfSendMessage
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const int WM_COPYDATA = 0x004A;
        const int Thread_SleepTime = 1000;
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [StructLayout(LayoutKind.Sequential)]
        struct CopyDataStruct
        {
            public IntPtr dwData;
            public int cbData;//字符串长度
            [MarshalAs(UnmanagedType.LPStr)]
            public string lpData;//字符串
        }
        [DllImport("User32.dll", EntryPoint = "SendMessage")]
        static extern int SendMessage
        (
            IntPtr hWnd,//目标窗体句柄
            int Msg,//WM_COPYDATA
            int wParam,//自定义数值
            ref  CopyDataStruct lParam//结构体
        );

        public MainWindow(string[] args)
        {
            InitializeComponent();
            string src = args[args.Length - 1];
            this.Visibility = Visibility.Collapsed;
            Thread.Sleep(Thread_SleepTime);

            if (src == "LogOutUC" || src == "LoginUC")
            {
                SendMessage("Lync Basic", src);
            }
            else
            {
                string[] strList = src.Split(',');
                string message = string.Empty;
                foreach (string str in strList)
                {
                    message += (str.Substring(str.IndexOf(":") + 1).TrimEnd('>') + ";");
                }
                string strMain = args[args.Length - 2];
                message = args[args.Length - 3] + ";" + strMain.Substring(strMain.IndexOf(":") + 1).TrimEnd('>') + ";" + message;
                message = message.TrimEnd(';');
                SendMessage("Lync Basic", message);
            }

            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
        }

        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        static void SendMessage(string windowName, string strMsg)
        {
            if (strMsg == null)
            {
                return;
            }
            IntPtr hwnd = FindWindow(null, windowName);
            if (hwnd != IntPtr.Zero)
            {
                CopyDataStruct cds;
                cds.dwData = IntPtr.Zero;
                cds.lpData = strMsg;
                //注意：长度为字节数
                cds.cbData = System.Text.Encoding.Default.GetBytes(strMsg).Length + 1;
                // 消息来源窗体
                int fromWindowHandler = 0;
                SendMessage(hwnd, WM_COPYDATA, fromWindowHandler, ref  cds);
            }
        }
    }
}
