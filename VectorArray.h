#ifndef VECTORARRAY_H
#define VECTORARRAY_H

#include <memory>
#include <iostream>

template <typename T>
class IArray
{
public:
    virtual void add(const T value, size_t _index) = 0;

    virtual T& operator[](size_t _index) = 0;
    virtual T get(size_t _index) const = 0;

    virtual void remove(size_t _index) = 0;

    virtual size_t size() const = 0;

    virtual ~IArray() {}
};

using namespace std;

template <typename T>
class VectorArray : public IArray<T>
{
public:
    template <typename K>
    class iterator
    {
    public:
        iterator(K* _data_ptr) { m_ptr = _data_ptr; }

        bool operator==(iterator& _i) const { return m_ptr == _i.m_ptr; }
        bool operator!=(iterator& _i) const { return !(*this == _i); }

        K& operator*() { return *m_ptr; }

        void operator++() { ++m_ptr; }
        void operator--() { --m_ptr; }

    private:
        K* m_ptr {nullptr};
    };

    VectorArray(size_t _capacity = 10, double _trashhold = 0.5)
               : m_trashhold(_trashhold), m_capacity(_capacity)
    {
        m_data_ptr = new T[m_capacity];
    }

    virtual iterator<T> begin()
    {
        return iterator<T>(m_data_ptr);
    }

    virtual iterator<T> end()
    {
        return iterator<T>(m_data_ptr + m_size);
    }

    void add(const T value, size_t _index)
    {
        if (m_size == m_capacity)
        {
            m_capacity = m_size + static_cast<size_t>(m_trashhold * m_size);
            T* new_data_ptr = new T[m_capacity];
            memcpy(new_data_ptr, m_data_ptr, m_size * sizeof (T));

            delete [] m_data_ptr;
            m_data_ptr = new_data_ptr;
        }
        memcpy(m_data_ptr + _index + 1, m_data_ptr + _index,  (m_size - _index) * sizeof (T));
        m_data_ptr[_index] = std::move(value);
        ++m_size;
    }

    T& operator[](size_t _index)
    {
        return m_data_ptr[_index];
    }

    T get(size_t _index) const
    {
        return m_data_ptr[_index];
    }

    void remove(size_t _index)
    {
        memcpy(m_data_ptr + _index, m_data_ptr + _index + 1, (m_size - 1 - _index) * sizeof (T));
        --m_size;
    }

    void print()
    {
        cout << "array: ";
        for (int ix = 0; ix < m_capacity; ++ix)
        {
            if (ix < m_size)
            {
                cout << m_data_ptr[ix] << " ";
            } else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }

    T* data()
    {
        return m_data_ptr;
    }

    size_t size() const
    {
        return m_size;
    }

    void clear()
    {
        m_size = 0;
    }

    ~VectorArray() { delete [] m_data_ptr; }

private:
    double m_trashhold {0.0};
    size_t m_capacity  {0};
    size_t m_size      {0};
        T* m_data_ptr  {nullptr};
};



#endif // VECTORARRAY_H
