using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    /// <summary>
    /// 操作日志管理类
    /// </summary>
    public class LogManager
    {
        /// <summary>
        /// 系统操作日志
        /// </summary>
        public static log4net.ILog SystemLog
        {
            get
            {
                return log4net.LogManager.GetLogger("System");
            }
        }      
    }
}
