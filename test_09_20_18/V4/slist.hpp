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
    template<typename T1>
    struct Cell
    {
        Cell(const T1& v) : _next(nullptr), _value(v), _count(1)
        {
            
        }
        
        ~Cell()
        {
            if (_next != nullptr)
                _next->decrease();
        }
        
        int count() const 
        {
            return _count;
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
        
        Cell<T1>* _next;
        T1 _value;
        int _count;
    };
    
    template<typename T1>
    class Iterator
    {
        friend class MyList<T1>;
        
    private:
        Cell<T1>* _cell;
        
    public:
        Iterator(Cell<T1>* cell) : _cell(cell)
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
    typedef Iterator<T> iterator;
    
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
        Cell<T>* cell = new Cell<T>(v);
        cell->_next = _first;
        _first = cell;
        
        ++_size;
    }
    
    void push_back(const T& v)
    {
        Cell<T>* cell = _first;
        
        if (cell == nullptr)
        {
            _first = new Cell<T>(v);
        }
        else
        {
            while (cell->_next != nullptr)
                cell = cell->_next;
            
            cell->_next = new Cell<T>(v);
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
    
    iterator insert(iterator at, const T& v)
    {
        iterator it = begin();
        if (it._cell == at._cell)
        {
            /* 
             * If we are inserting at the first cell, there is nothing special
             * to do. It is literally a push_front. This won't change any other
             * list.
             */
            push_front(v);
            return begin();
        }
        else
        {
            /* 
             * Otherwise, we have something like this, before inserting :
             *  cell_before -> cell_at -> cell_after
             * Usually, we would end up with that, after inserting :
             * cell_before -> new_cell -> cell_at -> cell_after.
             *
             * Updating the list this way will break lists built from this list.
             * cell_before needs to be replaced. If we change cell_before, we 
             * need to change the cell before it, because it no longer points 
             * to the right cell. We must do that to all cells that come before
             * the cell we are inserting at.
             */
            
            // new_head represents the new chain.
            Cell<T>* new_head = new Cell<T>(_first->_value);
            // We decrease old_first when we are done, because we don't hold it
            // anymore.
            Cell<T>* old_first = _first;
            
            // Jump to the second cell, we already copied the first.
            ++it;
            
            _first = new_head;
            
            for (; it != at; ++it)
            {
                new_head->_next = new Cell<T>(*it);
                new_head = new_head->_next;
            }
            
            // When it == at, link the last created cell with cell that holds v.
            Cell<T>* new_cell = new Cell<T>(v);
            new_head->_next = new_cell;
            new_cell->_next = at._cell;
            at._cell->increase();
            
            old_first->decrease();
            ++_size;
            return iterator(new_cell);
        }
    }
    
private:
    void set_first(Cell<T>* new_first)
    {
        _first = new_first;
        
        if (_first != nullptr)
            _first->increase();
    }
    
    Cell<T>* _first;
    std::size_t _size;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const MyList<T>& list) 
{
    typename MyList<T>::template Cell<T>* cell = list._first;
    
    while (cell != nullptr)
    {
        out << cell->_value << std::endl;
        cell = cell->_next;
    }
    
    return out;
}

#endif /* SLIST_HPP */