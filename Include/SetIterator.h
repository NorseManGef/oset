#pragma once

#include <iterator>

#define STB typename SetIteratorBase<T, sizeT, T&, T*>
#define CSTB typename SetIteratorBase<T, sizeT, const T&, const T*>

namespace nmg
{
template <typename T> class Node;

template <typename T> class OSet;

template <typename T, typename sizeT, typename refT, typename ptrT> class SetIteratorBase
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = size_t;
    using size_type = sizeT;
    using value_type = T;
    using pointer = ptrT;
    using reference = refT;

    using self = SetIteratorBase<T, sizeT, refT, ptrT>;

    self& operator++();   // prefix
    self operator++(int); // postfix

    self& operator--();
    self operator--(int);

    reference operator*();

    pointer operator->();

    self& operator=(const self& other);

    bool operator==(const self& other) const;
    bool operator!=(const self& other) const;

  protected:
    SetIteratorBase(Node<T>* node, bool isReverse);
    SetIteratorBase(const self& other);

  private:
    Node<T>* node;
    bool isReverse;
};

template <typename T, typename sizeT> class SetIterator : public SetIteratorBase<T, sizeT, T&, T*>
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = STB::difference_type;
    using size_type = STB::size_type;
    using value_type = STB::value_type;
    using pointer = STB::pointer;
    using reference = STB::reference;

    friend class OSet<T>;

  private:
    SetIterator(Node<T>* node, bool isReverse);
    SetIterator(const SetIterator<T, sizeT>& other);
};
template <typename T, typename sizeT> class ConstSetIterator : public SetIteratorBase<T, sizeT, const T&, const T*>
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = CSTB::difference_type;
    using size_type = CSTB::size_type;
    using value_type = CSTB::value_type;
    using pointer = CSTB::pointer;
    using reference = CSTB::reference;

    friend class OSet<T>;

  private:
    ConstSetIterator(Node<T>* node, bool isReverse);
    ConstSetIterator(const ConstSetIterator<T, sizeT>& other);
};
} // namespace nmg

#undef STB
#undef CSTB

#include "SetIterator.inc"
