#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"
#include <iostream>
using namespace std;

template <typename Object>
class Vector
{
  public:
    explicit Vector( int initSize = 0 )
      : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
      { objects = new Object[ theCapacity ]; }
      
    Vector(initializer_list<Object> init)
        : theSize{ int(init.size()) }, theCapacity{ theSize + SPARE_CAPACITY }
    {
        objects = new Object[theCapacity]; 
        
        int k = 0;
        for (auto itr = init.begin(); itr != init.end(); itr++)
        {
            objects[k++] = *itr;
        }

    }

    Vector( const Vector & rhs )
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    { 
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }
    
    Vector & operator= ( const Vector & rhs )
    {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    ~Vector( )
      { delete [ ] objects; }

    Vector( Vector && rhs )
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
   
    Vector & operator= ( Vector && rhs )
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        
        return *this;
    }
    
    bool empty( ) const
      { return size( ) == 0; }
    int size( ) const
      { return theSize; }
    int capacity( ) const
      { return theCapacity; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }

    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }

      // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
      // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back( )
    {
        if( empty( ) )
            throw UnderflowException{ };
        --theSize;
    }

    const Object & back ( ) const
    {
        if( empty( ) )
            throw UnderflowException{ };
        return objects[ theSize - 1 ];
    }

      // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
      { return &objects[ 0 ]; }
    const_iterator begin( ) const
      { return &objects[ 0 ]; }
    iterator end( )
      { return &objects[ size( ) ]; }
    const_iterator end( ) const
      { return &objects[ size( ) ]; }

    static const int SPARE_CAPACITY = 2;

    private:
        int theSize;
        int theCapacity;
        Object * objects;



    public:
        void print(ostream& out = cout) const
        {
            out << "Vector[ " << size() << " ] = { ";

            for (Vector<Object>::const_iterator itr = begin(); itr != end(); itr++)
            {
                out << *itr;
                if (itr + 1 != end()) 
                    out << " , ";
            }          
            out << " }" << endl;
        }
        
        iterator insert(iterator itr, Object&& x)
        {
            return insert(itr, x);
        }

        //-----------------------------------------------------------------------------//
        // ���� ����� �����ؼ� ������ �ڵ带 �߰����ּ���. 
        //-----------------------------------------------------------------------------//

        Vector<Object> operator+(const Vector& rhs)
        {
            Vector<Object> retVal;
           
            if (size() > rhs.size())
            {
                retVal.resize(size());
                for (int i = 0; i < rhs.size(); i++) 
                {
                    retVal.objects[i] = objects[i] + rhs.objects[i];
                }
                for (int i = rhs.size(); i < size(); i++)
                {
                    retVal.objects[i] = objects[i];
                }
            }
            else
            {
                retVal.resize(rhs.size()); 
                for (int i = 0; i < size(); i++)
                {
                    retVal.objects[i] = objects[i] + rhs.objects[i];
                }
                for (int i = size(); i < rhs.size(); i++)
                {
                    retVal.objects[i] = rhs.objects[i];
                }
            }
            return retVal;
        }

        Vector<Object> operator+(const Object& rhs)
        {
            Vector<Object> retVal;
            retVal.resize(size());
            for (int i = 0; i < size(); i++)
            {
                retVal.objects[i] = objects[i] + rhs;
            }
            return retVal;
        }

        Vector<Object> operator+(Object&& rhs)
        {
            Vector<Object> retVal;
            retVal.resize(size());
            for (int i = 0; i < size(); i++)
            {
                retVal.objects[i] = objects[i] + rhs;
            }
            return retVal;
        }

        iterator insert(iterator itr, const Object& x) // itr == vector.begin() == vector.object[0]
        {      
            resize(size() + 1);
            iterator it = end();
            while (it != itr)
            {
                *(it) = *(it - 1); // itr���� �� ĭ�� �ڷ� ���Ҹ� �ٲ�
                it--;
            }
            *itr = x;
            return itr;
        }

        iterator erase(iterator itr)
        {
            iterator it = itr;
            while (it != end() - 1 )
            {
                *it = *(it+1); 
                it++;
            }
            resize(size() - 1);
            return itr;
        }

        //-----------------------------------------------------------------------------//
        // ���� ����� �����ؼ� ������ �ڵ带 �߰����ּ���.
        //-----------------------------------------------------------------------------//
};

#endif