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
    /// Interaction logic for FrmToolBar.xaml
    /// </summary>
    public partial class FrmToolBar : Window
    {
        public FrmToolBar()
        {
            InitializeComponent();
            this.Background = new SolidColorBrush(Color.FromRgb(230,233,239));
        }

        private void startAudioCallButton_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }

        private void startVideoCallButton_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {

        }
    }
}
