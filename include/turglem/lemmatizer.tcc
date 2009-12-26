
/*
 * Copyright (C) 2007-2009, libturglem development team.
 * This file is released under the LGPL.
 * 
 */

template <typename _CHA>
size_t tl::lemmatizer::lemmatize(const char *src, tl::lem_result &lr, int use_prediction) const
{
    /* convert string to letters */

    lr.src = _CHA::string2letters(src);

    if (!lr.src.empty())
    {
        size_t fcount;
        int fdata [1024 * 2];

        fcount = turglem_lemmatize(tlem, lr.src.data(), lr.src.size(), fdata, 1024, _CHA::max_letter, use_prediction);
        lr.fi.resize(fcount);

        for (size_t i = 0; i < fcount; i++)
        {
            tl::form_info &f = lr.fi[i];
            f.paradigm = fdata[i * 2];
            f.src_form = fdata[i * 2 + 1];
        }

        return fcount;
    }

    return 0;
}

template <typename _CHA>
std::string tl::lemmatizer::get_text(const tl::lem_result &lr, uint32_t no, uint32_t form_id) const
{
    size_t sz;
    MAFSA_letter out_letters [1024];

    sz = turglem_build_form(tlem, lr.src.data(), lr.src.size(), out_letters, 1024,
                            lr.fi[no].paradigm, lr.fi[no].src_form, form_id);

    return _CHA::letters2string(out_letters, sz);
}

