#pragma once

template<typename T>
class myShared_ptr
{
    T* _data;
    size_t* _count;

    void release() 
    {
        if (_count) 
        {
            (*_count)--;

            if ((*_count) == 0)
            {
                delete _data;
                delete _count;
            }
        }
    }

public:

    myShared_ptr()
    {
        _data = nullptr;
        _count = nullptr;
    }
    explicit myShared_ptr(T* ptr)
    {
        _data = ptr;
        _count = new size_t(1);
    }
    myShared_ptr(const myShared_ptr<T>& sptr)
    {
        this->_data = sptr._data;

        if (sptr._count != nullptr)
            this->_count = new size_t(*(sptr._count) + 1);
    }
    myShared_ptr(myShared_ptr<T>&& sptr)
    {
        this->_data = sptr._data;
        this->_count = sptr._count;

        sptr._data = nullptr;
        sptr._count = nullptr;
    }

    myShared_ptr& operator=(const myShared_ptr<T>& sptr) 
    {
        if (this != &sptr) 
        {    
            release();

            this->_data = sptr._data;
            this->_count = sptr._count;

            if (_count) (*_count)++;
        }
        return *this;
    }

    T* get() const { return _data; }
    size_t use_count() const 
    {
        return ((_count != nullptr) ? (*_count) : 0);
    }

    T& operator*() const 
    {
        return *_data;
    }

    explicit operator bool()
    {
        return(_data != nullptr);
    }

    T* operator->() const { return _data;  }

    void reset(T* sptr = nullptr) 
    {
        release();

        if (sptr != nullptr) 
        {
            _data = sptr;
            _count = new size_t(1);
        }
        else 
        {
            _data = nullptr;
            _count = nullptr;
        }
    }

    template<typename T>
    friend ostream& operator<<(ostream& out, const myShared_ptr<T>& myPtr);

    ~myShared_ptr()  { release(); }
};


template<typename T>
ostream& operator<<(ostream& out, const myShared_ptr<T>& myPtr)
{
    out << myPtr.get(); return out;
}
