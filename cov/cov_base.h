#ifndef COV_BASE_H
#define COV_BASE_H

#ifdef __cplusplus // C++ codes
#include <string>
#include <memory>
#include <cstdint>
#include <map>

typedef struct CovData {
    //std::string PCaddress;
    //std::string function;
    std::string line;
    uint64_t hitCount;
} CovData;

class CovBase 
{
public:
    CovBase();
    ~CovBase();
    bool insertCovDesc(const char pcDesc[]);
private:
    std::map<std::string, std::map<std::string, CovData>> m_covDataMap; // file-> { line -> covData }
};
static std::unique_ptr<CovBase> g_CovBase = std::make_unique<CovBase>();

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((no_sanitize("no_profile_instrument_function")))
void c_insert_code_pc_desc(const char pcDesc[]);

#ifdef __cplusplus
}
#endif



#endif /* COV_BASE_H */