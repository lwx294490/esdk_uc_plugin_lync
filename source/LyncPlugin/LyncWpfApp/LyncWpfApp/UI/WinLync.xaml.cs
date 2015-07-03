using System;
using System.Collections.Generic;
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
using System.Diagnostics;
using System.Windows.Interop;
using System.Threading;
using System.Windows.Forms;
using System.ComponentModel;
using Microsoft.Win32;
using System.Reflection;
using Accessibility;
using System.IO;
using Microsoft.Lync.Model;
using Microsoft.Lync.Model.Group;
using System.Linq;
using System.Management;
using System.Globalization;
using System.Runtime.InteropServices;




namespace LyncWpfApp
{
#pragma warning disable 0618
    /// <summary>
    /// Interaction logic for WinLync.xaml
    /// </summary>
    public partial class WinLync : Window
    {
        int iToolBarHeightOff = 65;//工具盘高度偏移量
        int iWpfHeightTopOff = 30;//lync窗体高度偏移量
        int iWpfLeftWidthOff = 8;//lyn窗体宽度左偏移量
        double iWpfRightWidthOff = -1;//lyn窗体宽度右偏移量
        const int iToolBarWidthOff = 30;//工具盘宽度偏移量
        const int iHexValue = 256;//4bit最大值
        const int SW_HIDE = 0;//隐藏值
        const int SW_SHOWNORMAL = 1;//显示
        const int WM_GETTEXT = 13;//获取文本
        const int CHILDID_SELF = 0;//控件自身
        const int CHILDID_1 = 1;
        const int ClientChilrenNum = 5;
        const int OBJID_CLIENT = -4;
        const int WM_COPYDATA = 0x004A;//进程间传递数据
        const int WM_ACTIVATE = 7;//窗体激活
        const int SWP_NOSIZE = 0x0001;//保持当前大小
        const int SWP_NOMOVE = 0x0002;//保持当前位置
        const int RDW_INVALIDATE = 0x0001;
        const int RDW_ERASE = 0x0004;
        const int RDW_UPDATENOW = 0x0100;
        const int WM_MOVE = 0x0003;//移动窗口
        const byte KEYEVENTF_KEYUP = 2;
        const byte VK_CONTROL = 17;//CTRL键
        const byte VK_C = 67;// CTRL + C 键
        const int iLOGPIXELSX = 88;//水平分辨率
        const int iLOGPIXELSY = 90;//垂直分辨率
        const int iDelay = 500;//tooltip延迟  
        const int iThreadSleepTime = 5;//线程sleep时间
        const double dpi = 96.0;//基准dpi值
        const int iReloginTimeOff = 30;//注销超时秒数
        const int iReceiveLeftOff = -500;//来电接受窗体左偏移大小
        int iWpfHeightButtomOff = 30;//lync窗体高度偏移量
        double scaleUIY = 0;//系统dpi值
        bool shouldStop = false;//线程是的停止
        bool sizeChangeFinished = false;
        bool canReLogin = true;//被踢掉，是否能够重新登录
        public System.Timers.Timer timerReLogin;//重新登录计时器 
        string exeName = string.Empty;//lync进程名
        RECTSize WpfPreviousRECT = new RECTSize();//保存wpf尺寸变化之前的尺寸
        public ContactAvailability userState;//保存lync状态信息
        public FrmToolBar toolBar = null;//工具盘
        public WinCall winCall;//呼叫窗体       
        public WinCallReceive winCallReceive;//呼叫接听窗体   modify by jinyeqing   2015/6/5
        public System.Timers.Timer timer;//通话计时器 
        //modify by jinyeqing
        public bool isreturn=false;
        public bool isConnected = false;
        public bool isUcCount= true;
        int i = 0;   //6/23
        //modify by jinyeqing  2015/6/8
        public static GroupCollection LyncContactGroups;//lync联系人组集合
        static public LyncClient _Client = null;//lync客户端对象
        static ReaderWriterLockSlim lockObjLyncState = new ReaderWriterLockSlim();//获取lync客户端状态线程锁
        static ReaderWriterLockSlim lockObjLyncMove = new ReaderWriterLockSlim();//获取lync移动状态线程锁
        static ReaderWriterLockSlim lockLyncUCLoginOut = new ReaderWriterLockSlim();//获取lync移动状态线程锁
        ContactManager LyncContactManager;//lync联系人管理对象
        Process process = null;//lync进程
        IntPtr iLyncAppWinHandle;//lync窗体句柄
        IntPtr iMainWpfHandle;//主窗体句柄
        IntPtr iToolBarHandle;//工具盘句柄
        Thread threadRefreshToolBar = null;//刷新工具盘
        Thread threadGetLyncState = null;//获取lync state
        Thread threadGetLyncClient = null;//获取lync客户端
        Thread threadUCContactStateChanged = null;//UC状态改变处理线程
        Thread threadLyncClientStateChanged = null;//lync状态改变处理线程
        BackgroundWorker backgroundWorker = new BackgroundWorker();//BackgroundWorker 类允许您在单独的专用线程上运行操作
        delegate bool CallBack(int hwnd, int lParam);
        static CallBack callBackEnumChildWindows = new CallBack(ChildWindowProcess);//枚举子窗体回调函数
        static List<IntPtr> lyncChildHwndList = new List<IntPtr>();//lync子窗体列表
        static CallBack callBackFindSelectItem = new CallBack(FindSelectItemProcess);//查询lync窗体控件回调函数
        WinCallReceive receive;//来电接受窗体      
        HwndSourceHook hook;//捕捉画面消息钩子
        HwndSource hs;//包含 WPF 内容的 Win32 窗口
        DateTime dtStart;//开始时间
        System.Windows.Forms.ToolTip toolTipLabState;//工具盘tooltip
        public static int lyncCounter = 0;//打开的子窗体数量,用以控制工具盘的刷新
        public double scaleUIX = 0;//系统dpi值
        public WinDail winDial = null;//拨号盘画面
        public WinTwoDail winTwoDail;//二次拨号画面
        public WinAllContact winAllContact;//联系人画面
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        static extern int GetWindowThreadProcessId(IntPtr hwnd, int ID);
        [DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        [DllImport("user32.dll", SetLastError = true)]
        public static extern long SetParent(IntPtr hWndChild, IntPtr hWndNewParent);
        [DllImport("user32.dll", EntryPoint = "SetWindowPos", SetLastError = true)]
        static extern long SetWindowPos(IntPtr hwnd, IntPtr hWndInsertAfter, int x, int y, int cx, int cy, uint wFlags);
        [DllImport("user32.dll", EntryPoint = "MoveWindow", SetLastError = true)]
        static extern bool MoveWindow(IntPtr hwnd, int x, int y, int cx, int cy, bool repaint);
        [DllImport("User32.dll", EntryPoint = "PostMessage")]
        static extern int PostMessage(
            IntPtr hWnd,        // 信息发往的窗口的句柄
            int Msg,            // 消息ID
            int wParam,         // 参数1
            ref  COPYDATASTRUCT lParam  // 参数2
        );
        [DllImport("user32.dll")]
        static extern IntPtr GetDC(IntPtr hwnd);
        [DllImport("user32.dll")]
        static extern Int32 ReleaseDC(IntPtr hwnd, IntPtr hdc);
        [DllImport("gdi32.dll")]
        static extern uint GetPixel(IntPtr hdc, int nXPos, int nYPos);
        // 获得窗口矩形    
        [DllImport("user32.dll")]
        static extern int GetWindowRect(IntPtr hWnd, out RECT lpRect);
        // 获得客户区矩形    
        [DllImport("user32.dll")]
        static extern int GetClientRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("user32.dll", EntryPoint = "ShowWindow", SetLastError = true)]
        static extern bool ShowWindow(IntPtr hWnd, uint nCmdShow);
        [DllImport("user32.dll")]
        static extern int EnumChildWindows(int hWndParent, CallBack lpfn, int lParam);
        [DllImport("user32.dll")]
        static extern int GetWindowText(int hWnd, StringBuilder lpString, int nMaxCount);
        [DllImport("user32")]
        static extern bool IsWindowVisible(int hwnd);
        [DllImport("user32.dll", EntryPoint = "FindWindowEx")]
        static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);
        [DllImport("Oleacc.dll")]
        static extern int AccessibleObjectFromWindow(IntPtr hwnd, int dwObjectID, ref Guid refID, ref IAccessible ppvObject);
        [DllImport("Oleacc.dll")]
        static extern int AccessibleChildren(Accessibility.IAccessible paccContainer, int iChildStart, int cChildren, [Out] object[] rgvarChildren, out int pcObtained);
        [DllImport("user32.dll", EntryPoint = "keybd_event")]
        static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);
        [DllImport("gdi32.dll")]
        static extern int GetDeviceCaps(IntPtr hdc, int nIndex);
        [DllImport("user32.dll", EntryPoint = "SetFocus")]
        static extern int SetFocus(IntPtr hWnd);
        [DllImport("user32.dll")]
        static extern bool SetForegroundWindow(IntPtr hWnd);
        [DllImport("user32.dll", EntryPoint = "GetWindow")]
        static extern int GetWindow(IntPtr hWnd, int nCmd);
        [DllImport("user32.dll", ExactSpelling = true)]
        static extern IntPtr GetAncestor(IntPtr hwnd, int flags);
        [DllImport("kernel32.dll")]        
        static extern void ExitProcess(uint uExitCode);

        public bool isSigned;   //UC登陆状态 

        class UCStatePara
        {
            public SignInState signInState;
            public StringBuilder reason;
        }
        string ExeName//lync进程名
        {
            get
            {
                return exeName;
            }
            set
            {
                exeName = value;
            }
        }
        int WPFWidth
        {
            get;
            set;
        }
        int WPFHeight
        {
            get;
            set;
        }
        public static List<string> SelectedUserList
        {
            get;
            set;
        }
        public WinLync()//构造函数
        {
            LogManager.SystemLog.Debug("Start WinLync");
            InitializeComponent();            
            backgroundWorker.WorkerReportsProgress = true;           
            Loaded += new RoutedEventHandler(WinLync_Loaded);
            Closing += new CancelEventHandler(WinLync_Closing);
            try
            {
                RegistryKey pregkey10 = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Communicator");//获取2010指定路径下的键

                if (null != pregkey10 && null != pregkey10.GetValue("InstallationDirectory"))
                {
                    exeName = pregkey10.GetValue("InstallationDirectory") + "communicator.exe";
                }

                RegistryKey pregkey13 = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Office\15.0\Lync");//获取2013指定路径下的键,以2013为主
                if (null != pregkey13 && null != pregkey13.GetValue("InstallationDirectory"))
                {
                    exeName = pregkey13.GetValue("InstallationDirectory") + "lync.exe";                 
                }
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
            GetWinDPI();//获取系统DPI 
            GetWinCaptionHeight();       

            LogManager.SystemLog.Debug("End WinLync");
        }

       



        /// <summary>
        /// 获取系统窗体标题栏的高度
        /// </summary>
        void GetWinCaptionHeight()
        {
            try
            {
                RegistryKey pregkey = Registry.CurrentUser.OpenSubKey(@"Control Panel\Desktop\WindowMetrics");

                if (null != pregkey && null != pregkey.GetValue("CaptionHeight"))
                {
                    int iHeight = Convert.ToInt32(pregkey.GetValue("CaptionHeight"));
                   
                    if (iHeight == -270)
                    {
                        iToolBarHeightOff = 55;//工具盘高度偏移量
                        iWpfHeightTopOff = 25;//lync窗体高度偏移量
                        iWpfLeftWidthOff = 5;//lyn窗体宽度左偏移量
                        iWpfRightWidthOff = 0.5;//lyn窗体宽度右偏移量
                    }
                    else
                    {
                        iToolBarHeightOff = 65;//工具盘高度偏移量
                        iWpfHeightTopOff = 30;//lync窗体高度偏移量
                        iWpfLeftWidthOff = 8;//lyn窗体宽度左偏移量
                        iWpfRightWidthOff = -1;//lyn窗体宽度右偏移量
                    }
                }
            }
            catch (System.Exception ex)
            {
                iToolBarHeightOff = 65;//工具盘高度偏移量
                iWpfHeightTopOff = 30;//lync窗体高度偏移量
                iWpfLeftWidthOff = 8;//lyn窗体宽度左偏移量
                iWpfRightWidthOff = -1;//lyn窗体宽度右偏移量

                LogManager.SystemLog.Error(ex.ToString());
            }
           
        }

        /// <summary>
        /// 客户端关闭前处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void WinLync_Closing(object sender, CancelEventArgs e)
        {
            LogManager.SystemLog.Debug("Start WinLync_Closing");

            if (!process.HasExited)
            {
                e.Cancel = true;
                ShowWindow(iLyncAppWinHandle, SW_HIDE);
                SetParent(iLyncAppWinHandle, IntPtr.Zero);              

            }
               
            LogManager.SystemLog.Debug("End WinLync_Closing");
        }

               
        /// <summary>
        /// 客户端尺寸变化处理函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void WinLync_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            try
            {
                sizeChangeFinished = false;

                WpfPreviousRECT.left = this.Left;
                WpfPreviousRECT.top = this.Top;
                WpfPreviousRECT.width = this.Width;
                WpfPreviousRECT.height = this.Height;

                WPFWidth = (int)this.Width;
                WPFHeight = (int)this.Height;

                if (this.WindowState == WindowState.Maximized)
                {
                    MaximizedMoveToolBar();
                    MaximizedMoveWindow();
                }
                else if (this.iLyncAppWinHandle != IntPtr.Zero)
                {
                    MoveWindow(iToolBarHandle, 0, (int)((WPFHeight - iToolBarHeightOff) * scaleUIY), (int)(WPFWidth * scaleUIX), (int)(iToolBarWidthOff * scaleUIX), true);
                    MoveWindowVisible();
                }

                if (System.Windows.Forms.Control.MouseButtons != MouseButtons.Left && this.WindowState != WindowState.Maximized)//鼠标左键按下，不刷新画面
                {
                    SetLyncFocusForeground();//强制lync获取焦点、激活lync         
                }
            }
            finally
            {
                sizeChangeFinished = true;
            }
           
        }

        /// <summary>
        /// 强制lync获取焦点、激活lync
        /// </summary>
        void SetLyncFocusForeground()
        {
            LogManager.SystemLog.Debug("SetLyncFocusForeground");
            //设置lync得到焦点、激活，去掉边框阴影
            SetFocus(iLyncAppWinHandle);// 强制lync获取焦点
            SetForegroundWindow(iLyncAppWinHandle);//强制激活lync
            //设置wpf得到焦点、激活，防止lync边框显示，可以拖动lync          
           SetFocus(iMainWpfHandle);// 强制wpf获取焦点               
           SetForegroundWindow(iMainWpfHandle);//强制激活wpf             
          
        }
        /// <summary>
        /// 程序退出
        /// </summary>
        private void ExitApp()
        {
            //modify by jinyeqing 2015/6/2
          LogManager.SystemLog.Error(string.Format("Enter ExitApp"));
          bool isreturn = false;
          try
            {
                Dispatcher.Invoke(new Action(()
                    =>
                {
                    Visibility = Visibility.Hidden;
                }));
                if (_Client != null && _Client.State == ClientState.SignedOut)
                {
                    process.Kill();                   
                  
                }
                process.WaitForExit(5);  //modify by jinyeqing 2015/6/2 原先是没有5毫秒的等待超时的，现在定义5ms等待超时，这样就可以强制执行下面的程序  
                Dispatcher.Invoke(new Action(()
                =>
                {
                    shouldStop = true;
                    if (null != toolBar)
                    {
                        toolBar.Close();                       
                    }                                    
                    //modify by jinyeqing 2015/6/2                 
                    LogManager.SystemLog.Info(string.Format("SingletonObj.LoginInfo={0} ", SingletonObj.LoginInfo));                    
                    if (SingletonObj.LoginInfo != null && SingletonObj.LoginInfo.UserID != string.Empty)
                    {                       
                        isreturn = true;
                        LogManager.SystemLog.Info("enter StartSignOutUC");
                        StartSignOutUC();//注销UC
                        LogManager.SystemLog.Info("exit  StartSignOutUC"); 

                    }
                    //modify by jinyeqing 2015/6/2
                    //if (isreturn == false)
                    //{
                    //    LogManager.SystemLog.Info("isreturn is false ");
                    //    StartSignOutUC();//注销UC   这个isreturn打出来是为了确保上面的注销UC没执行的话，这边执行一下  
                    //}
                    //modify by jinyeqing 2015/6/2
                    StartUnInit();//释放UC                                       
                    RegistryKey pregkey;
                    if (exeName.IndexOf("Communicator") > 0)//lync 2010
                    {
                        pregkey = Registry.CurrentUser.OpenSubKey(@"Software\Microsoft\Communicator", true);//获取指定路径下的键
                    }
                    else
                    {
                        pregkey = Registry.CurrentUser.OpenSubKey(@"Software\Microsoft\Office\15.0\Lync", true);//获取指定路径下的键
                    }
                  
                    if (null != pregkey.GetValue("WindowRect"))//保存关闭时画面位置、大小，以十六进制、每个字段占四个bit、高字节在前存储
                    {
                        byte[] windowRect = new byte[16];

                        int index = 1;
                        int left = (int)Left;
                        if (left / iHexValue > 0)
                        {
                            windowRect[index] = (byte)(left / iHexValue);
                            left = left % iHexValue;
                        }
                        windowRect[index - 1] = (byte)left;
                        index += 4;

                        int top = (int)Top;
                        if (top / iHexValue > 0)
                        {
                            windowRect[index] = (byte)(top / iHexValue);
                            top = top % iHexValue;
                        }
                        windowRect[index - 1] = (byte)top;
                        index += 4;

                        int width = (int)(Width + Left);
                        if (width / iHexValue > 0)
                        {
                            windowRect[index] = (byte)(width / iHexValue);
                            width = width % iHexValue;
                        }
                        windowRect[index - 1] = (byte)width;
                        index += 4;

                        int heigth = (int)(Height + Top);
                        if (heigth / iHexValue > 0)
                        {
                            windowRect[index] = (byte)(heigth / iHexValue);
                            heigth = heigth % iHexValue;
                        }
                        windowRect[index - 1] = (byte)heigth;
                        pregkey.SetValue("WindowRect", windowRect, RegistryValueKind.Binary);
                    }
                    DeleteRegistry();                 
                    System.Windows.Forms.Application.ExitThread();  //modify by jinyeqing 2015/6/2 多打点日志 看卡在哪里 
                    Thread.Sleep(iThreadSleepTime);
                    ////modify by jinyeqing 2015/4/27  问题单（退出时后台LyncWpfApp进程还是在运行）  解决思路：可能插件退出之前程序已经卡死，都没跑进该方法，打日志标注一下
                    LogManager.SystemLog.Error(string.Format("Exit  ExitApp"));    

                    Environment.Exit(0);
                       
                  
                }));
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 客户端加载函数
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void WinLync_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {
                LogManager.SystemLog.Debug("Start WinLync_Loaded");
                this.Visibility = Visibility.Hidden; ;
                this.StateChanged += new EventHandler(WinLync_StateChanged);

                SelectedUserList = new List<string>();
                WPFWidth = (int)this.Width;
                WPFHeight = (int)this.Height;
                backgroundWorker.DoWork += new DoWorkEventHandler(backgroundWorker_DoWork);//在此事件处理程序中调用耗时的操作
                backgroundWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(backgroundWorker_RunWorkerCompleted);//当后台操作已完成、被取消或引发异常时发生
                backgroundWorker.RunWorkerAsync();//开始执行后台操作
                threadRefreshToolBar = new Thread(new ThreadStart(WinLync_RefreshToolBar));//在 Thread 上执行的方法
                threadRefreshToolBar.Priority = ThreadPriority.BelowNormal;    
                threadRefreshToolBar.Start();
                
                LogInBusiness.GetUCStateChanged = UCContactStateChanged;//获取UC登录状态 
                LogInBusiness.StatusChanged = UCStatusChanged;
                LogInBusiness.AVSessAdded = UCAVSessAdded;
                LogInBusiness.AVSessionClosed = UCAVSessionClosed;
                LogInBusiness.AVSessionConnected = UCAVSessionConnected;

                hook = new HwndSourceHook(WndProc);//MainWindow中注册Hook
                hs = PresentationSource.FromVisual(this) as HwndSource;
                if (null == hs)
                {
                    LogManager.SystemLog.Error("HwndSourceHook = NULL");
                    return;
                }
                hs.AddHook(hook);
                LogManager.SystemLog.Debug("End WinLync_Loaded");
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }

        }
        /// <summary>
        /// 获取系统DPI参数
        /// </summary>
        void GetWinDPI()
        {
            IntPtr screenDC = GetDC(IntPtr.Zero);
            int dpi_x = GetDeviceCaps(screenDC, iLOGPIXELSX);
            int dpi_y = GetDeviceCaps(screenDC, iLOGPIXELSY);
            scaleUIX = (dpi_x / dpi);
            scaleUIY = (dpi_y / dpi);
            ReleaseDC(IntPtr.Zero, screenDC);
            LogManager.SystemLog.Debug(string.Format("scaleUIX = {0}", scaleUIX));
        }

        /// <summary>
        /// 收到呼叫事件回调函数
        /// </summary>
        /// <param name="para"></param>
        void UCAVSessAdded(STAudioVideoParam para)
        {
            ////modify by jinyeqing 2015/5/19   由于锁屏或者呼叫产生奔溃时导致的 SingletonObj.LoginInfo.LyncName为空，所以加个判断条件，if和else 
            //if (SingletonObj.LoginInfo.LyncName != null || SingletonObj.LoginInfo.LyncName != "")
            //{
                LogManager.SystemLog.Debug(string.Format("callerAcc = {0}", para.callerAcc));
                LogManager.SystemLog.Debug(string.Format("LyncName = {0}", SingletonObj.LoginInfo.LyncName));
                string strBuffer = para.callerAcc;
                string str = "";
                if (para.AccountType == 0)
                {
                    str = StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                }
                strBuffer = strBuffer + str;
                Dispatcher.BeginInvoke(new Action(() =>
                {
                    receive = new WinCallReceive(this, strBuffer, para.isvideo_ == 1);
                    if (para.callMode == (int)MemberType.UC_IPPHONE)//iphones呼出来电时，不现实来电窗体
                    {
                        receive.Left = iReceiveLeftOff;
                    }
                    if (para.isConference == 1)      //来电是会议的时候，expander控件不可见,answer改为ConAnswer
                    {
                        receive.expander.Visibility = Visibility.Hidden;
                        receive.btnAnswer.Content = StringHelper.FindLanguageResource("ConAnswer");                      
                    }
                    receive.Show();
                }));
               
            //}
            //else
            //{
            //    Dialog.Show(StringHelper.FindLanguageResource("PleaseLoginUCagain"), StringHelper.FindLanguageResource("error")); 
            //}
        }

        /// <summary>
        /// 通话结束事件回调函数
        /// </summary>
        /// <param name="para"></param>
        public void UCAVSessionClosed(STMsgAVSessionClosedParam para)
        {
            LogManager.SystemLog.Debug("UCAVSessionClosed");
            this.isConnected = false;   //modify by jinyeqing 2015/6/8
            Dispatcher.BeginInvoke(new Action(() =>
            {
                if (winCall != null)
                {
                    winCall.Close();
                }             
                if (receive != null)
                {
                    receive.Close();
                }
            }));
            if (timer != null && timer.Enabled)
            {
                timer.Enabled = false;
            }
            i = 0;   //modify by 00327190   2015/6/23  将i置为0，这样就会避免第二次之后的设置Video图片失败   （654行）
        }
        /// <summary>
        /// 通话连接事件回调函数
        /// </summary>
        public void UCAVSessionConnected()
        {
            LogManager.SystemLog.Debug("UCAVSessionConnected");
            if (receive != null)
            {
                Dispatcher.Invoke(new Action(()
                =>
                {
                    receive.isCloseButton = false;
                    receive.model.isAnswerMessage = true;
                    receive.Close();
                }));
            }
            if (winCall == null)
            {
                return;
            }
            if (timer == null)
            {
                timer = new System.Timers.Timer();//实例化Timer类
                timer.Interval = iThreadSleepTime * 200;//设置间隔时间，为毫秒；
                timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);////到达时间的时候执行事件；
                timer.AutoReset = true;//设置是执行一次（false）还是一直执行(true)；
            }

            dtStart = DateTime.Now;
            timer.Enabled = true;//是否执行System.Timers.Timer.Elapsed事件；
            isConnected = true;  //modify by jinyeqing  2015/6/8  以下是因为语音未接通时不让主叫视频按钮显示            
            setBtn();
          
        }



        /// <summary>
        /// 设置图标状态
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void setBtn()
        {
            string str = winCall.strtemp;
            if (winCall.isAddContract == false)   //不执行wincall 里面
            {
                Dispatcher.Invoke(new Action(()
                =>
                {
                    if (toolBar.JointType == PhoneJointType.IPPhone_Device)
                    {
                        winCall.btnVideo.IsEnabled = false;     //话机联动状态下，不能呼叫视频
                        winCall.btnAddContact.IsEnabled = false;
                        winCall.btnBlindTransCall.IsEnabled = false;
                        winCall.btnDial.IsEnabled = true;
                        winCall.btnSetMicPhone.IsEnabled = true;
                        winCall.btnSetVol.IsEnabled = true;
                        winCall.btnCallSuspend.IsEnabled = true;
                        if (i == 0)
                        {
                            winCall.SetVideoImage();            //设置视频按钮图片        6/23    
                            i++;
                        }
                    }
                    else
                    {
                        winCall.btnVideo.IsEnabled = true;

                        if (SingletonObj.LoginInfo.LyncName != str.Split(';')[0] && str.Split(';').Length != 1) //被叫权限设置（不能使用添加按钮）
                        {
                            winCall.btnAddContact.IsEnabled = false;
                            winCall.btnBlindTransCall.IsEnabled = true;
                            if (i == 0)
                            {
                                winCall.SetVideoImage();            //设置视频按钮图片        6/23    
                                i++;
                            }
                        }
                        else
                        {
                            if (str.Split(';').Length > 2)   //会议中主叫可以加人但是不能呼叫转移
                            {
                                winCall.btnAddContact.IsEnabled = true;
                                winCall.btnBlindTransCall.IsEnabled = false;
                            }
                            else                            //两人会话中主叫可以加人可以呼叫转移
                            {
                                winCall.btnBlindTransCall.IsEnabled = true;
                                winCall.btnAddContact.IsEnabled = true;
                            }
                        }
                        winCall.btnCallSuspend.IsEnabled = true;
                        winCall.btnDial.IsEnabled = true;
                        winCall.btnSetMicPhone.IsEnabled = true;
                        winCall.btnSetVol.IsEnabled = true;
                    }
                }));
            }
            else
            {

                Dispatcher.Invoke(new Action(()
               =>
               {
                   if (toolBar.JointType == PhoneJointType.IPPhone_Device)
                   {
                       winCall.btnVideo.IsEnabled = false;     //话机联动状态下，不能呼叫视频
                       winCall.btnAddContact.IsEnabled = false;
                       winCall.btnBlindTransCall.IsEnabled = false;
                       winCall.btnSetMicPhone.IsEnabled = true;
                       winCall.btnSetVol.IsEnabled = true;
                       winCall.btnCallSuspend.IsEnabled = true;
                       winCall.btnDial.IsEnabled = true;
                   }
                   else
                   {
                       winCall.btnCallSuspend.IsEnabled = true;
                       winCall.btnDial.IsEnabled = true;
                       if (SingletonObj.LoginInfo.LyncName != str.Split(';')[0] && str.Split(';').Length != 1) //被叫权限设置（不能使用添加按钮）
                       {
                           winCall.btnAddContact.IsEnabled = false;
                           winCall.btnBlindTransCall.IsEnabled = true;
                       }
                       else
                       {
                           if ((str.Split(';').Length > 2))  //会议中主叫可以加人但是不能呼叫转移
                           {
                               winCall.btnAddContact.IsEnabled = true;
                               winCall.btnBlindTransCall.IsEnabled = false;
                           }
                           else                            //两人会话中主叫可以加人可以呼叫转移
                           {
                               winCall.btnBlindTransCall.IsEnabled = true;
                               winCall.btnAddContact.IsEnabled = true;
                           }
                       }
                       winCall.btnSetMicPhone.IsEnabled = true;
                       winCall.btnSetVol.IsEnabled = true;
                   }

               }));
            }
        }
        /// <summary>
        /// 通话时间计时器
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                if (winCall == null)
                {
                    timer.Enabled = false;
                    return;
                }
                DateTime dt = DateTime.Now;
                TimeSpan sp = dt.Subtract(dtStart);
                string hour = sp.Hours < 10 ? "0" + sp.Hours.ToString() : sp.Hours.ToString();
                string minutes = sp.Minutes < 10 ? "0" + sp.Minutes.ToString() : sp.Minutes.ToString();
                string seconds = sp.Seconds < 10 ? "0" + sp.Seconds.ToString() : sp.Seconds.ToString();
                winCall.labTime.Content = hour + ":" + minutes + ":" + seconds;
            }));
        }
        /// <summary>
        /// 状态回调函数
        /// </summary>
        /// <param name="_state"></param>
        /// <param name="_desc"></param>
        /// <param name="_contact"></param>
        /// <param name="_param"></param>
        void UCStatusChanged(int _state, STContact _contact)
        {
            ParameterizedThreadStart para = new ParameterizedThreadStart(UpdateUCContactStateThread);
            Thread thread = new Thread(para);
            thread.Priority = ThreadPriority.Highest;
            UCContactInfo info = new UCContactInfo();
            info.State = _state;
            info.User = _contact;
            thread.Start(info);
        }
        /// <summary>
        /// 更新联系人状态函数
        /// </summary>
        /// <param name="info"></param>
        private void UpdateUCContactStateThread(object info)
        {
            if (winCall == null)
            {
                return;
            }
            else
            {
                winCall.UpdateUCContactState(info);
            }
        }
        /// <summary>
        /// 窗体消息
        /// </summary>
        /// <param name="hwnd"></param>
        /// <param name="msg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <param name="handled"></param>
        /// <returns></returns>
        private IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                case WM_MOVE://窗体移动事件

                    if (lockObjLyncMove.TryEnterWriteLock(0))
                    {
                        try
                        {
                            Thread thread = new Thread(new ThreadStart(WpfMoveGetMouseState));
                            thread.Priority = ThreadPriority.Highest;
                            thread.Start();
                        }
                        finally
                        {
                            lockObjLyncMove.ExitWriteLock();
                        }                       
                    }
                    return (System.IntPtr)wParam;

                case WM_ACTIVATE://激活wpf画面，使其能够点击工具栏图标时前置显示
                    Thread.Sleep(iThreadSleepTime);//暂停，使GetLyncState先处理，设置wpf的可见性
                    if (this.Visibility == Visibility.Hidden)//当wpf隐藏时返回，快速点击任务栏的图标两次会出现wpf、lync分离的现象
                    {
                        ShowWindow(iMainWpfHandle, SW_HIDE);//隐藏wpf
                        return (System.IntPtr)wParam;
                    }
                    this.Activate();
                    this.Topmost = true;
                    this.Topmost = false;
                    return (System.IntPtr)wParam;

                case WM_COPYDATA://获取另一进程发过来的消息
                    COPYDATASTRUCT cds = (COPYDATASTRUCT)System.Runtime.InteropServices.Marshal.PtrToStructure(lParam, typeof(COPYDATASTRUCT));
                    LogManager.SystemLog.Info(string.Format("COPYDATASTRUCT = {0}", cds.cbData));
                    LyncMessageProcess(cds);
                    return (System.IntPtr)wParam;                

                default:
                    return (System.IntPtr)wParam;
            }
        }


       
       

        /// <summary>
        /// 获取鼠标状态，左键UP时开启线程，去掉lync阴影
        /// </summary>
        void WpfMoveGetMouseState()
        {
            if (lockObjLyncMove.TryEnterWriteLock(iThreadSleepTime))
            {
                try
                {
                    WpfMoveMessageFun();    
                    while (System.Windows.Forms.Control.MouseButtons == MouseButtons.Left)
                    {
                        Thread.Sleep(iThreadSleepTime);//sleep 5毫秒
                    }
                    Thread thread = new Thread(new ThreadStart(WpfMoveMessageFun));
                    thread.Start();
                }
                finally
                {
                    lockObjLyncMove.ExitWriteLock();
                }
            }
        }
        /// <summary>
        /// 判断wpf尺寸是否变化
        /// </summary>
        /// <returns></returns>
        bool IsWpfSizeChanged()
        {
            bool flag = false;
            Dispatcher.Invoke(new Action(() =>
            {
                if ((WpfPreviousRECT.width == Width && WpfPreviousRECT.height == Height) &&
                    (WpfPreviousRECT.left != Left || WpfPreviousRECT.top != Top))
                {
                    flag = true;
                }
            }));
            return flag;
        }
        /// <summary>
        /// wpf窗体移动处理函数
        /// </summary>
        void WpfMoveMessageFun()
        {
            LogManager.SystemLog.Debug("WpfMoveMessageFun");
            Thread.Sleep(iThreadSleepTime *20);//线程sleep 1秒，让画面的尺寸变化事件处理结束,否则尺寸改变事件发生在消息之后，获取不到变化后的尺寸
            if (IsWpfSizeChanged())//判断wpf尺寸是否变化，只有拖动标题栏时才进行强制刷新
            {
                InvokeWinReSize();//强制刷新画面，消除阴影                              
            }
        }
        /// <summary>
        /// 处理另一进程发过来的消息
        /// </summary>
        /// <param name="cds"></param>
        void LyncMessageProcess(COPYDATASTRUCT cds)
        {
            try
            {
                LogManager.SystemLog.Debug(cds.cbData);
                if (cds.lpData == "LogOutUC")//注销UC
                {
                    StartSignOutUC();
                }
                else if (cds.lpData == "LoginUC")//登录
                {
                    if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == null)
                    {
                        StartLoginUC();
                    }
                }
                else if (cds.lpData != "")
                {
                    if (SingletonObj.LoginInfo == null)
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("NoLogin"), StringHelper.FindLanguageResource("error"));
                        return;
                    }
                    if (winCall == null)
                    {
                        string[] strList = cds.lpData.Split(';');
                        if (strList.Count((x) => { return x.IndexOf("phone-context") > -1 ? true : false; }) > 0)
                        {
                            List<string> strListTemp = new List<string>();
                            for (int i = 0; i < strList.Length; i++)
                            {
                                if (strList[i].IndexOf("phone-context") < 0)
                                {
                                    strListTemp.Add(strList[i]);
                                }
                            }
                            strList = new string[strListTemp.Count];
                            cds.lpData = "";
                            for (int i = 0; i < strListTemp.Count; i++)
                            {
                                cds.lpData += strListTemp[i] + ";";
                                strList[i] = strListTemp[i];
                            }

                            cds.lpData = cds.lpData.Substring(0, cds.lpData.Length - 1);
                        }
                        MakeCallBusiness call = new MakeCallBusiness();
                        StringBuilder str = new StringBuilder();
                        string type = strList[0];
                        if (type == "VideoCall")//视频呼叫
                        {
                            if (strList.Length > 3)
                            {
                                Dialog.Show(StringHelper.FindLanguageResource("NoMultiplePersonVideo"), StringHelper.FindLanguageResource("error"));
                                return;
                            }                          
                          
                            if (toolBar.JointType == PhoneJointType.IPPhone_Device)
                            {
                                Dialog.Show(StringHelper.FindLanguageResource("NoSupportVideo"), StringHelper.FindLanguageResource("error"));
                                return;
                            }
                            call.insertMember((int)MemberType.UC_ACCOUNT, new StringBuilder(strList[2]));
                            winCall = new WinCall(this, cds.lpData);
                            winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                            winCall.Show();
                        }
                        else
                        {
                            //modify byjinyeqing  2015/6/3  多于20人不可以显示出来
                            if (strList.Length > 21)   //第一行是call　　所以应该是２１　 
                            {
                                DialogShow.Show(StringHelper.FindLanguageResource("somanypeople"), StringHelper.FindLanguageResource("error"), 2);
                                return;
                            }
                            if (strList.Length == 3)  //两人会话的操作(逻辑上为了与多人会议区别开来 modify by jinyeqing 2015/6/19)
                            {
                                str = new StringBuilder(strList[2].Substring(strList[2].IndexOf(':') + 1).TrimEnd('>'));
                                string a = ";" + str.ToString().Trim();
                                if (boolnum(str.ToString().Trim()) == false)     //不为纯数字就报警 ，若为纯数字，可能为话机用户，这里就不做和UC匹配的校验                               
                                //if (call.insertMember((int)MemberType.UC_ACCOUNT, str) != 0)  //moidify by jinyeqing 2015/6/8 以前没有if判断
                                {
                                    if (call.insertMember((int)MemberType.UC_ACCOUNT, str) != 0)
                                    //if (call.GetUCAccountByPhoneNo(str.ToString(), ucName) == "" || call.GetUCAccountByPhoneNo(str.ToString(), ucName) == null)  
                                    {
                                        string message = str + StringHelper.FindLanguageResource("NoSuchUCAccount");
                                        DialogShow.Show(message, StringHelper.FindLanguageResource("error"), 2);
                                        cds.lpData = cds.lpData.Replace(a, "");
                                        this.isUcCount = false;
                                        call.startContextCall();
                                        return;
                                    }

                                }
                                else  //纯数字能找到UC账户的，就把数字替换成UCname 
                                {
                                    StringBuilder ucName = new StringBuilder(100);
                                    call.GetUCAccountByPhoneNo(str.ToString(), ucName);
                                    string strTemp = null;

                                    if (ucName.ToString() == "")
                                    {
                                        strTemp = str.ToString();
                                        call.insertMember((int)MemberType.UC_IPPHONE, new StringBuilder(strTemp));
                                    }
                                    else
                                    {
                                        strTemp = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                                        call.insertMember((int)MemberType.UC_ACCOUNT, ucName);
                                        cds.lpData = cds.lpData.Replace(str.ToString().Trim(), strTemp);
                                    }                                  
                                }
                                if (call.startContextCall() == 0)
                                {                                    
                                    winCall = new WinCall(this, cds.lpData.Substring(cds.lpData.IndexOf(';') + 1));
                                    winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                                    winCall.Show();
                                }
                                else
                                {
                                    DialogShow.Show(StringHelper.FindLanguageResource("startContextCallFailed"), StringHelper.FindLanguageResource("error"), 2);
                                    return;

                                }
                            }
                            else   //三人至20人的会议 
                            {
                                for (int index = 2; index < strList.Length; index++)
                                {
                                    str = new StringBuilder(strList[index].Substring(strList[index].IndexOf(':') + 1).TrimEnd('>'));

                                    string a = ";" + str.ToString().Trim();
                                    StringBuilder ucName = new StringBuilder(100);
                                    call.insertMember((int)MemberType.UC_ACCOUNT, str);                                 

                                }
                                call.startContextCall();
                                winCall = new WinCall(this, cds.lpData.Substring(cds.lpData.IndexOf(';') + 1));
                                winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                                winCall.Show();
                            }
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }

        }

        private bool boolnum(string temp)
        {
            for (int i = 0; i < temp.Length; i++)
            {
                byte tempByte = Convert.ToByte(temp[i]);
                if ((tempByte < 48) || (tempByte > 57))
                {
                    return false;
                }
            }
            return true;
        }

        /// <summary>
        /// UC状态改变回调函数
        /// </summary>
        /// <param name="st"></param>
        private void UCContactStateChanged(SignInState st, StringBuilder reason)
        {
            UCStatePara ucStatePara = new UCStatePara();
            ucStatePara.reason = reason;
            ucStatePara.signInState = st;

            threadUCContactStateChanged = new Thread(new ParameterizedThreadStart(UCContactStateChangedMothod));
            threadUCContactStateChanged.Priority = ThreadPriority.AboveNormal;
            threadUCContactStateChanged.Start(ucStatePara);
        }

        /// <summary>
        /// UC状态改变处理函数
        /// </summary>
        /// <param name="ucStatePara"></param>
        void UCContactStateChangedMothod(object ucStatePara)
        {
            if (lockLyncUCLoginOut.TryEnterWriteLock(-1))
            {
                try
                {
                    SignInState st = (ucStatePara as UCStatePara).signInState;
                    StringBuilder _reason = (ucStatePara as UCStatePara).reason;

                    if (st == SignInState.Client_SignedIn)
                    {
                        isSigned = true;
                        LogInBusiness log = new LogInBusiness();
                        int devType = 0;
                        if (isSigned == true)
                        {
                            log.SetPhoneJointEventCallBack(toolBar.phoneJointEventCB);
                            log.GetPhoneJointDevType(ref devType);
                        }

                        UCUserInfo user = new UCUserInfo();
                        user = XmlHelper.GetUserConfig();
                        SingletonObj.LoginInfo = user;

                        if (_Client.Self == null || _Client.Self.Contact == null)
                        {
                            return;
                        }
                        string url = _Client.Self.Contact.Uri;
                        SingletonObj.LoginInfo.LyncName = url.Substring(url.IndexOf(":") + 1);

                        Dispatcher.Invoke(new Action(() =>
                        {
                            toolBar.LabState.Visible = true;
                            toolBar.PictureBoxProgress.Visible = false;
                            LogManager.SystemLog.Debug("UCContactStateChanged.SingletonObj.LoginInfo = " + SingletonObj.LoginInfo);
                            toolBar.SetButtonVisible(true);
                            toolBar.SetBtnImage(devType);
                        }));
                    }
                    else
                    {
                        isSigned = false;
                        SingletonObj.LoginInfo = null;
                        if (_reason == null)
                        {
                            return;
                        }
                        Dispatcher.Invoke(new Action(() =>
                        {
                            toolBar.LabState.Visible = true;
                            toolBar.SetButtonVisible(false);
                            toolBar.PictureBoxProgress.Visible = false;
                            if (winCall != null)//关闭通话界面,需要在uninit之后执行，否则不能再次登录
                            {
                                winCall.Close();
                            }
                            if (winDial != null)
                            {
                                winDial.Close();
                            }
                            if (toolBar.Setting != null)
                            {
                                toolBar.Setting.Close();
                            }
                            if (toolBar.History != null)
                            {
                                toolBar.History.Close();
                            }
                        })
                        );
                    }
                    SetLabStateToolTip(_reason);//设置状态提示信息
                }
                catch (System.Exception ex)
                {
                    LogManager.SystemLog.Error(ex.ToString());
                }
                finally
                {
                    lockLyncUCLoginOut.ExitWriteLock();
                }
            }
        }

        /// <summary>
        /// 开始计时
        /// </summary>
        void ReLoginStartTimer()
        {
            if (timerReLogin == null)
            {
                timerReLogin = new System.Timers.Timer();//实例化Timer类
                timerReLogin.Interval = iThreadSleepTime;//设置间隔时间，为毫秒；
                timerReLogin.Elapsed += new System.Timers.ElapsedEventHandler(timerReLogin_Elapsed);////到达时间的时候执行事件；
                timerReLogin.AutoReset = true;//设置是执行一次（false）还是一直执行(true)；
            }
            timerReLogin.Enabled = true;
        }
        /// <summary>
        /// 重新登录时间计时器
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void timerReLogin_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                if (canReLogin == false)//是否可以重新登录
                {
                    DateTime dt = DateTime.Now;
                    TimeSpan sp = dt.Subtract(dtStart);
                    if (sp.Seconds > iReloginTimeOff)//超过最大时间，允许重新登录 
                    {
                        canReLogin = true;//允许登录
                        timerReLogin.Enabled = false;//停止计时器
                    }
                }
                else
                {
                    timerReLogin.Enabled = false;//停止计时器
                }
            }));
        }
        /// <summary>
        /// 设置工具盘状态信息
        /// </summary>
        /// <param name="st"></param>
        void SetLabStateToolTip(StringBuilder _reason)
        {
            string str = "";

            switch (_reason.ToString())
            {
                case "sipkickout":
                    str = StringHelper.FindLanguageResource("SomewhereElse");//用户被踢
                    break;

                case "error pwd":
                case "empty pwd":
                case "account not existed":
                case "account error":
                    str = StringHelper.FindLanguageResource("AccountOrPwdError");//密码或账户为空
                    break;

                case "locked":
                    str = StringHelper.FindLanguageResource("AccountLocked");//账号已锁定
                    break;

                case "need change pwd":
                    str = StringHelper.FindLanguageResource("NeedChangePwd");//需要更换密码
                    break;

                case "timeout":
                    str = StringHelper.FindLanguageResource("Timeout");//超时
                    break;

                case "need new version":
                    str = StringHelper.FindLanguageResource("NeedNewVersion");//需要下载新版本才允许登录
                    break;

                case "need active":
                    str = StringHelper.FindLanguageResource("NeedActive");//用户未激活
                    break;

                case "log out ok":
                    str = StringHelper.FindLanguageResource("LogOutUC");//用户注销
                    break;

                case "":
                    str = StringHelper.FindLanguageResource("SignedInUC");//用户登录成功
                    break;

                default:
                    str = StringHelper.FindLanguageResource("NormalError");//登陆一般失败 
                    break;
            }

            Dispatcher.BeginInvoke(new Action(() =>
            {
                // Set up the ToolTip text for the Button
                toolTipLabState.SetToolTip(toolBar.LabState, str);
                LogManager.SystemLog.Debug("SetLabStateToolTip.SingletonObj.LoginInfo = " + SingletonObj.LoginInfo);               
                toolBar.LabState.Text = SingletonObj.LoginInfo == null ? StringHelper.FindLanguageResource("SignedUCFailed") : SingletonObj.LoginInfo.UserID;
            }));
        }
        /// <summary>
        /// 状态更改（例如，失去或获得输入焦点）时发生
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void WinLync_StateChanged(object sender, EventArgs e)
        {

            if (this.WindowState == WindowState.Minimized)//最小化时，去掉父窗体，隐藏lync
            {
                this.Visibility = Visibility.Hidden;
                ShowWindow(iLyncAppWinHandle, SW_HIDE);
                SetParent(iLyncAppWinHandle, IntPtr.Zero);              
                MoveWindowHidden();
            }
            else if (this.WindowState == WindowState.Maximized)//最大化时，需要重新设置lync大小
            {
                MaximizedMoveToolBar();
                MaximizedMoveWindow();
            }
        }
        /// <summary>
        /// 刷新工具栏，前置显示
        /// </summary>
        void WinLync_RefreshToolBar()
        {
            while (!shouldStop)
            {
                //2015/6/1 modify by jinyeqing 
                Thread.Sleep(iThreadSleepTime * 10);
                //2015/6/1 modify by jinyeqing 
                if (null != toolBar && !(WinLync.lyncCounter > 0))
                {
                    if (lockLyncUCLoginOut.TryEnterWriteLock(-1))
                    {
                        try
                        {
                            Dispatcher.Invoke(new Action(() =>
                            {
                                if (null != toolBar)
                                {                                    
                                    toolBar.Update();
                                    toolBar.Refresh();
                                    SetWindowPos(iToolBarHandle, iLyncAppWinHandle, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);                                    
                                    toolBar.LabState.Focus();

                                }
                            }));
                        }
                        finally
                        {
                            lockLyncUCLoginOut.ExitWriteLock();
                        }
                    }
                }
            }
        }
        /// <summary>
        /// 当后台操作已完成、被取消或引发异常时发生
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>ly
        void backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            try
            {
                LogManager.SystemLog.Debug("Start backgroundWorker_RunWorkerCompleted");
                RECT re = new RECT();
                GetLyncClientRect(out re);
                iMainWpfHandle = new WindowInteropHelper(this).Handle;
                MoveWindow(iMainWpfHandle, (int)(re.left), (int)(re.top), (int)(WPFWidth), (int)(WPFHeight), true);
                LogManager.SystemLog.Debug("End backgroundWorker_RunWorkerCompleted");
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 获取lync客户端尺寸
        /// </summary>
        /// <param name="re"></param>
        void GetLyncClientRect(out RECT re)
        {
            try
            {
                int iRet = 0;
                re = new RECT();
                while (_Client == null)
                {
                    Thread.Sleep(iThreadSleepTime);
                }
                while (iRet == 0)
                {
                    Thread.Sleep(iThreadSleepTime);
                    iRet = GetWindowRect(process.MainWindowHandle, out re);
                    if (iRet == 0)
                    {
                        process.Refresh();
                        iRet = GetWindowRect(process.MainWindowHandle, out re);
                        iLyncAppWinHandle = process.MainWindowHandle;
                    }
                    else
                    {
                        iLyncAppWinHandle = process.MainWindowHandle;
                        break;
                    }
                }
                LogManager.SystemLog.Debug(string.Format("GetLyncClientRect RECT left = {0}", re.left));
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                re = new RECT();
            }
        }

        /// <summary>
        /// 获取lync客户端
        /// </summary>
        void GetLyncClient()
        {
            while (_Client == null)
            {
                Thread.Sleep(iThreadSleepTime);
                try
                {
                    _Client = LyncClient.GetClient();
                    LyncContactManager = LyncClient.GetClient().ContactManager;
                    LyncContactGroups = LyncClient.GetClient().ContactManager.Groups;                  
                    _Client.StateChanged += new EventHandler<ClientStateChangedEventArgs>(LyncClientStateChanged);
                    if (_Client.State == ClientState.SignedIn)//增加状态改变处理函数之前已经登录成功
                    {
                        Thread.Sleep(iThreadSleepTime * 100);//等待1000毫秒，让lync状态改变时间触发
                    }
                }
                catch
                {
                    LogManager.SystemLog.Warn("LyncClient process is not running");
                }
            }
        }

        /// <summary>
        /// lync 联系人信息变化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void Contact_ContactInformationChanged(object sender, ContactInformationChangedEventArgs e)
        {           
            try
            {
                Contact contact = (sender as Contact);
                if (_Client.Self.Contact == null)
                {
                    return;
                }

                ContactAvailability availability = (ContactAvailability)contact.GetContactInformation(ContactInformationType.Availability);//Get the current availability value from Lync
                UCContactAvailability ucAvailability = GetUCState(availability);
                LogInBusiness log = new LogInBusiness();              
                log.PubSelfStatus((int)ucAvailability, new StringBuilder());
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 根据lync状态获取UC状态
        /// </summary>
        /// <param name="availability"></param>
        /// <returns></returns>
        UCContactAvailability GetUCState(ContactAvailability availability)
        {
            UCContactAvailability ucAvailability;
            switch (availability)
            {
                case ContactAvailability.Free:
                case ContactAvailability.FreeIdle:
                    ucAvailability = UCContactAvailability.Online;
                    break;
                case ContactAvailability.Busy:
                case ContactAvailability.BusyIdle:
                    ucAvailability = UCContactAvailability.Busy;
                    break;
                case ContactAvailability.DoNotDisturb:
                    ucAvailability = UCContactAvailability.NoDisturb;
                    break;
                case ContactAvailability.TemporarilyAway:
                case ContactAvailability.Away:
                    ucAvailability = UCContactAvailability.Leave;
                    break;
                default:
                    ucAvailability = UCContactAvailability.Offline;
                    break;

            }
            return ucAvailability;
        }
        /// <summary>
        /// 获取lync状态回调函数 
        /// </summary>
        /// <param name="ar"></param>
        void AsyncCallbackProcess(IAsyncResult ar)
        {
            if (ar.IsCompleted)
            {
                SearchResults searchResults = LyncContactManager.EndSearch(ar);
                if (searchResults != null && searchResults.Contacts.Count > 0)
                {
                    foreach (Contact contact in searchResults.Contacts)
                    {
                        ContactAvailability availability = (ContactAvailability)contact.GetContactInformation(ContactInformationType.Availability);//Get the current availability value from Lync
                    }
                }
            }
        }
        /// <summary>
        /// 更具名称获取lync状态
        /// </summary>
        /// <param name="str"></param>
        void LyncBeginSearch(string str)
        {
            LyncContactManager.BeginSearch(str, SearchProviders.OtherContacts, SearchFields.AllFields, SearchOptions.Default, 10, AsyncCallbackProcess, null);
        }
        /// <summary>
        /// 使用账号和密码登陆UC
        /// </summary>
        public void StartLoginUC()
        {
            try
            {        
                if (canReLogin == false)
                {
                    Dialog.Show(StringHelper.FindLanguageResource("logouting"), StringHelper.FindLanguageResource("error"));
                    return;
                }
                LogManager.SystemLog.Debug("Start StartLoginUC");
                UCUserInfo user = new UCUserInfo();
                user = XmlHelper.GetUserConfig();
                if (user != null && user.UserID != null && user.UserID != string.Empty && user.Password != null &&
                    user.Server != string.Empty && user.Port != string.Empty && user.Password != string.Empty)
                {
                    Dispatcher.BeginInvoke(new Action(()
                    =>
                    {
                        toolBar.LabState.Text = "";
                        toolBar.LabState.Visible = false;
                        toolBar.PictureBoxProgress.Visible = true;//开始登录UC，显示进度条
                    }));

                    LogInBusiness log = new LogInBusiness();
                    Dispatcher.Invoke(new Action(()  //modify by 00327190  6/12   之前是没有这个Dispatcher  放在主线程 
                   =>
                   {
                       UCServiceRetvCode iRet = (UCServiceRetvCode)log.Login(user.UserID, user.Password, user.Server + ":" + user.Port, user.Lang == "0" ? "2052" : "1033");
                       process.WaitForExit(5);  //modify by jinyeqing 2015/6/15 原先是没有5毫秒的等待超时的，现在定义5ms等待超时，这样就可以强制执行下面的程序
                       LogManager.SystemLog.DebugFormat("StartLoginUC iRet = {0}", iRet);
                       if (iRet != UCServiceRetvCode.UC_SDK_Success)
                       {
                           LogManager.SystemLog.Debug("Start StartLoginUC.Failed.Invoke");
                           Dispatcher.Invoke(new Action(()
                             =>
                           {
                               try
                               {
                                   toolBar.LabState.Text = SingletonObj.LoginInfo == null ? StringHelper.FindLanguageResource("SignedUCFailed") : SingletonObj.LoginInfo.UserID;
                                   toolBar.SetButtonVisible(SingletonObj.LoginInfo == null ? false : true);

                                   if (SingletonObj.LoginInfo != null)
                                   {
                                       toolTipLabState.SetToolTip(toolBar.LabState, StringHelper.FindLanguageResource("SignedInUC"));
                                       string url = _Client.Self.Contact.Uri;
                                       SingletonObj.LoginInfo.LyncName = url.Substring(url.IndexOf(":") + 1);
                                   }
                               }
                               finally
                               {
                                   toolBar.LabState.Visible = true;
                                   toolBar.PictureBoxProgress.Visible = false;
                               }

                           }));
                           LogManager.SystemLog.Debug("End StartLoginUC.Failed.Invoke");
                       }
                   }));
                }
                else
                {
                    toolBar.LabState.Text = StringHelper.FindLanguageResource("SignedUCFailed");
                    Dialog.Show(StringHelper.FindLanguageResource("NoUCAccount"), StringHelper.FindLanguageResource("SettingUC"));
                }
                LogManager.SystemLog.Debug("End StartLoginUC");
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 注销UC
        /// </summary>
        public void StartSignOutUC()//注销UC
        {
            LogManager.SystemLog.Debug("Start StartSignOutUC");
            LogInBusiness log = new LogInBusiness();
            log.SignOut();

            SingletonObj.LoginInfo = null;
            LogManager.SystemLog.Debug("Start StartSignOutUC.Invoke");
            Dispatcher.Invoke(new Action(()
                =>
            {
                toolBar.LabState.Text = StringHelper.FindLanguageResource("LogOutUC");
                toolBar.SetButtonVisible(false);
            }));
            LogManager.SystemLog.Debug("End StartSignOutUC.Invoke");
        }
        /// <summary>
        /// 是否UC资源
        /// </summary>
        private void StartUnInit()//释放资源
        {
            LogInBusiness log = new LogInBusiness();
            log.UnInit();
        }

        #region 已删除函数，备用
        /// <summary>
        /// 发现选择的用户信息
        /// </summary> 
        /// <param name="hwnd"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        static bool FindSelectItemProcess(int hwnd, int lParam)
        {
            try
            {
                IntPtr ptrUIHWND = FindWindowEx((IntPtr)hwnd, System.IntPtr.Zero, "NetUINativeHWNDHost", null);

                if (ptrUIHWND == IntPtr.Zero)
                {
                    return true;
                }

                SelectedUserList.Clear();
                List<string> lstUser = new List<string>();
                System.Windows.Forms.IDataObject data = System.Windows.Forms.Clipboard.GetDataObject();//从剪贴板中获取数据
                string str = (string)data.GetData(System.Windows.DataFormats.Text);
                if (null == str)
                {
                    return false;
                }
                string[] strList = str.Split(';');

                Guid guidCOM = new Guid(0x618736E0, 0x3C3D, 0x11CF, 0x81, 0xC, 0x0, 0xAA, 0x0, 0x38, 0x9B, 0x71);
                IAccessible IACurrent = null;
                AccessibleObjectFromWindow((IntPtr)ptrUIHWND, (int)OBJID_CLIENT, ref guidCOM, ref IACurrent);

                int childCount = IACurrent.accChildCount;
                object[] windowChildren = new object[childCount];
                int pcObtained;
                AccessibleChildren(IACurrent, 0, childCount, windowChildren, out pcObtained);

                string accName;
                foreach (IAccessible child in windowChildren)
                {
                    if (null == child)
                    {
                        continue;
                    }
                    accName = child.get_accName(CHILDID_SELF);

                    object[] clientChilrenWnd = GetAccessibleChildren(child);
                    if (clientChilrenWnd.Length == 0)
                    {
                        continue;
                    }
                    for (int i = 0; i < clientChilrenWnd.Length; i++)
                    {
                        IAccessible client = clientChilrenWnd[i] as IAccessible;
                        if (client == null)
                        {
                            continue;
                        }

                        object[] clientChilrenPan = GetAccessibleChildren(client);
                        if (clientChilrenPan.Length == 0 || clientChilrenPan[0].ToString() == "1")
                        {
                            continue;
                        }
                        IAccessible iAcc = clientChilrenPan[0] as IAccessible;
                        foreach (IAccessible childChild in clientChilrenPan)
                        {
                            if (childChild.accChildCount == 0)
                            {
                                continue;
                            }
                            accName = childChild.get_accName(CHILDID_SELF);
                            LogManager.SystemLog.Info(accName);
                            object[] clientChilrenContactItem = GetAccessibleChildren(childChild);
                            string sss = (clientChilrenContactItem[0] as IAccessible).get_accName(CHILDID_SELF);
                            if (clientChilrenContactItem.Length == 4 && accName == "")
                            {
                                iAcc = childChild;
                                break;
                            }
                        }
                    }
                }
                return true;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return false;
            }
        }
     
        /// <summary>
        /// 检索子 ID 或 IDispatch接口 的 范围 内的子对象 的 容器对象 的 访问
        /// </summary>
        /// <param name="paccContainer"></param>
        /// <returns></returns>
        static object[] GetAccessibleChildren(IAccessible paccContainer)
        {
            object[] rgvarChildren = new object[paccContainer.accChildCount];
            int pcObtained;
            AccessibleChildren(paccContainer, 0, paccContainer.accChildCount, rgvarChildren, out pcObtained);
            return rgvarChildren;
        }
        #endregion

        /// <summary>
        /// 点击工具栏呼叫按钮
        /// </summary>
        void ToolCallClicked()
        {
            EnumChildWindows((int)iMainWpfHandle, callBackFindSelectItem, 0);
        }

        /// <summary>
        /// Callback invoked when Self.BeginPublishContactInformation is completed
        /// </summary>
        /// <param name="result">The status of the asynchronous operation</param>
        private void PublishContactInformationCallback(IAsyncResult result)
        {
            _Client.Self.EndPublishContactInformation(result);
        }

        /// <summary>
        /// 获取lync状态
        /// </summary>
        public void GetLyncUserState()
        {
            if (_Client.Self.Contact == null)
            {
                userState = ContactAvailability.Free;
            }
            else
            {
                userState = (ContactAvailability)_Client.Self.Contact.GetContactInformation(ContactInformationType.Availability);//Get the current availability value from Lync
            }
        }

        /// <summary>
        /// Set the contact's current availability value from Lync
        /// </summary>
        public void SetAvailability(ContactAvailability state)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("SetAvailability state = {0}", state));
                //Add the availability to the contact information items to be published
                Dictionary<PublishableContactInformationType, object> newInformation =
                    new Dictionary<PublishableContactInformationType, object>();
                newInformation.Add(PublishableContactInformationType.Availability, state);
                _Client.Self.BeginPublishContactInformation(newInformation, PublishContactInformationCallback, null);

                UCContactAvailability ucAvailability = GetUCState(state);
                LogInBusiness log = new LogInBusiness();              
                log.PubSelfStatus((int)ucAvailability, new StringBuilder());
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }

        /// <summary>
        /// 获取lync、wpf状态，实现最小化、最小化到托盘、恢复置前的互操作工作
        /// </summary>
        void GetLyncState()
        {
            bool isVisible = false;
            RECT re = new RECT();
            while (!shouldStop)
            {
                if (lockObjLyncState.TryEnterWriteLock(0))
                {
                    try
                    {
                        Thread.Sleep(iThreadSleepTime);
                        GetClientRect(iLyncAppWinHandle, out re);

                        isVisible = (lyncChildHwndList.FindAll((x) =>//判断lync客户端是否可见，以lync中包含的控件为准
                        {
                            return IsWindowVisible((int)x) == true;
                        })                       
                       as List<IntPtr>).Count > 0 ? true : false;

                        if (_Client.State == ClientState.SigningOut ||
                            IsWinMinimized() && !isVisible || _Client.State == ClientState.SigningIn)//lync注销或正在登陆时，不刷新画面
                        {
                            continue;
                        }
                        if (!isVisible && Visibility == Visibility.Visible)//关闭wpf时
                        {
                            SetParent(iLyncAppWinHandle, IntPtr.Zero);
                            Dispatcher.Invoke(new Action(() => { Visibility = Visibility.Hidden; }));                           
                            MoveWindowHidden();
                            LogManager.SystemLog.Debug("GetLyncState Wpf Invoke Lync Hidden ");
                        }
                        else if (IsWinMinimized() && !IsWindowVisible((int)iLyncAppWinHandle))//最小化wpf
                        {
                            Dispatcher.Invoke(new Action(() => { this.Close(); }));
                            LogManager.SystemLog.Debug("GetLyncState Lync Invoke Hidden ");                           
                        }
                        else if (re.left == 0 && re.right == 0 && re.bottom == 0 && re.top == 0 && Visibility == Visibility.Visible)//最小化lync
                        {
                            ShowWindow(iLyncAppWinHandle, SW_SHOWNORMAL);
                            Dispatcher.Invoke(new Action(() => { this.Close(); }));
                            Dispatcher.Invoke(new Action(() => { Visibility = Visibility.Hidden; }));                          
                            MoveWindowHidden();
                        }
                        else if (isVisible && Visibility == Visibility.Hidden)//显示lync
                        {
                            ShowWindow(iLyncAppWinHandle, SW_HIDE);
                            ShowWindow(iMainWpfHandle, SW_SHOWNORMAL);
                            Dispatcher.Invoke(new Action(() => { Visibility = Visibility.Visible; re = GetWpfRECT(); }));

                            SetParent(iLyncAppWinHandle, iMainWpfHandle);
                            MoveWindowVisible();
                            ShowWindow(iLyncAppWinHandle, SW_SHOWNORMAL);                            
                            InvokeWinReSize();
                            LogManager.SystemLog.Debug(string.Format("GetLyncState Lync Invoke wpf Visible.GetWpfRECT.left = {0},top = {1} ", re.left, re.top));
                        }                          
                        else
                        {
                            while (!sizeChangeFinished)
                            {
                                Thread.Sleep(iThreadSleepTime);
                            }
                            GetClientRect(iLyncAppWinHandle, out re);
                            double iHeight = ((WPFHeight - iWpfHeightTopOff + iWpfHeightButtomOff) * scaleUIY) - (iWpfHeightTopOff * scaleUIY) - re.bottom;
                            double iWidth =  re.right - (WPFWidth - iWpfRightWidthOff) * scaleUIX + (iWpfLeftWidthOff * scaleUIX) / 2 ;
                            if ((re.left != 0 || re.top != 0 ||Math.Abs(iWidth)>2 ||
                               (Math.Abs(iHeight) > 4)) && Visibility == Visibility.Visible)//lync被拖动时，wpf适配lync窗体
                            {
                                Dispatcher.Invoke(new  Action( ()=>{WinLync_SizeChanged(null, null);}));
                                LogManager.SystemLog.Debug("GetLyncState.MoveWindowVisible");
                            }
                            else
                            {
                                IntPtr iPtrParent = GetAncestor(iLyncAppWinHandle, 1);
                                if (iPtrParent != iMainWpfHandle && isVisible && Visibility == Visibility.Visible)//lync、wpf脱离
                                {
                                    SetParent(iLyncAppWinHandle, iMainWpfHandle);
                                    MoveWindowVisible();
                                    LogManager.SystemLog.Debug("GetLyncState.MoveWindowVisible");
                                }
                            }
                        }                       
                    }
                    finally
                    {
                        lockObjLyncState.ExitWriteLock();
                    }
                }
            }
        }

        /// <summary>
        /// 设置lync 可见，移动lync位置
        /// </summary>
        void MoveWindowVisible()
        {
            MoveWindow(iLyncAppWinHandle, -(int)(iWpfLeftWidthOff * scaleUIX), -(int)(iWpfHeightTopOff * scaleUIY), (int)((WPFWidth + iWpfRightWidthOff) * scaleUIX),
                      (int)((WPFHeight - iWpfHeightTopOff + iWpfHeightButtomOff) * scaleUIY), true);

        }
        /// <summary>
        /// 隐藏lync 移动lync位置
        /// </summary>
        void MoveWindowHidden()
        {
            RECT re = new RECT();
            LogManager.SystemLog.Debug("Start MoveWindowHidden.Invoke");
            Dispatcher.Invoke(new Action(() => { re = GetWpfRECT(); }));
            LogManager.SystemLog.Debug("End MoveWindowHidden.Invoke");
            MoveWindow(iLyncAppWinHandle, (int)(re.left * scaleUIX), (int)(re.top * scaleUIY), (int)((re.right - re.left) * scaleUIX),
                       (int)((re.bottom - re.top) * scaleUIY), true);
        }
        /// <summary>
        /// 最大化时移动工具盘
        /// </summary>
        void MaximizedMoveToolBar()
        {
            MoveWindow(iToolBarHandle, 0, SystemInformation.VerticalScrollBarWidth + SystemInformation.WorkingArea.Height - (int)(iToolBarHeightOff * scaleUIX),
                        SystemInformation.HorizontalScrollBarHeight + SystemInformation.WorkingArea.Width, iToolBarWidthOff, true);
        }
        /// <summary>
        /// 最大化时移动lync
        /// </summary>
        void MaximizedMoveWindow()
        {
            MoveWindow(iLyncAppWinHandle, -(int)(iWpfLeftWidthOff * scaleUIX), -(int)(iWpfHeightTopOff * scaleUIY), SystemInformation.HorizontalScrollBarHeight +
                SystemInformation.WorkingArea.Width, SystemInformation.VerticalScrollBarWidth + SystemInformation.WorkingArea.Height - iWpfHeightTopOff, true);
        }
        /// <summary>
        /// 强制刷新画面，调整lync尺寸、去掉边框阴影
        /// </summary>
        void InvokeWinReSize()
        {
            LogManager.SystemLog.Debug("Start InvokeWinReSize.Invoke");
            Dispatcher.Invoke(new Action(() =>
            {
                WinLync_SizeChanged(null, null);
            }));
            LogManager.SystemLog.Debug("End InvokeWinReSize.Invoke");

        }
        /// <summary>
        /// 获取客户端矩形
        /// </summary>
        /// <returns></returns>
        RECT GetWpfRECT()
        {
            RECT re = new RECT();
            re.left = (int)(this.Left);
            re.top = (int)(this.Top);
            re.bottom = (int)(this.Top + this.Height);
            re.right = (int)(this.Left + this.Width);

            return re;
        }
        /// <summary>
        /// 判断客户端是否最小化
        /// </summary>
        /// <returns></returns>
        bool IsWinMinimized()
        {
            bool Minimized = false;
            if (lockLyncUCLoginOut.TryEnterWriteLock(-1))
            {
                try
                {
                    Dispatcher.Invoke(new Action(()
                        =>
                        {
                            Minimized = this.WindowState == WindowState.Minimized ? true : false;
                        }));
                }
                finally
                {
                    lockLyncUCLoginOut.ExitWriteLock();
                }
            }
            return Minimized;

        }
        /// <summary>
        /// 线程退出时处理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void process_Exited(object sender, EventArgs e)
        {
            ExitApp();
        }

        void LyncClientStateChangedMethod(object ob)
        {            
            if (lockLyncUCLoginOut.TryEnterWriteLock(-1))
            {
                try
                {
                    ClientStateChangedEventArgs e = ob as ClientStateChangedEventArgs;
                    if (e.NewState == ClientState.SignedOut || e.NewState == ClientState.SigningOut)//lync登出
                    {
                        iWpfHeightButtomOff = iWpfHeightTopOff;
                        if (null != toolBar)
                        {
                            if (e.NewState == ClientState.SigningOut)
                            {
                                Visibility isVisible = Visibility.Visible;
                                Dispatcher.Invoke(new Action(() =>
                                {
                                    toolBar.Visible = false;
                                    isVisible = this.Visibility;
                                    //隐藏时不重新设置lync尺寸
                                    if (isVisible == Visibility.Visible && this.WindowState != WindowState.Maximized)
                                    {
                                        MoveWindowVisible();//恢复lync高度
                                    }
                                }), System.Windows.Threading.DispatcherPriority.Send);//隐藏工具盘 
                            }
                        }
                        LogInBusiness log = new LogInBusiness();
                        log.SignOut();//lync 注销时 注销UC
                    }
                    if (e.NewState == ClientState.SignedIn)//登录成功 开始订阅自身状态 
                    {
                        iWpfHeightButtomOff = 0;
                        WinOptionSettingViewModel set = new WinOptionSettingViewModel();

                        set.SaveLyncAccountToConfig(StringHelper.GetLyncNameString(_Client.Self.Contact.Uri));

                        _Client.Self.Contact.ContactInformationChanged += new EventHandler<ContactInformationChangedEventArgs>(Contact_ContactInformationChanged);

                        ContactSubscription foundContactSubscription = LyncClient.GetClient().ContactManager.CreateSubscription();
                        foundContactSubscription.AddContact(_Client.Self.Contact);
                        List<ContactInformationType> subscribeTypeList = new List<ContactInformationType>();
                        subscribeTypeList.Add(ContactInformationType.Availability);
                        foundContactSubscription.Subscribe(ContactSubscriptionRefreshRate.High, subscribeTypeList);

                        LyncSignedInFun();
                    }
                    LogManager.SystemLog.Debug(string.Format("SingletonObj.LoginInfo = {0}", SingletonObj.LoginInfo));
                    LogManager.SystemLog.Debug(string.Format("Leave LyncClientStateChanged.NewState = {0}", e.NewState));
                }
                finally
                {
                    lockLyncUCLoginOut.ExitWriteLock();
                }
            }
          
        }
        /// <summary>
        /// lync状态改变
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void LyncClientStateChanged(object sender, ClientStateChangedEventArgs e)
        {           
            threadLyncClientStateChanged = new Thread(new ParameterizedThreadStart(LyncClientStateChangedMethod));            
            threadLyncClientStateChanged.Priority = ThreadPriority.AboveNormal;
           // threadLyncClientStateChanged.IsBackground = true;
            threadLyncClientStateChanged.Start(e);
           
        }
        /// <summary>
        /// lync登录成功回调函数
        /// </summary>
        void LyncSignedInFun()
        {
            LogManager.SystemLog.Debug("LyncSignedInFun");
            if (this.Visibility == Visibility.Hidden)
            {
                // Put it into this form  
                SetParent(iLyncAppWinHandle, iMainWpfHandle);
                Dispatcher.Invoke(new Action(() => { this.Visibility = Visibility.Visible; }));

                EnumChildWindows((int)iLyncAppWinHandle, callBackEnumChildWindows, 0);

                if (threadGetLyncState == null)
                {
                    threadGetLyncState = new Thread(new ThreadStart(GetLyncState));
                    threadGetLyncState.Priority = ThreadPriority.BelowNormal;
                   // threadGetLyncState.IsBackground = true;
                    threadGetLyncState.Start();
                   
                }

                this.SizeChanged -= new SizeChangedEventHandler(WinLync_SizeChanged);
                this.SizeChanged += new SizeChangedEventHandler(WinLync_SizeChanged);
            }

            bool isMax = false;
            Dispatcher.Invoke(new Action(() =>
                {
                    isMax = this.WindowState == WindowState.Maximized ? true : false;
                }));

            if (!isMax)
            {
                MoveWindowVisible();//恢复lync高度
            }           
            if (null != toolBar)
            {
                StartLoginUC();
            }
            SetToolBar();
        }

        /// <summary>
        /// 刷新工具栏
        /// </summary>
        void SetToolBar()
        {
            if (null == toolBar)
            {
                LogManager.SystemLog.DebugFormat("null == toolBar");
                Dispatcher.Invoke(new Action(() =>
                {
                    toolBar = new FrmToolBar(this);

                    if (scaleUIX == 1)
                    {
                        WinDPIAdapter();
                    }
                    else
                    {
                        toolBar.LabState.Location = new System.Drawing.Point((int)(355 * scaleUIX), 25);
                        toolBar.LabState.Size = new System.Drawing.Size(157, 18);
                    }

                    toolBar.Show();

                    SetToolBarTip();
                    iToolBarHandle = toolBar.Handle;
                    SetParent(iToolBarHandle, iMainWpfHandle);
                    MoveWindow(iToolBarHandle, 0, (int)((WPFHeight - iToolBarHeightOff) * scaleUIY), (int)(WPFWidth * scaleUIX), (int)(iToolBarWidthOff * scaleUIX), true);
                    toolBar.Visible = true;
                    toolBar.toolCallClick = new Action(ToolCallClicked);
                    toolBar.toolCallOver = new Action(ToolCallOver);

                    InvokeWinReSize();//强制刷新画面，DPI非97时需要
                    if (SingletonObj.LoginInfo == null || SingletonObj.LoginInfo.UserID == string.Empty)
                    {
                        StartLoginUC();
                    }
                    else
                    {
                        toolBar.BtnSetting.Visible = true;
                    }
                }));
            }
            else
            {
                LogManager.SystemLog.DebugFormat("toolBar.Visible = true");
                Dispatcher.Invoke(new Action(() => { toolBar.Visible = true; }));
            }

        }
        /// <summary>
        /// 设置tooltip
        /// </summary>
        void SetToolBarTip()
        {

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnHisitory = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnHisitory.AutoPopDelay = iDelay * 10;
            toolTipBtnHisitory.InitialDelay = iDelay;
            toolTipBtnHisitory.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnHisitory.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnHisitory.SetToolTip(toolBar.BtnHisitory, StringHelper.FindLanguageResource("Hisitory"));

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnSetting = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnSetting.AutoPopDelay = iDelay * 10;
            toolTipBtnSetting.InitialDelay = iDelay;
            toolTipBtnSetting.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnSetting.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnSetting.SetToolTip(toolBar.BtnSetting, StringHelper.FindLanguageResource("Setting"));

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnDail = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnDail.AutoPopDelay = iDelay * 10;
            toolTipBtnDail.InitialDelay = iDelay;
            toolTipBtnDail.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnDail.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnDail.SetToolTip(toolBar.BtnDail, StringHelper.FindLanguageResource("Keypad"));

            // Create the ToolTip and associate with the Form container.
            toolTipLabState = new System.Windows.Forms.ToolTip();
            // Set up the delays for the ToolTip.
            toolTipLabState.AutoPopDelay = iDelay * 10;
            toolTipLabState.InitialDelay = iDelay;
            toolTipLabState.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipLabState.ShowAlways = true;

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnPC = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnPC.AutoPopDelay = iDelay * 10;
            toolTipBtnPC.InitialDelay = iDelay;
            toolTipBtnPC.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnPC.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnPC.SetToolTip(toolBar.BtnPC, StringHelper.FindLanguageResource("eSpaceTerminal"));

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnIP = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnIP.AutoPopDelay = iDelay * 10;
            toolTipBtnIP.InitialDelay = iDelay;
            toolTipBtnIP.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnIP.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnIP.SetToolTip(toolBar.BtnIP, StringHelper.FindLanguageResource("IPPhone"));


            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnFWD = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnFWD.AutoPopDelay = iDelay * 10;
            toolTipBtnFWD.InitialDelay = iDelay;
            toolTipBtnFWD.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnFWD.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnFWD.SetToolTip(toolBar.BtnFWD, StringHelper.FindLanguageResource("FWD"));

            // Create the ToolTip and associate with the Form container.
            System.Windows.Forms.ToolTip toolTipBtnMail = new System.Windows.Forms.ToolTip();

            // Set up the delays for the ToolTip.
            toolTipBtnMail.AutoPopDelay = iDelay * 10;
            toolTipBtnMail.InitialDelay = iDelay;
            toolTipBtnMail.ReshowDelay = iDelay;
            // Force the ToolTip text to be displayed whether or not the form is active.
            toolTipBtnMail.ShowAlways = true;

            // Set up the ToolTip text for the Button
            toolTipBtnMail.SetToolTip(toolBar.BtnMail, StringHelper.FindLanguageResource("VoiceMail"));
        }
        /// <summary>
        /// 适配系统dpi
        /// </summary>
        void WinDPIAdapter()
        {
            CultureInfo currentCultureInfo = CultureInfo.CurrentCulture;
            if (currentCultureInfo.Name == "en-US")//英文系统画面适配
            {
                toolBar.PictureBoxProgress.Location = new System.Drawing.Point(70, -105);
            }
            else
            {
                toolBar.PictureBoxProgress.Location = new System.Drawing.Point(70, -111);
            }
            toolBar.PictureBoxProgress.Size = new System.Drawing.Size(250, 202);
            toolBar.LabState.Anchor = System.Windows.Forms.AnchorStyles.Right;
            toolBar.LabState.Location = new System.Drawing.Point((int)(333), 18);
            toolBar.LabState.Size = new System.Drawing.Size(118, 15);
            toolBar.LabState.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            toolBar.BtnHisitory.Location = new System.Drawing.Point(47, 3);
            toolBar.BtnHisitory.Size = new System.Drawing.Size(29, 24);
            toolBar.BtnSetting.Location = new System.Drawing.Point(12, 3);
            toolBar.BtnSetting.Size = new System.Drawing.Size(29, 24);
            toolBar.BtnDail.Location = new System.Drawing.Point(82, 3);
            toolBar.BtnDail.Size = new System.Drawing.Size(29, 24);
            toolBar.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            toolBar.ClientSize = new System.Drawing.Size(470, 50);
            toolBar.BtnIP.Location = new System.Drawing.Point(118, 3);
            toolBar.BtnIP.Size = new System.Drawing.Size(29, 24);
            toolBar.BtnPC.Location = new System.Drawing.Point(147, 3);
            toolBar.BtnPC.Size = new System.Drawing.Size(29, 24);
            toolBar.BtnFWD.Location = new System.Drawing.Point(181, 3);
            toolBar.BtnFWD.Size = new System.Drawing.Size(29, 24);
            toolBar.BtnMail.Location = new System.Drawing.Point(217, 3);
            toolBar.BtnMail.Size = new System.Drawing.Size(29, 24);
        }

        /// <summary>
        /// 工具栏鼠标移动处理函数
        /// </summary>
        void ToolCallOver()
        {
            try
            {
                keybd_event((byte)VK_CONTROL, 0, 0, 0);//模拟复制数据功能
                keybd_event((byte)VK_C, 0, 0, 0);
                keybd_event((byte)VK_C, 0, KEYEVENTF_KEYUP, 0);
                keybd_event((byte)VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 拉起lync进程
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                DeleteRegistry();//删除注册表，防止插件崩溃时 退出不能删除注册表信息
                ExecuteReg();//执行注册表导入
                Process[] processes;
                //Get the list of current active processes.
                processes = System.Diagnostics.Process.GetProcesses();
                foreach (Process p in processes)
                {
                    if (p.ProcessName == "communicator" || p.ProcessName == "lync")
                    {
                        process = p;
                        break;
                    }
                }
                if (process == null)
                {
                    if (this.exeName == string.Empty)//系统未安装Lync，退出
                    {
                        Dialog.Show(StringHelper.FindLanguageResource("NoLyncFound"), StringHelper.FindLanguageResource("error"));
                        Environment.Exit(0);
                    }
                    // Start the process 
                    process = System.Diagnostics.Process.Start(this.exeName);                    
                    StartGetLyncClientThread();
                }
                process.EnableRaisingEvents = true;
                process.Exited += new EventHandler(process_Exited);               
                // Wait for process to be created and enter idle condition 
                process.WaitForInputIdle();
                iLyncAppWinHandle = process.MainWindowHandle;
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        void StartGetLyncClientThread()
        {
            threadGetLyncClient = new Thread(new ThreadStart(GetLyncClient));
            threadGetLyncClient.Priority = ThreadPriority.Highest;
            //threadGetLyncClient.IsBackground = true;
            threadGetLyncClient.Start();
            
        }
        /// <summary>
        /// 删除注册表
        /// </summary>
        void DeleteRegistry()
        {
            try
            {
                bool is64System = GetOSBit() == 64 ? true : false;

                string strReg64 = @"Software\Wow6432Node\Microsoft\Office\15.0\Lync\SessionManager\Apps\";
                string strReg32 = @"Software\Microsoft\Office\15.0\Lync\SessionManager\Apps\";
                if (is64System)
                {
                    Registry.LocalMachine.DeleteSubKey(strReg64 + "{c42364DA-67B4-4AC4-930E-02C705D86505}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg64 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg64 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg64 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}", true);//删除指定路径下的键
                }
                else
                {
                    Registry.LocalMachine.DeleteSubKey(strReg32 + "{c42364DA-67B4-4AC4-930E-02C705D86505}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg32 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg32 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", true);//删除指定路径下的键
                    Registry.LocalMachine.DeleteSubKey(strReg32 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}", true);//删除指定路径下的键
                }
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>   
        /// 执行注册表导入   
        /// </summary>   
        /// <param name="regPath">注册表文件路径</param> 
        public void ExecuteReg()
        {
            if (exeName.IndexOf("Communicator") > 0)//lync 2010
            {
                LogManager.SystemLog.Debug("ExecuteReg Communicator");
                RegistryKey pregkey = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{F42364DA-67B4-4AC4-930E-02C705D86505}", true);//获取指定路径下的键
                string path = System.Windows.Forms.Application.StartupPath;
                string pathImage = path.Substring(0, path.IndexOf("bin"));
                if (null == pregkey)
                {
                    pregkey = Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{F42364DA-67B4-4AC4-930E-02C705D86505}");
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "ConversationWindowRightClick;ContactCardMenu;MainWindowRightClick", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("UCCallMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("UCCallMenuItem"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " Call" + " %user-id% %contact-id%", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\call.BMP", RegistryValueKind.String);

                }
                pregkey = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", true);//获取指定路径下的键
                if (null == pregkey)
                {
                    pregkey = Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}");
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "ConversationWindowRightClick;ContactCardMenu;MainWindowRightClick", RegistryValueKind.String);                    
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("UCVideoCallMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("UCVideoCallMenuItem"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " VideoCall" + " %user-id% %contact-id%", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\videocall.BMP", RegistryValueKind.String);
                }
                pregkey = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", true);//获取指定路径下的键
                if (null == pregkey)
                {
                    pregkey = Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}");
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "MainWindowActions", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("LoginUCMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("LoginUC"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " LoginUC", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\eSpaceLogin.BMP", RegistryValueKind.String);
                }
                pregkey = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{D6AA495B-0035-4AEB-AE7D-403CD6198972}", true);//获取指定路径下的键
                if (null == pregkey)
                {
                    pregkey = Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Communicator\SessionManager\Apps\{D6AA495B-0035-4AEB-AE7D-403CD6198972}");
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "MainWindowActions", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("LogOutUCMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("LogOutUC"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " LogOutUC", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\eSpaceLogin.BMP", RegistryValueKind.String);
                }
            }
            else//lync 2013
            {
                LogManager.SystemLog.Debug("ExecuteReg Lync2013");
                bool is64System = GetOSBit() == 64 ? true : false;

                RegistryKey pregkey = null;
                string strReg64 = @"Software\Wow6432Node\Microsoft\Office\15.0\Lync\SessionManager\Apps\";
                string strReg32 = @"Software\Microsoft\Office\15.0\Lync\SessionManager\Apps\";
                if (is64System)
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg64 + "{c42364DA-67B4-4AC4-930E-02C705D86505}", true);//获取指定路径下的键
                }
                else
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg32 + "{c42364DA-67B4-4AC4-930E-02C705D86505}", true);
                }

                string path = System.Windows.Forms.Application.StartupPath;
                string pathImage = path.Substring(0, path.IndexOf("bin"));
                if (null == pregkey)
                {
                    if (is64System)
                    {
                        Registry.LocalMachine.CreateSubKey(@"Software\Wow6432Node\Microsoft\Office\15.0\Lync\SessionManager");//64位系统必须单项增加，否则出现没权限异常
                        Registry.LocalMachine.CreateSubKey(strReg64);
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg64 + "{c42364DA-67B4-4AC4-930E-02C705D86505}");
                    }
                    else
                    {
                        Registry.LocalMachine.CreateSubKey(@"Software\Microsoft\Office\15.0\Lync\SessionManager");
                        Registry.LocalMachine.CreateSubKey(strReg32);
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg32 + "{c42364DA-67B4-4AC4-930E-02C705D86505}");
                    }

                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "ConversationWindowRightClick;ContactCardMenu;MainWindowRightClick", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("UCCallMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("UCCallMenuItem"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " Call" + " %user-id% %contact-id%", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\call.BMP", RegistryValueKind.String);

                }

                if (is64System)
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg64 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", true);//获取指定路径下的键
                }
                else
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg32 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", true);
                }
                if (null == pregkey)
                {
                    if (is64System)
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg64 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}", RegistryKeyPermissionCheck.ReadWriteSubTree);
                    }
                    else
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg32 + "{22F6531F-8BC3-4C78-9566-BB2EF3920D6A}");
                    }
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "ConversationWindowRightClick;ContactCardMenu;MainWindowRightClick", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("UCVideoCallMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("UCVideoCallMenuItem"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " VideoCall" + " %user-id% %contact-id%", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\videocall.BMP", RegistryValueKind.String);
                }
                if (is64System)
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg64 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", true);//获取指定路径下的键
                }
                else
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg32 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", true);
                }
                if (null == pregkey)
                {
                    if (is64System)
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg64 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}", RegistryKeyPermissionCheck.ReadWriteSubTree);
                    }
                    else
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg32 + "{4C1C052D-77D6-4DF9-8E9F-EDA6FD2431B3}");
                    }
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "MainWindowActions", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("LoginUCMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("LoginUC"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " LoginUC", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\eSpaceLogin.BMP", RegistryValueKind.String);
                }
                if (is64System)
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg64 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}", true);//获取指定路径下的键
                }
                else
                {
                    pregkey = Registry.LocalMachine.OpenSubKey(strReg32 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}", true);
                }
                if (null == pregkey)
                {
                    if (is64System)
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg64 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}", RegistryKeyPermissionCheck.ReadWriteSubTree);
                    }
                    else
                    {
                        pregkey = Registry.LocalMachine.CreateSubKey(strReg32 + "{D6AA495B-0035-4AEB-AE7D-403CD6198972}");
                    }
                    pregkey.SetValue("ApplicationInstallPath", path + "\\WpfSendMessage.exe", RegistryValueKind.String);
                    pregkey.SetValue("ApplicationType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("ExtensibleMenu", "MainWindowActions", RegistryValueKind.String);
                    pregkey.SetValue("HelpMessage", StringHelper.FindLanguageResource("LogOutUCMessage"), RegistryValueKind.String);
                    pregkey.SetValue("Name", StringHelper.FindLanguageResource("LogOutUC"), RegistryValueKind.String);
                    pregkey.SetValue("Path", path + "\\WpfSendMessage.exe" + " LogOutUC", RegistryValueKind.String);
                    pregkey.SetValue("SessionType", 0, RegistryValueKind.DWord);
                    pregkey.SetValue("SmallIcon", pathImage + "\\Image\\eSpaceLogin.BMP", RegistryValueKind.String);
                }
            }

        }

        /// <summary>
        /// 获取当前lync联系人列表中的数据
        /// </summary>
        /// <param name="hwnd"></param>
        /// <param name="lParam"></param>
        /// <returns></returns>
        static bool ChildWindowProcess(int hwnd, int lParam)
        {
            lyncChildHwndList.Add((IntPtr)hwnd);
            return true;
        }

        /// <summary>
        /// 获取操作系统位数（x32/64）
        /// </summary>
        /// <returns>int</returns>
        private int GetOSBit()
        {
            try
            {
                string addressWidth = String.Empty;
                ConnectionOptions mConnOption = new ConnectionOptions();
                ManagementScope mMs = new ManagementScope(@"\\localhost", mConnOption);
                ObjectQuery mQuery = new ObjectQuery("select AddressWidth from Win32_Processor");
                ManagementObjectSearcher mSearcher = new ManagementObjectSearcher(mMs, mQuery);
                ManagementObjectCollection mObjectCollection = mSearcher.Get();
                foreach (ManagementObject mObject in mObjectCollection)
                {
                    addressWidth = mObject["AddressWidth"].ToString();
                }
                LogManager.SystemLog.Debug(string.Format("GetOSBit = {0}", addressWidth));
                return Int32.Parse(addressWidth);
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return 32;
            }
        }
        /// <summary>
        /// 获取lync电话
        /// </summary>
        /// <returns></returns>
        public string GetLyncPhoneNumber()
        {
            string phone = "";
            List<object> list = _Client.Self.Contact.GetContactInformation(ContactInformationType.ContactEndpoints) as List<object>;
            foreach (object point in list)
            {
                if (((Microsoft.Lync.Model.ContactEndpoint)point).Type == ContactEndpointType.MobilePhone)
                {
                    phone = ((Microsoft.Lync.Model.ContactEndpoint)point).DisplayName;
                    break;
                }
            }
            return phone;
        }
    }
}