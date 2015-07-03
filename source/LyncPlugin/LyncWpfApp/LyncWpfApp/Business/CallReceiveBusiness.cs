using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
   public  class CallReceiveBusiness
    {
       public int AnswerCall()//该函数用于接听呼叫
       {
           try
           {             
               LogManager.SystemLog.Debug(string.Format("Start UC_SDK_AcceptCall"));
               int iRet = UCInterface.UC_SDK_AcceptCall();
               if (iRet != 0)
               {
                   LogManager.SystemLog.Error(string.Format("Start UC_SDK_AcceptCall error {0}", iRet));
                   return iRet;
               }
               LogManager.SystemLog.Debug(string.Format("End UC_SDK_AcceptCall"));
               return iRet;
           }
           catch (Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
               return -1;
           }
       }
       public int RejectCall()//该函数用于拒绝呼叫
       {
           try
           {
               LogManager.SystemLog.Debug(string.Format("Start UC_SDK_RejectCall"));
               int iRet = UCInterface.UC_SDK_RejectCall();
               if (iRet != 0)
               {
                   LogManager.SystemLog.Error(string.Format("Start UC_SDK_RejectCall error {0}", iRet));
                   return iRet;
               }
               LogManager.SystemLog.Debug(string.Format("End UC_SDK_RejectCall"));
               return iRet;
           }
           catch (Exception ex)
           {
               LogManager.SystemLog.Error(ex.ToString());
               return -1;
           }
       }
    }
}
