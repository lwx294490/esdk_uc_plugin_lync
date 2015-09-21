using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;

namespace LyncWpfApp
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void ClientSignInNotifyCB(int _state, StringBuilder _reason);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void StatusChangedCB(int _state, ref  STContact _contact);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void AVSessionClosedCB(ref STMsgAVSessionClosedParam _avParam);//通话结束事件回调函数指针
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void AVSessionConnectedCB();//通话连接事件回调函数指针
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void AVSessAddedCB(ref STAudioVideoParam _avParam);//收到呼叫事件回调函数指针
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void ConfMemberEventCB(ref STConfParam _avParam);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void CallEventCB(ref STCallParam _callParam);
    //[UnmanagedFunctionPointer(CallingConvention.StdCall)]
    //public delegate void PhoneJointEventCB(int _state);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void PhoneJointEventCB(ref PJStatusParam _pj);
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void CallReservedEventCB(int type,int reslut);//呼叫转移事件回调函数

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void CallTransEventCB(int type, int reslut);//呼叫盲转回调函数   //modify by jinyeiqng  6/3

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STCallExData
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string Num;//号码
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STConfParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string callerAcc_;
        public int memStatus;			//参考MemStatusInCall的定义
        public int memType;			//参考MemberType的定义
    };//会议参数
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STCallParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ucAcc;
        public int callStatus;		//参考CallStatus的定义
    };//呼叫参数

    //Call状态
    public enum CallStatus
    {
        CALL_VIDEO_REQ = 0, //视频呼叫请求
        CALL_VIDEO_CONNECTED, //视频呼叫接通
        CALL_VIDEO_CLOSE //视频呼叫接通
    };
    //话机联动类型
    public enum PhoneJointType
    {
        PC_Device = 0,	//PC作为通讯设备
        IPPhone_Device	//ip话机作为通讯设备
    };

    //话机联动通知状态
    public enum EM_PhoneJointStatusType
    {
        STATUS_START_SUCC = 0, //开启联动成功
        STATUS_START_FAILED = 1, //开启联动失败
        STATUS_STOP_SUCC = 2, //取消联动成功
        STATUS_STOP_FAILED = 3, //取消联动失败
        STATUS_ONLINE = 4, //IPPhone在线
        STATUS_OFFLINE = 5, //IPPhone离线
        STATUS_OFFHOOK = 6,  //IPPhone摘机
         STATUS_JOINT_OUTGOING = 7  //联动话机呼出
    };

    public class UCContactInfo
    {
        public STContact User { get; set; }
        public int State { get; set; }
    }
    public enum SignInState
    {
        Client_Uninited,
        Client_SignedFailed,
        Client_SigningIn,
        Client_SignedIn,
        Client_KickedOut,
        Client_Invalid
    };

    public struct COPYDATASTRUCT
    {
        public IntPtr dwData;
        public int cbData;
        [MarshalAs(UnmanagedType.LPStr)]
        public string lpData;
    }
    public enum UCServiceRetvCode
    {
        UC_SDK_Success = 0,			//成功
        UC_SDK_InvalidPara = 1,			//不合法的参数
        UC_SDK_Failed = 2,			//失败
        UC_SDK_NotInit = 3,			//未初始化
        UC_SDK_NullPtr = 4,			//空指针
        UC_SDK_FindUriErr = 5,			//查找用户uri错误
        UC_SDK_NotHaveCallTarget = 6,			//没有呼叫对象
        UC_SDK_InTempGroupNow = 7,			//已经在TempGroup内
        UC_SDK_NotFound = 8,			//没有找到
        UC_SDK_NoRight = 9,			//没有权限
        UC_SDK_NotLogin = 10			//未成功登录

    };
    //话机联动通知状态
    public enum PhoneJointStatusType
    {
        STATUS_START_SUCC = 0, //开启联动成功
        STATUS_START_FAILED = 1, //开启联动失败
        STATUS_STOP_SUCC = 2, //取消联动成功
        STATUS_STOP_FAILED = 3, //取消联动失败
        STATUS_ONLINE = 4, //IPPhone在线
        STATUS_OFFLINE = 5, //IPPhone离线
        STATUS_OFFHOOK = 6, //IPPhone摘机
        STATUS_JOINT_OUTGOING = 7  //联动话机呼出
    };

    //话机联动参数
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct PJStatusParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string CalleeNum;	//被叫绑定号
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string CalleeName;	//被叫名称
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ucCalleeAcc;//被叫UC账户
        public int PJ_Status;			     //参考EM_PhoneJointStatusType的定义

    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STAudioVideoParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string callerAcc;
        public int isvideo_;			//1表示视频，0表示不是视频
        public int callMode;			//1表示IPHone，表示软终端呼出
        public int AccountType;		//1表示IPPhone，表示UcAccount
        public int isConference;           //1表示conference ，0表示是点对点呼叫
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STMsgAVSessionClosedParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string caller_;       //对方uri
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string AVSessionId_;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string reason_;        //错误码
    } ;
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STContact
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string id;        //!< id
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string uri_;       //!< sip uri
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string fullUri_;   //!< sip full uri
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ucAcc_;     //!< account
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string staffNo_;   //!< staff no
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string name_;      //!< name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string nickName_;  //!< nick name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string qpinyin_;   //!< name fullpinyin
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string spinyin_;   //!< name simplepinyin
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string homePhone_;   //!< home phone
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string officePhone_; //!< office phone
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string officePhone2_; //!< office phone2
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string mobile_;      //!< mobile phone
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string otherPhone_;  //!< other phone
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string otherPhone2_; //!< other phone2
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string address_;     //!< address
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string email_;     //!< email
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string duty_;      //!< duty
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string fax_;       //!< fax
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string gender_;    //!< gender
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string corpName_;  //!< enterprise name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string deptName_;  //!< dept name
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string webSite_;   //!< web site
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string desc_;      //!< description
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string zip_;       //!< zip
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string signature_; //!< signature
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string imageID_;   //!< head image id
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string position_;  //!< 
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string location_;  //!< 
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string tzone_;     //!< contact time zone
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string avtool_;    //!< avaliable device (mic/speaker/camera)
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string device_;    //!< contact device type
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string terminalType_; //!< contact type
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ipphone1_;  //!< bind ipphone1 number
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ipphone2_;  //!< bind ipphone2 number
        public int flow_;              //!< mark contact status in the group(just used for fixedgroup)
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STVideoWindow
    {
        public int left;
        public int top;
        public int width;
        public int height;
        public int hWnd;
    };
    //窗口句柄

    public enum MemberStatusInCall
    {
        EndCallMember,		//结束某成员的通话
        ReInviteMember,		//重新呼叫某成员
        MuteMember,			//对某成员静音
        UnMuteMember,		//对某成员取消静音
        //modify by jinyeqing 2015/5/22
        DelCallMember      //移除与会者
    };
    // 矩形结构    
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }
    // 矩形结构    
    [StructLayout(LayoutKind.Sequential)]
    public struct RECTSize
    {
        public double left;
        public double top;
        public double height;
        public double width;
    }

    //会议中的成员状态
    public enum MemStatusInCall
    {
        CONF_MEM_INVITING = 0,	//正在呼叫某成员
        CONF_MEM_HANGUP,		//某成员挂断
        CONF_MEM_INCONF,		//正在会议中
        CONF_MEM_QUIT,			//成员离开
        CONF_MEM_MUTE,			//成员被静音
        CONF_MEM_UnMute,		//成员被取消静音
        CONF_MEM_SPK,			//成员在说话
        CONF_MEM_ADD,			//新增成员
        CONF_MEM_DEL,			//成员被删除
        None
    };
    //成员类型
    public enum MemberType
    {
        UC_ACCOUNT = 0,	//UC账户
        UC_IPPHONE	//IPPHONE
    };
    //历史记录
    [StructLayout(LayoutKind.Sequential)]
    public struct STTime
    {
        public int year;
        public int month;
        public int day;
        public int hour;
        public int minute;
        public int second;
    };
    public enum UCContactAvailability
    {
        Offline = 0,
        Online,
        Hide,
        Busy,
        Leave,
        NoDisturb,
        InvalidStatus,
    };
    public enum CallHistoryType
    {
        HISTORY_CALL_MISSED = 0,//未接电话
        HISTORY_CALL_ANSWERED,	//已接通话
        HISTORY_CALL_DIALED,	//已拨通话
        HISTORY_CALL_ALL		//全部通话
    };//单人呼叫历史数据
    [StructLayout(LayoutKind.Sequential)]
    public struct STCallHistroyItem
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string CallNum;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string CallName;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string ucAccount;//UC账户
        public STTime startTime;//开始时间
        public int duration; // -1 : missed call
        public int callType; //calltype
        public int recordID;
    };
    [StructLayout(LayoutKind.Sequential)]
    public struct STCallHistroyData
    {
        public int iTotal;
        public int iFrom;
        public int iTo;
        [MarshalAs(UnmanagedType.ByValArray)]
        public STCallHistroyItem[] stCallHistory;
    };
    [StructLayout(LayoutKind.Sequential)]
    public struct STDeviceListParam
    {
        public int iTotal;			//总共数目
        public int iFrom;			//开始索引
        public int iTo;			//结束索引
        [MarshalAs(UnmanagedType.ByValArray)]
        public STDeviceParam[] deviceList;
    } ;

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct STDeviceParam
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string name;       /*!< device name*/
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string deviceId;   /*!< device id*/
        public int index;            /*!< device no*/
        public int iscertified;      /*!< if device is verified by Huawei Corp.*/
        public int isactive;         /*!< if device is active*/
        public int type;             /*!< 设备类型*/
    } ;
    [StructLayout(LayoutKind.Sequential)]
    public struct STConvHistroyItem
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string convID;				//会议ID
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string compereName;		//主持人名称
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string compereAccount;		//主持人账户
        public STTime startTime;						//开始时间
        public int duration;							// -1 :表示未接来电
        public int partcipantNum;						//参与者个数
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct STConvHistroyData
    {
        public int iTotal;
        public int iFrom;
        public int iTo;
        [MarshalAs(UnmanagedType.ByValArray)]
        public STConvHistroyItem[] stConvHistory;
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct STConfPartItem
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string partName;//与会者名称
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string partAccount;//与会者账户
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct STConfPartData
    {
        public int partNum;//与会者个数
        [MarshalAs(UnmanagedType.ByValArray)]
        public STConfPartItem[] stConfPart;
    };
    public enum PortalType
    {
        SelfMgr_Portal = 0,	//个人管理页面
        BookConf_Portal = 1	//预定会议页面
    };

    //前传业务类型参数
    public enum ForwardServiceType
    {
        FORWARD_UNCONDITION = 0,	//无条件前传
        FORWARD_ONBUSY,				//遇忙前传
        FORWARD_NOREPLY,			//无应答前传
        FORWARD_OFFLINE,			//离线前传
        VOICEMAIL_UNCONDITION,		//无条件转语音邮箱
        VOICEMAIL_ONBUSY,			//遇忙转语音邮箱
        VOICEMAIL_NOREPLY,			//无应答转语音邮箱
        VOICEMAIL_OFFLINE,			//离线转语音邮箱
        FORWARD_BORDER				//边界
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct STConfMember
    {
         public int membertype;                      //成员类型
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string account;      
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct STConfMemList
    {
        public int size;          
        [MarshalAs(UnmanagedType.ByValArray)]
        public STConfMember[] stConfMem;
    };



[StructLayout(LayoutKind.Sequential)]
 public struct STContactList
{
	public int iTotal;
    [MarshalAs(UnmanagedType.ByValArray)]
	public STContact[] stContac;
} ;

    public class UCInterface
    {
        [DllImport("user32.dll")]
        public static extern int GetClientRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("user32.dll")]
        public static extern void ClientToScreen(IntPtr hWnd, ref Point p);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_Init();//初始化
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_UnInit();//释放资源
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SignInByPWD(string account, string pwd, string internalurl, string langID);//登录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SignOut();//初始化
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetLoginEventCB(ClientSignInNotifyCB clientSignInNotifyCallBack);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetStatusChangedCB(StatusChangedCB statusChangedCallBack);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCallEventCallBack(AVSessionClosedCB aVSessionClosedCallBack, AVSessionConnectedCB aVSessionConnectedCallBack, AVSessAddedCB aVSessAddedCallBack);//设置呼叫事件回调
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_MakeCall();//该函数用于发起呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_AddCallMember(int type, string lyncAccount);//该函数用于设置发起呼叫的目标用户
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_HoldCall();//通话保持
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_ResumeCall();//通话恢复
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_HangupCall();//该函数用于结束通话释放conversation，释放UC_SDK_InsertMember增加的成员
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_AcceptCall();//该函数用于接听呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_RejectCall();//该函数用于拒绝呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SendDTMF(char tones);//二次拨号
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_MuteMic();//麦克风静音
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_UnMuteMic();//麦克风取消静音
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_MakeVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
                                          int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);//发起视频呼叫或者将当前语音呼叫升级为视频呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_InviteMemberInCall(int memberType, StringBuilder lyncAccount);//该函数用于语音会议中邀请成员
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_TransCallToConf(byte[] _pContactList, int size);//该函数用于点呼转会议
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_DeleteMemberInCall(int memberType, StringBuilder lyncAccount);//该函数用于语音会议中删除成员
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_ModifyMemberStatusInCall(int operateType, int memberType, StringBuilder lyncAccount);//包括语音会议中断开某成员的语音，语音会议中重新呼叫某成员，语音会议中对某成员静音，对某成员取消静音4种。
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetMicLevel(ref int level);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetMicLevel(int level);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_MuteSpker();
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_UnMuteSpker();
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetSpkerLevel(int level);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetSpkerLevel(ref int level);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetConfMemEventCallBack(ConfMemberEventCB confMemEventCallBack);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_QueryCallHistory(CallHistoryType _callType, int _fromIndex, int _toIndex, byte[] _result, int _size);//查询单人呼叫历史记录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetMicDevList(int _fromIndex, int _toIndex, int _size, byte[] devList);//该函数用于获取麦克风设备列表
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetSpeakerDevList(int _fromIndex, int _toIndex, int _size, byte[] devList);//该函数用于获取扬声器设备列表
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetVideoDevList(int _fromIndex, int _toIndex, int _size, byte[] devList);//该函数用于获取视频设备列表
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetCurrentMicDev(byte[] device);//该函数用于获取当前麦克风设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetCurrentSpeakerDev(byte[] device);//该函数用于获取当前扬声器设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetCurrentVideoDev(byte[] device);//该函数用于获取当前扬声器设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCurrentMicDev(int index);//该函数用于设置当前麦克风设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCurrentSpeakerDev(int index);//该函数用于设置当前扬声器设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCurrentVideoDev(int index);//该函数用于设置当前视频设备
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_ClearCallHistroy(int _callType);//清除单人呼叫历史记录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_InsertCallHistory(int _CallType, string _url, string _name, int _duration);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_QueryConvHistory(int _fromIndex, int _toIndex, byte[] _result, int _size);//查询会议历史记录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_QueryHisConvPartByID(string _convID, int _fromIndex, int _toIndex, byte[] _result, int _size);//查询一条会议历史记录的参与者
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_ClearConvHistroy();//清除会议历史记录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_InsertConvHistory(string _leaderAccount, string _leaderName, int _duration, StringBuilder _historyID);//插入会议历史记录
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_InsertConvHistoryPart(string _historyID, string _partAccount, string _partName);//插入会议历史记录的与会人
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_AcceptVideoCall(int localHWnd, int localLeft, int localTop, int localWidth, int localHeight,
                                                        int remoteHWnd, int remoteLeft, int remoteTop, int remoteWidth, int remoteHeight);//接听视频呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_RejectVideoCall();//拒绝呼叫
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_HangupVideoCall();//结束视频通话
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetVideoCallEventCallBack(CallEventCB callEventCallBack);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetPhoneJointDevType(ref int _pDevType);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetPhoneJointDevType(int _pDevType);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetPhoneJointEventCallBack(PhoneJointEventCB pjEventCallBack);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_ForwardCall(int iMemberType, string pMember);//呼叫前转
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetUCAccount(string phoneNum, StringBuilder _UCAcc);//查询呼叫成员
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_OpenPortal(int _type);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_PubSelfStatus(int _Status,StringBuilder _Desc);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetContactStatus(int _AccountType,string _Account,ref int _Status);//获取联系人状态
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetContactInfo(StringBuilder _Account, ref  STContact _pContactInfo);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCallExService(int _type,ref STCallExData _Num);//设置呼叫前转
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetCallExService(int _type, ref STCallExData _CallExData);//获取前传业务及号码
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_BlindTransCall(int iMemberType, string pMember);//该函数用于呼叫盲转，当终端已经处于通话状态时，直接转移
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_GetEntContactList(string strSearchKey, int _fromIndex, int _toIndex, byte[] _pContactList);
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCallReservedEventCallBack(CallReservedEventCB crEventCallBack);//设置呼叫转移事件回调函数
        [DllImport(@"UCService.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static int UC_SDK_SetCallTransEventCallBack(CallTransEventCB crEventCallBack);//设置盲转转移事件回调函数
    }
}
