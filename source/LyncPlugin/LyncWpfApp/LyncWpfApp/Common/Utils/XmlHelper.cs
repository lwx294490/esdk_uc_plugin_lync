using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace LyncWpfApp
{
    public class XmlHelper
    { 
        /// <summary>
        /// 反序列化xml为对象
        /// </summary>
        /// <param name="xml">对象序列化后的Xml字符串</param>
        /// <returns></returns>
        public static T DeserializeToEntity<T>(string xml)
        {
            using (var sr = new StringReader(xml))
            {
                var xz = new XmlSerializer(typeof(T));
                try
                {
                    return (T)xz.Deserialize(sr);
                }
                catch (Exception xmle)
                {
                    LogManager.SystemLog.Error(xmle.ToString());
                    return default(T);
                }
            }
        }
        public static UCUserInfo GetUserConfig()
        {
            try
            {
                EncryptDecrypt.DecryptUserConfigFile();
                string xml = File.ReadAllText(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml", Encoding.UTF8);
                var doc = new XmlDocument();
                doc.LoadXml(xml);
                File.Delete(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml");
                XmlNode content = doc.SelectSingleNode(@"Content/UCUserInfo");
                return DeserializeToEntity<UCUserInfo>(content.OuterXml);
                
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return null;
            }
        }
        public static void SetUserConfig(UCUserInfo user)
        {
            try
            {
                EncryptDecrypt.DecryptUserConfigFile();
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml");

                XmlNode node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/UserID");
                node.InnerText = user.UserID;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Password");
                node.InnerText = user.Password;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/OutgoingDevice");
                node.InnerText = user.OutgoingDevice;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/CallMethod");
                node.InnerText = user.CallMethod;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/TransferCallTo");
                node.InnerText = user.TransferCallTo;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/MicPhone");
                node.InnerText = user.MicPhone;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Speaker");
                node.InnerText = user.Speaker;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Camera");
                node.InnerText = user.Camera;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Server");
                node.InnerText = user.Server;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Port");
                node.InnerText = user.Port;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Lang");
                node.InnerText = user.Lang;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Ver");
                node.InnerText = user.Ver;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/AutoStart");
                node.InnerText = user.AutoStart;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/MessageEnable");
                node.InnerText = user.MessageEnable;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/CallEnable");
                node.InnerText = user.CallEnable;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/MessageFilePath");
                node.InnerText = user.MessageFilePath;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/CallFileFilePath");
                node.InnerText = user.CallFileFilePath;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Available");
                node.InnerText = user.Available?"1":"0";

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Unavailable");
                node.InnerText = user.Unavailable ? "1" : "0";

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Busy");
                node.InnerText = user.Busy ? "1" : "0";

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/Voicemail");
                node.InnerText = user.Voicemail ? "1" : "0";

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/AvailableCallNumber");
                node.InnerText = user.AvailableCallNumber;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/UnavailableCallNumber");
                node.InnerText = user.UnavailableCallNumber ;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/BusyCallNumber");
                node.InnerText = user.BusyCallNumber;

                node = xmlDoc.SelectSingleNode(@"Content/UCUserInfo/VoicemailCallNumber");
                node.InnerText = user.VoicemailCallNumber ;
              
                xmlDoc.Save(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml");
                File.Delete(System.Windows.Forms.Application.StartupPath + "\\UserConfig.xml");
                EncryptDecrypt.EncryptUserConfigFile();
                File.Delete(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml");
            }
            catch (Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
    
    }
}
