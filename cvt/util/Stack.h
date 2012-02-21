/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_STACK_H
#define CVT_STACK_H

#include <cvt/util/Exception.h>
#include <cvt/util/SIMD.h>

namespace cvt {
	template<typename T>
		class Stack {
			public:
				Stack( size_t elements = 64 );
				~Stack();
				void push( T elem );
				T pop();
				T front();
				size_t size() const;
				bool isEmpty() const;

			private:
				void increaseSize();

				size_t _size;
				size_t _bufsize;
				T* _stack;
				T* _stack_base;
		};

	template<typename T>
	inline Stack<T>::Stack( size_t elements ) : _size( 0 ), _bufsize( elements )
	{
		_stack_base = new T[ elements ];
		_stack = _stack_base - 1;
	}

	template<typename T>
	inline Stack<T>::~Stack()
	{
		delete[] _stack_base;
	}

	template<typename T>
	inline void Stack<T>::push( T elem )
	{
		if( _size + 1 > _bufsize )
			increaseSize();
		_size++;
		_stack++;
		*_stack = elem;
	}

	template<typename T>
	inline T Stack<T>::pop( )
	{
#ifdef DEBUG
		if( isEmpty() )
			throw CVTException( "Stack empty! " );
#endif
		_size--;
		return *_stack--;
	}

	template<typename T>
	inline T Stack<T>::front( )
	{
#ifdef DEBUG
		if( isEmpty() )
			throw CVTException( "Stack empty! " );
#endif
		return *_stack;
	}

	template<typename T>
	inline size_t Stack<T>::size() const
	{
		return _size;
	}

	template<typename T>
	inline bool Stack<T>::isEmpty() const
	{
		return _size == 0;
	}

	template<typename T>
	inline void Stack<T>::increaseSize()
	{
		size_t newbufsize;

		if( _bufsize * sizeof( T ) < ( 4096 * 1024 ) )
			newbufsize = _bufsize << 1;
		else
			newbufsize = _bufsize + Math::pad( 4096 * 1024, sizeof( T ) );

		T* newbuf = new T[ newbufsize ];
		SIMD* simd = SIMD::instance();
		simd->Memcpy( ( uint8_t* ) newbuf, ( uint8_t* ) _stack_base, sizeof( T ) * _size  );
		delete[] _stack_base;
		_stack_base = newbuf;
		_stack = _stack_base + _size - 1;
		_bufsize = newbufsize;
	}
}

#endif
