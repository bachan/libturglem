
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __TURGLEM_DEFAULT_ADAPTER_H__
#define __TURGLEM_DEFAULT_ADAPTER_H__

#include <MAFSA/adapter.h>

/*
 *  0 :  0
 *  9 :  9
 *  A : 10
 *  Z : 35
 * AA : 36
 * YA : 67
 *  - : 68
 *  _ : 69 (space)
 *  | : 70 (delimiter)
 *
 */

#define DEFAULT_LETTER_0       0
#define DEFAULT_LETTER_9       9
#define DEFAULT_LETTER_A      10
#define DEFAULT_LETTER_Z      35
#define DEFAULT_LETTER_AA     36
#define DEFAULT_LETTER_YA     67
#define DEFAULT_LETTER_DEFIS  68
#define DEFAULT_LETTER_SPACE  69
#define DEFAULT_LETTER_DELIM  70

#define DEFAULT_BUFFER_SIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

/* returns count of converted bytes */

size_t DEFAULT_conv_string_to_letter_utf8   (const char *s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_string_utf8   (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_string_to_letter_cp1251 (const char *s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_string_cp1251 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_string_to_letter_koi8r  (const char *s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_string_koi8r  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_string_to_letter_koi8u  (const char *s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_string_koi8u  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

/* if you don't like null-terminated strings */

size_t DEFAULT_conv_binary_to_letter_utf8   (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_binary_utf8   (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_binary_to_letter_cp1251 (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_binary_cp1251 (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_binary_to_letter_koi8r  (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_binary_koi8r  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

size_t DEFAULT_conv_binary_to_letter_koi8u  (const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l);
size_t DEFAULT_conv_letter_to_binary_koi8u  (const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_DEFAULT_ADAPTER_H__ */
