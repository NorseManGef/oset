#pragma once

#include <iostream>

#include "oset.h"

#define TT template <typename T>
#define OST nmg::OSet<T>

TT OST::OSet()
{
    // TODO
}

TT OST::OSet(const OST& other)
{
    // TODO
}

TT OST::OSet(const OST&& other)
{
    // TODO
}

TT OST::~OSet()
{
    // TODO
}

/********** ITERATION **********/

TT typename OST::iterator OST::begin()
{
    // TODO
}

TT typename OST::const_iterator OST::cbegin() const
{
    // TODO
}

TT typename OST::iterator OST::rbegin()
{
    // TODO
}

TT typename OST::const_iterator OST::crbegin() const
{
    // TODO
}

TT typename OST::iterator OST::end()
{
    // TODO
}

TT typename OST::const_iterator OST::cend() const
{
    // TODO
}

TT typename OST::iterator OST::rend()
{
    // TODO
}

TT typename OST::const_iterator OST::crend() const
{
    // TODO
}

/********** DATA **********/

TT size_t OST::size() const
{
    // TODO
}

TT bool OST::empty() const
{
    // TODO
}

TT bool OST::contains(const T& item) const
{
    // TODO
}

/********** MUTATION **********/

TT bool OST::add(const T& item)
{
    // TODO
}

TT bool OST::remove(const T& item)
{
    // TODO
}

TT void OST::clear()
{
    // TODO
}

/********** OPERATORS **********/

TT OST& OST::operator=(const OST& other)
{
    // TODO
}

TT OST& OST::operator=(const OST&& other)
{
    // TODO
}

TT OST& OST::operator+=(const T& item)
{
    // TODO
}

TT std::ostream& operator<<(std::ostream& out, const OST& oset)
{
    // TODO
}
