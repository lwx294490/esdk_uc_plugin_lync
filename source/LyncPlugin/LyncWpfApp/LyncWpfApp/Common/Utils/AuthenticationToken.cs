using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Services.Protocols;

namespace LyncWpfApp
{
    [System.Xml.Serialization.XmlRootAttribute(Namespace = "", IsNullable = false)]
    public class AuthenticationToken : SoapHeader
    {
        private string _appId;
        public string appId
        {
            get
            {
                return this._appId;
            }
            set
            {
                this._appId = value;
            }
        }

        private string _pw;
        public string pw
        {
            get
            {
                return this._pw;
            }
            set
            {
                this._pw = value;
            }
        }
    }

}
