using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Collections.Specialized;
using System.Reflection;
using System.IO;

namespace LyncWpfApp
{
    internal static class UtilsSettings
    {
        internal static Configuration appSettings = null;

        static UtilsSettings()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            //通过URL获取时目录中含有#时出现问题
            //Uri uri = new Uri(Path.GetDirectoryName(assembly.CodeBase));
            ExeConfigurationFileMap map = new ExeConfigurationFileMap();

            map.ExeConfigFilename = Assembly.GetExecutingAssembly().CodeBase.Replace(@"file:///", string.Empty) + ".config";
            appSettings = ConfigurationManager.OpenMappedExeConfiguration(map, ConfigurationUserLevel.None);
        }

        private static AuthenticationToken _Header;
        internal static AuthenticationToken Header
        {
            get
            {
                if (_Header == null)
                {
                    AuthenticationToken myHeader = new AuthenticationToken();
                    if (appSettings.AppSettings.Settings["appId"] == null)
                    {
                        myHeader.appId = "";
                    }
                    else
                    {
                        myHeader.appId = appSettings.AppSettings.Settings["appId"].Value;
                    }

                    if (appSettings.AppSettings.Settings["pw"] == null)
                    {
                        myHeader.pw = "";
                    }
                    else
                    {
                        myHeader.pw = appSettings.AppSettings.Settings["pw"].Value;
                    }
                    _Header = myHeader;
                }
                return _Header;
            }
        }

        private static string _URL;
        internal static string URL
        {
            get
            {
                if (_URL == null)
                {
                    if (appSettings.AppSettings.Settings["url"] == null)
                    {
                        _URL = "http://127.0.0.1:8081";
                    }
                    else
                    {
                        _URL = appSettings.AppSettings.Settings["url"].Value;
                    }
                }
                return _URL;
            }
        }
    }
}
