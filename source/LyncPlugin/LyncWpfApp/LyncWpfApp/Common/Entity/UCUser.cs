using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace LyncWpfApp
{
    [Serializable]
    [XmlRoot("UCUserInfo")]
    public class UCUserInfo
    {
        //用户名
        [XmlElement("UserID")]
        public virtual string UserID
        {
            get;
            set;
        }
        //用户密码
        [XmlElement("Password")]
        public virtual string Password
        {
            get;
            set;
        }
        //呼出设备选项
        [XmlElement("OutgoingDevice")]
        public virtual string OutgoingDevice
        {
            get;
            set;
        }
        //呼叫方式选项
        [XmlElement("CallMethod")]
        public virtual string CallMethod
        {
            get;
            set;
        }
       //呼叫转移选项
        [XmlElement("TransferCallTo")]
        public virtual string TransferCallTo
        {
            get;
            set;
        }
        //麦克风选项
        [XmlElement("MicPhone")]
        public virtual string MicPhone
        {
            get;
            set;
        }
        //扬声器选项
        [XmlElement("Speaker")]
        public virtual string Speaker
        {
            get;
            set;
        }
       //摄像头选项
        [XmlElement("Camera")]
        public virtual string Camera
        {
            get;
            set;
        }
        //服务器
        [XmlElement("Server")]
        public virtual string Server
        {
            get;
            set;
        }
        //端口
        [XmlElement("Port")]
        public virtual string Port
        {
            get;
            set;
        }
        //语言
        [XmlElement("Lang")]
        public virtual string Lang
        {
            get;
            set;
        }
       //版本
        [XmlElement("Ver")]
        public virtual string Ver
        {
            get;
            set;
        }
       //自动启动
        [XmlElement("AutoStart")]
        public virtual string AutoStart
        {
            get;
            set;
        }

        [XmlElement("MessageEnable")]
        public virtual string MessageEnable
        {
            get;
            set;
        }
        [XmlElement("CallEnable")]
        public virtual string CallEnable
        {
            get;
            set;
        }
        [XmlElement("MessageFilePath")]
        public virtual string MessageFilePath
        {
            get;
            set;
        }
        [XmlElement("CallFileFilePath")]
        public virtual string CallFileFilePath
        {
            get;
            set;
        }

        [XmlElement("Available")]
        public virtual bool Available
        {
            get;
            set;
        }
        [XmlElement("Unavailable")]
        public virtual bool Unavailable
        {
            get;
            set;
        }
        [XmlElement("Busy")]
        public virtual bool Busy
        {
            get;
            set;
        }
        [XmlElement("Voicemail")]
        public virtual bool Voicemail
        {
            get;
            set;
        }

        [XmlElement("AvailableCallNumber")]
        public virtual string AvailableCallNumber
        {
            get;
            set;
        }
        [XmlElement("UnavailableCallNumber")]
        public virtual string UnavailableCallNumber
        {
            get;
            set;
        }
        [XmlElement("BusyCallNumber")]
        public virtual string BusyCallNumber
        {
            get;
            set;
        }
        [XmlElement("VoicemailCallNumber")]
        public virtual string VoicemailCallNumber
        {
            get;
            set;
        }

        public string LyncName
        {
            get;
            set;
        }
        [XmlElement("SetFWDService")]
        public virtual string SetFWDService
        {
            get;
            set;
        }
    }
}
