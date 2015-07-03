using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media.Imaging;
using System.Windows.Controls;

namespace LyncWpfApp
{
    public class UpdateImage
    {
        static public void UpdateData(Image img, string filePath)
        {
            string path = System.Windows.Forms.Application.StartupPath;
            string pathImage = path.Substring(0, path.IndexOf("bin"));
            BitmapImage imagetemp = new BitmapImage(new Uri(filePath, UriKind.Relative));
            img.Source = imagetemp;
               
            

        }
    }
}
