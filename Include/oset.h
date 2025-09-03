/*
    An ordered set. Efficient insertion, retrieval, and removal,
    while maintaining insertion order.
*/
#ifndef OSET_H
#define OSET_H
#include <iostream>

namespace ianwio
{
    // forward declarations for friend operators
    template <typename T> class OSet;
    template <typename T> std::ostream& operator << (std::ostream& out, const ianwio::OSet<T>& oset);

    template <typename T>
    class OSet
    {
        public:

        /********** ALIASES **********/

        using iterator = void; // TODO
        using const_iterator = void; // TODO

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
        OSet<T>& operator = (const OSet<T>& other);

        /// @brief move-assignment operator.
        /// @param other Itibag to move.
        /// @return This itibag.
        OSet<T>& operator = (const OSet<T> && other);

        /// @brief Adds an item to the collection.
        /// @param item The item to add.
        /// @return This itibag.
        OSet<T>& operator += (const T& item);

        /// @brief Inserts an oset into a stream.
        /// @param out The output stream to insert into.
        /// @param oset The oset to insert.
        /// @return The output stream.
        friend std::ostream& operator << <>(std::ostream& out, const OSet<T>& oset);
    };
};
#endif