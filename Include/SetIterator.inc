#pragma once

#include "SetIterator.h"
#include <stdexcept>

#define TTSRP template <typename T, typename sizeT, typename refT, typename ptrT>
#define STB nmg::SetIteratorBase<T, sizeT, refT, ptrT>
#define STBT TTSRP STB
#define TTS template <typename T, typename sizeT>
#define STP nmg::SetIteratorBase<T, sizeT, T&, T*>
#define STV nmg::SetIterator<T, sizeT>
#define STVT TTS STV
#define CSTB nmg::ConstSetIterator<T, sizeT>
#define CSTBT TTS CSTB

TTSRP typename STB::self& STB::operator++() // prefix
{
    if (node != nullptr)
    {
        if (isReverse)
        {
            node = node->prev;
        }
        else
        {
            node = node->next;
        }
    }
    return *this;
}

TTSRP typename STB::self STB::operator++(int)
{
    self tempIt(*this);
    if (node != nullptr)
    {
        if (isReverse)
        {
            node = node->prev;
        }
        else
        {
            node = node->next;
        }
    }
    return tempIt;
}

TTSRP typename STB::self& STB::operator--()
{
    if (isReverse)
    {
        node = node->next;
    }
    else
    {
        node = node->prev;
    }
    return *this;
}

TTSRP typename STB::self STB::operator--(int)
{
    self tempIt(*this);
    if (isReverse)
    {
        node = node->next;
    }
    else
    {
        node = node->prev;
    }
    return tempIt;
}

TTSRP typename STB::reference STB::operator*()
{
    if (node == nullptr)
    {
        throw std::out_of_range("node is null");
    }
    return node->_data;
}

TTSRP typename STB::pointer STB::operator->()
{
    return node->_data;
}

TTSRP typename STB::self& STB::operator=(const self& other)
{
    if (&other != this)
    {
        node = other.node;
        isReverse = other.isReverse;
    }
    return *this;
}

TTSRP bool STB::operator==(const self& other) const
{
    return node == other.node && isReverse == other.isReverse;
}

TTSRP bool STB::operator!=(const self& other) const
{
    return node != other.node && isReverse != other.isReverse;
}

STBT::SetIteratorBase(Node<T>* node, bool isReverse)
    : node(node), isReverse(isReverse)
{
}

STBT::SetIteratorBase(const self& other)
    : node(other.node), isReverse(other.isReverse)
{
}

STVT::SetIterator(Node<T>* node, bool isReverse)
    : STP(node, isReverse)
{
}

STVT::SetIterator(const STV& other)
    : STP(other.node, other.isReverse)
{
}

CSTBT::ConstSetIterator(Node<T>* node, bool isReverse)
    : STP(node, isReverse)
{
}

CSTBT::ConstSetIterator(const CSTB& other)
    : STP(other.node, other.isReverse)
{
}

#undef STB
#undef CSTB
#undef STP
#undef STV
#undef TTS
#undef TTSRP
#undef STBT
#undef STVT
#undef CSTBT
