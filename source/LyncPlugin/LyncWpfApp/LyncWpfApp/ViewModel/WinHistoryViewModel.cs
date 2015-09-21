using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Runtime.InteropServices;
using System.Data;

namespace LyncWpfApp
{
    public class WinHistoryViewModel
    {
        WinHisitory winHisitory;
        HistoryQueryBusiness query = new HistoryQueryBusiness();
        public ICommand RefreshCommand { get; set; }
        public ICommand ClearCommand { get; set; }
        int count = 100;    //modify by 00327190  2015/7/13  本来是200条一页
        public WinHistoryViewModel(WinHisitory window)
        {
            winHisitory = window;
            RefreshCommand = new DelegateCommand(RefreshCommandProcess);
            ClearCommand = new DelegateCommand(ClearCommandProcess);

        }
        void RefreshCommandProcess()
        {
            if (winHisitory.tabControlHistory.SelectedIndex ==0)//call
            {
                QueryCallHistory(winHisitory.tabControlCall.SelectedIndex,true);
            }
            else
            {
                QueryConferenceHistory(0, true);
            }
        }
        void ClearCommandProcess()
        {
            if (winHisitory.tabControlHistory.SelectedIndex == 0)
            {
                query.ClearCallHistroy((CallHistoryType)winHisitory.tabControlCall.SelectedIndex);
                QueryCallHistory(winHisitory.tabControlCall.SelectedIndex);
            }
            else
            {
                query.ClearConvHistroy();
                QueryConferenceHistory(0, true);
            }
        }
        public void QueryHistory(int index, string type)
        {
            if (type =="Call")
            {
                QueryCallHistory(index);
            }
            else
            {
                QueryConferenceHistory(index);
            }
        }
        void QueryCallHistory(int index,bool refresh = false)
        {
            QueryHistoryByPage(index,0);         
        }
        public void QueryHistoryByPage(int index, int page)
        {
            int iSizeSTCallHistroyData = Marshal.SizeOf(typeof(STCallHistroyData));
            int iSizeSTCallHistroyItem = Marshal.SizeOf(typeof(STCallHistroyItem));
            int uiBufSize = (iSizeSTCallHistroyData + iSizeSTCallHistroyItem * (count - 1));
            byte[] pCallHistory = new byte[uiBufSize];

            DataTable dt = new DataTable();           
            dt.Columns.Add("Phone");
            dt.Columns.Add("Name");
            dt.Columns.Add("Time");
            dt.Columns.Add("Duration");
            dt.Columns.Add("TelType");         


            List<CallItem> list = new List<CallItem>();
            UCServiceRetvCode iRet = (UCServiceRetvCode)query.QueryCallHistory((CallHistoryType)index, page * count, page * count + count - 1, pCallHistory, uiBufSize);
            if (UCServiceRetvCode.UC_SDK_Success == iRet)
            {
                IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTCallHistroyData);
                byte[] tempInfoByte = new byte[iSizeSTCallHistroyData];

                Marshal.Copy(pCallHistory, 0, tempInfoIntPtr, (int)iSizeSTCallHistroyData);
                STCallHistroyData head = (STCallHistroyData)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STCallHistroyData));

                winHisitory.labTotal.Content = "/" + ((head.iTotal % count) == 0 ? (head.iTotal / count == 0 ? 1 : head.iTotal / count).ToString() : (head.iTotal / count + 1).ToString());
                winHisitory.txtPage.Text = (page + 1).ToString();
                int second = 0;
                for (int i = -1; i < head.iTotal - 1 && i < head.iTo-head.iFrom; i++)
                {
                    Marshal.Copy(pCallHistory, iSizeSTCallHistroyData + iSizeSTCallHistroyItem * i, tempInfoIntPtr, (int)iSizeSTCallHistroyItem);
                    STCallHistroyItem item = (STCallHistroyItem)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STCallHistroyItem));

                    CallItem callItem = new CallItem();
                    //2015/8/24    UTF8 转码UNICODE
                    //byte[] buffer1 = Encoding.Default.GetBytes(item.CallName);
                    //byte[] buffer2 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer1, 0, buffer1.Length);
                    //string item1= Encoding.Default.GetString(buffer2, 0, buffer2.Length);
                    //callItem.Name = item1;
                    //byte[] buffer3 = Encoding.Default.GetBytes(item.CallNum);
                    //byte[] buffer4 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer3, 0, buffer3.Length);
                    //string item2 = Encoding.Default.GetString(buffer4, 0, buffer4.Length);
                    //callItem.Phone = item2;
                    //
                    callItem.Phone = item.CallNum;
                    callItem.Name = item.CallName;
                    DateTime dtTime = DateTime.Parse(item.startTime.year.ToString() + "-" + item.startTime.month + "-" + item.startTime.day
                                    + " " + item.startTime.hour + ":" + item.startTime.minute + ":" + item.startTime.second);
                    callItem.Time = dtTime.ToString("yyyy-MM-dd HH:mm:ss");
                    second=Convert.ToInt32(item.duration);
                    callItem.Duration = (second == -1 ? "00:00:00" : DateTime.Today.AddSeconds(second).ToString("HH:mm:ss"));
                    callItem.TelType = (CallHistoryType)item.callType;

                    list.Add(callItem);
                }
                Marshal.Release(tempInfoIntPtr);
            }
            else
            {
                winHisitory.labTotal.Content = "/1";
                winHisitory.txtPage.Text = "1";
            }

            switch ((CallHistoryType)index)
            {
                case CallHistoryType.HISTORY_CALL_ALL:
                    winHisitory.listAll.DataContext = null;
                    winHisitory.listAll.DataContext = list;                 
                    break;
                case CallHistoryType.HISTORY_CALL_ANSWERED:
                    winHisitory.listAnswered.DataContext = null;
                    winHisitory.listAnswered.DataContext = list;                    
                    break;
                case CallHistoryType.HISTORY_CALL_DIALED:
                    winHisitory.listDialed.DataContext = null;
                    winHisitory.listDialed.DataContext = list;                   
                    break;
                case CallHistoryType.HISTORY_CALL_MISSED:
                    winHisitory.listMissed.DataContext = null;
                    winHisitory.listMissed.DataContext = list;                    
                    break;
            }
        }
        public void QueryConferenceHistory(int page, bool refresh = false)
        {
         
            List<ConferenceItem> list = new List<ConferenceItem>();
            int iSizeSTConvHistroyData = Marshal.SizeOf(typeof(STConvHistroyData));
            int iSizeSTConvHistroyItem = Marshal.SizeOf(typeof(STConvHistroyItem));
            int uiBufSize = (iSizeSTConvHistroyData + iSizeSTConvHistroyItem * (count - 1));
            byte[] pCallHistory = new byte[uiBufSize];

            UCServiceRetvCode iRet = (UCServiceRetvCode)query.QueryConvHistory(page * count, (page + 1) * count - 1, pCallHistory, uiBufSize);
            if (UCServiceRetvCode.UC_SDK_Success == iRet)
            {
                IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTConvHistroyData);
                byte[] tempInfoByte = new byte[iSizeSTConvHistroyData];

                Marshal.Copy(pCallHistory, 0, tempInfoIntPtr, (int)iSizeSTConvHistroyData);
                STConvHistroyData head = (STConvHistroyData)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STConvHistroyData));

                winHisitory.labTotal.Content = "/" + ((head.iTotal % count) == 0 ? (head.iTotal / count == 0 ? 1 : head.iTotal / count).ToString() : (head.iTotal / count + 1).ToString());
                winHisitory.txtPage.Text = (page + 1).ToString();
                int second = 0;
                for (int i = -1; i < head.iTotal - 1 && i < head.iTo - head.iFrom; i++)
                {
                    Marshal.Copy(pCallHistory, iSizeSTConvHistroyData + iSizeSTConvHistroyItem * i, tempInfoIntPtr, (int)iSizeSTConvHistroyItem);
                    STConvHistroyItem item = (STConvHistroyItem)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STConvHistroyItem));

                    ConferenceItem it = new ConferenceItem();
                    //2015/8/24    UTF8 转码UNICODE
                    //byte[] buffer1 = Encoding.Default.GetBytes(item.compereName);
                    //byte[] buffer2 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer1, 0, buffer1.Length);
                    //string item1 = Encoding.Default.GetString(buffer2, 0, buffer2.Length);
                    //it.Initiator = item1;
                    it.Initiator = item.compereName;

                    DateTime dt = DateTime.Parse(item.startTime.year.ToString() + "-" + item.startTime.month + "-" + item.startTime.day
                                    + " " + item.startTime.hour + ":" + item.startTime.minute + ":" + item.startTime.second);
                    it.StartTime = dt.ToString("yyyy-MM-dd HH:mm:ss");
                    second = Convert.ToInt32(item.duration);
                    it.Duration = (second == -1 ? "00:00:00" : DateTime.Today.AddSeconds(second).ToString("HH:mm:ss"));
                    it.ConvID = item.convID;

                    list.Add(it);
                }

                winHisitory.listConference.ItemsSource = null;
                winHisitory.listConference.ItemsSource = list;
                Marshal.Release(tempInfoIntPtr);
            }
            else
            {
                winHisitory.labTotal.Content = "/1";
                winHisitory.txtPage.Text = "1";
            }
            if (list.Count > 0)
            {
                string _convID = list[0].ConvID;
                string initiator = list[0].Initiator;
                QueryHisConvPartByID(_convID, initiator);
            }
            else
            {
                winHisitory.listParticipants.ItemsSource = null;
            }
        }
       public void QueryHisConvPartByID(string _convID,string initiator)
       {
           List<ParticipantItem> list = new List<ParticipantItem>();
           int iSizeSTConfPartData = Marshal.SizeOf(typeof(STConfPartData));
           int iSizeSTConfPartItem = Marshal.SizeOf(typeof(STConfPartItem));
           int uiBufSize = (iSizeSTConfPartData + iSizeSTConfPartItem * (count - 1));
           byte[] pCallHistory = new byte[uiBufSize];

           UCServiceRetvCode iRet = (UCServiceRetvCode)query.QueryHisConvPartByID(_convID, 0, count - 1, pCallHistory, uiBufSize);
           if (UCServiceRetvCode.UC_SDK_Success == iRet)
           {
               IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTConfPartData);
               byte[] tempInfoByte = new byte[iSizeSTConfPartData];

               Marshal.Copy(pCallHistory, 0, tempInfoIntPtr, (int)iSizeSTConfPartData);
               STConfPartData head = (STConfPartData)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STConfPartData));
               ParticipantItem it;
               if (head.partNum > count)
               {
                   uiBufSize = (iSizeSTConfPartData + iSizeSTConfPartItem * (head.partNum - 1));
                   pCallHistory = new byte[uiBufSize];
                   query.QueryHisConvPartByID(_convID, 0, head.partNum - 1, pCallHistory, uiBufSize);
               }
               it = new ParticipantItem();
               it.Initiator = initiator;
               it.IsMain = true;
               list.Add(it);
               for (int i = -1; i < head.partNum - 1; i++)
               {
                   Marshal.Copy(pCallHistory, iSizeSTConfPartData + iSizeSTConfPartItem * i, tempInfoIntPtr, (int)iSizeSTConfPartItem);
                   STConfPartItem item = (STConfPartItem)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STConfPartItem));
                   //2015/8/24    UTF8 转码UNICODE
                   //byte[] buffer1 = Encoding.Default.GetBytes(item.partName);
                   //byte[] buffer2 = Encoding.Convert(Encoding.UTF8, Encoding.Default, buffer1, 0, buffer1.Length);
                   //string item1 = Encoding.Default.GetString(buffer2, 0, buffer2.Length);
                   //2015/8/24    UTF8 转码UNICODE
                   it = new ParticipantItem();
                   //it.Initiator = item1;
                   it.Initiator = item.partName;
                   it.IsMain = false;
                   list.Add(it);
               }
               Marshal.Release(tempInfoIntPtr);
           }
           winHisitory.listParticipants.ItemsSource = null;
           winHisitory.listParticipants.ItemsSource = list;
       }
    }
}
