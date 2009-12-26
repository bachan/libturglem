
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 *
 */

#ifndef __TURGLEM_PARADIGMS_H__
#define __TURGLEM_PARADIGMS_H__

#include <inttypes.h>
#include <MAFSA/automaton.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PARADIGMS_ERROR_NOMEM           1
#define PARADIGMS_ERROR_CANT_OPEN_FILE  2
#define PARADIGMS_ERROR_CORRUPTED_FILE  3

struct turglem_paradigms_struct
{
    uint8_t *_buffer;
    int shared;
};

typedef struct turglem_paradigms_struct *turglem_paradigms;

/* 
 * turglem_paradigms_load_from_binary_file:
 *
 * Opens binary file, load it to memory. Remember to free by
 * calling turglem_paradigms_close().
 *
 */

extern turglem_paradigms turglem_paradigms_load_from_binary_file(const char *fname, int *error);

/* 
 * turglem_paradigms_attach:
 *
 * Attaches paradigms as ptr. Feel free to call turglem_paradigms_close(),
 * memory won't be deallocated!
 *
 */

extern turglem_paradigms turglem_paradigms_attach(const void *ptr, int *error);

/* 
 * turglem_paradigms_close:
 *
 * Frees memory, allocated by turglem_paradigms_load_from_binary_file().
 * Does nothing if turglem_paradigms was created by turglem_paradigms_attach().
 *
 */

extern void turglem_paradigms_close(turglem_paradigms paradigms);

/* 
 * turglem_paradigms_get_paradigms_count:
 *
 * Returns paradigms count.
 * 
 */

extern size_t turglem_paradigms_get_paradigms_count(turglem_paradigms paradigms);

/* 
 * Returns form count for paradigm.
 * 
 */

extern size_t turglem_paradigms_get_form_count(turglem_paradigms paradigms, uint32_t paradigm);

/* 
 * Returns grammems of form of paradigm.
 * 
 */

extern uint64_t turglem_paradigms_get_grammem(turglem_paradigms paradigms, uint32_t paradigm, uint32_t flexia);

/* 
 * Returns part of speech of form of flexia.
 * 
 */

extern uint8_t turglem_paradigms_get_part_of_speech(turglem_paradigms paradigms, uint32_t paradigm, uint32_t flexia);

/* 
 * Returns prefix and/or suffix of form of flexia and their sizes.
 * 
 */

extern void turglem_paradigms_get_form_data(turglem_paradigms paradigms, uint32_t paradigm, uint32_t flexia, MAFSA_letter **prefix,
                                            size_t *prefix_sz, MAFSA_letter **suffix, size_t *suffix_sz);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_PARADIGMS_H__ */
