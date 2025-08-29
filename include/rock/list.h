#pragma once

#include <vector>
#include <stdexcept>

namespace rock
{
    template <typename T>
    class list
    {
    private:
        T* m_arr;
        int m_size;
        int m_capacity;

    void allocate_memory()
    {
        int newCapacity = m_capacity < 16 ? 16 : static_cast<int>(m_capacity * 2.5f);
        T* temp = new T[newCapacity];

        for (int i = 0; i < m_size; ++i)
        {
            temp[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = temp;
        m_capacity = newCapacity;
    }    
    
    public:
        list() : m_arr(nullptr), m_size(0), m_capacity(0) {}

        list(const list& list) 
            : m_size(list.size())
            , m_capacity(list.capacity())
        {
            m_arr = new T[m_capacity];

            for (int i = 0; i < m_size; ++i)
            {
                m_arr[i] = list.m_arr[i];
            }
        }

        list(const std::initializer_list<T> other) 
            : m_size(static_cast<int>(other.size()))
            , m_capacity(m_size)
        {
            m_arr = new T[m_capacity];

            int i = 0;
            for (auto& e : other)
            {
                m_arr[i] = e;
                ++i;
            }
        }

        list(const std::vector<T> other) : m_size(other.size()), m_capacity(other.capacity())
        {
            m_arr = new T[m_capacity];

            for (int i = 0; i < m_size; ++i)
            {
                m_arr[i] = other[i];
            }
        }

        list(int size, T element) : m_size(size), m_capacity(size)
        {
            m_arr = new T[size];
            for (int i = 0; i < size; ++i)
            {
                m_arr[i] = element;
            }
        }

        ~list()
        {
            delete []m_arr;
        }

        void push_back(T element)
        {
            if (m_size == m_capacity) allocate_memory();

            m_arr[m_size] = element;
            ++m_size;
        }

        void pop_back()
        {
            if (m_size == 0) return;
            --m_size;
        }

        void reserve(int newCapacity)
        {
            if (newCapacity > m_capacity)
            {
                T* temp = new T[newCapacity];

                for (int i = 0; i < m_size; ++i)
                {
                    temp[i] = m_arr[i];
                }
                delete[] m_arr;
                m_arr = temp;
                m_capacity = newCapacity;
            }
        }

        T& operator[](int i)
        {
            return at(i);
        }

        list& operator=(const list& other)
        {
            if (this == &other) return *this;

            delete[] m_arr;

            m_capacity = other.capacity();
            m_size = other.size();

            m_arr = new T[m_capacity];

            for (int i = 0; i < m_size; ++i)
            {
                m_arr[i] = other.m_arr[i];
            }
            return *this;
        }

        list& operator=(const std::vector<T>& other)
        {
            delete[] m_arr;

            m_capacity = other.capacity();
            m_size = other.size();

            m_arr = new T[m_capacity];

            for (int i = 0; i < m_size; ++i)
            {
                m_arr[i] = other[i];
            }
            return *this;
        }

        void operator=(const std::initializer_list<T> other)
        {
            delete[] m_arr;

            m_size = static_cast<int>(other.size());
            m_capacity = m_size;

            m_arr = new T[m_capacity];

            int i = 0;
            for (auto& e : other)
            {
                m_arr[i] = e;
                ++i;
            }
        }

        T& at(int i) 
        {
            if (i >= 0 && i < m_size) return m_arr[i];
            else throw std::out_of_range("rock::list: tried to access at invalid index!");
        }

        T* begin() {return m_arr;}
        T* end(){return m_arr + m_size;}

        const T* begin() const {return m_arr;}
        const T* end() const {return m_arr + m_size;}
 
        int size() const {return m_size;}
        int capacity() const {return m_capacity;}
    };    
}