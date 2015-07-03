using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    public class SoapFWDService//SOAP接口
    {
        ESGVoiceFWDNumberbinding eSGVoiceFWD = new ESGVoiceFWDNumberbinding(UtilsSettings.URL);//语音业务设置接口

        /// <summary>
        /// 呼叫前转业务设置，包括无条件前转、遇忙前转、无应答前转、离线前转
        /// </summary>
        /// <param name="userNumber"></param>
        /// <param name="fwdType"></param>
        /// <param name="fwdNumber"></param>
        public void SetFWDService(string userNumber, string fwdType, string fwdNumber)//UC用户号码前转设置
        {
            try
            {
                eSGVoiceFWD.Header = UtilsSettings.Header;
                int i = 0;
                eSGVoiceFWD.setFWDService(userNumber, fwdType, fwdNumber, out i);
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
        }
        /// <summary>
        /// 取消uc用户设置的前转号码
        /// </summary>
        /// <param name="userNumber"></param>
        /// <param name="fwdType"></param>
        /// <param name="fwdNumber"></param>
        public void UnSetFWDService(string userNumber, string fwdType)//取消uc用户设置的前转号码
        {
            eSGVoiceFWD.Header = UtilsSettings.Header;
            int i = 0;
            eSGVoiceFWD.unsetFWDService(userNumber, fwdType,out i);
        }
        /// <summary>
        /// 查询uc用户设置的前转号码
        /// </summary>
        /// <param name="userNumber"></param>
        /// <param name="fwdType"></param>
        /// <param name="fwdNumber"></param>
        public void QueryFWDService(string userNumber, out ESGVoiceFWDNumberInfo[] info)//取消uc用户设置的前转号码
        {
            eSGVoiceFWD.Header = UtilsSettings.Header;
            int i = 0;
            eSGVoiceFWD.queryFWDService(userNumber,out info, out i);
        }
    }
}
