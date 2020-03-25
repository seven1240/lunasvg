#ifndef REFPTR_H
#define REFPTR_H

#include <cstdlib>

namespace lunasvg {

template<typename T>
class RefPtr
{
public:
    ~RefPtr();
    RefPtr()
    {
        m_ptr = NULL;
        m_ref = NULL;
    }

    RefPtr(T* ptr)
    {
        m_ptr = ptr;
        m_ref = ptr ? new int(1) : NULL;
    }

    RefPtr(const RefPtr<T>& refPtr)
    {
        m_ptr = refPtr.m_ptr;
        m_ref = refPtr.m_ref;
        if(m_ref)
            (*m_ref)++;
    }

    RefPtr<T>& operator=(T* ptr);
    RefPtr<T>& operator=(const RefPtr<T>& refPtr);
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
    bool isNull() const { return m_ptr; }

private:
    T* m_ptr;
    int* m_ref;
};

template<typename T>
RefPtr<T>::~RefPtr()
{
    if(m_ref && --(*m_ref) == 0)
    {
        delete m_ptr;
        delete m_ref;
    }
}

template<typename T>
RefPtr<T>& RefPtr<T>::operator=(T *ptr)
{
    if(m_ref && --(*m_ref) == 0)
    {
        delete m_ptr;
        delete m_ref;
    }

    m_ptr = ptr;
    m_ref = ptr ? new int(1) : NULL;

    return *this;
}

template<typename T>
RefPtr<T>& RefPtr<T>::operator=(const RefPtr<T> &refPtr)
{
    if(&refPtr==this)
        return *this;

    if(m_ref && --(*m_ref) == 0)
    {
        delete m_ptr;
        delete m_ref;
    }

    m_ptr = refPtr.m_ptr;
    m_ref = refPtr.m_ref;
    if(m_ref)
        (*m_ref)++;

    return *this;
}

} // namespace lunasvg

#endif // REFPTR_H
