using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LyncWpfApp
{
    public class AddInToolBarWiewModel
    {
        FrmToolBar toolbar;
        public  AddInToolBarWiewModel(FrmToolBar toolbar)
        {
            this.toolbar = toolbar;
        }
        public void startContextCall(List<string> selectedUserList)
        {
            if (null != selectedUserList && selectedUserList.Count>0)
            {
                MakeCallBusiness call = new MakeCallBusiness();
                StringBuilder str = new StringBuilder();
                string strContact ="";
                for (int index = 0; index < selectedUserList.Count; index++)
                {
                    str = new StringBuilder(selectedUserList[index]);
                    call.insertMember(0,str);
                    strContact+=(str+";");
                }
                if (call.startContextCall() == 0) //插件呼叫管理模块的发起上下文呼叫业务接口
                {
                    WinCall winCall = new WinCall(toolbar.Lync, SingletonObj.LoginInfo.LyncName + ";" + strContact.TrimEnd(';'));
                    winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                    winCall.Show();
                    winCall.Title = "Calling: " + str.ToString();
                    toolbar.Lync.winCall = winCall;
                }
                else
                {                    
                    DialogShow.Show(StringHelper.FindLanguageResource("startContextCallFailed"), StringHelper.FindLanguageResource("error"), 2);
                    return;
                }
            }
        }
    }
}
