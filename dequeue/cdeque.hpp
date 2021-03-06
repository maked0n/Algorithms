#ifndef CDEQUE_HPP
#define CDEQUE_HPP
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <vector>

template<class T>
class CDeque
{
private:
    T* dq_data;                                 //array of elements
    std::size_t dq_capacity;                    //allocated capacity
    std::size_t dq_size;                        //number of elements
    std::size_t dq_begin;                       //the beginning of dq_data
    std::size_t dq_end;                         //the end of dq_data
    void Realloc(const std::size_t size);

public:
    CDeque();
    CDeque(std::size_t const allocatedcapacity);
    CDeque(const CDeque& deque);
    ~CDeque();

    class CDequeIterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        CDequeIterator();
        T* dqiter_data;                         //pointer to dq_data
        std::size_t dqiter_index;               //real indexes in dq_data
        std::size_t dqiter_begin;               //the beginning of dq_data
        std::size_t dqiter_end;                 //the end of dq_data
        std::size_t dqiter_size;                //number of elements
        std::size_t dqiter_capacity;            //allocated capacity

    public:
        CDequeIterator(T* data, const std::size_t begin, const std::size_t end,
                       const std::size_t size, const std::size_t capacity, const std::size_t index = 0)
        {
            dqiter_data = data;
            dqiter_begin = begin;
            dqiter_end = end;
            dqiter_size = size;
            dqiter_capacity = capacity;
            dqiter_index = index % dqiter_capacity;
        }

        CDequeIterator friend operator +(const int count, const CDequeIterator iter)
        {
            CDequeIterator result = iter;
            result.dqiter_index = (result.dqiter_index + count) % result.dqiter_capacity;

            return result;
        }
        CDequeIterator operator +(const int count)
        {
            CDequeIterator result = *this;
            result.dqiter_index = (result.dqiter_index + count) % dqiter_capacity;

            return result;
        }
        CDequeIterator operator -(const int count)
        {
            CDequeIterator result = *this;
            result.dqiter_index = (result.dqiter_index + result.dqiter_capacity - count) % result.dqiter_capacity;
            return result;
        }
        void operator +=(const int count)
        {
            dqiter_index = (dqiter_index + count) % dqiter_capacity;
        }
        void operator -=(const int count)
        {
            dqiter_index = (dqiter_index + dqiter_capacity - count) % dqiter_capacity;
        }
        T& operator [](const int n)
        {
            std::size_t resultIndex = (dqiter_index + n) % dqiter_capacity;
            return dqiter_data[resultIndex];
        }
        T& operator *()
        {
            return dqiter_data[dqiter_index];
        }
        CDequeIterator& operator ++()
        {
            dqiter_index = (dqiter_index + 1) % dqiter_capacity;
            return *this;
        }
        const CDequeIterator operator ++(int)
        {
            CDequeIterator resultIter = *this;
            resultIter.dqiter_index = (resultIter.dqiter_index + 1) % dqiter_capacity;
            return resultIter;
        }
        CDequeIterator& operator --()
        {
            dqiter_index = (dqiter_index + dqiter_capacity - 1) % dqiter_capacity;
            return *this;
        }
        const CDequeIterator operator --(int)
        {
            CDequeIterator resultIter = *this;
            resultIter.dqiter_index = (resultIter.dqiter_index + resultIter.dqiter_capacity - 1) % dqiter_capacity;
            return resultIter;
        }
        int operator -(const CDequeIterator iter)
        {
            std::size_t firstIndex = dqiter_index;
            std::size_t secondIndex = iter.dqiter_index;

            if(dqiter_begin != 0)                                                                       //possible only when dqiter_begin > dqiter_end
            {
                if(firstIndex >= dqiter_begin)
                    firstIndex = dqiter_index - dqiter_begin;
                else
                    firstIndex = dqiter_index + (dqiter_capacity - dqiter_begin);

                if(secondIndex >= dqiter_begin)
                    secondIndex = iter.dqiter_index - iter.dqiter_begin;
                else
                    secondIndex = iter.dqiter_index + (iter.dqiter_capacity - iter.dqiter_begin);
            }

            return (firstIndex - secondIndex);
        }
        bool operator <(const CDequeIterator iter)
        {
            std::size_t firstIndex = dqiter_index;
            std::size_t secondIndex = iter.dqiter_index;

            if(dqiter_begin != 0)                                                                       //possible only when dqiter_begin > dqiter_end
            {
                if(firstIndex >= dqiter_begin)
                    firstIndex = dqiter_index - dqiter_begin;
                else
                    firstIndex = dqiter_index + (dqiter_capacity - dqiter_begin);

                if(secondIndex >= dqiter_begin)
                    secondIndex = iter.dqiter_index - iter.dqiter_begin;
                else
                    secondIndex = iter.dqiter_index + (iter.dqiter_capacity - iter.dqiter_begin);
            }

            return (firstIndex < secondIndex ? true : false);
        }
        bool operator <=(const CDequeIterator iter)
        {
            std::size_t firstIndex = dqiter_index;
            std::size_t secondIndex = iter.dqiter_index;

            if(dqiter_begin != 0)                                                                       //possible only when dqiter_begin > dqiter_end
            {
                if(firstIndex >= dqiter_begin)
                    firstIndex = dqiter_index - dqiter_begin;
                else
                    firstIndex = dqiter_index + (dqiter_capacity - dqiter_begin);

                if(secondIndex >= dqiter_begin)
                    secondIndex = iter.dqiter_index - iter.dqiter_begin;
                else
                    secondIndex = iter.dqiter_index + (iter.dqiter_capacity - iter.dqiter_begin);
            }

            return (firstIndex <= secondIndex ? true : false);
        }
        bool operator >(const CDequeIterator iter)
        {
            std::size_t firstIndex = dqiter_index;
            std::size_t secondIndex = iter.dqiter_index;

            if(dqiter_begin != 0)                                                                       //possible only when dqiter_begin > dqiter_end
            {
                if(firstIndex >= dqiter_begin)
                    firstIndex = dqiter_index - dqiter_begin;
                else
                    firstIndex = dqiter_index + (dqiter_capacity - dqiter_begin);

                if(secondIndex >= dqiter_begin)
                    secondIndex = iter.dqiter_index - iter.dqiter_begin;
                else
                    secondIndex = iter.dqiter_index + (iter.dqiter_capacity - iter.dqiter_begin);
            }

            return (firstIndex > secondIndex ? true : false);
        }
        bool operator >=(const CDequeIterator iter)
        {
            std::size_t firstIndex = dqiter_index;
            std::size_t secondIndex = iter.dqiter_index;

            if(dqiter_begin != 0)                                                                       //possible only when dqiter_begin > dqiter_end
            {
                if(firstIndex >= dqiter_begin)
                    firstIndex = dqiter_index - dqiter_begin;
                else
                    firstIndex = dqiter_index + (dqiter_capacity - dqiter_begin);

                if(secondIndex >= dqiter_begin)
                    secondIndex = iter.dqiter_index - iter.dqiter_begin;
                else
                    secondIndex = iter.dqiter_index + (iter.dqiter_capacity - iter.dqiter_begin);
            }

            return (firstIndex >= secondIndex ? true : false);
        }
        bool operator ==(const CDequeIterator iter)
        {
            return (dqiter_index == iter.dqiter_index ? true : false);
        }
        bool operator !=(const CDequeIterator iter)
        {
            return (dqiter_index != iter.dqiter_index ? true : false);
        }
    };

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    CDequeIterator begin();
    CDequeIterator& begin() const;
    CDequeIterator& cbegin() const;
    std::reverse_iterator<CDequeIterator> rbegin();
    std::reverse_iterator<CDequeIterator>& rbegin() const;
    std::reverse_iterator<CDequeIterator>& crbegin() const;
    CDequeIterator end();
    CDequeIterator& end() const;
    CDequeIterator& cend() const;
    std::reverse_iterator<CDequeIterator> rend();
    std::reverse_iterator<CDequeIterator>& rend() const;
    std::reverse_iterator<CDequeIterator>& crend() const;
    std::size_t size() const;
    bool empty() const;
    T at(const int position) const;
    T& operator[](const std::size_t position);
};

template<class T>
CDeque<T>::CDeque(const std::size_t allocatedCapacity)
{
    dq_data = new T[allocatedCapacity];
    dq_capacity = allocatedCapacity;
    dq_size = 0;
    dq_begin = 0;
    dq_end = 0;
}

template<class T>
CDeque<T>::CDeque(const CDeque& deque)
{
    dq_data = deque.dq_data;
    dq_capacity = deque.dq_capacity;
    dq_size = deque.dq_size;
    dq_begin = deque.dq_begin;
    dq_end = deque.dq_end;
}

template<class T>
CDeque<T>::CDeque()
{
    dq_data = new T[2];
    dq_capacity = 2;
    dq_size = 0;
    dq_begin = 0;
    dq_end = 0;
}

template<class T>
CDeque<T>::~CDeque()
{
    if(dq_data)
        delete [] dq_data;
}

template<class T>
T& CDeque<T>::operator [](const std::size_t position)
{
    assert(position < dq_size);

    if(dq_begin != 0)
    {
        if(dq_begin + position >= dq_capacity)
            return dq_data[position - (dq_capacity - dq_begin)];
        else
            return dq_data[dq_begin + position];
    }
    else
        return dq_data[position];
}

template<class T>
void CDeque<T>::Realloc(const std::size_t size)
{
    T* tempDeque = new T[size];

    for(std::size_t i = dq_begin, tmpPos = 0; i != dq_end ; i = (i + 1) % dq_capacity, ++tmpPos)
        tempDeque[tmpPos] = dq_data[i];

    delete [] dq_data;

    dq_data = tempDeque;

    dq_capacity = size;
    dq_begin = 0;
    dq_end = dq_size;
}

template<class T>
void CDeque<T>::push_back(const T& value)
{
    if((dq_size + 1) == dq_capacity && dq_size != 0)
        Realloc(dq_capacity * 2);

    dq_data[dq_end] = value;
    ++dq_size;
    dq_end = (dq_end + 1) % dq_capacity;
}

template<class T>
void CDeque<T>::push_front(const T& value)
{
    if((dq_size + 1) == dq_capacity && dq_size != 0)
        Realloc(dq_capacity * 2);

    dq_begin = (dq_begin - 1) % dq_capacity;
    dq_data[dq_begin] = value;
    ++dq_size;
}

template<class T>
void CDeque<T>::pop_back()
{
    if(dq_size <= 0)
        return;

    if(4 * dq_size <= dq_capacity)
        Realloc(dq_capacity / 2);

    --dq_size;
    dq_end = (dq_end - 1) % dq_capacity;
}

template<class T>
void CDeque<T>::pop_front()
{
    if(dq_size <= 0)
        return;

    dq_begin = (dq_begin + 1) % dq_capacity;

    if(4 * dq_size <= dq_capacity)
        Realloc(dq_capacity / 2);

    --dq_size;
}

template<class T>
typename CDeque<T>::CDequeIterator& CDeque<T>::begin() const
{
    const CDeque<T>::CDequeIterator beginIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_begin);
    return &beginIter;
}

template<class T>
typename CDeque<T>::CDequeIterator CDeque<T>::begin()
{
    CDeque<T>::CDequeIterator beginIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_begin);
    return beginIter;
}

template<class T>
typename CDeque<T>::CDequeIterator& CDeque<T>::cbegin() const
{
    const CDeque<T>::CDequeIterator beginIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_begin);
    return &beginIter;
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator>& CDeque<T>::rbegin() const
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(end());
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator> CDeque<T>::rbegin()
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(end());
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator>& CDeque<T>::crbegin() const
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(cend());
}

template<class T>
typename CDeque<T>::CDequeIterator& CDeque<T>::end() const
{
    const CDeque<T>::CDequeIterator endIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_end);
    return &endIter;
}

template<class T>
typename CDeque<T>::CDequeIterator CDeque<T>::end()
{
    CDeque<T>::CDequeIterator endIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_end);
    return endIter;
}

template<class T>
typename CDeque<T>::CDequeIterator& CDeque<T>::cend() const
{
    CDeque<T>::CDequeIterator endIter(dq_data, dq_begin, dq_end, dq_size, dq_capacity, dq_end);
    return &endIter;
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator> CDeque<T>::rend()
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(begin());
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator>& CDeque<T>::rend() const
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(begin());
}

template<class T>
std::reverse_iterator<typename CDeque<T>::CDequeIterator>& CDeque<T>::crend() const
{
    return std::reverse_iterator<typename CDeque<T>::CDequeIterator>(cbegin());
}

template<class T>
std::size_t CDeque<T>::size() const
{
    return dq_size;
}

template<class T>
bool CDeque<T>::empty() const
{
    return (dq_size == 0 ? true : false);
}

template<class T>
T CDeque<T>::at(const int position) const
{
    assert(position < dq_size);

    if(dq_begin != 0)
    {
        if(dq_begin + position >= dq_capacity)
            return dq_data[position - (dq_capacity - dq_begin)];
        else
            return dq_data[dq_begin + position];
    }
    else
        return dq_data[position];
}

#endif // CDEQUE_HPP
