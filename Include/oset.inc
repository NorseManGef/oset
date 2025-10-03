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
}

/********** ITERATION **********/

TT typename OST::iterator OST::begin()
{
    return iterator(_head, false);
}

TT typename OST::const_iterator OST::cbegin() const
{
    return const_iterator(_head, false);
}

TT typename OST::iterator OST::rbegin()
{
    return iterator(_tail, true);
}

TT typename OST::const_iterator OST::crbegin() const
{
    return const_iterator(_tail, true);
}

TT typename OST::iterator OST::end()
{
    return iterator(nullptr, false);
}

TT typename OST::const_iterator OST::cend() const
{
    return const_iterator(nullptr, false);
}

TT typename OST::iterator OST::rend()
{
    return iterator(nullptr, true);
}

TT typename OST::const_iterator OST::crend() const
{
    return const_iterator(nullptr, true);
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
    int base = hval % _capacity;

    if (findItem(base, item))
    {
        return false;
    }

    Node_t* node = new Node_t(item);
    if (_tail != nullptr)
    {
        node->prev = _tail;
        _tail->next = node;
        _tail = node;
    }
    else
    {
        _tail = node;
        _head = node;
    }

    int offset = 0;

    // attempt to add MAX_COLLISION_AMOUNT times, if it fails: resize, and try again.
    bool needsResize = true;
    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        int index = (base + offset) % _capacity;

        if (_data[index] == nullptr)
        {
            _data[index] = node;
            needsResize = false;
            break;
        }
        else
        {
            offset = offset == 0 ? 2 : offset * 2;
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
    int base = hval % _capacity;
    int offset = 0;

    int index;

    // searches for the item. If not found, return false, else remove.
    bool itemFound = false;
    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        index = (base + offset) % _capacity;

        if (_data[index] != nullptr && _data[index]->_data == item)
        {
            itemFound = true;
            break;
        }
        offset = offset == 0 ? 2 : offset * 2;
    }
    if (!itemFound)
    {
        return false;
    }

    remove_node(_data[index]);
    
    delete _data[index];
    _data[index] = nullptr;

    --_size;
    return true;
}

TT void OST::clear()
{
    delete[] _data;
    _data = nullptr;

    clear_list();
    _size = 0;
    _capacity = 0;
}

/********** OPERATORS **********/

TT OST& OST::operator=(const OST& other)
{
    if (this != other)
    {
        _size = other._size;
        _capacity = other._capacity;
        delete[] _data;
        _data = new Node_t*[_capacity];
        std::copy(other._data, other._data + _capacity, _data);

        copy_list(other._head);
    }
    return *this;
}

TT OST& OST::operator=(const OST&& other)
{
    _data = other._data;
    other._data = nullptr;

    _head = other._head;
    other._head = nullptr;

    _tail = other._tail;
    other._tail = nullptr;

    _size = other._size;
    other->_size = 0;

    _capacity = other._capacity;
    other->_capacity = 0;
}

TT OST& OST::operator+=(const T& item)
{
    if (!add(item))
    {
        throw item_already_exists("item: " << item << " already present in set");
    }
    return *this;
}

TT std::ostream& operator<<(std::ostream& out, const OST& oset)
{
    out << "[";
    nmg::Node<T>* current = oset._head;
    for (; current->next != nullptr; current = current->next)
    {
        out << current->_data << ", ";
    }
    out << current->_data;
    out << "]";
    return out;
}

TT bool OST::findItem(int base, const T& item) const
{
    int offset = 0;

    for (int i = 0; i < MAX_COLLISION_AMOUNT; ++i)
    {
        int index = (base + offset) % _capacity;
        if (_data[index] != nullptr && _data[index]->_data == item)
        {
            return true;
        }
        offset = offset == 0 ? 2 : offset * 2;
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

TT void OST::clear_list()
{
    while (_head != nullptr)
    {
        Node_t* node = _head;
        _head = _head->next;
        delete node;
    }
}

TT void OST::copy_list(const Node_t* source)
{
    if (_head != nullptr)
    {
        clear_list();
    }

    _head = new Node_t*(source->_data);
    _tail = _head;
    source = source->next;

    while (source != nullptr)
    {
        _tail->next = new Node_t*(source->_data);
        _tail->next->prev = _tail;

        _tail = _tail->next;
        source = source->next;
    }
}

TT void OST::resize_data()
{
    bool needsResize;
    do {
        delete[] _data;
        _capacity = _capacity * 4;

        _data = new Node_t*[_capacity];

        for (int i = 0; i < _capacity; ++i)
        {
            _data[i] = nullptr;
        }


        for (Node_t* current = _head; current != nullptr; current = current->next)
        {
            hash_t hval = hash(current->_data);
            int base = hval % _capacity;

            int offset = 0;
            
            needsResize = true;
            for(int i = 0; i < MAX_COLLISION_AMOUNT; ++i){
                int index = (base + offset) % _capacity;
                if (_data[index] == nullptr)
                {
                    _data[index] = current;
                    needsResize = false;
                    break;
                }
                else
                {
                    offset = offset == 0 ? 2 : offset * 2;
                }
            }
            if (needsResize) break;
        }
    }
    while (needsResize);
}
