
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 *
 */

#ifndef __TURGLEM_LEMMATIZER_H__
#define __TURGLEM_LEMMATIZER_H__

#include <MAFSA/automaton.h>
#include <turglem/paradigms.h>
#include <turglem/prediction.h>

#define TURGLEM_ERROR_NOMEM       1
#define TURGLEM_ERROR_DICTIONARY  2
#define TURGLEM_ERROR_PREDICTION  3
#define TURGLEM_ERROR_PARADIGMS   4

#ifdef __cplusplus
extern "C" {
#endif

struct turglem_struct
{
    MAFSA_automaton   words;
    turglem_paradigms paradigms;
    MAFSA_automaton   prediction;
};

typedef struct turglem_struct *turglem;

/* 
 * turglem_load:
 *
 * Loads all lemmatizer data from files: main automaton, prediction automaton, paradigms.
 * prediction may be 0, if you are not going to use prediction at all.
 * 
 */

extern turglem turglem_load(const char *fname_dic_autom, const char *fname_predict_autom, const char *fname_paradigms, int *err_no, int *err_what);

/* 
 * turglem_attach:
 *
 * Attaches lemmatizer data from pointers. Safe to do turglem_close() after this.
 * 
 */

extern turglem turglem_attach(const void *ptr_dic_autom_nodes, const void *ptr_dic_autom_links, const void *ptr_predict_autom_nodes,
                              const void *ptr_predict_autom_links, const void *ptr_paradigms);

extern void turglem_close(turglem lem);

/* 
 * turglem_lemmatize:
 *
 * Lemmitizes string of letters, fills array of pairs (flexia_number, form_number)
 * and returns the number of such pairs.
 * 
 */

extern size_t turglem_lemmatize(turglem lem, const MAFSA_letter *l, size_t sz_l, int *out_pair_array, size_t sz_array, MAFSA_letter delim, int use_prediction);

/* 
 * turglem_build_form (builds form number n_form):
 *
 * s_in  / sz_s_in   -- source string, for which was called turglem_lemmatize
 * s_out / sz_s_out  -- output buffer (RETURNS the number of letters used from buffer)
 * s_flexia + s_form -- flexia and form pair returned by turglem_lemmatize
 * n_form            -- form to build
 * 
 */

extern size_t turglem_build_form(turglem lem, const MAFSA_letter *s_in, size_t sz_s_in, MAFSA_letter *s_out, size_t sz_s_out, int src_paradigm, int src_form, int n_form);

extern const char *turglem_error_no_string(int err_no);
extern const char *turglem_error_what_string(int err_what);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_LEMMATIZER_H__ */
