#ifndef _XMLRPCUTIL_H_
#define _XMLRPCUTIL_H_
//
// XmlRpc++ Copyright (c) 2002-2003 by Chris Morley
//
#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif

#ifndef MAKEDEPEND
# include <string>

#if defined(_WINDOWS)
#else
#include <pthread.h>
#endif

#endif

#if defined(_MSC_VER)
# define snprintf	    _snprintf
# define vsnprintf    _vsnprintf
# define strcasecmp	  _stricmp
# define strncasecmp	_strnicmp
#elif defined(__BORLANDC__)
# define strcasecmp stricmp
# define strncasecmp strnicmp
#endif


#define XMLRPC_FAULTCODE_101    101 // 表示调用需要认证的方法,但未登录.
#define XMLRPC_FAULTCODE_102    102 // 表示调用过程未能成功,xmlrpc server目前不抛该异常.


namespace XmlRpc {

  //! Utilities for XML parsing, encoding, and decoding and message handlers.
  class XmlRpcUtil {
  public:
    // hokey xml parsing
    //! Returns contents between <tag> and </tag>, updates offset to char after </tag>
    static std::string parseTag(const char* tag, std::string const& xml, int* offset);

    //! Returns true if the tag is found and updates offset to the char after the tag
    static bool findTag(const char* tag, std::string const& xml, int* offset);

    //! Returns the next tag and updates offset to the char after the tag, or empty string
    //! if the next non-whitespace character is not '<'
    static std::string getNextTag(std::string const& xml, int* offset);

    //! Returns true if the tag is found at the specified offset (modulo any whitespace)
    //! and updates offset to the char after the tag
    static bool nextTagIs(const char* tag, std::string const& xml, int* offset);


    //! Convert raw text to encoded xml.
    static std::string xmlEncode(const std::string& raw);

    //! Convert encoded xml to raw text
    static std::string xmlDecode(const std::string& encoded);


    //! Dump messages somewhere
    static void log(int level, const char* fmt, ...);

    //! Dump error messages somewhere
    static void error(const char* fmt, ...);

#ifdef _WINDOWS
#else
    static int getLock(pthread_mutex_t *mutex);
    static int freeLock(pthread_mutex_t *mutex);
#endif

  };
} // namespace XmlRpc

#endif // _XMLRPCUTIL_H_
