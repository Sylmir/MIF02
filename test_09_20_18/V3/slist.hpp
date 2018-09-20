#ifndef SLIST_HPP
#define SLIST_HPP

#include <cassert>
#include <cstdlib>

#include <exception>
#include <iostream>

template<typename T>
class MyList
{
private:
    struct Cell
    {
        Cell(const T& v) : _next(nullptr), _value(v), _count(1)
        {
            
        }
        
        ~Cell()
        {
            if (_next != nullptr)
                _next->decrease();
        }
        
        void increase()
        {
            assert(_count > 0 && "Cannot increase cell with _count of 0 or less");
            ++_count;
        }
        
        void decrease()
        {
            assert(_count > 0 && "Cannot decrease cell with _count of 0 or less");
            
            --_count;
            if (_count == 0)
            {
                delete this;
            }
        }
        
        Cell* _next;
        T _value;
        int _count;
    };
    
    class Iterator
    {
    private:
        Cell* _cell;
        
    public:
        Iterator(Cell* cell) : _cell(cell)
        {
            
        }
        
        Iterator& operator++() 
        {
            _cell = _cell->_next;
            return *this;
        }
        
        Iterator operator++(int)
        {
            Iterator copy(*this);
            _cell = _cell->_next;
            return copy;
        }
        
        bool operator==(const Iterator& rhs)
        {
            return _cell == rhs._cell;
        }
        
        bool operator!=(const Iterator& rhs)
        {
            return !(*this == rhs);
        }
        
        const T& operator*() const
        {
            return _cell->_value;
        }
    };
    
public:
    typedef Iterator iterator;
    
public:
    MyList() : _first(nullptr), _size(0)
    {
        
    }
    
    MyList(MyList const& other)
    {
        set_first(other._first);
        _size = other._size;
    }
    
    MyList& operator=(MyList const& rhs)
    {
        if (_first != nullptr)
            _first->decrease();
        
        set_first(rhs._first);
        
        _size = rhs._size;
        
        return *this;
    }
    
    ~MyList()
    {
        if (_first != nullptr)
            _first->decrease();
    }
    
    void push_front(const T& v)
    {
        Cell* cell = new Cell(v);
        cell->_next = _first;
        _first = cell;
        
        ++_size;
    }
    
    void push_back(const T& v)
    {
        Cell* cell = _first;
        
        if (cell == nullptr)
        {
            _first = new Cell(v);
        }
        else
        {
            while (cell->_next != nullptr)
                cell = cell->_next;
            
            cell->_next = new Cell(v);
        }
        
        ++_size;
    }
    
    const T& front() const
    {
        if (_first == nullptr)
            throw std::runtime_error("Empty list");
        
        return _first->_value;
    }
    
    std::size_t size() const
    {
        return _size;
    }
    
    template<typename T1> 
    friend std::ostream& operator<<(std::ostream&, const MyList<T1>&);
    
    iterator begin() const
    {
        return iterator(_first);
    }
    
    iterator end() const
    {
        return iterator(nullptr);
    }
    
private:
    void set_first(Cell* new_first)
    {
        _first = new_first;
        
        if (_first != nullptr)
            _first->increase();
    }
    
    Cell* _first;
    std::size_t _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const MyList<T>& list) 
{
    typename MyList<T>::Cell* cell = list._first;
    
    while (cell != nullptr)
    {
        out << cell->_value << std::endl;
        cell = cell->_next;
    }
    
    return out;
}

#endif /* SLIST_HPP */