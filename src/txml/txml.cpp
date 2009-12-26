
/* 
 * Copyright (C) 2004-2009, Alexander Pankov <pianozoid@rambler.ru>
 * 
 * txml library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <txml/txml.hpp>

#define BUFFER_SIZE 128

extern "C" void callback_characters(void *vThis, const char *szData, int iLength);
extern "C" void callback_start_element(void *vThis, const char *szName, const char **pszAttributes);
extern "C" void callback_end_element(void *vThis, const char *szName);

void txml::determination_object::load_from_file(const char *fname)
{
    txml::parser parser(this);
    parser.filename = fname;

    FILE *f = fopen(fname, "r");

    if (!f)
    {
        char error_text[BUFFER_SIZE];
        snprintf(error_text, BUFFER_SIZE, "Cannot open file %s", fname);
        throw std::logic_error(error_text);
    }

    char buf[BUFFER_SIZE];
    while (!feof(f))
    {
        memset(buf, 0, BUFFER_SIZE);
        size_t sz = fread(buf, sizeof(char), BUFFER_SIZE, f);

        if (0 != ferror(f))
        {
            char error_text[BUFFER_SIZE];
            snprintf(error_text, BUFFER_SIZE, "Cannot read from file %s", fname);
            throw std::logic_error(error_text);
        }

        parser.parse(buf, sz, feof(f) ? true : false);
    }

    fclose(f);
}

void txml::determination_object::load_from_string(const char *s)
{
    txml::parser parser(this);
    parser.parse(s, strlen(s), true);
}

void callback_characters(void *vThis, const char *szData, int iLength)
{
    ((txml::parser *) vThis)->characters(szData, iLength);
}

void callback_start_element(void *vThis, const char *szName, const char **pszAttributes)
{
    ((txml::parser *) vThis)->start_element(szName, pszAttributes);
}

void callback_end_element(void *vThis, const char *szName)
{
    ((txml::parser *) vThis)->end_element(szName);
}

#if 0
static int callback_unknown_encoding_handler(void * vThis, const XML_Char *name, XML_Encoding *info)
{
    return 0;
}
#endif

txml::parser::parser(determination_object *d) : data(d)
{
    the_parser = XML_ParserCreate("UTF-8");
    XML_SetUserData(the_parser, this);
#if 0
    XML_SetUnknownEncodingHandler(the_parser, callback_unknown_encoding_handler, NULL);
#endif
    XML_SetUnknownEncodingHandler(the_parser, NULL, NULL);
    XML_SetElementHandler(the_parser, callback_start_element, callback_end_element);
    XML_SetCharacterDataHandler(the_parser, callback_characters);
}

txml::parser::~parser()
{
    XML_ParserFree(the_parser);
}

void txml::parser::parse(const char *szDataSource, unsigned int iDataLength, bool bIsFinal)
{
    int iFinal = bIsFinal;
    if (XML_Parse(the_parser, szDataSource, iDataLength, iFinal) == XML_STATUS_ERROR)
    {
        raiseError(XML_ErrorString(XML_GetErrorCode(the_parser)));
    }    
}

void txml::parser::raiseError(const std::string &err)
{
    const char *fn = filename.c_str();
    const char *er = err.c_str();

    int row = XML_GetCurrentLineNumber(the_parser);
    int col = XML_GetCurrentColumnNumber(the_parser);

    char errbuf [BUFFER_SIZE];
    snprintf(errbuf, BUFFER_SIZE, "XML error (%s): %s, line %d, column %d", fn, er, row, col);

    throw std::logic_error(errbuf);
}

void txml::parser::determine()
{
    det_iter = levels.begin();
    data->determine(this);
}
    
void txml::parser::setValue(std::string &var)
{
    var += current_value;
}

void txml::parser::setValue( int32_t &var) { var = atoi  (current_value.c_str()); }
void txml::parser::setValue( int64_t &var) { var = atoll (current_value.c_str()); }
void txml::parser::setValue(uint32_t &var) { var = atoi  (current_value.c_str()); }
void txml::parser::setValue(uint64_t &var) { var = atoll (current_value.c_str()); }

void txml::parser::characters(const char *szChars, unsigned int iLength)
{
    current_value += std::string(szChars, iLength);
}

void txml::parser::start_element(const char *szName, const char **pszAttributes)
{
    levels.push_back(szName);

    for (int i = 0; pszAttributes[i] && pszAttributes[i + 1]; i +=2)
    {
        levels.push_back(pszAttributes[i]);
        current_value = pszAttributes[i + 1];
        determine();
        levels.pop_back();
    }

    /* bugfix 2006-02-02 for list and vector */

    levels.push_back("");
    current_value = "";
    determine();
    levels.pop_back();

    /* end of bugfix 2006-02-02 */

    current_value.clear();
}

void txml::parser::end_element(const char *szName)
{
    (void) szName;

    determine();
    current_value.clear();
    levels.pop_back();
}

