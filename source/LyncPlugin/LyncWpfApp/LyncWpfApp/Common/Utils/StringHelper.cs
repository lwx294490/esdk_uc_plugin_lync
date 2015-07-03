using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using Microsoft.Lync.Model.Group;
using Microsoft.Lync.Model;

namespace LyncWpfApp
{
    public class StringHelper
    {
        public static string FindLanguageResource(string key)
        {
            var value = Application.Current.TryFindResource(key) != null ? string.Format(Application.Current.TryFindResource(key).ToString(), key) :
                        (Application.Current.TryFindResource("CommonMistake") ?? key);
            return value.ToString();
        }
        /// <summary>
        /// 获取@之前的字符串
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string GetSubString(string str)
        {
            if (str.IndexOf("@") != -1)
            {
                return str.Substring(0, str.IndexOf("@"));
            }
            else
            {
                return str;
            }
        }
        /// <summary>
        /// 获取@之后的字符串
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string GetLyncDomainString(string str)
        {
            if (str ==null)
            {
                return "";
            }
            if (str.IndexOf("@") != -1)
            {
                return str.Substring(str.IndexOf("@"));
            }
            else
            {
                return str;
            }
        }
        /// <summary>
        /// 获取lync uri
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string GetLyncUrl(string str)
        {
            long lNum = 0;
            if (long.TryParse(str,out lNum))
            {
                return str;
            }
            foreach (Microsoft.Lync.Model.Group.Group group in WinLync.LyncContactGroups)
            {
                foreach (Contact contact in (ContactCollection)(group))
                {
                    if (contact.Uri.IndexOf(str + "@") > 0)
                    {
                        return contact.Uri;
                    }
                }
            }           
            return "sip:" + str + GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
        }

        /// <summary>
        /// 获取Lync名
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static string GetLyncNameString(string str)
        {
            string name = "";
            if (str.IndexOf(":") != -1)
            {
                name =  str.Substring(str.IndexOf(":") + 1);
            }
            name = GetSubString(name);
            
            return name;
        }
    }
}
