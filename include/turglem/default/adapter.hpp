
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __TURGLEM_DEFAULT_ADAPTER_HPP__
#define __TURGLEM_DEFAULT_ADAPTER_HPP__

#include <string>
#include <turglem/lemmatizer.hpp>
#include <turglem/default/adapter.h>

struct default_utf8_adapter
{
    enum { max_letter = DEFAULT_LETTER_DELIM };

    static MAFSA::l_string string2letters(const char *s)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_string_to_letter_utf8(s, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2string(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_string_utf8(s, sz, arr, DEFAULT_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
    static MAFSA::l_string binary2letters(const char *s, size_t sz)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_binary_to_letter_utf8(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2binary(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_binary_utf8(s, sz, arr, DEFAULT_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
};

struct default_cp1251_adapter
{
    enum { max_letter = DEFAULT_LETTER_DELIM };

    static MAFSA::l_string string2letters(const char *s)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_string_to_letter_cp1251(s, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2string(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_string_cp1251(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return std::string (arr, arr_sz);
    }
    static MAFSA::l_string binary2letters(const char *s, size_t sz)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_binary_to_letter_cp1251(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2binary(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_binary_cp1251(s, sz, arr, DEFAULT_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
};

struct default_koi8r_adapter
{
    enum { max_letter = DEFAULT_LETTER_DELIM };

    static MAFSA::l_string string2letters(const char *s)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_string_to_letter_koi8r(s, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2string(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_string_koi8r(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return std::string (arr, arr_sz);
    }
    static MAFSA::l_string binary2letters(const char *s, size_t sz)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_binary_to_letter_koi8r(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2binary(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_binary_koi8r(s, sz, arr, DEFAULT_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
};

struct default_koi8u_adapter
{
    enum { max_letter = DEFAULT_LETTER_DELIM };

    static MAFSA::l_string string2letters(const char *s)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_string_to_letter_koi8u(s, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2string(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_string_koi8u(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return std::string (arr, arr_sz);
    }
    static MAFSA::l_string binary2letters(const char *s, size_t sz)
    {
        MAFSA_letter arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_binary_to_letter_koi8u(s, sz, arr, DEFAULT_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2binary(const MAFSA_letter *s, size_t sz)
    {
        char arr [DEFAULT_BUFFER_SIZE];
        size_t arr_sz = DEFAULT_conv_letter_to_binary_koi8u(s, sz, arr, DEFAULT_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
};

#endif /* __TURGLEM_DEFAULT_ADAPTER_HPP__ */
