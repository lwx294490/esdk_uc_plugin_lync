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

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for Dialog.xaml
    /// </summary>
    public partial class DialogWindow : Window
    { 
        // 自动关闭的时间限制，如3为3秒后自动关闭
        private int second;
        // 计数器，用以判断当前窗口弹出后持续的时间
        private int counter;
        private Timer timer1;
       
        public DialogWindow()
        {
           
            InitializeComponent();
            WinLync.lyncCounter++;
            this.Closed += new EventHandler((sender, e)
                =>
                {
                    WinLync.lyncCounter--;
                });
        }

        private void btnOK_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        public void ShowDialog(string message, string title)
        {
            labContext.Content = message;
            this.Title = title == null ? "" : title;            
            this.ShowDialog();
        }
        public void ShowDialog1(string message,string title, int second)
        {
           
            // 获得时间限制
            this.second = second;
            // 初始化计数器
            this.counter = 0;
            // 初始化按钮的文本          
            var a = StringHelper.FindLanguageResource("OK");
            this.button1.Content = string.Format("{0}({1})",a, this.second - this.counter);
            // 激活并启动timer，设置timer的触发间隔为1000毫秒（1秒）
            this.timer1 = new Timer();
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new EventHandler(timer1_Tick);
            this.timer1.Start();
            labContext.Content = message;
            this.Title = title == null ? "" : title;
            this.button1.Content = string.Format("{0}({1})", a,this.second - this.counter);
            this.ShowDialog();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // 如果没有到达指定的时间限制
            if (this.counter <= this.second)
            {
                // 刷新按钮的文本
                var a = StringHelper.FindLanguageResource("OK");
                this.button1.Content = string.Format("{0}({1})", a, this.second - this.counter);
               // this.r();
                // 计数器自增
                this.counter++;
            }
            // 如果到达时间限制
            else
            {
                // 关闭timer
                this.timer1.Enabled = false;
                this.timer1.Stop();
                // 关闭对话框
                this.Close();
            }
        }
       
    }
    public class Dialog
    {
        public static void Show(string message, string title = null)
        {
            DialogWindow win = new DialogWindow();
            win.ShowDialog(message, title);
        }
    }

    public class DialogShow
    {
        public static void Show(string message, string title = null,int second=3)
        {
            DialogWindow win = new DialogWindow();
            win.ShowDialog1(message,title,second);
        }
    }

    
   
}
