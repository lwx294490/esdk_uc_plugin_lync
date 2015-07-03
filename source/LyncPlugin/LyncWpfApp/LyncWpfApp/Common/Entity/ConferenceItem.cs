using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace LyncWpfApp
{
    [Serializable]
    [XmlRoot("ConferenceItem")]
    public class ConferenceItem
    {
        [XmlElement("Initiator")]
        public virtual string Initiator { get; set; }

        [XmlElement("StartTime")]
        public virtual string StartTime { get; set; }

        [XmlElement("Duration")]
        public virtual string Duration { get; set; }

        [XmlElement("ConvID")]
        public virtual string ConvID { get; set; }
    }
}
