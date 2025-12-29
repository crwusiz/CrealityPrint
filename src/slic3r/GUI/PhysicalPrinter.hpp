#ifndef slic3r_PhysicalPrinter_hpp_
#define slic3r_PhysicalPrinter_hpp_

#include "libslic3r/Preset.hpp"
using namespace std;

namespace Slic3r { 
namespace GUI {

class PhysicalPrinter
{

public:
    PhysicalPrinter(const string& hostType,const string& hostUrl,const string& apiKey, const bool& ignoreCertRevocation);
    ~PhysicalPrinter() {};

    bool TestConnection(string& info);
    PrintHostType getPrintHostType(const string& input); 

private:
    string m_hostType;
    string m_hostUrl;
    string m_apiKey;
    DynamicPrintConfig* m_config{nullptr};
       
};

} 
} 


#endif