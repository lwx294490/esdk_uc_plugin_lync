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
using System.Windows.Interop;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinCallReceive.xaml
    /// </summary>
    public partial class WinCallReceive : Window
    {
        public WinCallReceiveViewModel model;
        public WinLync lync;
        public string callName;      
        public bool isCloseButton = true;
        public bool isreturn=false;      
        //modify by jinyeqing 2015/6/5
        // 自动关闭的时间限制，如3为3秒后自动关闭
        private int second;
        // 计数器，用以判断当前窗口弹出后持续的时间
        private int counter;
        public string UcPhoneNo;   //查询自己的号码
        public string UcPhoneNo1;   //查询对方的号码
        public bool isvideo;         //是否为视频       
        public int  i=0;         //是否为视频       
        private Timer timer1;
        public bool isClose = false;   //语音升级 视频升级方挂断后传递的值让接受方也挂断    

        public WinCallReceive(WinLync lync, string name, bool isVide)
        {
            InitializeComponent();             
            btnFinish.Visibility = Visibility.Hidden;
            imgOtherPhone.Visibility = Visibility.Hidden;
            txtOtherPhone.Visibility = Visibility.Hidden; 
            callName = name;           
            model = new WinCallReceiveViewModel(this, isVide);
            this.lync = lync;
            this.DataContext = model;
            this.Title = StringHelper.GetSubString(name);
            isvideo = isVide;
            if (isVide)
            {
                this.Height = 120;               
            }
            else
            {
                imgType.Visibility = Visibility.Collapsed;
            }
            if (lync.isConnected == true)   //语音升级视频后再转移，此时expander不可见，espace无此种转移
            {
                this.expander.Visibility = Visibility.Hidden;
                //modify by 00327190  2015/7/27   语音升级视频时，未接受请求时，本地的视频升级按钮，加人按钮，呼叫保持按钮不能使用
                lync.winCall.btnVideo.IsEnabled = false;   
                lync.winCall.btnAddContact.IsEnabled = false;
                lync.winCall.btnCallSuspend.IsEnabled = false;           
                                
            }
            WinLync.lyncCounter++;
            this.Left = SystemParameters.WorkArea.Width - this.Width;
            this.Top = SystemParameters.WorkArea.Height - this.Height;
            this.Closing += new System.ComponentModel.CancelEventHandler(WinCallReceive_Closing);
            this.Closed += new EventHandler((sender, e)
                =>
            {
                WinLync.lyncCounter--;
            });
            GetPhone();   //2015/7/28
            lync.isHave = true;
           
        }

        void WinCallReceive_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (isCloseButton)
            {
                Visibility = Visibility.Hidden;
                model.DeclineCommand.Execute(isCloseButton);
                lync.isHave=false;
                return;
            }
            if (model.isAnswerMessage)
            {
                string str = callName + ";" + SingletonObj.LoginInfo.LyncName;
                lync.winCall = new WinCall(lync, str);
                //modify by 00327190 2015/7/25  之前插入到已拨电话中了 
                lync.winCall.callType = CallHistoryType.HISTORY_CALL_ANSWERED;
                //lync.winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                lync.winCall.Show();
                lync.isHave = false;
            }
            else   //只要关闭改界面，都强制变为False
            { 
                lync.isHave = false;
            }
        }

        private void expander_Expanded(object sender, RoutedEventArgs e)
        {

            imgType.Visibility = Visibility.Hidden;
            btnFinish.Visibility = Visibility.Visible;
            imgOtherPhone.Visibility = Visibility.Visible;
            txtOtherPhone.Visibility = Visibility.Visible;
            this.Height = 90;
        }

        private void expander_Collapsed(object sender, RoutedEventArgs e)
        {
            if (isvideo)  //视频呼叫 
            {
                imgType.Visibility = Visibility.Visible;
                btnFinish.Visibility = Visibility.Hidden;
                imgOtherPhone.Visibility = Visibility.Hidden;
                txtOtherPhone.Visibility = Visibility.Hidden;
                this.Height = 120;
            }
            else
            {
                imgType.Visibility = Visibility.Collapsed;
                btnFinish.Visibility = Visibility.Hidden;
                imgOtherPhone.Visibility = Visibility.Hidden;
                txtOtherPhone.Visibility = Visibility.Hidden;
                this.Height = 64;
            }
        }
       

        private void txtOtherPhone_GotMouseCapture(object sender, System.Windows.Input.MouseEventArgs e)
        {
            if (txtOtherPhone.Text == StringHelper.FindLanguageResource("transfernNumber"))
            {
                txtOtherPhone.Text = "";
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.isreturn = true;
            // 获得时间限制
            this.second = 26;    //半分钟未响应就自动关闭 （为了前后有时间误差，要低于30实际上，保证Wincall后挂断）
            // 初始化计数器
            this.counter = 0;
            // 初始化按钮的文本         

            // 激活并启动timer，设置timer的触发间隔为1000毫秒（1秒）
            this.timer1 = new Timer();
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new EventHandler(timer1_Tick);
            this.timer1.Start();
            if (this.isClose == true)
            {
                this.Close();
            }
            IntPtr hwnd = new WindowInteropHelper(this).Handle;
            lync.hwnd = hwnd;          
          
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // 如果没有到达指定的时间限制
            if (this.counter <= this.second)
            {
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
                lync.isHave = false;  //2015/8/3               
            }
        }

        //获取本人和对方的话机号码
        //get the phoneNos of your own and caller's
        private void GetPhone()
        {
            //7/28            
            UserConfigBusiness conf = new UserConfigBusiness();
            STContact con = new STContact();
            int iRet = conf.GetContactInfo(new StringBuilder(SingletonObj.LoginInfo.UserID), ref con);
            if (iRet == 0)
            {
                UcPhoneNo = con.ipphone1_;
            }
            string name1 = StringHelper.GetSubString(callName);
            int iRet1 = conf.GetContactInfo(new StringBuilder(name1), ref con);
            if (iRet1 == 0)
            {
                UcPhoneNo1 = con.ipphone1_;
            }
            else  //modify by 00327190   2015/9/17  纯话机用户拨打Lync
            {
                UcPhoneNo1 = name1;
            }
        }

       
       
    }
}
