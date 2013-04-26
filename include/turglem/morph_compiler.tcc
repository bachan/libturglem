
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

template<typename _ABC>
void morph_compiler<_ABC>::process_stat_data()
{
    for (std::map<MAFSA::l_string, std::map<std::pair<uint, uint>, uint> >::iterator i = prediction_data.begin(); i != prediction_data.end(); ++i)
    {
        std::pair<uint, uint> max1;
        uint max2 = 0;

#if 0
        /* uncomment this to see statistics of prediction */
        printf("'%s'\n", i->first.c_str());
#endif

        for (std::map<std::pair<uint, uint>, uint>::const_iterator j =  i->second.begin(); j != i->second.end(); ++j)
        {
#if 0
            printf("[%d:%d] -> %d\n", j->first.first, j->first.second, j->second);
#endif
            if (j->second >= max2)
            {
                max1 = j->first;
                max2 = j->second;
            }
        }

        i->second.clear();
        i->second[max1] = max2;
    }
}

template<typename _ABC>
void morph_compiler<_ABC>::add_stats(const MAFSA::l_string& s, unsigned int flex, unsigned int form, unsigned int max_pref_suf_len)
{        
    for (unsigned int i = 2; i < 6; ++i)
    {
        if (s.size() < i || max_pref_suf_len >= i) continue;

        prediction_data[s.substr(s.size() - i, i)][std::pair<unsigned int, unsigned int>(flex, form)]++;
    }
}

template<typename _ABC>
void morph_compiler<_ABC>::save_prediction_dict(const char * predict_out)
{
    MAFSA::daciuk<_ABC::max_letter+1> dict;
        
    process_stat_data();

    std::map<MAFSA::l_string/*std::basic_string<MAFSA_letter>*/, std::map<std::pair<unsigned int, unsigned int>, unsigned int> >::iterator i;

    for (i = prediction_data.begin(); i!= prediction_data.end(); ++i)
    {
        MAFSA::l_string out = i->first;
            
        out.push_back(_ABC::max_letter);
            
        unsigned int v = i->second.begin()->first.first;

        while (v)
        {
            out.push_back(v % (_ABC::max_letter));
            v = v / (_ABC::max_letter);
        }
            
        out.push_back(_ABC::max_letter);
            
        v = i->second.begin()->first.second;

        while (v)
        {
            out.push_back(v % (_ABC::max_letter));
            v = v / (_ABC::max_letter);
        }
            
        dict.insert(out.data(), out.size());
    }
        
    dict.save_to_file(predict_out);    
}

template<typename _ABC>
void morph_compiler<_ABC>::save_main_dict(const char * dict_out)
{
    MAFSA::daciuk<_ABC::max_letter+1> dic;
    
    for (unsigned int i = 0; i < lemmas_loader.root.ls.size(); i++)
    {
#if 0
        printf("- %d %d\n", 0, lem.root.ls[i].idx);
#endif

        for(uint j = 0; j < paradigms_loader.root.paradigms[lemmas_loader.root.ls[i].idx].forms.size(); j++)
        {
            
            struct paradigms_xml_loader::ROOT::PARADIGM::FORM form = paradigms_loader.root.paradigms[lemmas_loader.root.ls[i].idx].forms[j];
            
            MAFSA::l_string pref = _ABC::string2letters(form.prefix.c_str());
            MAFSA::l_string suff = _ABC::string2letters(form.suffix.c_str());
            MAFSA::l_string s = pref + _ABC::string2letters(lemmas_loader.root.ls[i].word.c_str()) + suff;
            
            uint max_len = pref.size() > suff.size() ? pref.size() : suff.size();
            
            if (form.pos < 3 || form.pos >= 18 || form.pos == 8)
            {
                add_stats(s, lemmas_loader.root.ls[i].idx, j, max_len);
            }

            s.push_back(_ABC::max_letter);

            unsigned int v = lemmas_loader.root.ls[i].idx;

            while (v)
            {
                s.push_back(v % (_ABC::max_letter));
                v = v / (_ABC::max_letter);
            }

            s.push_back(_ABC::max_letter);
            
            v = j;

            while (v)
            {
                s.push_back(v % (_ABC::max_letter));
                v = v / (_ABC::max_letter);
            }

            dic.insert(s.data(), s.size());            
        }
    }
    
    dic.save_to_file(dict_out);
}

template<typename _ABC>
bool morph_compiler<_ABC>::load_and_convert_paradigms(const char *xml_source, const char *bin_out)
{
    paradigms_loader.load_from_file(xml_source);

    if (0 != bin_out)
    {
        /* now we have to process <i>paradigms_loader</i> and save it to file bin_out */

        std::vector<uint32_t> header;
        std::vector<uint8_t> body;

        header.resize(paradigms_loader.root.paradigms.size()+1);
        header[0] = paradigms_loader.root.paradigms.size();

        int off = 1;

        for (unsigned int i = 0; i < paradigms_loader.root.paradigms.size(); ++i)
        {
            off += paradigms_loader.root.paradigms[i].forms.size() + 2;
        }

        for (unsigned int i = 0; i < paradigms_loader.root.paradigms.size(); ++i)
        {
            header[i+1] = header.size();
            header.push_back(paradigms_loader.root.paradigms[i].forms.size());

            for (unsigned int j = 0; j < paradigms_loader.root.paradigms[i].forms.size(); ++j)
            {
                header.push_back(4 * off + body.size());

                struct paradigms_xml_loader::ROOT::PARADIGM::FORM& form = paradigms_loader.root.paradigms[i].forms[j];

                MAFSA::l_string pref = _ABC::string2letters(form.prefix.c_str());
                MAFSA::l_string suff = _ABC::string2letters(form.suffix.c_str());

                /* GENERATING FORM SERIALIZATION */

                char buffer[1024];
                char *p = buffer;

                *p++ = 0; /* alignment */
                *p++ = (uint8_t) form.pos;
                *p++ = pref.size();
                *p++ = suff.size();

                memcpy(p, &form.grammem, sizeof(uint64_t));
                p += sizeof(uint64_t);

                memcpy(p, pref.data(), pref.size() * sizeof(MAFSA_letter));
                p += pref.size();

                memcpy(p, suff.data(), suff.size() * sizeof(MAFSA_letter));
                p += suff.size();

                int len = (p - buffer + 3) & 0xFFFC;

                for (int i = 0; i < len; i++)
                {
                    body.push_back(buffer[i]);
                }
            }
        }

        FILE *fl_out = fopen(bin_out, "wb");

        if(NULL == fl_out) return false;

        if(header.size() != fwrite(&header[0], sizeof(uint32_t), header.size(), fl_out)) return false;
        if(  body.size() != fwrite(  &body[0], sizeof(uint8_t),    body.size(), fl_out)) return false;

        fclose(fl_out);
    }

    return true;
}

template<typename _ABC>
bool morph_compiler<_ABC>::load_lemmas(const char * xml_source)
{
    lemmas_loader.load_from_file(xml_source);
    return true;
}

template<typename _ABC>
bool morph_compiler<_ABC>::process_and_save_dicts(const char * dict_out, const char * predict_out)
{
    save_main_dict(dict_out);    

    if (predict_out)
    {
        save_prediction_dict(predict_out);
    }

    return true;
}

