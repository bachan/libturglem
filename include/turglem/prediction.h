
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 *
 */

#ifndef __TURGLEM_PREDICTION_H__
#define __TURGLEM_PREDICTION_H__

#include <MAFSA/automaton.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Do prediction.
 * 
 */

extern size_t turglem_prediction_predict(MAFSA_automaton pred, const MAFSA_letter *l, size_t sz_l, MAFSA_letter delim, int *out_pair_array, size_t sz_array);

#ifdef __cplusplus
}
#endif

#endif /* __TURGLEM_PREDICTION_H__ */
