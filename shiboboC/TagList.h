#ifndef SHIBOBO_TAGLIST_H_
#define SHIBOBO_TAGLIST_H_

#include "NameTag.h"

namespace shibobo {
    class TagList {
        NameTag* m_tags{};
        int m_size{};
        int m_count{};

    public:
      TagList(int num);
      void add(const NameTag& nt);
      void print() const;
      ~TagList();
    };
}

#endif