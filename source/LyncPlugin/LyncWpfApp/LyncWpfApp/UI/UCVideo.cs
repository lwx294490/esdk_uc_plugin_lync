using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LyncWpfApp
{
    public partial class UCVideo : UserControl
    {
        public TextBox Local
        {
            get { return local; }
        }
        public TextBox Remote
        {
            get { return remote; }
        }
        public UCVideo()
        {
            InitializeComponent();
        }
    }
}
