
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __TURGLEM_ENGLISH_ADAPTER_HPP__
#define __TURGLEM_ENGLISH_ADAPTER_HPP__

#include <string>
#include <turglem/lemmatizer.hpp>
#include <turglem/english/adapter.h>

struct english_utf8_adapter
{
    enum { max_letter = ENGLISH_LETTER_DELIM };

    static MAFSA::l_string string2letters(const char *s)
    {
        MAFSA_letter arr [ENGLISH_BUFFER_SIZE];
        size_t arr_sz = ENGLISH_conv_string_to_letter_utf8(s, arr, ENGLISH_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2string(const MAFSA_letter *s, size_t sz)
    {
        char arr [ENGLISH_BUFFER_SIZE];
        size_t arr_sz = ENGLISH_conv_letter_to_string_utf8(s, sz, arr, ENGLISH_BUFFER_SIZE);
        return std::string (arr, arr_sz);
    }
    static MAFSA::l_string binary2letters(const char *s, size_t sz)
    {
        MAFSA_letter arr [ENGLISH_BUFFER_SIZE];
        size_t arr_sz = ENGLISH_conv_binary_to_letter_utf8(s, sz, arr, ENGLISH_BUFFER_SIZE);
        return MAFSA::l_string (arr, arr_sz);
    }
    static std::string letters2binary(const MAFSA_letter *s, size_t sz)
    {
        char arr [ENGLISH_BUFFER_SIZE];
        size_t arr_sz = ENGLISH_conv_letter_to_binary_utf8(s, sz, arr, ENGLISH_BUFFER_SIZE);    
        return std::string (arr, arr_sz);
    }
};

#endif /* __TURGLEM_ENGLISH_ADAPTER_HPP__ */
