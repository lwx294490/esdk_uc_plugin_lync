using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinHisitory.xaml
    /// </summary>
    public partial class WinHisitory : Window
    {
        double WinWidth = 700;
        double MarginRight = -350;
        int callIndex = -1;
        int confIndex = -1;
        WinHistoryViewModel model;
        WinLync Lync;
        public static bool isHave = false;
        public WinHisitory(WinLync Lync)
        {
            this.Lync = Lync;
            InitializeComponent();
            dateTimeFrom.SelectedDate = DateTime.Now.AddDays(-10);
            dateTimeTo.SelectedDate = DateTime.Now.AddDays(1);
            model = new WinHistoryViewModel(this);
            this.DataContext = model;
            WinLync.lyncCounter++;
            this.Closed += new EventHandler(WinHisitory_Closed);

            this.Title = StringHelper.FindLanguageResource("Hisitory");
            isHave = true;
        }

        void WinHisitory_Closed(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            isHave = false;
            Lync.toolBar.History = null;
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            tabItemCall.Margin = new Thickness(0, 0, MarginRight - e.NewSize.Width + WinWidth, 0);
        }

        private void tabControlCall_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int index = tabControlCall.SelectedIndex;
            if (callIndex != index)
            {
                callIndex = index;
                model.QueryHistory(index, "Call");

            }
        }

        private void tabControlHistory_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int index = tabControlHistory.SelectedIndex;
            if (index == 1 && confIndex == -1)
            {
                confIndex = index;
                model.QueryHistory(0, "Conference");
            }
            else if (index == 0)
            {
                if (confIndex == 1)
                {
                    callIndex = tabControlCall.SelectedIndex;
                    model.QueryHistory(callIndex, "Call");
                }

                confIndex = -1;
            }
        }

        private void imgFrist_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            txtPage.Text = "1";
            if (tabControlHistory.SelectedIndex == 0)
            {
                model.QueryHistoryByPage(tabControlCall.SelectedIndex, 0);
            }
            else
            {
                model.QueryConferenceHistory(Convert.ToInt32(txtPage.Text) - 1, true);
            }
        }

        private void imgPrev_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            int next = Convert.ToInt32(txtPage.Text) - 1;
            if (next == 0)
            {
                next++;
            }
            txtPage.Text = next.ToString();
            if (tabControlHistory.SelectedIndex == 0)
            {
                model.QueryHistoryByPage(tabControlCall.SelectedIndex, Convert.ToInt32(txtPage.Text) - 1);
            }
            else
            {
                model.QueryConferenceHistory(Convert.ToInt32(txtPage.Text) - 1, true);
            }
        }

        private void imgGo_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {

            if (tabControlHistory.SelectedIndex == 0)
            {
                model.QueryHistoryByPage(tabControlCall.SelectedIndex, Convert.ToInt32(txtPage.Text) - 1);
            }
            else
            {
                model.QueryConferenceHistory(Convert.ToInt32(txtPage.Text) - 1, true);
            }
        }

        private void imgNext_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            int next = Convert.ToInt32(txtPage.Text) + 1;
            if (next > (Convert.ToInt32(labTotal.Content.ToString().Substring(labTotal.Content.ToString().IndexOf('/') + 1))))
            {
                next--;
            }
            txtPage.Text = next.ToString();
            if (tabControlHistory.SelectedIndex == 0)
            {
                model.QueryHistoryByPage(tabControlCall.SelectedIndex, Convert.ToInt32(txtPage.Text) - 1);
            }
            else
            {
                model.QueryConferenceHistory(Convert.ToInt32(txtPage.Text) - 1, true);
            }
        }

        private void imgLast_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            txtPage.Text = (Convert.ToInt32(labTotal.Content.ToString().Substring(labTotal.Content.ToString().IndexOf('/') + 1))).ToString();
            if (tabControlHistory.SelectedIndex == 0)
            {
                model.QueryHistoryByPage(tabControlCall.SelectedIndex, Convert.ToInt32(txtPage.Text) - 1);
            }
            else
            {
                model.QueryConferenceHistory(Convert.ToInt32(txtPage.Text) - 1, true);
            }
        }
        private void txtNumber_KeyDown(object sender, KeyEventArgs e)
        {
            if (!((e.Key >= Key.D0 && e.Key <= Key.D9) || (e.Key >= Key.NumPad0 && e.Key <= Key.NumPad9)))  //之前是e.Key >= Key.NumPad1  e.Key >= Key.D1   2015/8/14
            {
                e.Handled = true;
            }
        }

        private void txtNumber_TextChanged(object sender, TextChangedEventArgs e)
        {
            var textBox = sender as TextBox;
            int total = Convert.ToInt32(labTotal.Content.ToString().Substring(labTotal.Content.ToString().IndexOf('/') + 1));
            string str = textBox.Text;
            if (str == "")
            {
                textBox.Text = "1";
            }
            if (this.IsValidPhoneNumber(str) == false)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Invalidnum"), StringHelper.FindLanguageResource("error"), 2);
                textBox.Text = "1";
                return;
            }          
            TextChange[] change = new TextChange[e.Changes.Count];
            e.Changes.CopyTo(change, 0);

            int offset = change[0].Offset;
            if (change[0].AddedLength > 0)
            {
                double num = 0;
                if (!Double.TryParse(textBox.Text, out num))
                {
                    textBox.Text = textBox.Text.Remove(offset, change[0].AddedLength);
                    textBox.Select(offset, 0);
                }
            }
            if (Convert.ToInt32(textBox.Text.Trim().Replace(" ", "")) > total)
            {
                textBox.Text = total.ToString();
            }
        }

        private void listConference_SelectedCellsChanged(object sender, SelectedCellsChangedEventArgs e)
        {
            int index = (sender as DataGrid).SelectedIndex;
            if (index > -1)
            {
                string _convID = (listConference.ItemsSource as List<ConferenceItem>)[index].ConvID;
                string initiator = (listConference.ItemsSource as List<ConferenceItem>)[index].Initiator;
                model.QueryHisConvPartByID(_convID, initiator);
            }
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (Lync.winCall != null)
            {
                DialogShow.Show(StringHelper.FindLanguageResource("Youareincallalready"), StringHelper.FindLanguageResource("error"), 2);  //不能同时发起两路通话
                return;
            }
            List<CallItem> list = new List<CallItem>();
            int index = -1;
            if (tabControlCall.SelectedIndex == 0)
            {
                list = listMissed.DataContext as List<CallItem>;
                index = listMissed.SelectedIndex;
            }
            else if (tabControlCall.SelectedIndex == 1)
            {
                list = listAnswered.DataContext as List<CallItem>;
                index = listAnswered.SelectedIndex;
            }
            else if (tabControlCall.SelectedIndex == 2)
            {
                list = listDialed.DataContext as List<CallItem>;
                index = listDialed.SelectedIndex;
            }
            else if (tabControlCall.SelectedIndex == 3)
            {
                list = listAll.DataContext as List<CallItem>;
                index = listAll.SelectedIndex;
            }

            if (index < 0)
            {
                return;
            }
            CallItem item = list[index];

            MakeCallBusiness call = new MakeCallBusiness();
            MemberType type;
            if (item.Phone.IndexOf("@") < 0)
            {
                type = MemberType.UC_IPPHONE;
            }
            else
            {
                type = MemberType.UC_ACCOUNT;
            }
            string str = "";
            if (item.Phone.IndexOf(":") != -1)
            {
                str = item.Phone.Substring(item.Phone.IndexOf(":") + 1);
            }
            else
            {
                str = item.Phone;
            }
            //2015/8/24    UNICODE  转码   UTF8 
            //byte[] buffer1 = Encoding.UTF8.GetBytes(str.Trim().Replace(" ",""));
            //byte[] buffer2 = Encoding.Convert(Encoding.Unicode, Encoding.UTF8, buffer1, 0, buffer1.Length);
            //string item1 = Encoding.UTF8.GetString(buffer2,0, buffer2.Length);
            //call.insertMember((int)type, new StringBuilder(item1));       
            call.insertMember((int)type, new StringBuilder(str));          
            if (call.startContextCall() == 0)
            {
                str = SingletonObj.LoginInfo.LyncName + ";" + str;
                Lync.winCall = new WinCall(Lync, str);
                Lync.winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                Lync.winCall.Show();
            }
            else
            {
                Dialog.Show(StringHelper.FindLanguageResource("startContextCallFailed"), StringHelper.FindLanguageResource("error"));
                return;   
            }
        }

        private void Grid_PreviewMouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            int index = (sender as DataGrid).SelectedIndex;
            if (index == -1)
            {
                switch ((sender as DataGrid).Name)
                {
                    case "listMissed":
                        listMissed.ContextMenu = null;
                        break;
                    case "listDialed":
                        listDialed.ContextMenu = null;
                        break;
                    case "listAnswered":
                        listAnswered.ContextMenu = null;
                        break;
                    case "listAll":
                        listAll.ContextMenu = null;
                        break;
                }
            }
            else
            {
                listMissed.ContextMenu = menuMissed;
                listDialed.ContextMenu = menuDialed;
                listAnswered.ContextMenu = menuAnswered;
                listAll.ContextMenu = menuAll;
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

        }

        /// <summary>
        /// 校验是否为纯数字
        /// werther the number is right or not 
        /// </summary>
        /// <param name="dialContent"></param>
        public bool IsValidPhoneNumber(string phoneNumber)
        {
            if (string.IsNullOrEmpty(phoneNumber))
            {
                return false;
            }

            phoneNumber = phoneNumber.Trim();

            foreach (char ch in phoneNumber)
            {
                if ((ch >= '0' && ch <= '9') || ch == '*' || ch == '#')
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }

            return true;
        }
    }
}
