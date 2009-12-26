
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __TURGLEM_ENGLISH_ADAPTER_H__
#define __TURGLEM_ENGLISH_ADAPTER_H__

#include <MAFSA/adapter.h>

/*
 *  A :  0
 *  Z : 25
 *  - : 26
 *  ' : 27
 *  | : 28 (delimiter)
 *
 */

#define ENGLISH_LETTER_A            0
#define ENGLISH_LETTER_Z           25
#define ENGLISH_LETTER_DEFIS       26
#define ENGLISH_LETTER_APOSTROPHE  27
#define ENGLISH_LETTER_DELIM       28

#define ENGLISH_BUFFER_SIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

/* returns count of converted bytes */

size_t ENGLISH_conv_string_to_letter_utf8 (const char *s, MAFSA_letter *l, size_t sz_l);
size_t ENGLISH_conv_letter_to_string_utf8 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

/* if you don't like null-terminated strings */

size_t ENGLISH_conv_binary_to_letter_utf8 (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t ENGLISH_conv_letter_to_binary_utf8 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_ENGLISH_ADAPTER_H__ */
