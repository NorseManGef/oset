/*
    An ordered set. Efficient insertion, retrieval, and removal,
    while maintaining insertion order.
*/

#pragma once
#ifndef OSET_H
#define OSET_H
#include <iostream>
#include <stdexcept>
#include "SetIterator.h"


namespace nmg
{

const size_t DEFAULT_CAPACITY = 64;
const int MAX_COLLISION_AMOUNT = 4;
// forward declarations for friend operators
template <typename T> class OSet;
template <typename T> std::ostream& operator<<(std::ostream& out, const nmg::OSet<T>& oset);

struct item_already_exists : public std::logic_error
{
    item_already_exists(const char* message)
        : std::logic_error(message)
    {
    }

    item_already_exists()
        : std::logic_error("item already exists")
    {
    }
};

template <typename T> struct Node
{
    T _data;
    Node<T>* next;
    Node<T>* prev;

    explicit Node(const T& item)
        : next(nullptr), prev(nullptr), _data(item)
    {
    }
};

template <typename T> class OSet
{
  public:
    /********** ALIASES **********/

    using iterator = SetIterator<T, size_t>;
    using const_iterator = ConstSetIterator<T, size_t>;
    using Node_t = Node<T>;

    /********** CONSTRUCTORS **********/

    /// @brief Default constructor.
    OSet();

    /// @brief Copy constructor.
    /// @param other Itibag data being copied to this itibag.
    OSet(const OSet<T>& other);

    /// @brief Move constructor.
    /// @param other Itibag data to be moved to this itibag.
    OSet(const OSet<T>&& other);

    /// @brief Destructor.
    ~OSet();

    /********** ITERATION **********/

    /// @brief Create iterator to beginning.
    /// @return An iterator to the beginning of the collection.
    iterator begin();

    /// @brief Create constant iterator to beginning.
    /// @return A const iterator to the beginning of the collection.
    const_iterator cbegin() const;

    /// @brief Create reverse iterator to end,
    /// @return A reverse iterator to the end of the collection.
    iterator rbegin();

    /// @brief Create const reverse iterator to end.
    /// @return A const reverse iterator to the end of the collection.
    const_iterator crbegin() const;

    /// @brief Create iterator to end.
    /// @return An iterator to the end of the collection.
    iterator end();

    /// @brief Create constant iterator to end.
    /// @return A constant iterator to the end of the collection.
    const_iterator cend() const;

    /// @brief Create reverse iterator to beginning.
    /// @return A reverse iterator to the beginning of the collection.
    iterator rend();

    /// @brief Create const reverse iterator to beginning.
    /// @return A constant reverse iterator to the beginning of the collection.
    const_iterator crend() const;

    /********** DATA **********/

    /// @brief Gets the size of the collection.
    /// @return The size of the collection.
    size_t size() const;

    /// @brief Returns if the collection is empty.
    /// @return True if the collection is empty, false otherwise.
    bool empty() const;

    /// @brief Returns if the item is in the collection.
    /// @param item The item to search for.
    /// @return True if the item is in the collection, false otherwise.
    bool contains(const T& item) const;

    /********** MUTATION **********/

    /// @brief Add an item to the itibag.
    /// @param item Item to be added.
    /// @return true for success, false for failure.
    bool add(const T& item);

    /// @brief Remove an item from the itibag.
    /// @param item Item to be removed.
    /// @return True if the item was removed. False if it was not.
    bool remove(const T& item);

    /// @brief Removes all items from the itibag.
    void clear();

    /********** OPERATORS **********/

    /// @brief copy-assignment operator.
    /// @param other Itibag to copy.
    /// @return This itibag.
    OSet<T>& operator=(const OSet<T>& other);

    /// @brief move-assignment operator.
    /// @param other Itibag to move.
    /// @return This itibag.
    OSet<T>& operator=(const OSet<T>&& other);

    /// @brief Adds an item to the collection.
    /// @param item The item to add.
    /// @return This itibag.
    OSet<T>& operator+=(const T& item);

    /// @brief Inserts an oset into a stream.
    /// @param out The output stream to insert into.
    /// @param oset The oset to insert.
    /// @return The output stream.
    friend std::ostream& operator<< <>(std::ostream& out, const OSet<T>& oset);

  private:
    Node_t** _data;
    size_t _size;
    size_t _capacity;
    Node_t* _head;
    Node_t* _tail;

    void copy_list(const Node_t* source);
    void clear_list();
    void resize_data();
    bool findItem(int index, const T& item);
    void remove_node(Node_t* node);
};
}; // namespace nmg

#include "oset.inc"
#endif
