#include "KlipperCXInterface.hpp"
#include "slic3r/Utils/Http.hpp"
#include <boost/log/trivial.hpp>
#include <curl/curl.h>
#include <exception>
#include <string>
#include "nlohmann/json_fwd.hpp"
#include "slic3r/GUI/GUI.hpp"
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/detail/md5.hpp>

namespace {
std::string build_gcode_upload_path(const std::string& local_file_path, const std::string& display_name)
{
    std::string normalized_name = display_name.empty() ? "unnamed" : display_name;
    if (boost::iends_with(normalized_name, ".gcode"))
        normalized_name.resize(normalized_name.size() - 6);

    const std::string content_md5 = Slic3r::GUI::get_file_md5(local_file_path);
    const std::string hash_input  = normalized_name + ":" + content_md5;

    using boost::uuids::detail::md5;
    md5              md5_hash;
    md5::digest_type md5_digest{};
    std::string      md5_digest_str;

    md5_hash.process_bytes(hash_input.data(), hash_input.size());
    md5_hash.get_digest(md5_digest);
    boost::algorithm::hex(md5_digest, md5_digest + std::size(md5_digest), std::back_inserter(md5_digest_str));

    return "model/slice/" + md5_digest_str + ".gcode.gz";
}
}

namespace RemotePrint {
KlipperCXInterface::KlipperCXInterface() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

KlipperCXInterface::~KlipperCXInterface() {
    curl_global_cleanup();
}
void KlipperCXInterface::cancelSendFileToDevice()
{
    m_upload_file.setCancel(true);
}
std::future<void> KlipperCXInterface::sendFileToDevice(const std::string& serverIp, int port, const std::string& uploadFileName, const std::string& localFilePath, std::function<void(float,double)> progressCallback, std::function<void(int)> uploadStatusCallback, std::function<void(std::string)> onCompleteCallback) {
    m_upload_file.setCancel(false);
    return std::async(std::launch::async, [=]() {
        try{
        m_upload_file.setProcessCallback(progressCallback);
            int nRet = m_upload_file.getAliyunInfo();
            if (nRet != 0)
            {
                uploadStatusCallback(1);
                return;
            }
                
            nRet = m_upload_file.getOssInfo();
            if (nRet != 0)
            {
                uploadStatusCallback(2);
                return;
            }

            std::string target_name = uploadFileName;
            if (boost::iends_with(uploadFileName, ".gcode")) {
                target_name = uploadFileName.substr(0, uploadFileName.size() - 6);
            }
                ;
            //std::string local_target_path = wxString(localFilePath).utf8_str().data();
            std::string target_path = build_gcode_upload_path(localFilePath, target_name);
            nRet                    = m_upload_file.uploadFileToAliyun(localFilePath, target_path, target_name);
            if (nRet != 0)
            {
                uploadStatusCallback(nRet);
                return;
            }

            
            nRet = m_upload_file.uploadGcodeToCXCloud(target_name, target_path, onCompleteCallback);
            uploadStatusCallback(nRet);
        }catch(Slic3r::GUI::ErrorCodeException& e){
            uploadStatusCallback(e.code());
        }catch(std::exception& e){
            uploadStatusCallback(1000);
        }
    });
}
}