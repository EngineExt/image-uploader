#ifndef IU_CORE_SETTINGS_ENCODEDPASSWORD_H
#define IU_CORE_SETTINGS_ENCODEDPASSWORD_H

#pragma once

#include <string>
#ifdef IU_WTL
#include "atlheaders.h"
#endif

class CEncodedPassword {
public:
    CEncodedPassword();
    CEncodedPassword(const std::string& d);
    std::string toEncodedData() const;
    void fromPlainText(const std::string& data)
    {
        data_ = data;
    }
    void fromEncodedData(const std::string& data)
    {
        DecodeString(data, data_);
    }
#ifdef IU_WTL
    void fromPlainText(CString& data)
    {
        data_ = IuCoreUtils::WstringToUtf8((LPCTSTR)data);
    }
    operator CString()
    {
        return IuCoreUtils::Utf8ToWstring(data_).c_str();
    }
    /*operator LPCTSTR() {
        return IuCoreUtils::Utf8ToWstring(data_).c_str();
    }*/
    CEncodedPassword& operator=(const CString& text);
#endif
    operator std::string&() {
        return data_;
    }
    //operator const TCHAR*();
   

    static void DecodeString(const std::string& encodedString, std::string & Result, const char* code = "{DAb[]=_T('')+b/16;H3N SHJ");
    static void EncodeString(const std::string& plainText, std::string& Result, const char* code = "{DAb[]=_T('')+b/16;H3N SHJ");
private:
    std::string data_;
};

#endif
