// vector standard header
#pragma once
#ifndef _VECTOR_
#define _VECTOR_
#ifndef RC_INVOKED
#include <memory>
#include <stdexcept>

#ifdef _MSC_VER
 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
 #pragma warning(disable: 4244)
#endif  /* _MSC_VER */

_STD_BEGIN
template<class _Ty,
	class _Ax = allocator<_Ty> >
	class vector;

		// TEMPLATE CLASS _Vector_const_iterator
template<class _Ty,
	class _Alloc>
	class _Vector_const_iterator
		: public _Ranit<_Ty, typename _Alloc::difference_type,
			typename _Alloc::const_pointer, typename _Alloc::const_reference>
	{	// iterator for nonmutable vector
public:
	typedef _Vector_const_iterator<_Ty, _Alloc> _Myt;
	typedef vector<_Ty, _Alloc> _Myvec;
	typedef typename _Alloc::pointer _Tptr;

	typedef random_access_iterator_tag iterator_category;
	typedef _Ty value_type;
	typedef typename _Alloc::difference_type difference_type;
	typedef typename _Alloc::const_pointer pointer;
	typedef typename _Alloc::const_reference reference;

#if _SECURE_SCL
	typedef _Range_checked_iterator_tag _Checked_iterator_category;
#endif

#if _SECURE_SCL && !_HAS_ITERATOR_DEBUGGING
	typedef pointer _Checked_iterator_base_type;

	_Checked_iterator_base_type _Checked_iterator_base() const
	{
		return _Myptr;
	}

	void _Checked_iterator_assign_from_base(_Checked_iterator_base_type _Base)
	{
		this->_Myptr = const_cast<_Tptr>(_Base);
	}
#endif

	// Setting _Inner_type implies that the internal structure of vector is
	// an array of _Ty. This information is used in the copy and move algorithm.
	// The helper function _Ptr_cat will return _Scalar_ptr_iterator_tag if you
	// pass a vector iterator.
	typedef _Tptr _Inner_type;

	_Vector_const_iterator()
		{	// construct with null pointer
		_Myptr = 0;
		}

 #if _HAS_ITERATOR_DEBUGGING
	_Vector_const_iterator(_Tptr _Ptr, const _Container_base *_Pvector)
		{	// construct with pointer _Ptr
		_SCL_SECURE_VALIDATE(_Pvector == NULL || (((_Myvec *)_Pvector)->_Myfirst <= _Ptr && _Ptr <= ((_Myvec *)_Pvector)->_Mylast));
		this->_Adopt(_Pvector);
		_Myptr = _Ptr;
		}

 #elif _SECURE_SCL
	_Vector_const_iterator(_Tptr _Ptr, const _Container_base *_Pvector)
		{	// construct with pointer _Ptr
		_SCL_SECURE_VALIDATE(_Pvector != NULL && ((_Myvec *)_Pvector)->_Myfirst <= _Ptr && _Ptr <= ((_Myvec *)_Pvector)->_Mylast);
		this->_Set_container(_Pvector);
		_Myptr = _Ptr;
		}

 #else
	explicit _Vector_const_iterator(_Tptr _Ptr)
		{	// construct with pointer _Ptr
		_Myptr = _Ptr;
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	reference operator*() const
		{	// return designated object

 #if _HAS_ITERATOR_DEBUGGING
		if (this->_Mycont == 0
			|| _Myptr < ((_Myvec *)this->_Mycont)->_Myfirst
			|| ((_Myvec *)this->_Mycont)->_Mylast <= _Myptr)
			{
			_DEBUG_ERROR("vector iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
			}
 #else
 		_SCL_SECURE_VALIDATE(this->_Has_container());
		_SCL_SECURE_VALIDATE_RANGE(_Myptr < ((_Myvec *)(this->_Getmycont()))->_Mylast);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (*_Myptr);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (&**this);
		}

	_Myt& operator++()
		{	// preincrement
		_SCL_SECURE_VALIDATE(this->_Has_container());
		_SCL_SECURE_VALIDATE_RANGE(_Myptr < ((_Myvec *)(this->_Getmycont()))->_Mylast);

 #if _HAS_ITERATOR_DEBUGGING
		if (this->_Mycont == 0
			|| ((_Myvec *)this->_Mycont)->_Mylast <= _Myptr)
			_DEBUG_ERROR("vector iterator not incrementable");
 #endif /* _HAS_ITERATOR_DEBUGGING */

		++_Myptr;
		return (*this);
		}

	_Myt operator++(int)
		{	// postincrement
		_Myt _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Myt& operator--()
		{	// predecrement
		_SCL_SECURE_VALIDATE(this->_Has_container());
		_SCL_SECURE_VALIDATE_RANGE(_Myptr > ((_Myvec *)(this->_Getmycont()))->_Myfirst);

 #if _HAS_ITERATOR_DEBUGGING
		if (this->_Mycont == 0
			|| _Myptr == ((_Myvec *)this->_Mycont)->_Myfirst)
			_DEBUG_ERROR("vector iterator not decrementable");
 #endif /* _HAS_ITERATOR_DEBUGGING */

		--_Myptr;
		return (*this);
		}

	_Myt operator--(int)
		{	// postdecrement
		_Myt _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Myt& operator+=(difference_type _Off)
		{	// increment by integer
		_SCL_SECURE_VALIDATE(this->_Has_container());
		_SCL_SECURE_VALIDATE_RANGE(
			_Myptr + _Off <= ((_Myvec *)(this->_Getmycont()))->_Mylast &&
			_Myptr + _Off >= ((_Myvec *)(this->_Getmycont()))->_Myfirst);
		_Myptr += _Off;
		return (*this);
		}

	_Myt operator+(difference_type _Off) const
		{	// return this + integer
		_Myt _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Myt& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Myt operator-(difference_type _Off) const
		{	// return this - integer
		_Myt _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Myt& _Right) const
		{	// return difference of iterators

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #else
		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Same_container(_Right));
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (_Myptr - _Right._Myptr);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}

	bool operator==(const _Myt& _Right) const
		{	// test for iterator equality

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #else
		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Same_container(_Right));
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (_Myptr == _Right._Myptr);
		}

	bool operator!=(const _Myt& _Right) const
		{	// test for iterator inequality
		return (!(*this == _Right));
		}

	bool operator<(const _Myt& _Right) const
		{	// test if this < _Right

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #else
		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Same_container(_Right));
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (_Myptr < _Right._Myptr);
		}

	bool operator>(const _Myt& _Right) const
		{	// test if this > _Right
		return (_Right < *this);
		}

	bool operator<=(const _Myt& _Right) const
		{	// test if this <= _Right
		return (!(_Right < *this));
		}

	bool operator>=(const _Myt& _Right) const
		{	// test if this >= _Right
		return (!(*this < _Right));
		}

 #if _HAS_ITERATOR_DEBUGGING
	void _Compat(const _Myt& _Right) const
		{	// test for compatible iterator pair
		if (this->_Mycont == 0 || this->_Mycont != _Right._Mycont)
			{
			_DEBUG_ERROR("vector iterators incompatible");
			_SCL_SECURE_INVALID_ARGUMENT;
			}
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	static void _Xlen()
		{	// report a length_error
		_THROW(length_error, "vector<T> too long");
		}

	static void _Xran()
		{	// report an out_of_range error
		_THROW(out_of_range, "invalid vector<T> subscript");
		}

	static void _Xinvarg()
		{	// report an invalid_argument error
		_THROW(invalid_argument, "invalid vector<T> argument");
		}

	_Tptr _Myptr;	// offset of element in vector
	};

template<class _Ty,
	class _Alloc> inline
	_Vector_const_iterator<_Ty, _Alloc> operator+(
		typename _Vector_const_iterator<_Ty, _Alloc>::difference_type _Off,
		_Vector_const_iterator<_Ty, _Alloc> _Next)
	{	// add offset to iterator
	return (_Next += _Off);
	}

		// TEMPLATE CLASS _Vector_iterator
template<class _Ty,
	class _Alloc>
	class _Vector_iterator
		: public _Vector_const_iterator<_Ty, _Alloc>
	{	// iterator for mutable vector
public:
	typedef _Vector_iterator<_Ty, _Alloc> _Myt;
	typedef _Vector_const_iterator<_Ty, _Alloc> _Mybase;

	typedef random_access_iterator_tag iterator_category;
	typedef _Ty value_type;
	typedef typename _Alloc::difference_type difference_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::reference reference;

#if _SECURE_SCL && !_HAS_ITERATOR_DEBUGGING
	typedef pointer _Checked_iterator_base_type;

	_Checked_iterator_base_type _Checked_iterator_base() const
		{
		return (this->_Myptr);
		}

	void _Checked_iterator_assign_from_base(_Checked_iterator_base_type _Base)
		{
		this->_Myptr = _Base;
		}
#endif

	_Vector_iterator()
		{	// construct with null vector pointer
		}

 #if _HAS_ITERATOR_DEBUGGING
	_Vector_iterator(pointer _Ptr, const _Container_base *_Pvector)
		: _Mybase(_Ptr, _Pvector)
		{	// construct with pointer _Ptr
		}

 #elif _SECURE_SCL
	_Vector_iterator(pointer _Ptr, const _Container_base *_Pvector)
		: _Mybase(_Ptr, _Pvector)
		{	// construct with pointer _Ptr
		}

 #else
	explicit _Vector_iterator(pointer _Ptr)
		: _Mybase(_Ptr)
		{	// construct with pointer _Ptr
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	reference operator*() const
		{	// return designated object
		return ((reference)**(_Mybase *)this);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (&**this);
		}

	_Myt& operator++()
		{	// preincrement
		++(*(_Mybase *)this);
		return (*this);
		}

	_Myt operator++(int)
		{	// postincrement
		_Myt _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Myt& operator--()
		{	// predecrement
		--(*(_Mybase *)this);
		return (*this);
		}

	_Myt operator--(int)
		{	// postdecrement
		_Myt _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Myt& operator+=(difference_type _Off)
		{	// increment by integer
		(*(_Mybase *)this) += _Off;
		return (*this);
		}

	_Myt operator+(difference_type _Off) const
		{	// return this + integer
		_Myt _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Myt& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Myt operator-(difference_type _Off) const
		{	// return this - integer
		_Myt _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Mybase& _Right) const
		{	// return difference of iterators
		return (*(_Mybase *)this - _Right);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}
	};

template<class _Ty,
	class _Alloc> inline
	_Vector_iterator<_Ty, _Alloc> operator+(
		typename _Vector_iterator<_Ty, _Alloc>::difference_type _Off,
		_Vector_iterator<_Ty, _Alloc> _Next)
	{	// add offset to iterator
	return (_Next += _Off);
	}

		// TEMPLATE CLASS _Vector_val
template<class _Ty,
	class _Alloc>
	class _Vector_val
		: public _CONTAINER_BASE_AUX_ALLOC<_Alloc>
	{	// base class for vector to hold allocator _Alval
protected:
	_Vector_val(_Alloc _Al = _Alloc())
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Alval(_Al)
		{	// construct allocator from _Al
		}

	typedef typename _Alloc::template
		rebind<_Ty>::other _Alty;

	_Alty _Alval;	// allocator object for values
	};

		// TEMPLATE CLASS vector
template<class _Ty,
	class _Ax>
	class vector
		: public _Vector_val<_Ty, _Ax>
	{	// varying size array of values
public:
	typedef vector<_Ty, _Ax> _Myt;
	typedef _Vector_val<_Ty, _Ax> _Mybase;
	typedef typename _Mybase::_Alty _Alloc;
	typedef _Alloc allocator_type;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type _Dift;
	typedef _Dift difference_type;
	typedef typename _Alloc::pointer _Tptr;
	typedef typename _Alloc::const_pointer _Ctptr;
	typedef _Tptr pointer;
	typedef _Ctptr const_pointer;
	typedef typename _Alloc::reference _Reft;
	typedef _Reft reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::value_type value_type;

  #define _VEC_ITER_BASE(it)	(it)._Myptr

	typedef _Vector_iterator<_Ty, _Alloc> iterator;
	typedef _Vector_const_iterator<_Ty, _Alloc> const_iterator;

//	friend class _Vector_iterator<_Ty, _Alloc>;
	friend class _Vector_const_iterator<_Ty, _Alloc>;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	vector()
		: _Mybase()
		{	// construct empty vector
		_Buy(0);
		}

	explicit vector(const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct empty vector with allocator
		_Buy(0);
		}

	explicit vector(size_type _Count)
		: _Mybase()
		{	// construct from _Count * _Ty()
		_Construct_n(_Count, _Ty());
		}

	vector(size_type _Count, const _Ty& _Val)
		: _Mybase()
		{	// construct from _Count * _Val
		_Construct_n(_Count, _Val);
		}

	vector(size_type _Count, const _Ty& _Val, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct from _Count * _Val, with allocator
		_Construct_n(_Count, _Val);
		}

	vector(const _Myt& _Right)
		: _Mybase(_Right._Alval)
		{	// construct by copying _Right
		if (_Buy(_Right.size()))
			_TRY_BEGIN
			_Mylast = _Ucopy(_Right.begin(), _Right.end(), _Myfirst);
			_CATCH_ALL
			_Tidy();
			_RERAISE;
			_CATCH_END
		}

	template<class _Iter>
		vector(_Iter _First, _Iter _Last)
		: _Mybase()
		{	// construct from [_First, _Last)
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		vector(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct from [_First, _Last), with allocator
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Construct(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// initialize with _Count * _Val
		size_type _Size = (size_type)_Count;
		_Construct_n(_Size, (_Ty)_Val);
		}

	template<class _Iter>
		void _Construct(_Iter _First,
			_Iter _Last, input_iterator_tag)
		{	// initialize with [_First, _Last), input iterators
		_Buy(0);
		_TRY_BEGIN
		insert(begin(), _First, _Last);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	void _Construct_n(size_type _Count, const _Ty& _Val)
		{	// construct from _Count * _Val
		if (_Buy(_Count))
			{	// nonzero, fill it
			_TRY_BEGIN
			_Mylast = _Ufill(_Myfirst, _Count, _Val);
			_CATCH_ALL
			_Tidy();
			_RERAISE;
			_CATCH_END
			}
		}

	~vector()
		{	// destroy the object
		_Tidy();
		}

	_Myt& operator=(const _Myt& _Right)
		{	// assign _Right
		if (this != &_Right)
			{	// worth doing

 #if _HAS_ITERATOR_DEBUGGING
			this->_Orphan_all();
 #endif /* _HAS_ITERATOR_DEBUGGING */

			if (_Right.size() == 0)
				clear();	// new sequence empty, erase existing sequence
			else if (_Right.size() <= size())
				{	// enough elements, copy new and destroy old
				pointer _Ptr = _STDEXT unchecked_copy(_Right._Myfirst, _Right._Mylast,
					_Myfirst);	// copy new
				_Destroy(_Ptr, _Mylast);	// destroy old
				_Mylast = _Myfirst + _Right.size();
				}
			else if (_Right.size() <= capacity())
				{	// enough room, copy and construct new
				pointer _Ptr = _Right._Myfirst + size();
				_STDEXT unchecked_copy(_Right._Myfirst, _Ptr, _Myfirst);
				_Mylast = _Ucopy(_Ptr, _Right._Mylast, _Mylast);
				}
			else
				{	// not enough room, allocate new array and construct new
				if (_Myfirst != 0)
					{	// discard old array
					_Destroy(_Myfirst, _Mylast);
					this->_Alval.deallocate(_Myfirst, _Myend - _Myfirst);
					}
				if (_Buy(_Right.size()))
					_Mylast = _Ucopy(_Right._Myfirst, _Right._Mylast,
						_Myfirst);
				}
			}
		return (*this);
		}

	void reserve(size_type _Count)
		{	// determine new minimum length of allocated storage
		if (max_size() < _Count)
			_Xlen();	// result too long
		else if (capacity() < _Count)
			{	// not enough room, reallocate
			pointer _Ptr = this->_Alval.allocate(_Count);

			_TRY_BEGIN
			_Umove(begin(), end(), _Ptr);
			_CATCH_ALL
			this->_Alval.deallocate(_Ptr, _Count);
			_RERAISE;
			_CATCH_END

			size_type _Size = size();
			if (_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(_Myfirst, _Mylast);
				this->_Alval.deallocate(_Myfirst, _Myend - _Myfirst);
				}

 #if _HAS_ITERATOR_DEBUGGING
			this->_Orphan_all();
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_Myend = _Ptr + _Count;
			_Mylast = _Ptr + _Size;
			_Myfirst = _Ptr;
			}
		}

	size_type capacity() const
		{	// return current length of allocated storage
		return (_Myfirst == 0 ? 0 : _Myend - _Myfirst);
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_Myfirst, this));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_Myfirst, this));
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (iterator(_Mylast, this));
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(_Mylast, this));
		}

	iterator _Make_iter(const_iterator _Where) const
		{	// make iterator from const_iterator
		return (iterator(_Where._Myptr, this));
		}

 #else /* _HAS_ITERATOR_DEBUGGING */
	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_Myfirst));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_Myfirst));
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (iterator(_Mylast));
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(_Mylast));
		}

	iterator _Make_iter(const_iterator _Where) const
		{	// make iterator from const_iterator
		return (iterator(_Where._Myptr));
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

	void resize(size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
		resize(_Newsize, _Ty());
		}

	void resize(size_type _Newsize, _Ty _Val)
		{	// determine new length, padding with _Val elements as needed
		if (size() < _Newsize)
			_Insert_n(end(), _Newsize - size(), _Val);
		else if (_Newsize < size())
			erase(begin() + _Newsize, end());
		}

	size_type size() const
		{	// return length of sequence
		return (_Mylast - _Myfirst);
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		return (this->_Alval.max_size());
		}

	bool empty() const
		{	// test if sequence is empty
		return (size() == 0);
		}

	_Alloc get_allocator() const
		{	// return allocator object for values
		return (this->_Alval);
		}

	const_reference at(size_type _Pos) const
		{	// subscript nonmutable sequence with checking
		if (size() <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
		}

	reference at(size_type _Pos)
		{	// subscript mutable sequence with checking
		if (size() <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
		}

	const_reference operator[](size_type _Pos) const
		{	// subscript nonmutable sequence

 #if _HAS_ITERATOR_DEBUGGING
		if (size() <= _Pos)
			{
			_DEBUG_ERROR("vector subscript out of range");
			_SCL_SECURE_OUT_OF_RANGE;
			}
 #endif /* _HAS_ITERATOR_DEBUGGING */
		_SCL_SECURE_VALIDATE_RANGE(_Pos < size());

		return (*(_Myfirst + _Pos));
		}

	reference operator[](size_type _Pos)
		{	// subscript mutable sequence

 #if _HAS_ITERATOR_DEBUGGING
		if (size() <= _Pos)
			{
			_DEBUG_ERROR("vector subscript out of range");
			_SCL_SECURE_OUT_OF_RANGE;
			}
 #endif /* _HAS_ITERATOR_DEBUGGING */
		_SCL_SECURE_VALIDATE_RANGE(_Pos < size());

		return (*(_Myfirst + _Pos));
		}

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(end() - 1));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(end() - 1));
		}

	void push_back(const _Ty& _Val)
		{	// insert element at end
		if (size() < capacity())

 #if _HAS_ITERATOR_DEBUGGING
			{ // room at end, construct it there
			_Orphan_range(_Mylast, _Mylast);
			_Mylast = _Ufill(_Mylast, 1, _Val);
			}

 #else /* _HAS_ITERATOR_DEBUGGING */
			_Mylast = _Ufill(_Mylast, 1, _Val);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		else
			insert(end(), _Val);
		}

 #if _HAS_ITERATOR_DEBUGGING
	void pop_back()
		{	// erase element at end
		if (empty())
			_DEBUG_ERROR("vector empty before pop");
		else
			{	// erase last element
			_Orphan_range(_Mylast - 1, _Mylast);
			_Destroy(_Mylast - 1, _Mylast);
			--_Mylast;
			}
		}

 #else /* _HAS_ITERATOR_DEBUGGING */
	void pop_back()
		{	// erase element at end
		if (!empty())
			{	// erase last element
			_Destroy(_Mylast - 1, _Mylast);
			--_Mylast;
			}
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	template<class _Iter>
		void assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last)
		_Assign(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Assign(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// assign _Count * _Val
		_Assign_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _Iter>
		void _Assign(_Iter _First, _Iter _Last, input_iterator_tag)
		{	// assign [_First, _Last), input iterators
		erase(begin(), end());
		insert(begin(), _First, _Last);
		}

	void assign(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Assign_n(_Count, _Val);
		}

	iterator insert(const_iterator _Where, const _Ty& _Val)
		{	// insert _Val at _Where
		size_type _Off = size() == 0 ? 0 : _Where - begin();
		_Insert_n(_Where, (size_type)1, _Val);
		return (begin() + _Off);
		}

	void insert(const_iterator _Where, size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, _Count, _Val);
		}

	template<class _Iter>
		void insert(const_iterator _Where, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
		_Insert(_Where, _First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
			_Int_iterator_tag)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, (size_type)_First, (_Ty)_Last);
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
			input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators

 #if _HAS_ITERATOR_DEBUGGING
		if (_Where._Mycont != this
			|| _Where._Myptr < _Myfirst || _Mylast < _Where._Myptr)
			_DEBUG_ERROR("vector insert iterator outside range");
 #endif /* _HAS_ITERATOR_DEBUGGING */

		if (_First != _Last)
			{	// worth doing, gather at end and rotate into place
			size_type _Oldsize = size();
			size_type _Whereoff = _Where._Myptr - _Myfirst;

			for (; _First != _Last; ++_First)
				_Insert_n(end(), (size_type)1, (value_type)*_First);

			_Reverse(_Myfirst + _Whereoff, _Myfirst + _Oldsize);
			_Reverse(_Myfirst + _Oldsize, _Mylast);
			_Reverse(_Myfirst + _Whereoff, _Mylast);
			}
		}

	template<class _Iter>
		void _Insert(const_iterator _Where,
			_Iter _First, _Iter _Last, forward_iterator_tag)
		{	// insert [_First, _Last) at _Where, forward iterators

 #if _HAS_ITERATOR_DEBUGGING
		if (_Where._Mycont != this
			|| _Where._Myptr < _Myfirst || _Mylast < _Where._Myptr)
			_DEBUG_ERROR("vector insert iterator outside range");
		_DEBUG_RANGE(_First, _Last);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		size_type _Count = 0;
		_Distance(_First, _Last, _Count);
		size_type _Capacity = capacity();

		if (_Count == 0)
			;
		else if (max_size() - size() < _Count)
			_Xlen();	// result too long
		else if (_Capacity < size() + _Count)
			{	// not enough room, reallocate
			_Capacity = max_size() - _Capacity / 2 < _Capacity
				? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
			if (_Capacity < size() + _Count)
				_Capacity = size() + _Count;
			pointer _Newvec = this->_Alval.allocate(_Capacity);
			pointer _Ptr = _Newvec;

			_TRY_BEGIN
			_Ptr = _Umove(_Myfirst, _VEC_ITER_BASE(_Where),
				_Newvec);	// copy prefix
			_Ptr = _Ucopy(_First, _Last, _Ptr);	// add new stuff
			_Umove(_VEC_ITER_BASE(_Where), _Mylast, _Ptr);	// copy suffix
			_CATCH_ALL
			_Destroy(_Newvec, _Ptr);
			this->_Alval.deallocate(_Newvec, _Capacity);
			_RERAISE;
			_CATCH_END

			_Count += size();
			if (_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(_Myfirst, _Mylast);
				this->_Alval.deallocate(_Myfirst, _Myend - _Myfirst);
				}

 #if _HAS_ITERATOR_DEBUGGING
			this->_Orphan_all();
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_Myend = _Newvec + _Capacity;
			_Mylast = _Newvec + _Count;
			_Myfirst = _Newvec;
			}
		else
			{	// new stuff fits, append and rotate into place
			_Ucopy(_First, _Last, _Mylast);

			_Reverse(_Where._Myptr, _Mylast);
			_Reverse(_Mylast, _Mylast + _Count);
			_Reverse(_Where._Myptr, _Mylast + _Count);

			_Mylast += _Count;

 #if _HAS_ITERATOR_DEBUGGING
			_Orphan_range(_Where._Myptr, _Mylast);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			}
		}

 	void _Reverse(pointer _First, pointer _Last)
		{	// reverse a subrange
		for (; _First != _Last && _First != --_Last; ++_First)
			_STD _Swap_adl(*_First, *_Last);
		}

 #if _HAS_ITERATOR_DEBUGGING
	iterator erase(const_iterator _Where)
		{	// erase element at where
		if (_Where._Mycont != this
			|| _Where._Myptr < _Myfirst || _Mylast <= _Where._Myptr)
			_DEBUG_ERROR("vector erase iterator outside range");
		_STDEXT unchecked_copy(_Where._Myptr + 1, _Mylast, _Where._Myptr);
		_Destroy(_Mylast - 1, _Mylast);
		_Orphan_range(_Where._Myptr, _Mylast);
		--_Mylast;
		return (iterator(_Where._Myptr, this));
		}

 #else /* _HAS_ITERATOR_DEBUGGING */
	iterator erase(const_iterator _Where)
		{	// erase element at where
		_STDEXT unchecked_copy(_VEC_ITER_BASE(_Where) + 1, _Mylast,
			_VEC_ITER_BASE(_Where));
		_Destroy(_Mylast - 1, _Mylast);
		--_Mylast;
		return (_Make_iter(_Where));
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	iterator erase(const_iterator _First_arg,
		const_iterator _Last_arg)
		{	// erase [_First, _Last)
		iterator _First = _Make_iter(_First_arg);
		iterator _Last = _Make_iter(_Last_arg);

		if (_First != _Last)
			{	// worth doing, copy down over hole

 #if _HAS_ITERATOR_DEBUGGING
			if (_Last < _First || _First._Mycont != this
				|| _First._Myptr < _Myfirst || _Mylast < _Last._Myptr)
				_DEBUG_ERROR("vector erase iterator outside range");
			pointer _Ptr = _STDEXT unchecked_copy(_VEC_ITER_BASE(_Last), _Mylast,
				_VEC_ITER_BASE(_First));
			_Orphan_range(_First._Myptr, _Mylast);

 #else /* _HAS_ITERATOR_DEBUGGING */
			pointer _Ptr = _STDEXT unchecked_copy(_VEC_ITER_BASE(_Last), _Mylast,
				_VEC_ITER_BASE(_First));
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_Destroy(_Ptr, _Mylast);
			_Mylast = _Ptr;
			}
#if _HAS_ITERATOR_DEBUGGING
        return (iterator(_First._Myptr, this));
#else
		return (_First);
#endif
		}

	void clear()
		{	// erase all
		erase(begin(), end());
		}

	void swap(_Myt& _Right)
		{	// exchange contents with _Right
		if (this == &_Right)
			;	// same object, do nothing
		else if (this->_Alval == _Right._Alval)
			{	// same allocator, swap control information

 #if _HAS_ITERATOR_DEBUGGING
			this->_Swap_all(_Right);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			this->_Swap_aux(_Right);

			_STD swap(_Myfirst, _Right._Myfirst);
			_STD swap(_Mylast, _Right._Mylast);
			_STD swap(_Myend, _Right._Myend);
			}
		else
			{	// different allocator, do multiple assigns
			this->_Swap_aux(_Right);

			_Myt _Ts = *this;

			*this = _Right;
			_Right = _Ts;
			}
		}



protected:
	void _Assign_n(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Ty _Tmp = _Val;	// in case _Val is in sequence
		erase(begin(), end());
		insert(begin(), _Count, _Tmp);
		}

	bool _Buy(size_type _Capacity)
		{	// allocate array with _Capacity elements
		_Myfirst = 0, _Mylast = 0, _Myend = 0;
		if (_Capacity == 0)
			return (false);
		else if (max_size() < _Capacity)
			_Xlen();	// result too long
		else
			{	// nonempty array, allocate storage
			_Myfirst = this->_Alval.allocate(_Capacity);
			_Mylast = _Myfirst;
			_Myend = _Myfirst + _Capacity;
			}
		return (true);
		}

	void _Destroy(pointer _First, pointer _Last)
		{	// destroy [_First, _Last) using allocator
		_Destroy_range(_First, _Last, this->_Alval);
		}

	void _Tidy()
		{	// free all storage
		if (_Myfirst != 0)
			{	// something to free, destroy and deallocate it

 #if _HAS_ITERATOR_DEBUGGING
			this->_Orphan_all();
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_Destroy(_Myfirst, _Mylast);
			this->_Alval.deallocate(_Myfirst, _Myend - _Myfirst);
			}
		_Myfirst = 0, _Mylast = 0, _Myend = 0;
		}

	template<class _Iter>
		pointer _Ucopy(_Iter _First, _Iter _Last, pointer _Ptr)
		{	// copy initializing [_First, _Last), using allocator
		return (_STDEXT unchecked_uninitialized_copy(_First, _Last,
			_Ptr, this->_Alval));
		}

	template<class _Iter>
		pointer _Umove(_Iter _First, _Iter _Last, pointer _Ptr)
		{	// move initializing [_First, _Last), using allocator
		return (_STDEXT _Unchecked_uninitialized_move(_First, _Last,
			_Ptr, this->_Alval));
		}

	void _Insert_n(const_iterator _Where,
		size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where

 #if _HAS_ITERATOR_DEBUGGING
		if (_Where._Mycont != this
			|| _Where._Myptr < _Myfirst || _Mylast < _Where._Myptr)
			_DEBUG_ERROR("vector insert iterator outside range");
 #endif /* _HAS_ITERATOR_DEBUGGING */

		size_type _Capacity = capacity();

		if (_Count == 0)
			;
		else if (max_size() - size() < _Count)
			_Xlen();	// result too long
		else if (_Capacity < size() + _Count)
			{	// not enough room, reallocate
			_Capacity = max_size() - _Capacity / 2 < _Capacity
				? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
			if (_Capacity < size() + _Count)
				_Capacity = size() + _Count;
			pointer _Newvec = this->_Alval.allocate(_Capacity);
			size_type _Whereoff = _VEC_ITER_BASE(_Where) - _Myfirst;
			int _Ncopied = 0;

			_TRY_BEGIN
			_Ufill(_Newvec + _Whereoff, _Count, _Val);	// add new stuff
			++_Ncopied;
			_Umove(this->_Myfirst, _VEC_ITER_BASE(_Where),
				_Newvec);	// move prefix
			++_Ncopied;
			_Umove(_VEC_ITER_BASE(_Where), this->_Mylast,
				_Newvec + (_Whereoff + _Count));	// move suffix
			_CATCH_ALL
			if (1 < _Ncopied)
				_Destroy(_Newvec, _Newvec + _Whereoff);
			if (0 < _Ncopied)
				_Destroy(_Newvec + _Whereoff, _Newvec + _Whereoff + _Count);
			this->_Alval.deallocate(_Newvec, _Capacity);
			_RERAISE;
			_CATCH_END

			_Count += size();
			if (_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(_Myfirst, _Mylast);
				this->_Alval.deallocate(_Myfirst, _Myend - _Myfirst);
				}

 #if _HAS_ITERATOR_DEBUGGING
			this->_Orphan_all();
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_Myend = _Newvec + _Capacity;
			_Mylast = _Newvec + _Count;
			_Myfirst = _Newvec;
			}
		else if ((size_type)(_Mylast - _VEC_ITER_BASE(_Where)) < _Count)
			{	// new stuff spills off end
			_Ty _Tmp = _Val;	// in case _Val is in sequence

			_Umove(_VEC_ITER_BASE(_Where), _Mylast,
				_VEC_ITER_BASE(_Where) + _Count);	// copy suffix

			_TRY_BEGIN
			_Ufill(_Mylast, _Count - (_Mylast - _VEC_ITER_BASE(_Where)),
				_Tmp);	// insert new stuff off end
			_CATCH_ALL
			_Destroy(_VEC_ITER_BASE(_Where) + _Count, _Mylast + _Count);
			_RERAISE;
			_CATCH_END

			_Mylast += _Count;

 #if _HAS_ITERATOR_DEBUGGING
			_Orphan_range(_Where._Myptr, _Mylast);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			std::fill(_VEC_ITER_BASE(_Where), _Mylast - _Count,
				_Tmp);	// insert up to old end
			}
		else
			{	// new stuff can all be assigned
			_Ty _Tmp = _Val;	// in case _Val is in sequence

			pointer _Oldend = _Mylast;
			_Mylast = _Umove(_Oldend - _Count, _Oldend,
				_Mylast);	// copy suffix

 #if _HAS_ITERATOR_DEBUGGING
			_Orphan_range(_Where._Myptr, _Mylast);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			_STDEXT _Unchecked_move_backward(_VEC_ITER_BASE(_Where), _Oldend - _Count,
				_Oldend);	// copy hole
			std::fill(_VEC_ITER_BASE(_Where), _VEC_ITER_BASE(_Where) + _Count,
				_Tmp);	// insert into hole
			}
		}

	pointer _Ufill(pointer _Ptr, size_type _Count, const _Ty &_Val)
		{	// copy initializing _Count * _Val, using allocator
		_STDEXT unchecked_uninitialized_fill_n(_Ptr, _Count, _Val, this->_Alval);
		return (_Ptr + _Count);
		}

	static void _Xlen()
		{	// report a length_error
		_THROW(length_error, "vector<T> too long");
		}

	static void _Xran()
		{	// report an out_of_range error
		_THROW(out_of_range, "invalid vector<T> subscript");
		}

	static void _Xinvarg()
		{	// report an invalid_argument error
		_THROW(invalid_argument, "invalid vector<T> argument");
		}

 #if _HAS_ITERATOR_DEBUGGING
	void _Orphan_range(pointer _First, pointer _Last) const
		{	// orphan iterators within specified (inclusive) range
		_Lockit _Lock(_LOCK_DEBUG);
		const_iterator **_Pnext = (const_iterator **)&this->_Myfirstiter;
		while (*_Pnext != 0)
			if ((*_Pnext)->_Myptr < _First || _Last < (*_Pnext)->_Myptr)
				_Pnext = (const_iterator **)&(*_Pnext)->_Mynextiter;
			else
				{	// orphan the iterator
				(*_Pnext)->_Mycont = 0;
				*_Pnext = (const_iterator *)(*_Pnext)->_Mynextiter;
				}
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	pointer _Myfirst;	// pointer to beginning of array
	pointer _Mylast;	// pointer to current end of sequence
	pointer _Myend;	// pointer to end of array
	};

	// vector implements a performant swap
template <class _Ty, class _Ax>
	class _Move_operation_category<vector<_Ty, _Ax> >
	{
	public:
		typedef _Swap_move_tag _Move_cat;
	};

		// vector TEMPLATE FUNCTIONS
template<class _Ty,
	class _Alloc> inline
	bool operator==(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test for vector equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator!=(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test for vector inequality
	return (!(_Left == _Right));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test if _Left < _Right for vectors
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test if _Left > _Right for vectors
	return (_Right < _Left);
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<=(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test if _Left <= _Right for vectors
	return (!(_Right < _Left));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>=(const vector<_Ty, _Alloc>& _Left,
		const vector<_Ty, _Alloc>& _Right)
	{	// test if _Left >= _Right for vectors
	return (!(_Left < _Right));
	}

template<class _Ty,
	class _Alloc> inline
	void swap(vector<_Ty, _Alloc>& _Left, vector<_Ty, _Alloc>& _Right)
	{	// swap _Left and _Right vectors
	_Left.swap(_Right);
	}

//
// TEMPLATE CLASS vector<bool, Alloc> AND FRIENDS
//
typedef unsigned _Vbase;	// word type for vector<bool> representation
const int _VBITS = 8 * sizeof (_Vbase);	// at least CHAR_BITS bits per word

		// CLASS _Vb_iter_base
template<class _Sizet,
	class _Difft,
	class _MycontTy>
	class _Vb_iter_base
		: public _Ranit<_Bool, _Difft, bool *, bool>
	{	// store information common to reference and iterators
public:
#if _SECURE_SCL
	typedef _Range_checked_iterator_tag _Checked_iterator_category;
#endif

	_Vb_iter_base()
		: _Myptr(0), _Myoff(0)
		{	// construct with null pointer
		}

 #if _HAS_ITERATOR_DEBUGGING
	_Vb_iter_base(_Vbase *_Ptr, _Sizet _Off,
		const _Container_base *_Mypvbool)
		: _Myptr(_Ptr), _Myoff(_Off)
		{	// construct with offset and pointer
		_SCL_SECURE_VALIDATE(_Mypvbool != NULL);
		this->_Adopt(_Mypvbool);
		}

 #elif _SECURE_SCL
	_Vb_iter_base(_Vbase *_Ptr, _Sizet _Off,
		const _Container_base *_Mypvbool)
		: _Myptr(_Ptr), _Myoff(_Off)
		{	// construct with offset and pointer
		_SCL_SECURE_VALIDATE(_Mypvbool != NULL);
		this->_Set_container(_Mypvbool);
		}
 #else
	_Vb_iter_base(_Vbase *_Ptr, _Sizet _Off)
		: _Myptr(_Ptr), _Myoff(_Off)
		{	// construct with offset and pointer
		}
 #endif

	_Vbase *_Myptr;
	_Sizet _Myoff;

	static void _Xlen()
		{	// report a length_error
		_THROW(length_error, "vector<bool> too long");
			}

	static void _Xran()
		{	// report an out_of_range error
		_THROW(out_of_range, "invalid vector<bool> subscript");
		}

	static void _Xinvarg()
		{	// report an invalid_argument error
		_THROW(invalid_argument, "invalid vector<bool> argument");
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	_Vbase * _My_cont_begin() const
		{
		return (_VEC_ITER_BASE(((_MycontTy *)this->
			_Getmycont())->_Myvec.begin()));
		}

	_Sizet _My_actual_offset() const
		{
		_Sizet _Off = this->_Myoff;
		_Off += _VBITS * (this->_Myptr - _My_cont_begin());
		return (_Off);
		}
 #endif
	};

		// CLASS _Vb_reference
template<class _Sizet,
	class _Difft,
	class _MycontTy>
	class _Vb_reference
		: public _Vb_iter_base<_Sizet, _Difft, _MycontTy>
	{	// reference to a bit within a base word
public:
	typedef _Vb_iter_base<_Sizet, _Difft, _MycontTy> _Mybase;
	typedef _Vb_reference<_Sizet, _Difft, _MycontTy> _Mytype;

	_Vb_reference()
		{	// construct with null pointer
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	_Vb_reference(const _Mybase& _Right)
		: _Mybase(_Right._Myptr, _Right._Myoff, _Right._Getmycont())
		{	// construct with base
		}

 #else /* _HAS_ITERATOR_DEBUGGING */
	_Vb_reference(const _Mybase& _Right)
		: _Mybase(_Right._Myptr, _Right._Myoff)
		{	// construct with base
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	_Mytype& operator=(const _Mytype& _Right)
		{	// assign _Vb_reference _Right to bit
		return (*this = bool(_Right));
		}

	_Mytype& operator=(bool _Val)
		{	// assign _Val to bit
		if (_Val)
			*_Getptr() |= _Mask();
		else
			*_Getptr() &= ~_Mask();
		return (*this);
		}

	void flip()
		{	// toggle the bit
		*_Getptr() ^= _Mask();
		}

	bool operator~() const
		{	// test if bit is reset
		return (!bool(*this));
		}

	operator bool() const
		{	// test if bit is set
		return ((*_Getptr() & _Mask()) != 0);
		}

	_Vbase *_Getptr() const
		{	// get pointer to base word

 #if _HAS_ITERATOR_DEBUGGING
		if (this->_Mycont == 0 || this->_Myptr == 0)
			{
			_DEBUG_ERROR("vector<bool> iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
			}
 #else /* _HAS_ITERATOR_DEBUGGING */
 		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Myptr != NULL);
		_SCL_SECURE_VALIDATE_RANGE(this->_My_actual_offset() < ((_MycontTy *)this->_Getmycont())->_Mysize);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (this->_Myptr);
		}

protected:
	_Vbase _Mask() const
		{	// convert offset to mask
		return ((_Vbase)(1 << this->_Myoff));
		}
	};

template<class _Sizet,
	class _Difft,
	class _MycontTy>
	void swap(_Vb_reference<_Sizet, _Difft, _MycontTy> _Left,
		_Vb_reference<_Sizet, _Difft, _MycontTy> _Right)
	{	// swap _Left and _Right vector<bool> elements
	bool _Val = _Left;
	_Left = _Right;
	_Right = _Val;
	}

		// CLASS _Vb_const_iterator
template<class _Sizet,
	class _Difft,
	class _MycontTy>
	class _Vb_const_iterator
		: public _Vb_iter_base<_Sizet, _Difft, _MycontTy>
	{	// iterator for nonmutable vector<bool>
public:
	typedef _Vb_iter_base<_Sizet, _Difft, _MycontTy> _Mybase;
	typedef _Vb_const_iterator<_Sizet, _Difft, _MycontTy> _Mytype;

	typedef _Vb_reference<_Sizet, _Difft, _MycontTy> _Reft;
	typedef bool const_reference;

	typedef random_access_iterator_tag iterator_category;
	typedef _Bool value_type;
	typedef _Sizet size_type;
	typedef _Difft difference_type;
	typedef const_reference *pointer;
	typedef const_reference reference;

	_Vb_const_iterator()
		{	// construct with null reference
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	_Vb_const_iterator(const _Vbase *_Ptr, const _Container_base *_Mypvbool)
		: _Mybase((_Vbase *)_Ptr, 0, (_Container_base *)_Mypvbool)

 #else
	_Vb_const_iterator(const _Vbase *_Ptr)
		: _Mybase((_Vbase *)_Ptr, 0)

 #endif
		{	// construct with offset and pointer
		}

	const_reference operator*() const
		{	// return (reference to) designated object
		return (_Reft(*this));
		}

	_Mytype& operator++()
		{	// preincrement
		_Inc();
		return (*this);
		}

	_Mytype operator++(int)
		{	// postincrement
		_Mytype _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Mytype& operator--()
		{	// predecrement
		_Dec();
		return (*this);
		}

	_Mytype operator--(int)
		{	// postdecrement
		_Mytype _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Mytype& operator+=(difference_type _Off)
		{	// increment by integer
		if (_Off == 0)
			return (*this); // early out
		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Myptr != NULL);
		if (_Off < 0)
			{
			_SCL_SECURE_VALIDATE_RANGE(this->_My_actual_offset() >= ((size_type)-_Off));
			}
		else
			{
			_SCL_SECURE_VALIDATE_RANGE((this->_My_actual_offset() + _Off) <= ((_MycontTy *)this->_Getmycont())->_Mysize);
			}
		if (_Off < 0 && this->_Myoff < 0 - (size_type)_Off)
			{	/* add negative increment */
			this->_Myoff += _Off;
			this->_Myptr -= 1 + ((size_type)(-1) - this->_Myoff) / _VBITS;
			this->_Myoff %= _VBITS;
			}
		else
			{	/* add non-negative increment */
			this->_Myoff += _Off;
			this->_Myptr += this->_Myoff / _VBITS;
			this->_Myoff %= _VBITS;
			}
		return (*this);
		}

	_Mytype operator+(difference_type _Off) const
		{	// return this + integer
		_Mytype _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Mytype& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Mytype operator-(difference_type _Off) const
		{	// return this - integer
		_Mytype _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(
		const _Mytype& _Right) const
		{	// return difference of iterators

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (_VBITS * (this->_Myptr - _Right._Myptr)
			+ (difference_type)this->_Myoff
			- (difference_type)_Right._Myoff);
		}

	const_reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}

	bool operator==(const _Mytype& _Right) const
		{	// test for iterator equality

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (this->_Myptr == _Right._Myptr
			&& this->_Myoff == _Right._Myoff);
		}

	bool operator!=(const _Mytype& _Right) const
		{	// test for iterator inequality
		return (!(*this == _Right));
		}

	bool operator<(const _Mytype& _Right) const
		{	// test if this < _Right

 #if _HAS_ITERATOR_DEBUGGING
		_Compat(_Right);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (this->_Myptr < _Right._Myptr
			|| this->_Myptr == _Right._Myptr
				&& this->_Myoff < _Right._Myoff);
		}

	bool operator>(const _Mytype& _Right) const
		{	// test if this > _Right
		return (_Right < *this);
		}

	bool operator<=(const _Mytype& _Right) const
		{	// test if this <= _Right
		return (!(_Right < *this));
		}

	bool operator>=(const _Mytype& _Right) const
		{	// test if this >= _Right
		return (!(*this < _Right));
		}

protected:

 #if _HAS_ITERATOR_DEBUGGING
	void _Compat(const _Mytype& _Right) const
		{	// test for compatible iterator pair
		if (this->_Mycont == 0 || this->_Mycont != _Right._Mycont)
			_DEBUG_ERROR("vector<bool> iterators incompatible");
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	void _Dec()
		{	// decrement bit position
		if (this->_Myoff != 0)
			{
			--this->_Myoff;
			}
		else
			{
			_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Myptr != NULL);
			_SCL_SECURE_VALIDATE_RANGE(this->_Myptr > this->_My_cont_begin());
			--this->_Myptr;
			this->_Myoff = _VBITS - 1;
			}
		}

	void _Inc()
		{	// increment bit position
		_SCL_SECURE_VALIDATE(this->_Has_container() && this->_Myptr != NULL);
		_SCL_SECURE_VALIDATE_RANGE((this->_My_actual_offset() + 1) <= ((_MycontTy *)this->_Getmycont())->_Mysize);
		if (this->_Myoff < _VBITS - 1)
			++this->_Myoff;
		else
			this->_Myoff = 0, ++this->_Myptr;
		}
	};

template<class _Sizet,
	class _Difft,
	class _MycontTy>
	_Vb_const_iterator<_Sizet, _Difft, _MycontTy> operator+(_Difft _Off,
		_Vb_const_iterator<_Sizet, _Difft, _MycontTy> _Right)
		{	// return _Right + integer
		return (_Right += _Off);
		}

	// CLASS _Vb_iterator
template<class _Sizet,
	class _Difft,
	class _MycontTy>
	class _Vb_iterator
		: public _Vb_const_iterator<_Sizet, _Difft, _MycontTy>
	{	// iterator for mutable vector<bool>
public:
	typedef _Vb_const_iterator<_Sizet, _Difft, _MycontTy> _Mybase;
	typedef _Vb_iterator<_Sizet, _Difft, _MycontTy> _Mytype;

	typedef _Vb_reference<_Sizet, _Difft, _MycontTy> _Reft;
	typedef bool const_reference;

	typedef random_access_iterator_tag iterator_category;
	typedef _Bool value_type;
	typedef _Sizet size_type;
	typedef _Difft difference_type;
	typedef _Reft *pointer;
	typedef _Reft reference;

	_Vb_iterator()
		{	// construct with null reference
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	_Vb_iterator(_Vbase *_Ptr, _Container_base *_Mypvbool)
		: _Mybase(_Ptr, _Mypvbool)

 #else
	_Vb_iterator( _Vbase *_Ptr)
		: _Mybase(_Ptr)
 #endif /* _HAS_ITERATOR_DEBUGGING */

		{	// construct with offset and pointer
		}

	reference operator*() const
		{	// return (reference to) designated object
		return (_Reft(*this));
		}

	_Mytype& operator++()
		{	// preincrement
		++*(_Mybase *)this;
		return (*this);
		}

	_Mytype operator++(int)
		{	// postincrement
		_Mytype _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Mytype& operator--()
		{	// predecrement
		--*(_Mybase *)this;
		return (*this);
		}

	_Mytype operator--(int)
		{	// postdecrement
		_Mytype _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Mytype& operator+=(difference_type _Off)
		{	// increment by integer
		*(_Mybase *)this += _Off;
		return (*this);
		}

	_Mytype operator+(difference_type _Off) const
		{	// return this + integer
		_Mytype _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Mytype& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Mytype operator-(difference_type _Off) const
		{	// return this - integer
		_Mytype _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Mybase& _Right) const
		{	// return difference of iterators
		return (*(_Mybase *)this - _Right);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}
	};

template<class _Sizet,
	class _Difft,
	class _MycontTy>
	_Vb_iterator<_Sizet, _Difft, _MycontTy> operator+(_Difft _Off,
		_Vb_iterator<_Sizet, _Difft, _MycontTy> _Right)
		{	// return _Right + integer
		return (_Right += _Off);
		}

		// CLASS vector_bool
template<class _Alloc>
	class vector<_Bool, _Alloc>
		: public _CONTAINER_BASE_AUX_ALLOC<_Alloc>
	{	// varying size array of bits
public:
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type _Dift;
	typedef std::vector<_Vbase,
		typename _Alloc::template rebind<_Vbase>::other>
			_Vbtype;
	typedef std::vector<_Bool, _Alloc> _Myt;


	typedef _Dift difference_type;
	typedef _Bool _Ty;
	typedef _Alloc allocator_type;

	typedef _Vb_reference<size_type, _Dift, _Myt> reference;
	typedef bool const_reference;
	typedef bool value_type;

	typedef reference _Reft;
	typedef _Vb_const_iterator<size_type, difference_type, _Myt> const_iterator;
	typedef _Vb_iterator<size_type, difference_type, _Myt> iterator;

	friend class _Vb_iter_base<size_type, difference_type, _Myt>;
	friend class _Vb_reference<size_type, difference_type, _Myt>;
	friend class _Vb_const_iterator<size_type, difference_type, _Myt>;
	friend class _Vb_iterator<size_type, difference_type, _Myt>;

	typedef iterator pointer;
	typedef const_iterator const_pointer;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	static const int _VBITS = std::_VBITS;

	vector()
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Alloc()), _Mysize(0), _Myvec()
		{	// construct empty vector
		}

	vector(const _Myt& _Right)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Right.get_allocator()), _Mysize(_Right._Mysize), _Myvec(_Right._Myvec)
		{	// copy construct vector; an implicitly defined copy constructor would not create an aux object.
		}

	explicit vector(const _Alloc& _Al)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Mysize(0), _Myvec(_Al)
		{	// construct empty vector, with allocator
		}

	explicit vector(size_type _Count, bool _Val = false)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Alloc()), _Mysize(0), _Myvec(_Nw(_Count), (_Vbase)(_Val ? -1 : 0))
		{	// construct from _Count * _Val
		_Trim(_Count);
		}

	vector(size_type _Count, bool _Val, const _Alloc& _Al)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Mysize(0), _Myvec(_Nw(_Count), (_Vbase)(_Val ? -1 : 0), _Al)
		{	// construct from _Count * _Val, with allocator
		_Trim(_Count);
		}

	template<class _Iter>
		vector(_Iter _First, _Iter _Last)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Alloc()), _Mysize(0), _Myvec()
		{	// construct from [_First, _Last)
		_BConstruct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		vector(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Mysize(0), _Myvec(_Al)
		{	// construct from [_First, _Last), with allocator
		_BConstruct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _BConstruct(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// initialize from _Count * _Val
		size_type _Num = (size_type)_Count;
		_Myvec.assign(_Num, (_Ty)_Val ? -1 : 0);
		_Trim(_Num);
		}

	template<class _Iter>
		void _BConstruct(_Iter _First, _Iter _Last, input_iterator_tag)
		{	// initialize from [_First, _Last), input iterators
		insert(begin(), _First, _Last);
		}

	~vector()
		{	// destroy the object
		_Mysize = 0;
		}

	void reserve(size_type _Count)
		{	// determine new minimum length of allocated storage
		_Myvec.reserve(_Nw(_Count));
		}

	size_type capacity() const
		{	// return current length of allocated storage
		return (_Myvec.capacity() * _VBITS);
		}

 #if _HAS_ITERATOR_DEBUGGING || _SECURE_SCL
	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_VEC_ITER_BASE(_Myvec.begin()), this));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_VEC_ITER_BASE(_Myvec.begin()), this));
		}

 #else
	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_VEC_ITER_BASE(_Myvec.begin())));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_VEC_ITER_BASE(_Myvec.begin())));
		}
 #endif

	iterator end()
		{	// return iterator for end of mutable sequence
		iterator _Tmp = begin();
		if (0 < _Mysize)
			_Tmp += _Mysize;
		return (_Tmp);
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		const_iterator _Tmp = begin();
		if (0 < _Mysize)
			_Tmp += _Mysize;
		return (_Tmp);
		}

	iterator _Make_iter(const_iterator _Where)
		{	// make iterator from const_iterator
		iterator _Tmp = begin();
		if (0 < _Mysize)
			_Tmp += _Where - begin();
		return (_Tmp);
		}

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

	void resize(size_type _Newsize, bool _Val = false)
		{	// determine new length, padding with _Val elements as needed
		if (size() < _Newsize)
			_Insert_n(end(), _Newsize - size(), _Val);
		else if (_Newsize < size())
			erase(begin() + _Newsize, end());
		}

	size_type size() const
		{	// return length of sequence
		return (_Mysize);
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		const size_type _Maxsize = _Myvec.max_size();
		return (_Maxsize < (size_type)(-1) / _VBITS
			? _Maxsize * _VBITS : (size_type)(-1));
		}

	bool empty() const
		{	// test if sequence is empty
		return (size() == 0);
		}

	_Alloc get_allocator() const
		{	// return allocator object for values
		// Work around a BE problem.
		_Alloc _Alret = _Myvec.get_allocator();
		return (_Alret);
		}

	const_reference at(size_type _Off) const
		{	// subscript nonmutable sequence with checking
		if (size() <= _Off)
			_Xran();
		return (*(begin() + _Off));
		}

	reference at(size_type _Off)
		{	// subscript mutable sequence with checking
		if (size() <= _Off)
			_Xran();
		return (*(begin() + _Off));
		}

	const_reference operator[](size_type _Off) const
		{	// subscript nonmutable sequence
		return (*(begin() + _Off));
		}

	reference operator[](size_type _Off)
		{	// subscript mutable sequence
		return (*(begin() + _Off));
		}

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(end() - 1));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(end() - 1));
		}

	void push_back(bool _Val)
		{	// insert element at end
		insert(end(), _Val);
		}

	void pop_back()
		{	// erase element at end
		if (!empty())
			erase(end() - 1);
		}

	template<class _Iter>
		void assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last)
		_Assign(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Assign(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// assign _Count * _Val
		_Assign_n((size_type)_Count, (bool)_Val);
		}

	template<class _Iter>
		void _Assign(_Iter _First, _Iter _Last, input_iterator_tag)
		{	// assign [_First, _Last), input iterators
		erase(begin(), end());
		insert(begin(), _First, _Last);
		}

	void assign(size_type _Count, bool _Val)
		{	// assign _Count * _Val
		_Assign_n(_Count, _Val);
		}

	iterator insert(const_iterator _Where, bool _Val)
		{	// insert _Val at _Where
		size_type _Off = _Where - begin();
		_Insert_n(_Where, (size_type)1, _Val);
		return (begin() + _Off);
		}

	void insert(const_iterator _Where, size_type _Count, bool _Val)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, _Count, _Val);
		}

	template<class _Iter>
		void insert(const_iterator _Where, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
		_Insert(_Where, _First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _Count, _Iter _Val,
			_Int_iterator_tag)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, (size_type)_Count, (bool)_Val);
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
			input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators
		size_type _Off = _Where - begin();

		for (; _First != _Last; ++_First, ++_Off)
			insert(begin() + _Off, *_First);
		}

	template<class _Iter>
		void _Insert(const_iterator _Where,
			_Iter _First, _Iter _Last,
			forward_iterator_tag)
		{	// insert [_First, _Last) at _Where, forward iterators

 #if _HAS_ITERATOR_DEBUGGING
		_DEBUG_RANGE(_First, _Last);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		size_type _Count = 0;
		_Distance(_First, _Last, _Count);

		size_type _Off = _Insert_x(_Where, _Count);
		std::copy(_First, _Last, begin() + _Off);
		}

	iterator erase(const_iterator _Where_arg)
		{	// erase element at _Where
		iterator _Where = _Make_iter(_Where_arg);
		size_type _Off = _Where - begin();

 #if _HAS_ITERATOR_DEBUGGING
		if (end() <= _Where)
			_DEBUG_ERROR("vector<bool> erase iterator outside range");
		std::copy(_Where + 1, end(), _Where);
		_Orphan_range(_Off, _Mysize);

 #else /* _HAS_ITERATOR_DEBUGGING */
		std::copy(_Where + 1, end(), _Where);
 #endif /* _HAS_ITERATOR_DEBUGGING */

		_Trim(_Mysize - 1);
		return (begin() + _Off);
		}

	iterator erase(const_iterator _First_arg, const_iterator _Last_arg)
		{	// erase [_First, _Last)
		iterator _First = _Make_iter(_First_arg);
		iterator _Last = _Make_iter(_Last_arg);
		size_type _Off = _First - begin();

 #if _HAS_ITERATOR_DEBUGGING
		if (_Last < _First || end() < _Last)
			_DEBUG_ERROR("vector<bool> erase iterator outside range");
		iterator _Next = std::copy(_Last, end(), _First);
		size_type _Newsize = _Next - begin();
		_Orphan_range(_Newsize, _Mysize);
		_Trim(_Newsize);

 #else /* _HAS_ITERATOR_DEBUGGING */
		iterator _Next = std::copy(_Last, end(), _First);
		_Trim(_Next - begin());
 #endif /* _HAS_ITERATOR_DEBUGGING */

		return (begin() + _Off);
		}

	void clear()
		{	// erase all elements
		erase(begin(), end());
		}

	void flip()
		{	// toggle all elements
		for (_Vbtype::iterator _Next = _Myvec.begin();
			_Next != _Myvec.end(); ++_Next)
			*_Next = (_Vbase)~*_Next;
		_Trim(_Mysize);
		}

	void swap(_Myt& _Right)
		{	// exchange contents with right
		if (this != &_Right)
			{	// different, worth swapping

 #if _HAS_ITERATOR_DEBUGGING
			this->_Swap_all(_Right);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			this->_Swap_aux(_Right);
			_STD swap(_Mysize, _Right._Mysize);
			_Myvec.swap(_Right._Myvec);
			}
		}



	static void swap(reference _Left, reference _Right)
		{	// swap _Left and _Right vector<bool> elements
		bool _Val = _Left;

		_Left = _Right;
		_Right = _Val;
		}


protected:
	void _Assign_n(size_type _Count, bool _Val)
		{	// assign _Count * _Val
		erase(begin(), end());
		_Insert_n(begin(), _Count, _Val);
		}

	void _Insert_n(const_iterator _Where,
		size_type _Count, bool _Val)
		{	// insert _Count * _Val at _Where
		size_type _Off = _Insert_x(_Where, _Count);
		std::fill(begin() + _Off, begin() + (_Off + _Count), _Val);
		}

	size_type _Insert_x(const_iterator _Where, size_type _Count)
		{	// make room to insert _Count elements at _Where
		size_type _Off = _Where - begin();

 #if _HAS_ITERATOR_DEBUGGING
		if (end() < _Where)
			_DEBUG_ERROR("vector<bool> insert iterator outside range");
		bool _Realloc = capacity() - size() < _Count;
 #endif /* _HAS_ITERATOR_DEBUGGING */

		if (_Count == 0)
			;
		else if (max_size() - size() < _Count)
			_Xlen();	// result too long
		else
			{	// worth doing
			_Myvec.resize(_Nw(size() + _Count), 0);
			if (size() == 0)
				_Mysize += _Count;
			else
				{	// make room and copy down suffix
				iterator _Oldend = end();
				_Mysize += _Count;
				std::copy_backward(begin() + _Off, _Oldend, end());
				}

 #if _HAS_ITERATOR_DEBUGGING
			_Orphan_range(_Realloc ? 0 : _Off, _Mysize);
 #endif /* _HAS_ITERATOR_DEBUGGING */

			}
		return (_Off);
		}

	static size_type _Nw(size_type _Count)
		{	// return number of base words from number of bits
		return ((_Count + _VBITS - 1) / _VBITS);
		}

 #if _HAS_ITERATOR_DEBUGGING
	void _Orphan_range(size_type _Offlo, size_type _Offhi) const
		{	// orphan iterators within specified (inclusive) range
		typedef _Vb_iter_base<size_type, difference_type, _Myt> _Myiterbase;

		_Lockit _Lock(_LOCK_DEBUG);
		_Vbase *_Base = (_Vbase *)_VEC_ITER_BASE(_Myvec.begin());

		_Myiterbase **_Pnext =
			(_Myiterbase **)&this->_Myfirstiter;
		while (*_Pnext != 0)
			{	// test offset from beginning of vector
			size_type _Off = _VBITS * ((*_Pnext)->_Myptr - _Base)
				+ (*_Pnext)->_Myoff;
			if (_Off < _Offlo || _Offhi < _Off)
				_Pnext = (_Myiterbase **)&(*_Pnext)->_Mynextiter;
			else
				{	// orphan the iterator
				(*_Pnext)->_Mycont = 0;
				*_Pnext = (_Myiterbase *)(*_Pnext)->_Mynextiter;
				}
			}
		}
 #endif /* _HAS_ITERATOR_DEBUGGING */

	void _Trim(size_type _Size)
		{	// trim base vector to exact length in bits
		if (max_size() < _Size)
			_Xlen();	// result too long
		size_type _Words = _Nw(_Size);

		if (_Words < _Myvec.size())
			_Myvec.erase(_Myvec.begin() + _Words, _Myvec.end());
		_Mysize = _Size;
		_Size %= _VBITS;
		if (0 < _Size)
			_Myvec[_Words - 1] &= (_Vbase)((1 << _Size) - 1);
		}

	void _Xlen() const
		{	// report a length_error
		_THROW(length_error, "vector<bool> too long");
		}

	void _Xran() const
		{	// throw an out_of_range error
		_THROW(out_of_range, "invalid vector<bool> subscript");
		}

	size_type _Mysize;	// current length of sequence
	_Vbtype _Myvec;	// base vector of words
	};

typedef vector<bool, allocator<bool> > _Bvector;

#if _HAS_TRADITIONAL_STL
 typedef _Bvector bit_vector;
 #define __vector__	vector
#endif /* _HAS_TRADITIONAL_STL */

_STD_END

#ifdef _MSC_VER
 #pragma warning(default: 4244)
 #pragma warning(pop)
 #pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _VECTOR_ */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */

/*
 * Copyright (c) 1992-2008 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V5.05:0009 */
