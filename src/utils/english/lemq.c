
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <auto/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>
#include <turglem/lemmatizer.h>
#include <turglem/english/adapter.h>

#define TENG_DICT TURGLEM_INSTALL_PREFIX "/share/turglem/english/dict_english.auto"
#define TENG_PRED TURGLEM_INSTALL_PREFIX "/share/turglem/english/prediction_english.auto"
#define TENG_PARA TURGLEM_INSTALL_PREFIX "/share/turglem/english/paradigms_english.bin"

#define TENG_SHOW_NFORM    (1 << 0)
#define TENG_SHOW_PARADIGM (1 << 1)

typedef struct teng_getopt
    teng_getopt_t;

struct teng_getopt
{
    uint32_t show;
    int no_prediction;
};

static struct option options [] =
{
    { "nform"         , 0, NULL, 'n' },
    { "paradigm"      , 0, NULL, 'p' },
    { "no-prediction" , 0, NULL, 'P' },
    {  NULL           , 0, NULL,  0  },
};

int teng_getopt_usage(int argc, char **argv)
{
    fprintf(stderr,

        "Usage:                                          \n"
        "  %s -[P]n [WORD]...                            \n"
        "  %s -[P]p [WORD]...                            \n"
        "                                                \n"
        "Options:                                        \n"
        "  -n, --nform         : show normal form only   \n"
        "  -p, --paradigm      : show the whole paradigm \n"
        "                                                \n"
        "  -P, --no-prediction : don't use prediction    \n"
        "                                                \n"

    , argv[0], argv[0]);

    return 0;
}

int teng_getopt_parse(int argc, char **argv, teng_getopt_t *opts)
{
    int c;

    while (-1 != (c = getopt_long(argc, argv, "npP", options, NULL)))
    {
        switch (c)
        {
            case 'n': opts->show |= TENG_SHOW_NFORM; break;
            case 'p': opts->show |= TENG_SHOW_PARADIGM; break;

            case 'P': opts->no_prediction = 1; break;

            default:
                return -1;
        }
    }

    return 0;
}

static int lemmatize_and_print(turglem lem, const char *s, size_t sz_s, teng_getopt_t *opts)
{
    int form [2 * 1024];
    MAFSA_letter letter_src [1024];
    ssize_t sz_letter_src;
    size_t sz_form, i;

    if (0 > (sz_letter_src = ENGLISH_conv_binary_to_letter_utf8(s,
        sz_s, letter_src, 1024)))
    {
        return -1;
    }

    sz_form = turglem_lemmatize(lem, letter_src, sz_letter_src, form,
        1024, ENGLISH_LETTER_DELIM, !opts->no_prediction);

    for (i = 0; i < sz_form; ++i)
    {
        size_t j;
        size_t fsz;

        if (opts->show & TENG_SHOW_NFORM)
        {
            MAFSA_letter letter_dst [1024];
            char binary_dst [1024];

            size_t sz_letter_dst;
            size_t sz_binary_dst;

            sz_letter_dst = turglem_build_form(lem, letter_src, sz_letter_src,
                letter_dst, 1024, form[2*i], form[2*i+1], 0);

            sz_binary_dst = ENGLISH_conv_letter_to_binary_utf8(letter_dst,
                sz_letter_dst, binary_dst, 1024);

            printf("%.*s%c", (int) sz_binary_dst, binary_dst,
                i < sz_form - 1 ? '|' : '\n');
        }

        if (opts->show & TENG_SHOW_PARADIGM)
        {
            fsz = turglem_paradigms_get_form_count(lem->paradigms, form[2*i]);

            printf("\033[1mPARADIGM  FORM                                                       GRAMMEM  POS\033[m\n");

            for (j = 0; j < fsz; ++j)
            {
                MAFSA_letter letter_dst [1024];
                char binary_dst [1024];

                size_t sz_letter_dst;
                size_t sz_binary_dst;

                uint64_t grm;
                uint8_t  pos;

                size_t k;
                size_t grm_pos;
                  char grm_str [256];

                grm = turglem_paradigms_get_grammem(lem->paradigms, form[2*i], j);
                pos = turglem_paradigms_get_part_of_speech(lem->paradigms, form[2*i], j);

                sz_letter_dst = turglem_build_form(lem, letter_src, sz_letter_src,
                    letter_dst, 1024, form[2*i], form[2*i+1], j);

                sz_binary_dst = ENGLISH_conv_letter_to_binary_utf8(letter_dst,
                    sz_letter_dst, binary_dst, 1024);

                grm_pos = snprintf(grm_str, 256, ",");

                for (k = 0; k < 64; ++k)
                {
                    if (grm & (1 << k))
                    {
                        grm_pos += snprintf(grm_str + grm_pos, 256 - grm_pos,
                            "%"PRIuMAX",", (uintmax_t) k);
                    }
                }

                printf("%8d  %4"PRIuMAX"  %s  %3"PRIu8"  %.*s %s\n", form[2*i], (uintmax_t) j, grm_str,
                    pos, (int) sz_binary_dst, binary_dst, (form[2*i+1] == j) ? "*" : " ");
            }
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    turglem lem;

    int err_no;
    int err_what;
    int i;

    teng_getopt_t opts;
    memset(&opts, 0, sizeof(opts));

    if (0 != teng_getopt_parse(argc, argv, &opts))
    {
        teng_getopt_usage(argc, argv);
        exit(EXIT_FAILURE);
    }

    if (0 == opts.show)
    {
        teng_getopt_usage(argc, argv);
        exit(EXIT_FAILURE);
    }

    lem = turglem_load(TENG_DICT, TENG_PRED, TENG_PARA, &err_no, &err_what);

    if (0 != err_no)
    {
        fprintf(stderr, "turglem_load("TENG_DICT", "TENG_PRED", "TENG_PARA", ...):"
            " %d: %s", err_no, turglem_error_what_string(err_what));

        exit(EXIT_FAILURE);
    }

    for (i = optind; i < argc; ++i)
    {
        lemmatize_and_print(lem, argv[i], strlen(argv[i]), &opts);
    }

    if (argc > optind)
    {
        exit(EXIT_SUCCESS);
    }

    while (!feof(stdin) && !ferror(stdin))
    {
        char word [1024];
        size_t sz;

        if (NULL == fgets(word, 1024, stdin))
        {
            continue;
        }

        sz = strcspn(word, "\r\n");
        word[sz] = 0;

        lemmatize_and_print(lem, word, sz, &opts);
    }

    turglem_close(lem);

    return 0;
}

