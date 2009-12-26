
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <turglem/paradigms.h>

turglem_paradigms turglem_paradigms_load_from_binary_file(const char *fname, int *error)
{
    size_t sz;
    size_t i;
    turglem_paradigms prdms;

    FILE *fp = fopen(fname, "rb");
    if(0 == fp)
    {
        if (error) *error = PARADIGMS_ERROR_CANT_OPEN_FILE;
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    prdms = (turglem_paradigms)malloc(sizeof(struct turglem_paradigms_struct));
    if(0 == prdms)
    {
        if (error) *error = PARADIGMS_ERROR_NOMEM;
        fclose(fp);

        return 0;
    }
    
    prdms->_buffer = (uint8_t *) malloc(sizeof(uint8_t) * sz);
    if(0 == prdms->_buffer)
    {
        if (error) *error = PARADIGMS_ERROR_NOMEM;
        fclose(fp);
        free(prdms);

        return 0;
    }

    i = fread(prdms->_buffer, sizeof(uint8_t), sz, fp);
    if (i != sz)
    {
        if (error) *error = PARADIGMS_ERROR_CORRUPTED_FILE;
        fclose(fp);
        free(prdms->_buffer);
        free(prdms);

        return 0;
    }

    fclose(fp);

    prdms->shared = 0;

    return prdms;
}

turglem_paradigms turglem_paradigms_attach(const void *ptr, int *error)
{
    turglem_paradigms prdms;

    (void) ptr;

    if (0 == (prdms = (turglem_paradigms) malloc(sizeof(struct turglem_paradigms_struct))))
    {
        if (error) *error = PARADIGMS_ERROR_NOMEM;
        return 0;
    }

    prdms->shared = 1;
    return prdms;
}

void turglem_paradigms_close(turglem_paradigms paradigms)
{
    if (paradigms->_buffer && !paradigms->shared)
    {
        free(paradigms->_buffer);
    }
    
    free(paradigms);
}

size_t turglem_paradigms_get_paradigms_count(turglem_paradigms paradigms)
{
    return *((uint32_t *) paradigms->_buffer);
}

size_t turglem_paradigms_get_form_count(turglem_paradigms paradigms, uint32_t paradigm)
{
    uint32_t *head = (uint32_t *) paradigms->_buffer;

    return head[head[paradigm + 1]];
}

uint64_t turglem_paradigms_get_grammem(turglem_paradigms paradigms, uint32_t paradigm, uint32_t flexia)
{
    uint32_t *header = (uint32_t *) paradigms->_buffer;
    uint8_t  *data_p = paradigms->_buffer + header[header[paradigm + 1] + flexia + 1] + 4;
    uint64_t res_grammem;

    memcpy(&res_grammem, data_p, sizeof(uint64_t));

    return res_grammem;
}

uint8_t turglem_paradigms_get_part_of_speech(turglem_paradigms paradigms, uint32_t paradigm, uint32_t flexia)
{
    uint32_t *header = (uint32_t *) paradigms->_buffer;
    uint8_t *data_p = paradigms->_buffer + header[header[paradigm + 1] + flexia + 1] + 1;

    return *data_p;
}

void turglem_paradigms_get_form_data(turglem_paradigms paradigms, uint32_t paradigm, uint32_t form, MAFSA_letter **prefix,
                                     size_t *prefix_sz, MAFSA_letter **suffix, size_t *suffix_sz)
{
    uint32_t *header = (uint32_t *) paradigms->_buffer;
    uint8_t  *data_p = paradigms->_buffer + header[header[paradigm + 1] + form + 1] + 2;
        
    *prefix_sz = *data_p++;
    *suffix_sz = *data_p++;
    
    data_p += sizeof(uint64_t);
        
    *prefix = (MAFSA_letter*)data_p;
    *suffix = (MAFSA_letter*)data_p + *prefix_sz;
}

