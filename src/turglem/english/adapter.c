
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <stdio.h>
#include <turglem/english/adapter.h>

size_t ENGLISH_conv_string_to_letter_utf8(const char *s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    size_t pos = 0;
    while (*i && pos < sz_l)
    {
        if (*i == '\'')
        {
            l[pos] = ENGLISH_LETTER_APOSTROPHE;
        }
        else
        if (*i == '-')
        {
            l[pos] = ENGLISH_LETTER_DEFIS;
        }
        else
        {
            if (*i >= 'A' && *i <= 'Z')
            {
                l[pos] = *i - 'A';
            }
            else
            if (*i >= 'a' && *i <= 'z')
            {
                l[pos] = *i - 'a';
            }
            else
            {
                break;
            }
        }
        i++;
        pos++;
    }
    return pos;
}

size_t ENGLISH_conv_binary_to_letter_utf8(const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    const u_char *e = i + sz_s;
    size_t pos = 0;
    while (pos < sz_l && i < e)
    {
        if (*i == '\'')
        {
            l[pos] = ENGLISH_LETTER_APOSTROPHE;
        }
        else
        if (*i == '-')
        {
            l[pos] = ENGLISH_LETTER_DEFIS;
        }
        else
        {
            if (*i >= 'A' && *i <= 'Z')
            {
                l[pos] = *i - 'A';
            }
            else
            if (*i >= 'a' && *i <= 'z')
            {
                l[pos] = *i - 'a';
            }
            else
            {
                break;
            }
        }
        i++;
        pos++;
    }
    return pos;
}

size_t ENGLISH_conv_letter_to_string_utf8(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos + 1 < sz_s && pos < sz_l)
    {
        switch (l[pos])
        {
            case ENGLISH_LETTER_DEFIS:
                s[pos] = '-';
                break;
            case ENGLISH_LETTER_APOSTROPHE:
                s[pos] = '\'';
                break;
            case ENGLISH_LETTER_DELIM:
                s[pos] = '|';
                break;
            default:
                s[pos] = 'A' + l[pos];
                break;
        }
        pos++;
    }
    s[pos] = 0;
    return pos;
}

size_t ENGLISH_conv_letter_to_binary_utf8(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos < sz_s && pos < sz_l)
    {
        switch (l[pos])
        {
            case ENGLISH_LETTER_DEFIS:
                s[pos] = '-';
                break;
            case ENGLISH_LETTER_APOSTROPHE:
                s[pos] = '\'';
                break;
            case ENGLISH_LETTER_DELIM:
                s[pos] = '|';
                break;
            default:
                s[pos] = 'A' + l[pos];
                break;
        }
        pos++;
    }
    return pos;
}

