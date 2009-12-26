
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <turglem/morph_compiler.hpp>
#include <turglem/english/adapter.hpp>

int main(int argc, char **argv)
{
    if (6 != argc)
    {
        fprintf(stderr, "Usage: %s paradigms.xml lemmas.xml dict.out.dic "
            "paradigms.out.bin prediction.out.dic\n", argv[0]);

        exit(EXIT_FAILURE);
    }

    morph_compiler<english_utf8_adapter> mc;

    printf("Loading english paradigms...\n");
    mc.load_and_convert_paradigms(argv[1], argv[4]);

    printf("Loading english lemmas...\n");
    mc.load_lemmas(argv[2]);

    printf("Building english dictionaries...\n");
    mc.process_and_save_dicts(argv[3], argv[5]);

    return 0;
}

