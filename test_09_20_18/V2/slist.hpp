#ifndef SLIST_HPP
#define SLIST_HPP

#include <cstdlib>

#include <exception>
#include <iostream>

template<typename T>
class MyList
{
public:
    MyList() : _first(nullptr), _size(0)
    {
        
    }
    
    MyList(MyList const&) = delete;
    MyList& operator=(MyList const&) = delete;
    
    ~MyList()
    {
        if (_first != nullptr)
            delete _first;
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
    
private:
    struct Cell
    {
        Cell(const T& v) : _next(nullptr), _value(v) 
        {
            
        }
        
        ~Cell()
        {
            if (_next != nullptr)
                delete _next;
        }
        
        Cell* _next;
        T _value;
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
    
    Cell* _first;
    std::size_t _size;
    
public:
    typedef Iterator iterator;
    
    iterator begin() const
    {
        return iterator(_first);
    }
    
    iterator end() const
    {
        return iterator(nullptr);
    }
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