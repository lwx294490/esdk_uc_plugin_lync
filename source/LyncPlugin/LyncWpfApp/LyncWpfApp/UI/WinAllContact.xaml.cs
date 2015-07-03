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
using Microsoft.Lync.Model;
using Microsoft.Lync.Model.Group;
using System.Data;
using System.Runtime.InteropServices;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinAllContact.xaml
    /// </summary>
    public partial class WinAllContact : Window
    {
        DataTable dtSource;
        DataTable dtContact = new DataTable();
        DataTable dtSelectedContact = new DataTable();
        public Action<DataTable> AddContactChanged;
        WinLync lync;
        WinCall winCall;
        bool isBlindTransCall = false;

         /// <summary>
         /// 获取前两百条数据
         /// </summary>
         /// <param name="strSearchKey">查询关键字</param>
        void GetAllLyncContacts(string strSearchKey = "",int page=0)
        {
            dtContact = new DataTable();
            dtContact.Columns.Add("Name");            
            dtContact.Columns.Add("Url");
            dtContact.Columns.Add("Phone");

            if (dtSelectedContact.Columns.Count == 0)
            {
                dtSelectedContact.Columns.Add("Name");               
                dtSelectedContact.Columns.Add("Url");
                dtSelectedContact.Columns.Add("Phone");
            }

            MakeCallBusiness call = new MakeCallBusiness();

            int maxCount = 200;//最多查询的数量
            int count = 100;//每次查询的数量
            int iSizeSTContactList = Marshal.SizeOf(typeof(STContactList));
            int iSizeSTContact = Marshal.SizeOf(typeof(STContact));
            int uiBufSize = (iSizeSTContactList + iSizeSTContact * (count - 1));
            byte[] pSTContactList = new byte[uiBufSize];

            UCServiceRetvCode iRet = (UCServiceRetvCode)call.GetEntContactList(strSearchKey, page * count, page * count+count - 1, pSTContactList);
            if (UCServiceRetvCode.UC_SDK_Success == iRet)
            {
                string strLyncURI = StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);                
                IntPtr tempInfoIntPtr = Marshal.AllocHGlobal((int)iSizeSTContactList);                
                byte[] tempInfoByte = new byte[iSizeSTContactList];
                try
                {
                    Marshal.Copy(pSTContactList, 0, tempInfoIntPtr, (int)iSizeSTContactList);
                    STContactList head = (STContactList)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STContactList));
                    this.labTotal.Content = "/" + ((head.iTotal % count) == 0 ? (head.iTotal / count == 0 ? 1 : head.iTotal / count).ToString() : (head.iTotal / count + 1).ToString());
                    this.txtPage.Text = (page + 1).ToString();

                    for (int index = -1; index < head.iTotal - 1 && index < count - 1; index++)
                    {
                        Marshal.Copy(pSTContactList, iSizeSTContactList + iSizeSTContact * index, tempInfoIntPtr, (int)iSizeSTContact);
                        STContact item = (STContact)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STContact));
                        dtContact.Rows.Add(item.name_, string.IsNullOrEmpty(item.uri_) ? "" : item.uri_ + strLyncURI, item.mobile_);                     
                    }                    
                    if (head.iTotal > count)//继续查询
                    {
                        //最多查询maxCount条数据
                        if (head.iTotal < maxCount)
                        {
                            maxCount = head.iTotal;
                        }
                        int num = maxCount % count != 0 ? (maxCount / count + 1) : maxCount / count;//需要查询的次数

                        for (int iNum = 1; iNum < num;iNum++ )
                        {
                            iRet = (UCServiceRetvCode)call.GetEntContactList(strSearchKey, iNum * count, iNum * count + count - 1, pSTContactList);
                            if (UCServiceRetvCode.UC_SDK_Success == iRet)
                            {
                                Marshal.Copy(pSTContactList, 0, tempInfoIntPtr, (int)iSizeSTContactList);
                                head = (STContactList)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STContactList));

                                for (int index = -1; index < (maxCount - iNum * count - 1) && index < count - 1; index++)
                                {
                                    Marshal.Copy(pSTContactList, iSizeSTContactList + iSizeSTContact * index, tempInfoIntPtr, (int)iSizeSTContact);
                                    STContact item = (STContact)Marshal.PtrToStructure(tempInfoIntPtr, typeof(STContact));                                   
                                    dtContact.Rows.Add(item.name_, string.IsNullOrEmpty(item.uri_) ? "" : item.uri_ + strLyncURI, item.mobile_);
                                    
                                }
                            }
                            else
                            {
                                LogManager.SystemLog.Error("GetAllLyncContacts failed");
                                break;
                            }
                        }
                    }
                }
                finally
                {
                    Marshal.Release(tempInfoIntPtr);
                }
                
            }
            else
            {
                LogManager.SystemLog.Error("GetAllLyncContacts failed");
            }

            #region 根据lync接口查询lync用户的联系人列表
            //foreach (Microsoft.Lync.Model.Group.Group group in WinLync.LyncContactGroups)
            //{
            //    foreach (Contact contact in (ContactCollection)(group))
            //    {
            //        int index = -1;
            //        foreach (DataRow dr in dtContact.Rows)
            //        {
            //            if (dr["Url"].ToString() == contact.Uri)
            //            {
            //                index = 0;
            //            }
            //        }
            //        if (index == -1)
            //        {
            //            string phone = "";
            //            List<object> list = contact.GetContactInformation(ContactInformationType.ContactEndpoints) as List<object>;
            //            foreach (object point in list)
            //            {
            //                if (((Microsoft.Lync.Model.ContactEndpoint)point).Type == ContactEndpointType.WorkPhone)
            //                {
            //                    phone = ((Microsoft.Lync.Model.ContactEndpoint)point).DisplayName;
            //                }
            //            }
            //           string name = contact.GetContactInformation(ContactInformationType.DisplayName).ToString();                       
            //           dtContact.Rows.Add(name, contact.Uri, phone);                     

            //        }
            //    }
            //}
            #endregion
        }

        public WinAllContact(WinLync lync, bool isBlindTransCall = false)
        {
            InitializeComponent();
            this.isBlindTransCall = isBlindTransCall;

            //是查询两百条数据
            GetAllLyncContacts("",0);
            try
            {
                for (int i = 0; i < dtContact.Rows.Count; i++)//对数据按名称进行排序
                {
                    string iName = dtContact.Rows[i][0].ToString();
                    for (int j = i + 1; j < dtContact.Rows.Count; j++)
                    {
                        string jName = dtContact.Rows[j][0].ToString();
                        if (iName.CompareTo(jName) == 1)
                        {
                            object[] temp = new object[3];
                            temp = dtContact.Rows[j].ItemArray;
                            dtContact.Rows[j].ItemArray= dtContact.Rows[i].ItemArray;
                            dtContact.Rows[i].ItemArray = temp;
                            iName = jName;
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                LogManager.SystemLog.Error(ex.ToString());
            }
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;
            WinLync.lyncCounter++;
            this.lync = lync;
            this.Closed += new EventHandler(WinAllContact_Closed);
            this.txtInput.Focus();//是输入文本获取焦点
        }

        void WinAllContact_Closed(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            lync.winAllContact = null;
        }

        private void tabControl1_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (listContact.SelectedIndex<0)
            {
                return;
            }

            foreach (DataRow d in dtSelectedContact.Rows)
            {
                if (d["Url"].ToString() == dtContact.Rows[listContact.SelectedIndex][1].ToString())
                {
                    return;
                }
            }
            DataRow dr = dtSelectedContact.NewRow();
            dr[0] = dtContact.Rows[listContact.SelectedIndex][0];
            dr[1] = dtContact.Rows[listContact.SelectedIndex][1];
            dr[2] = dtContact.Rows[listContact.SelectedIndex][2];

            //if (dr[1].ToString().IndexOf("sip")<0)
            //{
            //    dr[2] = dr[0];
            //    dr[0] = "";
            //    dr[1] = "";
            //}
            dtSelectedContact.Rows.Add(dr);
            listSelectedContact.DataContext = null;
            listSelectedContact.DataContext = dtSelectedContact;
            listSelectedContact.ScrollIntoView(listSelectedContact.Items[dtSelectedContact.Rows.Count - 1], listSelectedContact.Columns[0]);

            //是否是盲转窗体
            if (isBlindTransCall)
            {
                btnOK_Click(null, null);
            }
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            if (txtNumber.Text.ToString() == "")
            {
                return;
            }
            else
            {
                boolnum(txtNumber.Text.ToString());
            }
            if (boolnum(txtNumber.Text.ToString()) == true)
            {
                //modify by jinyeqing  00327190  2015/6/10  添加号码时先看是否是UC用户，如果是按照UC帐号添加，不是就按话机号码添加 
                MakeCallBusiness call = new MakeCallBusiness();
                StringBuilder ucName = new StringBuilder(100);
                if (call.GetUCAccountByPhoneNo(txtNumber.Text.ToString(), ucName) != "" && call.GetUCAccountByPhoneNo(txtNumber.Text.ToString(), ucName) != null)
                {
                    foreach (DataRow d in dtSelectedContact.Rows)
                    {
                        if (d["Phone"].ToString() == txtNumber.Text.ToString())
                        {
                            return;
                        }
                    }
                    DataRow dr = dtSelectedContact.NewRow();
                    string str = txtNumber.Text.ToString();
                    int page=0;
                    GetAllLyncContacts(str, page);
                    dtSource = dtContact.Copy();
                    string strLyncURI = StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                    string name = "";
                    for (int i = 0; i < dtSource.Rows.Count; i++)
                    {
                        if (dtSource.Rows[i]["URL"].ToString().Trim() == call.GetUCAccountByPhoneNo(txtNumber.Text.ToString(), ucName) + strLyncURI)
                        {
                            name = dtSource.Rows[i]["NAME"].ToString().Trim();
                        }
                    }
                    dr[0] = name;                  
                    dr[1] = call.GetUCAccountByPhoneNo(txtNumber.Text.ToString(), ucName) + strLyncURI;
                    dr[2] = txtNumber.Text.ToString();
                    dtSelectedContact.Rows.Add(dr);
                    listSelectedContact.DataContext = null;
                    listSelectedContact.DataContext = dtSelectedContact;
                    listSelectedContact.ScrollIntoView(listSelectedContact.Items[dtSelectedContact.Rows.Count - 1], listSelectedContact.Columns[0]);

                    txtName.Text = "";
                    txtNumber.Text = "";
                }
                //之前没有if ，只有中间的循环体部分
                else
                {
                    foreach (DataRow d in dtSelectedContact.Rows)
                    {
                        if (d["Phone"].ToString() == txtNumber.Text.ToString())
                        {
                            return;
                        }
                    }
                    DataRow dr = dtSelectedContact.NewRow();
                    dr[0] = txtName.Text.ToString();
                    dr[2] = txtNumber.Text.ToString();
                    dtSelectedContact.Rows.Add(dr);
                    listSelectedContact.DataContext = null;
                    listSelectedContact.DataContext = dtSelectedContact;
                    listSelectedContact.ScrollIntoView(listSelectedContact.Items[dtSelectedContact.Rows.Count - 1], listSelectedContact.Columns[0]);

                    txtName.Text = "";
                    txtNumber.Text = "";
                }

                //是否是盲转窗体
                if (isBlindTransCall)
                {
                    btnOK_Click(null, null);
                }
            }
            else
            {               
                //DialogShow.Show(message, StringHelper.FindLanguageResource("error"), 2);
                winCall.OpenDialogTiming("notnum", "error", 2);
                return;
            }
        }
        private bool boolnum(string temp)
        {
            for (int i = 0; i < temp.Length; i++)
            {
                byte tempByte = Convert.ToByte(temp[i]);
                if ((tempByte < 48) || (tempByte > 57))
                {
                    return false;
                }
            }
            return true;
        }

        private void btnDelete_Click(object sender, RoutedEventArgs e)
        {
            if (listSelectedContact.SelectedIndex > -1)
            {
                dtSelectedContact.Rows.RemoveAt(listSelectedContact.SelectedIndex);
                listSelectedContact.DataContext = null;
                listSelectedContact.DataContext = dtSelectedContact;
            }
        }

        private void btnCancle_Click(object sender, RoutedEventArgs e)
        {
            listSelectedContact.DataContext = null;
            this.Close();
        }

        private void btnOK_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            if (AddContactChanged != null)
            {
                AddContactChanged(dtSelectedContact);
            }
        }

        private void txtNumber_KeyDown(object sender, KeyEventArgs e)
        {
            if (!((e.Key >= Key.D0 && e.Key <= Key.D9) || (e.Key >= Key.NumPad0 && e.Key <= Key.NumPad9)))
            {
                e.Handled = true;
            }
        }

        private void txtNumber_TextChanged(object sender, TextChangedEventArgs e)
        {
            var textBox = sender as TextBox;
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
        }

        /// <summary>
        /// 关键字查询
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnQuery_Click(object sender, RoutedEventArgs e)
        {
            string str = txtInput.Text.ToString();
            int page = 0;
            GetAllLyncContacts(str,page);

            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;
        }

        private void imgFrist_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            txtPage.Text = "1";
            string str = txtInput.Text.ToString();
            GetAllLyncContacts(str, Convert.ToInt32(txtPage.Text) - 1);
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;

        }

        private void imgPrev_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            int next = Convert.ToInt32(txtPage.Text) - 1;
            if (next == 0)
            {
                next++;
            }
            txtPage.Text = next.ToString();
            string str = txtInput.Text.ToString();
            GetAllLyncContacts(str, Convert.ToInt32(txtPage.Text) - 1);
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;

        }

        private void imgGo_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            string str = txtInput.Text.ToString();
            GetAllLyncContacts(str, Convert.ToInt32(txtPage.Text) - 1);
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;
        }

        private void imgNext_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            string str = txtInput.Text.ToString();
            int next = Convert.ToInt32(txtPage.Text) + 1;
            if (next > (Convert.ToInt32(labTotal.Content.ToString().Substring(labTotal.Content.ToString().IndexOf('/') + 1))))
            {
                next--;
            }
            txtPage.Text = next.ToString();

            GetAllLyncContacts(str,Convert.ToInt32(txtPage.Text) - 1);
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;
        }




        private void imgLast_MouseLeftButtonUp(object sender, RoutedEventArgs e)
        {
            string str = txtInput.Text.ToString();
            txtPage.Text = (Convert.ToInt32(labTotal.Content.ToString().Substring(labTotal.Content.ToString().IndexOf('/') + 1))).ToString();
            GetAllLyncContacts(str, Convert.ToInt32(txtPage.Text) - 1);
            dtSource = dtContact.Copy();
            this.listContact.DataContext = dtContact;

        }
    }
}
