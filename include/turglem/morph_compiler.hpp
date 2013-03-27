
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

#ifndef __MORPH_COMPILER_HPP__
#define __MORPH_COMPILER_HPP__

#include <string.h>
#include <inttypes.h>
#include <coda/txml.hpp>
#include <MAFSA/daciuk.hpp>
#include <turglem/string.hpp>

template<typename _ABC>
class morph_compiler
{
    struct paradigms_xml_loader : public coda::txml_determination_object
    {
        struct ROOT : public coda::txml_determination_object
        {
            struct PARADIGM : public coda::txml_determination_object
            {
                struct FORM : public coda::txml_determination_object
                {
                    std::string prefix;
                    std::string suffix;

                    uint32_t pos;
                    uint64_t grammem;
                    uint32_t id;
            
                    void determine(coda::txml_parser *parser)
                    {
                        parser->determineMember("s",  suffix);
                        parser->determineMember("ps", pos);
                        parser->determineMember("g",  grammem);
                        parser->determineMember("p",  prefix);
                        parser->determineMember("id", id);
                    }
                };
            
                std::vector<FORM> forms;
            
                void determine(coda::txml_parser *parser)
                {
                    parser->determineMember("f", forms);
                }
            };            
        
            std::vector<PARADIGM> paradigms;
        
            void determine(coda::txml_parser *parser)
            {
                parser->determineMember("paradigm", paradigms);
            }
        };

        ROOT root;

        void determine(coda::txml_parser *parser)
        {
            parser->determineMember("paradigms", root);
        }
    };
    
    struct lemmas_xml_loader : public coda::txml_determination_object
    {
        struct ROOT : public coda::txml_determination_object
        {
            struct LEMMA : public coda::txml_determination_object
            {
                std::string word;
                std::string prefix;
                uint32_t idx;
            
                void determine(coda::txml_parser *parser)
                {
                    parser->determineMember("id", word);                                        
                    parser->determineMember("prefix", prefix);                    
                    parser->determineMember("p", idx);
                }
            };
            
            std::vector<LEMMA> ls;
        
            void determine(coda::txml_parser *parser)
            {
                parser->determineMember("l", ls);
            }
        };            
    
        ROOT root;

        void determine(coda::txml_parser *parser)
        {
            parser->determineMember("lemmas", root);
        }
    };

    paradigms_xml_loader paradigms_loader;
    lemmas_xml_loader lemmas_loader;

    std::map<MAFSA::l_string, std::map<std::pair<unsigned int, unsigned int>, unsigned int> > prediction_data;    

    void process_stat_data();
    void add_stats(const MAFSA::l_string &s, unsigned int flex, unsigned int form, unsigned int max_pref_suf_len);
    void save_prediction_dict(const char *predict_out);
    void save_main_dict(const char *dict_out);

public:    
    bool load_and_convert_paradigms(const char *xml_source, const char *bin_out);
    bool load_lemmas(const char *xml_source);
    
    /* if (0 == predict_out) then prediction dict is not generated */

    bool process_and_save_dicts(const char *dict_out, const char *predict_out);
};

#include "morph_compiler.tcc"

#endif /* __MORPH_COMPILER_HPP__ */
