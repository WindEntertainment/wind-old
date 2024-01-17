#include "utils.h"
#include <openssl/evp.h>

namespace wind {
    namespace assets {
        asset_id getAssetIdByName(const std::string &str) {
            EVP_MD_CTX* mdctx;           
            unsigned char* md5_digest;
            unsigned int   md5_digest_len = EVP_MD_size(EVP_md5());
        
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

            EVP_DigestUpdate(mdctx, str.c_str(), str.size());

            md5_digest = (unsigned char *)OPENSSL_malloc(md5_digest_len);
            EVP_DigestFinal_ex(mdctx, md5_digest, &md5_digest_len);
            EVP_MD_CTX_free(mdctx);
            
            asset_id id = *((asset_id*)md5_digest);
            return id;
        }
    }
}