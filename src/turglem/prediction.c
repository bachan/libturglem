
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <MAFSA/automaton.h>
#include <turglem/prediction.h>

size_t turglem_prediction_predict(MAFSA_automaton pred, const MAFSA_letter *l, size_t sz_l, MAFSA_letter delim, int *out_pair_array, size_t sz_array)
{
    int keep = 1;
    uint32_t i;

    MAFSA_letter tmp [64];
    
    for (i = 5; i >= 2 && keep; --i)
    { 
        if (sz_l <= i) continue;

        if (MAFSA_automaton_enumerate_int_pair(pred, l + sz_l - i, i, tmp, 64, delim, out_pair_array, sz_array))
        {
            keep = 0;
        }
    }
            
    return !keep;
}

