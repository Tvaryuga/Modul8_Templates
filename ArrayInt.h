#pragma once
#ifndef INTARRAY_H
#define INTARRAY_H
#include <iostream>
#include <exception>
#include <climits>

using std::exception;

class bad_length : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: Bad length of array!";
    }
};
class bad_range : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: Bad range of array!";
    }
};

template <typename T>
class ArrayInt
{
private:
    int m_length{};
    T* m_data{};

public:
    ArrayInt() = default;
    ArrayInt(int length);
    ArrayInt(ArrayInt<T>& copy);
    ~ArrayInt();
    void erase();
    void set(const int index, T value);
    T& operator[](int index);
    void resize(int newLength);
    void findElement(const int index) const;                      // поиск элемента по индексу
    void insertBefore(T value, int index);
    void remove(int index);
    void insertAtBeginning(T value);
    void insertAtEnd(T value);
    int getLength() const;
    void copyContainerTo(ArrayInt<T>& to);                       // Вызывающий объект копируется в контейнер переданный в параметре

    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, ArrayInt<T>& container);
    ArrayInt<T>& operator=(ArrayInt<T>& array);
};

// ArrayInt methods
template <typename T>
void ArrayInt<T>::set(const int index, T value)
{
    if (index < 0 || index >= m_length)
        throw bad_range();
    else
    {
        m_data[index] = value;
    }
        
}
template <typename T>
ArrayInt<T>::ArrayInt(int length)
{
    m_length = length;
    if (length < 0)
        throw bad_length();
    if (length > INT_MAX)
        throw bad_length();
    if (length > 0)
        m_data = new T[length]{};
    else
        m_data = nullptr;
}

template <typename T>
ArrayInt<T>::ArrayInt(ArrayInt<T>& copy)
{
    m_length = copy.getLength();
    m_data = new T[m_length];
    for (int i(0); i < m_length; i++)
        m_data[i] = copy[i];
}

template <typename T>
ArrayInt<T>::~ArrayInt()
{
    delete[] m_data;
}

template <typename T>
void ArrayInt<T>::erase()
{
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
}

template <typename T>
T& ArrayInt<T>::operator[](int index)
{
    if (index < 0 || index >= m_length)
        throw bad_range();
    return m_data[index];
}

template <typename T>
void ArrayInt<T>::resize(int newLength)
{
    // if the array is already the right length, we're done
    if (newLength == m_length)
        return;

    if (newLength < 0)
        throw bad_length();
    // If we are resizing to an empty array, do that and return
    if (newLength == 0)
    {
        erase();
        return;
    }
    T* data{ new T[newLength] };

    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };
        int index = 0;
        for (; index < elementsToCopy; ++index)
            data[index] = m_data[index];
        if (newLength > m_length)
            while (index < newLength)
            {
                data[index] = 0;
                index++;
            }

    }
    else if (m_length == 0)
    {
        int index = 0;
        while (index < newLength)
        {
            data[index] = 0;
            index++;
        }
    }

    delete[] m_data;

    m_data = data;
    m_length = newLength;
}

template <typename T>
void ArrayInt<T>::findElement(const int index) const                                       // поиск элемента по индексу
{
    if (index < 0 || index >= m_length)
        throw bad_range();
    std::cout << "\nThe element " << index << " was founded! It equals " << m_data[index] << std::endl;
}

template <typename T>
void ArrayInt<T>::insertBefore(T value, int index)
{
    if (index < 0 || index > m_length)
        throw bad_range();

    T* data = new T[m_length + 1];

    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    data[index] = value;

    for (int after{ index }; after < m_length; ++after)
        data[after + 1] = m_data[after];

    delete[] m_data;
    m_data = data;
    ++m_length;
}

template <typename T>
void ArrayInt<T>::remove(int index)
{

    if (index < 0 || index >= m_length)
        throw bad_range();

    if (m_length == 1)
    {
        erase();
        return;
    }

    T* data{ new T[m_length - 1] };

    for (int before{ 0 }; before < index; ++before)
        data[before] = m_data[before];

    for (int after{ index + 1 }; after < m_length; ++after)
        data[after - 1] = m_data[after];

    delete[] m_data;
    m_data = data;
    --m_length;
}

template <typename T>
void ArrayInt<T>::insertAtBeginning(T value) { insertBefore(value, 0); }

template <typename T>
void ArrayInt<T>::insertAtEnd(T value) { insertBefore(value, m_length); }

template <typename T>
int ArrayInt<T>::getLength() const { return m_length; }

template <typename T>
void ArrayInt<T>::copyContainerTo(ArrayInt<T>& to)                                    // Копирование контейнера если их размеры равны
{
    if (this == &to)
        return;
    if (to.getLength() != this->getLength())
        throw bad_length();
    for (int i(0); i < to.getLength(); i++)
        to[i] = (*this)[i];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, ArrayInt<T>&  container)
{
    for (int i(0); i < container.getLength(); i++)
        os << container[i] << " ";
    return os;
}
template <typename T>
ArrayInt<T>& ArrayInt<T>::operator=(ArrayInt<T>& array)
{
    if (this == &array)
        return *this;
    delete[] m_data;
    m_length = array.getLength();
    m_data = new T[m_length];
    for (int i(0); i < m_length; i++)
        m_data[i] = array[i];
    return *this;
}
#endif