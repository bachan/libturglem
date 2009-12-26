
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <turglem/default/adapter.h>

#define DELIMITER_STRING "~!?@#$%^&*()_.-+=/|\\<>:;"

#define DTRAPEZNIKOV_UKR 1

#define TOGGLE_UKR if (!ukr)  \
{                             \
    ukr = 1;                  \
    if (NULL != ret_i)        \
    {                         \
        i = ret_i;            \
        pos = ret_pos;        \
        continue;             \
    }                         \
}

#define CHANGE_LETTER(newcode) TOGGLE_UKR;  \
    l[pos] = (u_char) (newcode);

#define I_OR_E(code, ukr_code) if(ukr)  \
{                                       \
    l[pos] = (u_char) (ukr_code);       \
}                                       \
else                                    \
{                                       \
    l[pos] = (u_char) (code);           \
    if (NULL == ret_i)                  \
    {                                   \
        ret_i = i;                      \
        ret_pos = pos;                  \
    }                                   \
}

/* cp1251 */

size_t DEFAULT_conv_string_to_letter_cp1251(const char *s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (*i && pos < sz_l)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
#if (DTRAPEZNIKOV_UKR)
        if (*i == 0xA5 || *i == 0xB4)  /* dtrapeznikov ukr: Ґ, ґ */
        {
            CHANGE_LETTER(39);
        }
        else
        if (*i == 0xAA || *i == 0xBA)  /* dtrapeznikov ukr: Є, є */
        {
            CHANGE_LETTER(41);
        }
        else
        if (*i == 0xAF || *i == 0xBF)  /* dtrapeznikov ukr: Ї, ї */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xB2 || *i == 0xB3)  /* dtrapeznikov ukr: І, і */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0x92)  /* dtrapeznikov ukr: ’ */
        {
            CHANGE_LETTER(26 + 36);
        }
        else
        if (*i == 0xC5 || *i == 0xE5)  /* dtrapeznikov ukr: Е, е */
        {
            I_OR_E(41, 29 + 36);
        }
        else
        if (*i == 0xC8 || *i == 0xE8)  /* dtrapeznikov ukr: И. и */
        {
            I_OR_E(44, 27 + 36);
        }
        else
#endif
        if (*i >= 0xC0)
        {
            l[pos] = ((*i - 0xC0) % 0x20) + 36;
        }
        else
        if (*i == 0xA8 || *i == 0xB8)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_binary_to_letter_cp1251(const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    const u_char *e = i + sz_s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (pos < sz_l && i < e)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
#if (DTRAPEZNIKOV_UKR)
        if (*i == 0xA5 || *i == 0xB4)  /* dtrapeznikov ukr: Ґ, ґ */
        {
            CHANGE_LETTER(39);
        }
        else
        if (*i == 0xAA || *i == 0xBA)  /* dtrapeznikov ukr: Є, є */
        {
            CHANGE_LETTER(41);
        }
        else
        if (*i == 0xAF || *i == 0xBF)  /* dtrapeznikov ukr: Ї, ї */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xB2 || *i == 0xB3)  /* dtrapeznikov ukr: І, і */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0x92)  /* dtrapeznikov ukr: ’ */
        {
            CHANGE_LETTER(26 + 36);
        }
        else
        if (*i == 0xC5 || *i == 0xE5)  /* dtrapeznikov ukr: Е, е */
        {
            I_OR_E(41, 29 + 36);
        }
        else
        if (*i == 0xC8 || *i == 0xE8)  /* dtrapeznikov ukr: И. и */
        {
            I_OR_E(44, 27 + 36);
        }
        else
#endif
        if (*i >= 0xC0)
        {
            l[pos] = ((*i - 0xC0) % 0x20) + 36;
        }
        else
        if (*i == 0xA8 || *i == 0xB8)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_letter_to_string_cp1251(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos + 1 < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = l[pos] + 0xC0 - 36;
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    s[pos] = 0;
    return pos;
}

size_t DEFAULT_conv_letter_to_binary_cp1251(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = l[pos] + 0xC0 - 36;
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    return pos;
}

/* koi8r, koi8u */

static uint8_t koi8_string2letters [] = {
    30,  0,  1, 22,  4,  5, 20,  3, 21,  8,  9, 10, 11, 12, 13, 14,
    15, 31, 16, 17, 18, 19,  6,  2, 28, 27,  7, 24, 29, 25, 23, 26
};

static uint8_t koi8_letters2string [] = {
    0xE1, 0xE2, 0xF7, 0xE7, 0xE4, 0xE5, 0xF6, 0xFA, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0,
    0xF2, 0xF3, 0xF4, 0xF5, 0xE6, 0xE8, 0xE3, 0xFE, 0xFB, 0xFD, 0xFF, 0xF9, 0xF8, 0xFC, 0xE0, 0xF1,
    0x2D, 0x7C
};

size_t DEFAULT_conv_string_to_letter_koi8r(const char *s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    size_t pos = 0;
    while (*i && pos < sz_l)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
        if (*i >= 0xC0)
        {
            l[pos] = koi8_string2letters[(*i - 0xC0) % 0x20] + 36;
        }
        else
        if (*i == 0xA3 || *i == 0xB3)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_binary_to_letter_koi8r(const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    const u_char *e = i + sz_s;
    size_t pos = 0;
    while (pos < sz_l && i < e)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
        if (*i >= 0xC0)
        {
            l[pos] = koi8_string2letters[(*i - 0xC0) % 0x20] + 36;
        }
        else
        if (*i == 0xA3 || *i == 0xB3)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_letter_to_string_koi8r(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos + 1 < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = koi8_letters2string[l[pos] - 36];
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    s[pos] = 0;
    return pos;
}

size_t DEFAULT_conv_letter_to_binary_koi8r(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = koi8_letters2string[l[pos] - 36];
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    return pos;
}

size_t DEFAULT_conv_string_to_letter_koi8u(const char *s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (*i && pos < sz_l)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
#if (DTRAPEZNIKOV_UKR)
        if (*i == 0xBD || *i == 0xAD)  /* dtrapeznikov ukr: Ґ, ґ */
        {
            CHANGE_LETTER(39);
        }
        else
        if (*i == 0xB4 || *i == 0xA4)  /* dtrapeznikov ukr: Є, є */
        {
            CHANGE_LETTER(41);
        }
        else
        if (*i == 0xB7 || *i == 0xA7)  /* dtrapeznikov ukr: Ї, ї */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xB6 || *i == 0xA6)  /* dtrapeznikov ukr: І, і */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xC5 || *i == 0xE5)  /* dtrapeznikov ukr: Е, е */
        {
            I_OR_E(41, 29 + 36);
        }
        else
        if (*i == 0xC9 || *i == 0xE9)  /* dtrapeznikov ukr: И, и */
        {
            I_OR_E(44, 27 + 36);
        }
        else
#endif
        if (*i >= 0xC0)
        {
            l[pos] = koi8_string2letters[(*i - 0xC0) % 0x20] + 36;
        }
        else
        if (*i == 0xA3 || *i == 0xB3)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_binary_to_letter_koi8u(const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l)
{
    const u_char *i = (const u_char *) s;
    const u_char *e = i + sz_s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (pos < sz_l && i < e)
    {
        if (*i >= '0' && *i <= '9')
        {
            l[pos] = *i - '0';
        }
        else
        if (*i >= 'a' && *i <= 'z')
        {
            l[pos] = *i - 'a' + 10;
        }
        else
        if (*i >= 'A' && *i <= 'Z')
        {
            l[pos] = *i - 'A' + 10;
        }
        else
#if (DTRAPEZNIKOV_UKR)
        if (*i == 0xBD || *i == 0xAD)  /* dtrapeznikov ukr: Ґ, ґ */
        {
            CHANGE_LETTER(39);
        }
        else
        if (*i == 0xB4 || *i == 0xA4)  /* dtrapeznikov ukr: Є, є */
        {
            CHANGE_LETTER(41);
        }
        else
        if (*i == 0xB7 || *i == 0xA7)  /* dtrapeznikov ukr: Ї, ї */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xB6 || *i == 0xA6)  /* dtrapeznikov ukr: І, і */
        {
            CHANGE_LETTER(44);
        }
        else
        if (*i == 0xC5 || *i == 0xE5)  /* dtrapeznikov ukr: Е, е */
        {
            I_OR_E(41, 29 + 36);
        }
        else
        if (*i == 0xC9 || *i == 0xE9)  /* dtrapeznikov ukr: И, и */
        {
            I_OR_E(44, 27 + 36);
        }
        else
#endif
        if (*i >= 0xC0)
        {
            l[pos] = koi8_string2letters[(*i - 0xC0) % 0x20] + 36;
        }
        else
        if (*i == 0xA3 || *i == 0xB3)
        {
            l[pos] = 41;
        }
        else
        {
            if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
            {
                i++;
                continue;
            }

            l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
        }
        i++;
        pos++;
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_letter_to_string_koi8u(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos + 1 < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = koi8_letters2string[l[pos] - 36];
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    s[pos] = 0;
    return pos;
}

size_t DEFAULT_conv_letter_to_binary_koi8u(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    size_t pos = 0;
    while (pos < sz_s && pos < sz_l)
    {
        if (l[pos] < 10)
        {
            s[pos] = l[pos] + '0';
        }
        else
        if (l[pos] < 36)
        {
            s[pos] = l[pos] + 'A' - 10;
        }
        else
        if (l[pos] < 68)
        {
            s[pos] = koi8_letters2string[l[pos] - 36];
        }
        else
        if (l[pos] == 68)
        {
            s[pos] = '-';
        }
        else
        if (l[pos] == 69)
        {
            s[pos] = ' ';
        }
        else
        {
            s[pos] = '|';
        }
        pos++;
    }
    return pos;
}

/* utf8 */

size_t DEFAULT_conv_string_to_letter_utf8(const char *s, MAFSA_letter *l, size_t sz_l)
{
    uint32_t cur_letter;
    const u_char *i = (const u_char *) s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (*i && pos < sz_l)
    {
        if (i[0] >= '0' && i[0] <= '9')
        {
            l[pos] = i[0] - '0';
            i++;
            pos++;
        }
        else
        if (i[0] >= 'a' && i[0] <= 'z')
        {
            l[pos] = i[0] - 'a' + 10;
            i++;
            pos++;
        }
        else
        if (i[0] >= 'A' && i[0] <= 'Z')
        {
            l[pos] = i[0] - 'A' + 10;
            i++;
            pos++;
        }
        else
        {
            if (*i < 0x80)
            {
                if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
                {
                    i++;
                    continue;
                }

                l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
                i++;
                pos++;
                continue;
            }

            if ((i[0] & 0xE0) != 0xC0)
            {
#if (DTRAPEZNIKOV_UKR)
                if ((i[0] == 0xE2) && (i[1] == 0x80) && (i[2] == 0x99))  /* dtrapeznikov ukr: ’ */
                {
                    CHANGE_LETTER(26 + 36);
                    i += 3;
                    pos++;
                    continue;
                }
#endif
                break;
            }

            if ((i[1] & 0xC0) != 0x80)
            {
                break;
            }

            cur_letter = ((i[0] & 0x1F) << 6) | (i[1] & 0x3F);

#if (DTRAPEZNIKOV_UKR)
            if (cur_letter == 0x0415 || cur_letter == 0x0435)  /* dtrapeznikov ukr: Е, е */
            {
                I_OR_E(41, 29 + 36);
            }
            else
            if (cur_letter == 0x0418 || cur_letter == 0x0438)  /* dtrapeznikov ukr: И, и */
            {
                I_OR_E(44, 27 + 36);
            }
            else
#endif
            if (cur_letter >= 0x0410 && cur_letter <= 0x044F)
            {
                l[pos] = ((cur_letter - 0x0410) % 0x20) + 36;
            }
            else
            if (cur_letter == 0x0401 || cur_letter == 0x0451)
            {
                l[pos] = 5 + 36;
            }
#if (DTRAPEZNIKOV_UKR)
            else
            if (cur_letter == 0x0404 || cur_letter == 0x0454)  /* dtrapeznikov ukr: Є, є */
            {
                CHANGE_LETTER(41);
            }
            else
            if (cur_letter == 0x0406 || cur_letter == 0x0456)  /* dtrapeznikov ukr: І, і */
            {
                CHANGE_LETTER(44);
            }
            else
            if (cur_letter == 0x0407 || cur_letter == 0x0457)  /* dtrapeznikov ukr: Ї, ї */
            {
                CHANGE_LETTER(44);
            }
            else
            if (cur_letter == 0x0490 || cur_letter == 0x0491) /* dtrapeznikov ukr: Ґ, ґ */
            {
                CHANGE_LETTER(39);
            }
#endif

/* XXX : выше не проверялась валидность более чем двухсимвольного утф */

#if 0
            else
            {
                break;
            }
#endif
            i += 2;
            pos++;
        }
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_binary_to_letter_utf8(const char *s, size_t sz_s, MAFSA_letter *l, size_t sz_l)
{
    uint32_t cur_letter;
    const u_char *i = (const u_char *) s;
    const u_char *e = i + sz_s;
    size_t pos = 0;
#if (DTRAPEZNIKOV_UKR)
    int ukr = 0;
    const u_char *ret_i = NULL;
    size_t ret_pos = 0;
#endif
    while (pos < sz_l && i < e)
    {
        if (i[0] >= '0' && i[0] <= '9')
        {
            l[pos] = i[0] - '0';
            i++;
            pos++;
        }
        else
        if (i[0] >= 'a' && i[0] <= 'z')
        {
            l[pos] = i[0] - 'a' + 10;
            i++;
            pos++;
        }
        else
        if (i[0] >= 'A' && i[0] <= 'Z')
        {
            l[pos] = i[0] - 'A' + 10;
            i++;
            pos++;
        }
        else
        {
            if (*i < 0x80)
            {
                if (0 == pos || 68 == (0xFE & l[pos-1])) /* 68 or 69 */
                {
                    i++;
                    continue;
                }

                l[pos] = strchr(DELIMITER_STRING, *i) ? 68 : 69; /* ? '-' : ' ' */
                i++;
                pos++;
                continue;
            }

            if ((i[0] & 0xE0) != 0xC0)
            {
#if (DTRAPEZNIKOV_UKR)
                if ((i[0] == 0xE2) && (i[1] == 0x80) && (i[2] == 0x99))  /* dtrapeznikov ukr: ’ */
                {
                    CHANGE_LETTER(26 + 36);
                    i += 3;
                    pos++;
                    continue;
                }
#endif
                break;
            }

            if ((i[1] & 0xC0) != 0x80)
            {
                break;
            }

            cur_letter = ((i[0] & 0x1F) << 6) | (i[1] & 0x3F);

#if (DTRAPEZNIKOV_UKR)
            if (cur_letter == 0x0415 || cur_letter == 0x0435)  /* dtrapeznikov ukr: Е, е */
            {
                I_OR_E(41, 29 + 36);
            }
            else
            if (cur_letter == 0x0418 || cur_letter == 0x0438)  /* dtrapeznikov ukr: И, и */
            {
                I_OR_E(44, 27 + 36);
            }
            else
#endif
            if (cur_letter >= 0x0410 && cur_letter <= 0x044F)
            {
                l[pos] = ((cur_letter - 0x0410) % 0x20) + 36;
            }
            else
            if (cur_letter == 0x0401 || cur_letter == 0x0451)
            {
                l[pos] = 5 + 36;
            }
#if (DTRAPEZNIKOV_UKR)
            else
            if (cur_letter == 0x0404 || cur_letter == 0x0454)  /* dtrapeznikov ukr: Є, є */
            {
                CHANGE_LETTER(41);
            }
            else
            if (cur_letter == 0x0406 || cur_letter == 0x0456)  /* dtrapeznikov ukr: І, і */
            {
                CHANGE_LETTER(44);
            }
            else
            if (cur_letter == 0x0407 || cur_letter == 0x0457)  /* dtrapeznikov ukr: Ї, ї */
            {
                CHANGE_LETTER(44);
            }
            else
            if (cur_letter == 0x0490 || cur_letter == 0x0491) /* dtrapeznikov ukr: Ґ, ґ */
            {
                CHANGE_LETTER(39);
            }
#endif

/* XXX : выше не проверялась валидность более чем двухсимвольного утф */

#if 0
            else
            {
                break;
            }
#endif
            i += 2;
            pos++;
        }
    }
    return (0 == pos || 68 != (0xFE & l[pos-1])) ? pos : pos-1;
}

size_t DEFAULT_conv_letter_to_string_utf8(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    uint32_t c;
    size_t pos_w = 0, pos_r = 0;
    while (pos_w + 1 < sz_s && pos_r < sz_l)
    {
        if (l[pos_r] < 10)
        {
            s[pos_w] = l[pos_r] + '0';
            pos_w += 1;
        }
        else
        if (l[pos_r] < 36)
        {
            s[pos_w] = l[pos_r] + 'A' - 10;
            pos_w += 1;
        }
        else
        if (l[pos_r] < 68)
        {
            if (pos_w + 2 >= sz_s) break;
            c = l[pos_r] + 0x0410 - 36;
            s[pos_w] = (c >> 6) | 0xC0;
            s[pos_w + 1] = (c & 0x3F) | 0x80;
            pos_w += 2;
        }
        else
        if (l[pos_r] == 68)
        {
            s[pos_w] = '-';
            pos_w += 1;
        }
        else
        if (l[pos_r] == 69)
        {
            s[pos_w] = ' ';
            pos_w += 1;
        }
        else
        {
            s[pos_w] = '|';
            pos_w += 1;
        }
        pos_r++;
    }
    s[pos_w] = 0;
    return pos_w;
}

size_t DEFAULT_conv_letter_to_binary_utf8(const MAFSA_letter *l, size_t sz_l, char *s, size_t sz_s)
{
    uint32_t c;
    size_t pos_w = 0, pos_r = 0;
    while (pos_w < sz_s && pos_r < sz_l)
    {
        if (l[pos_r] < 10)
        {
            s[pos_w] = l[pos_r] + '0';
            pos_w += 1;
        }
        else
        if (l[pos_r] < 36)
        {
            s[pos_w] = l[pos_r] + 'A' - 10;
            pos_w += 1;
        }
        else
        if (l[pos_r] < 68)
        {
            if (pos_w + 2 >= sz_s) break;
            c = l[pos_r] + 0x0410 - 36;
            s[pos_w] = (c >> 6) | 0xC0;
            s[pos_w + 1] = (c & 0x3F) | 0x80;
            pos_w += 2;
        }
        else
        if (l[pos_r] == 68)
        {
            s[pos_w] = '-';
            pos_w += 1;
        }
        else
        if (l[pos_r] == 69)
        {
            s[pos_w] = ' ';
            pos_w += 1;
        }
        else
        {
            s[pos_w] = '|';
            pos_w += 1;
        }
        pos_r++;
    }
    return pos_w;
}

