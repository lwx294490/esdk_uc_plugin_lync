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
    /// Interaction logic for WinDail.xaml
    /// </summary>
    public partial class WinDail : Window
    {
        WinLync Lync;
        public WinDail(WinLync Lync)
        {
            InitializeComponent();
            this.Lync = Lync;
            this.Closed += new EventHandler(WinDail_Closed);
            WinLync.lyncCounter++;
            imgNum1.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum1.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum2.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum2.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum3.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum3.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum4.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum4.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum5.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum5.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum6.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum6.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum7.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum7.MouseLeave += new MouseEventHandler(img_MouseLeave);

            imgNum8.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum8.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum9.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum9.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNum0.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNum0.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNumS.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNumS.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgNumX.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgNumX.MouseLeave += new MouseEventHandler(img_MouseLeave);

            imgCall.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgCall.MouseLeave += new MouseEventHandler(img_MouseLeave);
            imgBack.MouseEnter += new MouseEventHandler(img_MouseEnter);
            imgBack.MouseLeave += new MouseEventHandler(img_MouseLeave);

            this.Title = StringHelper.FindLanguageResource("Keypad");
            this.txtNumber.Focus();
        }

        void img_MouseLeave(object sender, MouseEventArgs e)
        {
            Image img = sender as Image;
            string str = img.Source.ToString();
            if (img.Tag.ToString() == "call" || img.Tag.ToString() == "back")
            {
                img.Source = new BitmapImage(new Uri(str.Substring(0, str.LastIndexOf("_")) + "_1.png", UriKind.RelativeOrAbsolute));
            }
            else
            {
                img.Source = new BitmapImage(new Uri(str.Substring(0, str.LastIndexOf("/")) + "/2.png", UriKind.RelativeOrAbsolute));
            }
        }

        void img_MouseEnter(object sender, MouseEventArgs e)
        {
            Image img = sender as Image;
            string str = img.Source.ToString();
            if (img.Tag.ToString() == "call" || img.Tag.ToString() == "back")
            {
                img.Source = new BitmapImage(new Uri(str.Substring(0, str.LastIndexOf("_")) + "_2.png", UriKind.RelativeOrAbsolute));
            }
            else
            {
                img.Source = new BitmapImage(new Uri(str.Substring(0, str.LastIndexOf("/")) + "/1.png", UriKind.RelativeOrAbsolute));
            }
        }

        void WinDail_Closed(object sender, EventArgs e)
        {
            WinLync.lyncCounter--;
            Lync.winDial = null;
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            Image img = ((sender as Button).Content as StackPanel).Children[0] as Image;
            if (img.Tag.ToString() == "call")
            {
                if (txtNumber.Text.ToString()=="")
                {
                    return;
                }
                if (Lync.winCall!=null)
                {
                    this.Close();
                    Dialog.Show(StringHelper.FindLanguageResource("TwoCallsSameTime"), StringHelper.FindLanguageResource("error"));
                    return;
                }
                //拨号              
                MakeCallBusiness call = new MakeCallBusiness();
                StringBuilder ucName = new StringBuilder(100);
                call.GetUCAccount(txtNumber.Text.ToString(), ucName);
                string str = null;

                if (ucName.ToString()=="")
                {
                    str = txtNumber.Text.ToString();
                    call.insertMember((int)MemberType.UC_IPPHONE, new StringBuilder(str));
                }
                else
                {
                    str = ucName + StringHelper.GetLyncDomainString(SingletonObj.LoginInfo.LyncName);
                    call.insertMember((int)MemberType.UC_ACCOUNT, ucName);
                }

                if (call.startContextCall() == 0)   //modify by 00327190  2015/6/18 只要返回值不为0，就不能执行以下操作
                {
                    this.Close();

                    WinCall winCall = new WinCall(Lync, SingletonObj.LoginInfo.LyncName + ";" + str.ToString());
                    winCall.callType = CallHistoryType.HISTORY_CALL_DIALED;
                    winCall.Show();
                    Lync.winCall = winCall;
                }
                else
                {
                    this.Close();
                    DialogShow.Show(StringHelper.FindLanguageResource("startContextCallFailed"), StringHelper.FindLanguageResource("error"), 2);
                    return;
                }
            }
            else if (img.Tag.ToString() == "back")
            {
                if (txtNumber.Text.Length > 0)
                {
                    txtNumber.Text = txtNumber.Text.Substring(0, txtNumber.Text.Length - 1);
                }
            }
            else
            {
                txtNumber.Text = txtNumber.Text + img.Tag.ToString();
                txtNumber.Focus();
                txtNumber.Select(txtNumber.Text.Length, 0);
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
                string str = textBox.Text.Replace("*", "").Replace("#", "");
                if (!Double.TryParse(str, out num) && str!="")
                {
                    textBox.Text = textBox.Text.Remove(offset, change[0].AddedLength);
                    textBox.Select(offset, 0);
                }
                txtNumber.ToolTip = textBox.Text;
            }
        }

      
      
    }
}
