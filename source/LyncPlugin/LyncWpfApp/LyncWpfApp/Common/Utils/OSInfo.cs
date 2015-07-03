using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
   public class OSInfo
    {
        /// <summary>
        /// 获取操作系统版本号
        /// </summary>
        /// <returns></returns>
        public string GetOSVersion()
        {
            Version ver = System.Environment.OSVersion.Version;
            string strClient = "";
            if (ver.Major == 5 && ver.Minor == 1)
            {
                strClient = "Win XP";
            }
            else if (ver.Major == 6 && ver.Minor == 0)
            {
                strClient = "Win Vista";
            }
            else if (ver.Major == 6 && ver.Minor == 1)
            {
                strClient = "Win 7";
            }
            else if (ver.Major == 6 && ver.Minor == 2)
            {
                strClient = "Win 8";
            }
            else if (ver.Major == 5 && ver.Minor == 0)
            { strClient = "Win 2000"; }
            else
            {
                strClient = "Win 9";
            }
            return strClient;
        }
    }
}