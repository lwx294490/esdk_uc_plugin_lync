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
using System.Windows.Interop;

namespace LyncWpfApp
{
    /// <summary>
    /// Interaction logic for WinSlide.xaml
    /// </summary>
    public partial class WinSlide : Window
    {
        WinCall call;
        string type;
        public WinSlide(WinCall call,string type)
        {
            InitializeComponent();
            this.type = type;
            this.call = call;
            this.Loaded += new RoutedEventHandler(WinSlide_Loaded);
        }

        void WinSlide_Loaded(object sender, RoutedEventArgs e)
        {
            this.slider.ValueChanged += new RoutedPropertyChangedEventHandler<double>(slider_ValueChanged);
        }

        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            call.model.Slider_ValueChanged((int)e.NewValue*10, type);
            slider.SelectionEnd = e.NewValue;
        }

        private void Window_MouseLeave(object sender, MouseEventArgs e)
        {
            this.Hide();
        }
    }
}
