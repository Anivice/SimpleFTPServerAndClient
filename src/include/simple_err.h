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
ADD_ERROR_INFORMATION_(SUCCESS, 0, "Success")

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
