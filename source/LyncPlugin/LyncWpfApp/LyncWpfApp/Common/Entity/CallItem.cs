using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace LyncWpfApp
{
     [Serializable]
     [XmlRoot("CallItem")]
    public class CallItem
    {
         [XmlElement("TelType")]
         public virtual CallHistoryType TelType { get; set; }

         [XmlElement("TelTypeImage")]
         public virtual string TelTypeImage
         {
             get
             {
                 if (TelType == CallHistoryType.HISTORY_CALL_ANSWERED)
                 {
                     return @"/Image/call/callIn.bmp";
                 }
                 else if (TelType == CallHistoryType.HISTORY_CALL_DIALED)
                 {
                     return @"/Image/call/callOut.bmp";
                 }
                 else if (TelType == CallHistoryType.HISTORY_CALL_MISSED)
                 {
                     return @"/Image/call/callMissed.bmp";
                 }
                 else
                 {
                     return @"";
                 }
             }
         }
         [XmlElement("Phone")]
         public virtual string Phone { get; set; }

         [XmlElement("Name")]
         public virtual string Name { get; set; }

         [XmlElement("Time")]
         public virtual string Time { get; set; }

         [XmlElement("Duration")]
         public virtual string Duration { get; set; }
    }
}
