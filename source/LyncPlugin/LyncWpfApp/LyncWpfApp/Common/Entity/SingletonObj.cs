using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    public class SingletonObj
    { 
        /// <summary>
        /// 用户登陆后携带的信息
        /// 用户登陆成功后初始化此对象
        /// </summary>
        public static UCUserInfo LoginInfo
        {
            get;
            set;
        }
    }
}
