
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

#ifndef __TXML_HPP__
#define __TXML_HPP__

#include <list>
#include <string>
#include <vector>
#include <expat.h>
#include <inttypes.h>
#include <sys/types.h>

namespace txml {

class parser;
    
struct determination_object
{
    virtual ~determination_object() {}
    virtual void determine(parser *p) = 0;
    void load_from_file(const char *fname);
    void load_from_string(const char *s);
};

class parser
{
    friend class determination_object;

    struct level_desc
    {
        std::string key;
        int pushed;
        level_desc(const char *k) : key(k), pushed(0) {};
    };

    XML_Parser the_parser;
    std::string filename;

    std::vector<level_desc> levels;
    std::vector<level_desc>::iterator det_iter;

    std::string current_value;
    determination_object *data;

    void determine();
    void setValue(std::string &var);

    void setValue( int32_t &var);
    void setValue( int64_t &var);
    void setValue(uint32_t &var);
    void setValue(uint64_t &var);
    
    template <typename _T>
    void setValue(_T &var)
    {
        var.determine(this);
    }

    template <typename _T>
    void setValue(std::list<_T> &var)
    {
        det_iter--;
        if (!det_iter->pushed)
        {
            det_iter->pushed = 1;
            var.push_back(_T());
        }
        _T &item = var.back();
        det_iter++;
        setValue(item);
    }

    template <typename _T>
    void setValue(std::vector<_T> &var)
    {
        det_iter--;
        if (!det_iter->pushed)
        {
            det_iter->pushed = 1;
            var.push_back(_T());
        }
        _T &item = var.back();
        det_iter++;
        setValue(item);
    }

    void parse(const char *szDataSource, unsigned int iDataLength, bool bIsFinal = true);

public:
    parser(determination_object *d);
    ~parser();
    void raiseError(const std::string &err);

    template <typename _T>
    bool determineMember(const std::string &key, _T &var)
    {
        if (det_iter == levels.end())
        {
            if (!key.empty()) return false;
            setValue(var);
            return true;
        }
        if (det_iter->key == key)
        {
            det_iter++;
            setValue(var);
            det_iter--;
            return true;
        }
        return false;
    }

    void characters(const char *szChars, unsigned int iLength);
    void start_element(const char *szName, const char **pszAttributes);
    void end_element(const char *szName);
};

}

#endif
