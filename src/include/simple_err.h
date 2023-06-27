#ifndef SIMPLE_ERR_H
#define SIMPLE_ERR_H

/** @file
 * This file defines a simple error class
 */

#include <debug.h>
#include <exception>
#include <cstdint>

/// _ADD_ERROR_INFORMATION_(error_code_name, error_code_value, error_code_text)
#define ADD_ERROR_INFORMATION_(code, val, info)    \
static const char * code##_ERR_TEXT = info;         \
const unsigned long int code##_CDX = val;

// add error information
ADD_ERROR_INFORMATION_(SUCCESS,                 0,  "Success")
ADD_ERROR_INFORMATION_(SOCKET_CREATION_FAILED,  1,  "Socket creation failed")
ADD_ERROR_INFORMATION_(ADDRESS_CONVERT_FAILED,  2,  "Convert socket")
ADD_ERROR_INFORMATION_(CONNECT_FAILED,          3,  "Connection failed")
ADD_ERROR_INFORMATION_(ERROR_IN_READ,           4,  "Error presented in read")
ADD_ERROR_INFORMATION_(ERROR_IN_WRITE,          5,  "Error presented in write")
ADD_ERROR_INFORMATION_(BIND_FAILED,             6,  "Bind failed")
ADD_ERROR_INFORMATION_(ACCEPT_FAILED,           7,  "Accept failed")
ADD_ERROR_INFORMATION_(LISTEN_FAILED,           8,  "Listen failed")

#undef ADD_ERROR_INFORMATION_


class simple_error_t : public std::exception
{
    trace_info_t _trace_info;
    uint64_t error_code;
    std::string what_str;

public:
    const trace_info_t & trace_info = _trace_info;

    explicit simple_error_t(uint64_t _error_code, const std::string& extra = "");
    const char * what();
    [[nodiscard]] uint64_t get_err_code() const { return error_code; }
};

#endif //SIMPLE_ERR_H
