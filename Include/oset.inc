#pragma once

#include <algorithm>
#include <iostream>

#include "oset.h"

#include "hash.h"

#define TT template <typename T>
#define OST nmg::OSet<T>

TT OST::OSet()
    : _capacity(DEFAULT_CAPACITY), _size(0), _head(nullptr), _tail(nullptr)
{
    _data = new Node_t*[_capacity];
    for (int i = 0; i < _capacity; ++i)
    {
        _data[i] = nullptr;
    }
}

TT OST::OSet(const OST& other)
    : _capacity(other._capacity), _size(other._size)
{
    _data = new Node_t*[_capacity];
    std::copy(other._data, other._data + _capacity, _data);
    copy_list(other._head);
}

TT OST::OSet(const OST&& other)
    : _capacity(other._capacity), _size(other._size), _data(other._data), _head(other._head), _tail(other._tail)
{
    other._data = nullptr;
}

TT OST::~OSet()
{
    clear();
    delete _data;
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
    return _size;
}

TT bool OST::empty() const
{
    return _size == 0;
}

TT bool OST::contains(const T& item) const
{
    hash_t hval = hash(item);
    int index = hval % _capacity;

    return findItem(index, item);
}

/********** MUTATION **********/

TT bool OST::add(const T& item)
{
    hash_t hval = hash(item);
    int index = hval % _capacity;

    if (findItem(index, item))
    {
        return false;
    }

    Node_t* node = new Node_t(item);
    node->prev = _tail;
    _tail->next = node;
    _tail = node;

    // attempt to add MAX_COLLISION_AMOUNT times, if it fails: resize, and try again.
    bool needsResize = true;
    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        if (_data[index] == nullptr)
        {
            _data[index] = node;
            needsResize = false;
            break;
        }
        else
        {
            index = index * index;
        }
    }
    if (needsResize)
    {
        resize_data();
        add(item);
    }

    ++_size;
    return true;
}

TT bool OST::remove(const T& item)
{
    hash_t hval = hash(item);
    int index = hval % _capacity;

    // searches for the item. If not found, return false, else remove.
    bool itemFound = false;
    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        if (_data[index] != nullptr && _data[index] == item)
        {
            itemFound = true;
            break;
        }
        index = index * index;
    }
    if (!itemFound)
    {
        return false;
    }

    remove_node(_data[index]);

    _data[index] = nullptr;

    --_size;
    return true;
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

TT bool OST::findItem(int index, const T& item)
{
    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        if (_data[index] != nullptr && _data[index]->_data == item)
        {
            return true;
        }
        index = index * index;
    }
    return false;
}

TT void OST::remove_node(Node_t* node)
{
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        _head = node->next;
    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        _tail = node->prev;
}
