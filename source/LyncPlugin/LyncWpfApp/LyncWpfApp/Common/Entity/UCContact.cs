using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.ComponentModel;

namespace LyncWpfApp
{

    public class UCContact : INotifyPropertyChanged
    {
        //用户名
        string username;
        public virtual string UserName
        {
            get { return username; }
            set
            {

                username = value;
                NotifyChange("UserName");

            }
        }
        UCContactAvailability online;
        public virtual UCContactAvailability Online
        {
            get { return online; }
            set
            {
                online = value;
                NotifyChange("OnlineImage");

            }
        }
        MemStatusInCall mute;
        public virtual MemStatusInCall Mute
        {
            get { return mute; }
            set
            {
                mute = value;
                NotifyChange("MuteImage");
            }
        }
        string onlineImage;
        public virtual string OnlineImage
        {
            get
            {
                if (Online == UCContactAvailability.Online)
                {
                    return @"/Image/call/main_status_online.png";
                }
                else if (Online == UCContactAvailability.Busy)
                {
                    return @"/Image/call/busy.png";
                }
                else if (Online == UCContactAvailability.Hide || Online == UCContactAvailability.Leave)
                {
                    return @"/Image/call/Away.png";
                }
                else if (Online == UCContactAvailability.NoDisturb)
                {
                    return @"/Image/call/main_status_nodisturb.png";
                }
                else
                {
                    return @"/Image/call/main_status_offline.png";
                }
            }
            set
            {

                onlineImage = value;
                NotifyChange("OnlineImage");

            }
        }
        string muteImage;
        public virtual string MuteImage
        {
            get
            {
                if (Mute == MemStatusInCall.CONF_MEM_HANGUP || Mute == MemStatusInCall.CONF_MEM_QUIT)
                {
                    return @"/Image/call/conf_hangup.png";
                }
                else if (Mute == MemStatusInCall.CONF_MEM_MUTE)
                {
                    return @"/Image/call/conf_mute.png";
                }
                else if (Mute == MemStatusInCall.CONF_MEM_UnMute || Mute == MemStatusInCall.CONF_MEM_INCONF)
                {
                    return @"/Image/call/conf_connected.png";
                }
                else if (Mute == MemStatusInCall.CONF_MEM_INVITING)
                {
                    return @"/Image/call/conf_connecting.png";
                }
                else
                {
                    return @"";
                }
            }
            set
            {
                if (value != null)
                {
                    muteImage = value;
                    NotifyChange("MuteImage");
                }
            }
        }
        bool isLeader;
        public virtual bool IsLeader
        {
            get { return isLeader; }
            set
            {

                isLeader = value;
                NotifyChange("LeaderImage");

            }
        }
        string leaderImage;
        public virtual string LeaderImage
        {
            get
            {
                if (IsLeader == true)
                {
                    return @"/Image/call/conf_leader.png";
                }
                else
                {
                    return @"";
                }
            }
            set
            {
                leaderImage = value;
                NotifyChange("LeaderImage");

            }
        }
        bool isSpeaker;
        public virtual bool IsSpeaker
        {
            get { return isSpeaker; }
            set
            {
                isSpeaker = value;
                NotifyChange("SpeakerImage");
            }
        }
        string speakerImage;
        public virtual string SpeakerImage
        {
            get
            {
                if (IsSpeaker == true && Mute != MemStatusInCall.CONF_MEM_HANGUP && Mute != MemStatusInCall.CONF_MEM_QUIT && Mute != MemStatusInCall.CONF_MEM_MUTE)
                {
                    return @"/Image/call/conf_speaker.png";
                }
                else
                {
                    return @"";
                }
            }
            set
            {
                if (value != null)
                {
                    speakerImage = value;
                    NotifyChange("SpeakerImage");
                }
            }
        }
        MemberType ucMemberType;
        public MemberType UCMemberType
        {
            get
            {
                return ucMemberType;
            }
            set
            {
                ucMemberType = value;
                NotifyChange("UCMemberType");
            }
        }

        #region INotifyPropertyChanged 成员
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyChange(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        #endregion
    }
    public class ContactCompar : IEqualityComparer<UCContact>
    {
        public bool Equals(UCContact x, UCContact y)
        {
            return x.UserName == y.UserName;
        }

        public int GetHashCode(UCContact obj)
        {
            return obj.ToString().GetHashCode();
        }
    }
}
