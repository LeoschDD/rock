#pragma once

#include "list.h"

namespace rock
{
    template<typename K, typename T>
    class hashmap
    {
    private:
        struct entry
        {
            K key{};
            T element{};
            bool used{false};
            bool deleted{false};
        };
        
        rock::list<entry> m_entries;

        int m_size;
        int m_capacity;

    private:
        static inline size_t mixHash(size_t x)
        {
            x ^= x >> 33;
            x *= 0xff51afd7ed558ccdULL;
            x ^= x >> 33;
            x *= 0xc4ceb9fe1a85ec53ULL;
            x ^= x >> 33;
            return x;
        }
        
        size_t hash(const K& key)
        {
            return mixHash(static_cast<size_t>(std::hash<K>{}(key))) & 
                          (static_cast<size_t>(m_capacity) - 1);
        }

        size_t index(const K& key, bool& found)
        {
            size_t i = hash(key);
            
            int deleted = -1;

            int counter = 0;
            while (counter < m_capacity)
            {
                entry& e = m_entries.at((int)i);

                if (!e.used) 
                {
                    found = false;
                    return deleted != -1 ? static_cast<size_t>(deleted) : i;
                }

                if (!e.deleted && e.key == key)
                {
                    found = true;
                    return i;
                }

                if (e.deleted && deleted == -1)
                {
                    deleted = i;
                }
                
                ++counter;
                i = (i + 1) % m_capacity;
            }
            throw std::runtime_error("rock::hashmap: hashmap full");
        }

        void resize()
        {   
            int newCapacity = static_cast<int>(m_capacity * 2);          
            int oldCapacity = m_capacity;
            m_capacity = newCapacity;
            m_size = 0;

            rock::list<entry> temp(m_entries);

            m_entries = rock::list<entry>();
            for (int i = 0; i < newCapacity; ++i)
            {
                m_entries.push_back(entry{});
            }

            for (int i = 0; i < oldCapacity; ++i)
            {
                entry& e = temp.at(i);
                if (e.used && !e.deleted) insert(e.key, e.element);
            }
        }

    public:
        hashmap() : m_size(0), m_capacity(16)
        {
            for (int i = 0; i < m_capacity; ++i)
            {
                m_entries.push_back(entry{});
            }
        }

        void insert(const K& key, const T& element)
        {
            if (m_size * 2 > m_capacity) resize();

            bool foundKey = false;
            size_t i = index(key, foundKey);

            entry& e = m_entries.at(i);

            if (foundKey)
            {
                e.element = element;
                return;
            }

            e.element = element;
            e.key = key;
            e.used = true;
            e.deleted = false;

            m_size++;                

        }

        void erase(const K& key)
        {
            bool foundKey = false;
            size_t i = index(key, foundKey);
            if (foundKey)
            {
                entry& e = m_entries.at(i);
                e = entry{};
                e.deleted = true;
                e.used = true;
                --m_size;
            }
        }

        T* at(const K& key)
        {
            bool foundKey = false;
            size_t i = index(key, foundKey);
            if (foundKey) return &m_entries.at(i).element;
            return nullptr;
        }

        T& operator[](const K& key)
        {
            if (m_size * 2 > m_capacity) resize();

            bool foundKey = false;
            size_t i = index(key, foundKey);

            entry& e = m_entries.at(i);

            if (!foundKey) 
            {
                e.key = key;
                e.used = true;
                e.deleted = false;
                m_size++;                
            }
            return e.element;
        }

        int size() const {return m_size;}
        int capacity() const {return m_capacity;}
    };    
}