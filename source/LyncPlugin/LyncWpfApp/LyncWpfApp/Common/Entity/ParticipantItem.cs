using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace LyncWpfApp
{
    [Serializable]
    [XmlRoot("ConferenceItem")]
    public class ParticipantItem
    {
        [XmlElement("Initiator")]
        public virtual string Initiator { get; set; }

        [XmlElement("IsMain")]
        public virtual bool IsMain { get; set; }

        [XmlElement("MainImage")]
        public virtual string MainImage
        {
            get
            {
                if (IsMain == true)
                {
                    return @"/Image/call/compere.png";
                }
                else
                {
                    return @"";
                }
            }
        }
    }
}
