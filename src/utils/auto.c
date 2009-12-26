
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <MAFSA/automaton.h>
#include <turglem/default/adapter.h>
#include <turglem/english/adapter.h>
#include <turglem/russian/adapter.h>

typedef struct auto_getopt auto_getopt_t;
typedef int (* auto_handle_fp) (const auto_getopt_t *opts, const char *s, size_t sz_s);

int auto_handle_words(const auto_getopt_t *opts, const char *s, size_t sz_s);
int auto_handle_files(const auto_getopt_t *opts, const char *s, size_t sz_s);

struct auto_getopt
{
    unsigned flags:28;

    unsigned place:2;
    unsigned human:1;
    unsigned quiet:1;

    const char     *s_prefix,   *s_invert,   *s_substr;
    MAFSA_letter   *l_prefix,   *l_invert,   *l_substr;
          size_t sz_l_prefix, sz_l_invert, sz_l_substr;

    auto_handle_fp handle;

    MAFSA_letter delim;
    MAFSA_conv_string_to_letter string_to_letter;
    MAFSA_conv_letter_to_string letter_to_string;
    MAFSA_conv_binary_to_letter binary_to_letter;
    MAFSA_conv_letter_to_binary letter_to_binary;
};

static struct option options [] =
{
    { "files"         , 0, NULL, 'f' },
    { "words"         , 0, NULL, 'w' },
    { "prefix-search" , 1, NULL, 'p' },
    { "invert-search" , 1, NULL, 'r' },
    { "substr-search" , 1, NULL, 's' },
    { "adapt-english" , 0, NULL, 'E' },
    { "adapt-russian" , 0, NULL, 'R' },
    { "adapt-ukraine" , 0, NULL, 'U' },
    { "human"         , 0, NULL, 'h' },
    { "quiet"         , 0, NULL, 'q' },
    {  NULL           , 0, NULL,  0  },
};

int auto_getopt_usage(int argc, char **argv)
{
    fprintf(stderr,
        "Usage:                                          \n"
        "  %s -[p:r:s:ERUhq]f [FILE]...                  \n"
        "  %s -[p:r:s:ERUhq]w [WORD]...                  \n"
        "                                                \n"
    , argv[0], argv[0]);

    fprintf(stderr,
        "Options:                                               \n"
        "  -f, --files                  : use files as args     \n"
        "  -w, --words                  : use words as args     \n"
        "                                                       \n"
    );

    fprintf(stderr,
        "  -p, --prefix-search <string> : search for values in automaton that begin with <string>        \n"
        "  -r, --invert-search <string> : search for values in automaton that are substrings of <string> (CURRENTLY BROKEN) \n"
        "  -s, --substr-search <string> : search for values in automaton that contain <string>           \n"
        "                                                                                                \n"
    );

    fprintf(stderr,
        "  -E, --adapt-english          : use english adapter   \n"
        "  -R, --adapt-russian          : use russian adapter   \n"
        "  -U, --adapt-ukraine          : use ukraine adapter (NOT IMPLEMENTED)  \n"
        "                                                       \n"
    );

    fprintf(stderr,
        "  -h, --human                  : human readable output \n"
        "  -q, --quiet                  : quiet output          \n"
        "                                                       \n"
    );

    return 0;
}

int auto_getopt_parse(int argc, char **argv, auto_getopt_t *opts)
{
    int c;

    opts->delim            = DEFAULT_LETTER_DELIM;
    opts->string_to_letter = DEFAULT_conv_string_to_letter_utf8;
    opts->letter_to_string = DEFAULT_conv_letter_to_string_utf8;
    opts->binary_to_letter = DEFAULT_conv_binary_to_letter_utf8;
    opts->letter_to_binary = DEFAULT_conv_letter_to_binary_utf8;

    while (-1 != (c = getopt_long(argc, argv, "fwp:r:s:ERUhq", options, NULL)))
    {
        switch (c)
        {
            case 'f': opts->handle = auto_handle_files; break;
            case 'w': opts->handle = auto_handle_words; break;

            case 'p': opts->s_prefix = optarg; break;
            case 'r': opts->s_invert = optarg; break;
            case 's': opts->s_substr = optarg; break;

            case 'E':
                opts->delim            = ENGLISH_LETTER_DELIM;
                opts->string_to_letter = ENGLISH_conv_string_to_letter_utf8;
                opts->letter_to_string = ENGLISH_conv_letter_to_string_utf8;
                opts->binary_to_letter = ENGLISH_conv_binary_to_letter_utf8;
                opts->letter_to_binary = ENGLISH_conv_letter_to_binary_utf8;
                break;
            case 'R':
                opts->delim            = RUSSIAN_LETTER_DELIM;
                opts->string_to_letter = RUSSIAN_conv_string_to_letter_utf8;
                opts->letter_to_string = RUSSIAN_conv_letter_to_string_utf8;
                opts->binary_to_letter = RUSSIAN_conv_binary_to_letter_utf8;
                opts->letter_to_binary = RUSSIAN_conv_letter_to_binary_utf8;
                break;
#if 0
            case 'U':
                opts->delim            = UKRAINE_LETTER_DELIM;
                opts->string_to_letter = UKRAINE_conv_string_to_letter_utf8;
                opts->letter_to_string = UKRAINE_conv_letter_to_string_utf8;
                opts->binary_to_letter = UKRAINE_conv_binary_to_letter_utf8;
                opts->letter_to_binary = UKRAINE_conv_letter_to_binary_utf8;
                break;
#endif

            case 'h': opts->human = 1; break;
            case 'q': opts->quiet = 1; break;

            default:
                return -1;
        }
    }

    return 0;
}

int auto_load(int argc, char **argv, auto_getopt_t *opts)
{
    if (NULL == opts->handle)
    {
        return -1;
    }

    if (opts->s_prefix)
    {
        opts->l_prefix = (MAFSA_letter *) malloc(1024);
        if (NULL == opts->l_prefix) return -1;

        opts->sz_l_prefix = opts->string_to_letter(opts->s_prefix,
            opts->l_prefix, 1024);
    }

    if (opts->s_invert)
    {
        opts->l_invert = (MAFSA_letter *) malloc(1024);
        if (NULL == opts->l_invert) return -1;

        opts->sz_l_invert = opts->string_to_letter(opts->s_invert,
            opts->l_invert, 1024);
    }

    if (opts->s_substr)
    {
        opts->l_substr = (MAFSA_letter *) malloc(1024);
        if (NULL == opts->l_substr) return -1;

        opts->sz_l_substr = opts->string_to_letter(opts->s_substr,
            opts->l_substr, 1024);
    }

    return 0;
}

int auto_free(auto_getopt_t *opts)
{
    free(opts->l_prefix);
    free(opts->l_invert);
    free(opts->l_substr);

    return 0;
}

static void *auto_memmem(const void *m, size_t sz_m, const void *n, size_t sz_n)
{
    const u_char *bm, *em, *bn, *en;

    if (!m || !sz_m) return NULL;
    if (!n || !sz_n) return (void *) m;
    if (sz_m < sz_n) return NULL;

    bm = (const u_char *) m; em = bm + sz_m;
    bn = (const u_char *) n; en = bn + sz_n;

    for (; bm < em; ++bm)
    {
        if (*bm == *bn)
        {
            const u_char *pm, *pn;

            for (pm = bm, pn = bn; pm < em && pn < en; ++pm, ++pn)
            {
                if (*pm != *pn) break;
            }

            if (pn == en) return (void *) bm;
        }
    }

    return NULL;
}

static void auto_handle_files_cb(void *arg, const MAFSA_letter *letter, size_t sz_letter)
{
     char buffer [1024];
    const MAFSA_letter *values;

    size_t result;
    size_t adjust;
    size_t sz_values;
    size_t sz_buffer;
    size_t i;

    const auto_getopt_t *opts = (const
        auto_getopt_t *) arg;

    if (opts->l_substr && NULL == auto_memmem(letter, sz_letter,
        opts->l_substr, opts->sz_l_substr))
    {
        return;
    }

    if (opts->l_invert && NULL == auto_memmem(opts->l_substr,
        opts->sz_l_substr, letter, sz_letter))
    {
        return;
    }

    if (0 == opts->human || NULL == (values = memchr(
        letter, opts->delim, sz_letter)))
    {
        sz_buffer = opts->letter_to_binary(letter, sz_letter, buffer, 1024);
        printf("%.*s\n", (int) sz_buffer, buffer);
        return;
    }

    sz_values = letter - values + sz_letter;
    sz_letter = values - letter;

    sz_buffer = opts->letter_to_binary(letter, sz_letter, buffer, 1024);
    printf("%.*s", (int) sz_buffer, buffer);

    result = 0;
    adjust = 1;

    for (i = 0; i < sz_values; ++i)
    {
        for (; i < sz_values && opts->delim != values[i]; ++i)
        {
            result += adjust * values[i];
            adjust *= opts->delim;
        }

        if (0 != result) printf("|%"PRIuMAX"", (uintmax_t) result);
        if (i >= sz_values) printf("\n");

        result = 0;
        adjust = 1;
    }
}

int auto_handle_files(const auto_getopt_t *opts, const char *s, size_t sz_s)
{
    MAFSA_automaton ma;
    MAFSA_letter tmp [1024];

    if (NULL == (ma = MAFSA_automaton_load_from_binary_file(s, 0)))
    {
        return -1;
    }

    MAFSA_automaton_enumerate(ma, opts->l_prefix, opts->sz_l_prefix,
        tmp, 1024, (void *) opts, auto_handle_files_cb);

    MAFSA_automaton_close(ma);
    return 0;
}

int auto_handle_words(const auto_getopt_t *opts, const char *s, size_t sz_s)
{
    char o [1024];
    MAFSA_letter l [1024];

    size_t sz_o;
    size_t sz_l;

    sz_l = opts->binary_to_letter(s, sz_s, l, 1024);
    sz_o = opts->letter_to_binary(l, sz_l, o, 1024);

    printf("%.*s\n", (int) sz_o, o);

    return 0;
}

int main(int argc, char **argv)
{
    int i;

    auto_getopt_t opts;
    memset(&opts, 0, sizeof(opts));

    if (0 != auto_getopt_parse(argc, argv, &opts))
    {
        auto_getopt_usage(argc, argv);
        exit(EXIT_FAILURE);
    }

    if (0 != auto_load(argc, argv, &opts))
    {
        auto_getopt_usage(argc, argv);
        exit(EXIT_FAILURE);
    }

    for (i = optind; i < argc; ++i)
    {
        if (0 == opts.quiet) fprintf(stderr,
            "processing %s\n", argv[i]);

        opts.handle(&opts, argv[i], strlen(argv[i]));
    }

    if (argc > optind)
    {
        exit(EXIT_SUCCESS);
    }

    while (!feof(stdin) && !ferror(stdin))
    {
        char argi [1024];
        size_t sz;

        if (NULL == fgets(argi, 1024, stdin))
        {
            continue;
        }

        sz = strcspn(argi, "\r\n");
        argi[sz] = 0;

        if (0 == opts.quiet) fprintf(stderr,
            "processing %s\n", argi);

        opts.handle(&opts, argi, sz);
    }

    auto_free(&opts);

    return 0;
}

