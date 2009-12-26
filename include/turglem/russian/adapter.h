
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __TURGLEM_RUSSIAN_ADAPTER_H__
#define __TURGLEM_RUSSIAN_ADAPTER_H__

#include <MAFSA/adapter.h>

/*
 *  A :  0
 * YA : 31 (no YO)
 *  - : 32
 *  | : 33 (delimiter)
 *
 */

#define RUSSIAN_LETTER_A       0
#define RUSSIAN_LETTER_YA     31
#define RUSSIAN_LETTER_DEFIS  32
#define RUSSIAN_LETTER_DELIM  33

#define RUSSIAN_BUFFER_SIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

/* returns count of converted bytes */

size_t RUSSIAN_conv_string_to_letter_utf8   (const char *s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_string_utf8   (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_string_to_letter_cp1251 (const char *s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_string_cp1251 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_string_to_letter_koi8r  (const char *s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_string_koi8r  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_string_to_letter_koi8u  (const char *s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_string_koi8u  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

/* if you don't like null-terminated strings */

size_t RUSSIAN_conv_binary_to_letter_utf8   (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_binary_utf8   (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_binary_to_letter_cp1251 (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_binary_cp1251 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_binary_to_letter_koi8r  (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_binary_koi8r  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t RUSSIAN_conv_binary_to_letter_koi8u  (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t RUSSIAN_conv_letter_to_binary_koi8u  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_RUSSIAN_ADAPTER_H__ */
