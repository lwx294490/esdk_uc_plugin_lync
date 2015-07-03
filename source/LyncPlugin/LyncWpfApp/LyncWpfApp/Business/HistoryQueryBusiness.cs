using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    public class HistoryQueryBusiness
    {
        public int QueryCallHistory(CallHistoryType _callType, int _fromIndex, int _toIndex, byte[] _result, int _size)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_QueryCallHistory"));
                int iRet = UCInterface.UC_SDK_QueryCallHistory(_callType, _fromIndex, _toIndex, _result, _size);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_QueryCallHistory error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_QueryCallHistory"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
        public int ClearCallHistroy(CallHistoryType _callType)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_ClearCallHistroy"));
                int iRet = UCInterface.UC_SDK_ClearCallHistroy((int)_callType);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_ClearCallHistroy error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_ClearCallHistroy"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }

        }
        public int InsertCallHistory(CallHistoryType _CallType, string _url, string _name, int _duration)
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InsertCallHistory"));
                int iRet = UCInterface.UC_SDK_InsertCallHistory((int)_CallType, _url, _name, _duration);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_InsertCallHistory error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_InsertCallHistory"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }

        public int QueryConvHistory(int _fromIndex, int _toIndex, byte[] _result, int _size)//查询会议历史记录
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_QueryConvHistory"));
                int iRet = UCInterface.UC_SDK_QueryConvHistory(_fromIndex, _toIndex, _result, _size);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_QueryConvHistory error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_QueryConvHistory"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
        public int QueryHisConvPartByID(string _convID, int _fromIndex, int _toIndex, byte[] _result, int _size)//查询一条会议历史记录的参与者
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_QueryHisConvPartByID"));
                int iRet = UCInterface.UC_SDK_QueryHisConvPartByID(_convID, _fromIndex, _toIndex, _result, _size);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_QueryHisConvPartByID error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_QueryHisConvPartByID"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
        public int ClearConvHistroy()//清除会议历史记录
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_ClearConvHistroy"));
                int iRet = UCInterface.UC_SDK_ClearConvHistroy();
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_ClearConvHistroy error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_ClearConvHistroy"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
        public int InsertConvHistory(string _leaderAccount, string _leaderName, int _duration, StringBuilder _historyID)//插入会议历史记录
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InsertConvHistory"));
                int iRet = UCInterface.UC_SDK_InsertConvHistory(_leaderAccount, _leaderName, _duration, _historyID);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_InsertConvHistory error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_InsertConvHistory"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
        public int InsertConvHistoryPart(string _historyID, string _partAccount, string _partName)//插入会议历史记录的与会人
        {
            try
            {
                LogManager.SystemLog.Debug(string.Format("Start UC_SDK_InsertConvHistoryPart"));
                int iRet = UCInterface.UC_SDK_InsertConvHistoryPart(_historyID, _partAccount, _partName);
                if (iRet != 0)
                {
                    LogManager.SystemLog.Error(string.Format("Start UC_SDK_InsertConvHistoryPart error {0}", iRet));
                    return iRet;
                }
                LogManager.SystemLog.Debug(string.Format("End UC_SDK_InsertConvHistoryPart"));
                return iRet;
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
                return -1;
            }
        }
    }
}
