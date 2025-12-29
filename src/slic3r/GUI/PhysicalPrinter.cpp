#include "PhysicalPrinter.hpp"

#include "GUI_App.hpp"
#include "slic3r/Utils/PrintHost.hpp"

namespace Slic3r { namespace GUI {

std::map<std::string, PrintHostType> keys_map_PrintHostType
{
    {"htPrusaLink", htPrusaLink},   
    {"htPrusaConnect", htPrusaConnect},
    {"htOctoPrint", htOctoPrint},   
    {"htDuet", htDuet},
    {"htFlashAir", htFlashAir},     
    {"htAstroBox", htAstroBox},
    {"htRepetier", htRepetier},     
    {"htMKS", htMKS},
    {"htESP3D", htESP3D},           
    {"htObico", htObico},
    {"htFlashforge", htFlashforge}, 
    {"htSimplyPrint", htSimplyPrint}
    //{"htCrealityPrint", htCrealityPrint}

};

PhysicalPrinter::PhysicalPrinter(const string& hostType,const string& hostUrl,const string& apiKey, const bool& ignoreCertRevocation) 
{ 
    this->m_hostType = hostType;
    this->m_hostUrl  = hostUrl;
    this->m_apiKey = apiKey; 
    m_config  = &wxGetApp().preset_bundle->printers.get_edited_preset().config;
    m_config->set_key_value("host_type", new ConfigOptionEnum<PrintHostType>(getPrintHostType(hostType)));
    m_config->opt_string("printhost_apikey") = apiKey;
    m_config->opt_string("print_host")       = hostUrl;
    m_config->set_key_value("printhost_ssl_ignore_revoke",new ConfigOptionBool(ignoreCertRevocation));

}

bool PhysicalPrinter::TestConnection(string& info)
{
    if (!this->m_config) return false;
    std::unique_ptr<PrintHost> host(PrintHost::get_print_host(this->m_config));
    if (!host) {
        return false;
    }

    wxString msg;
    bool     result = host->test(msg);
    if (result) 
    {
        info = (host->get_test_ok_msg()).ToUTF8();
    } 
    else 
    {
        info = (host->get_test_failed_msg(msg)).ToUTF8();
    }

    return result;
}

PrintHostType PhysicalPrinter::getPrintHostType(const string& input)
{ 
/*    auto it = keys_map_PrintHostType.find(input); 
    if (it != keys_map_PrintHostType.end()) 
    {
        return it->second;
    }
    return htCrealityPrint;*/ // CrealityPrint

    return htOctoPrint;
}




}} // namespace Slic3r::GUI