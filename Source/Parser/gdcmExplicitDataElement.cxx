#include "gdcmExplicitDataElement.h"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream &_os, const ExplicitDataElement &_val)
{
  return _val.Write(_os);
}

DICOMOStream& ExplicitDataElement::Write(DICOMOStream &_os) const
{
  //const DataElement &de = 
  //_os << de;
  _os.Write(VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    _os.Write(ValueLengthField);
    }
  else if( VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    assert( ValueLengthField != 0xFFFFFFFF );
    _os.Write(ValueLengthField);
    }
  else
    {
    uint16_t vl = ValueLengthField;
    // Write Value Length (16bits)
    _os.Write(vl);
    }
  // We have the length we should be able to write the value
  _os.Write(ValueField);
  return _os;
}

//-----------------------------------------------------------------------------
//DICOMIStream& operator>>(DICOMIStream &_os, ExplicitDataElement &_val)
//{
//  return _os.Read(_val);
//}


} // end namespace gdcm
