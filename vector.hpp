/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:37:57 by kycho             #+#    #+#             */
/*   Updated: 2021/06/03 00:56:07 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator>
# include <stdexcept>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	// ############## vector iterator ###########################################################
    template<typename T>
    struct _vector_iterator
    {
        typedef _vector_iterator<T>					_Self;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::random_access_iterator_tag     iterator_category;

		pointer ptr;

		_vector_iterator() : ptr() {}
		_vector_iterator(const pointer& x) : ptr(x) {}
        
        reference operator*() const
        {
			return *ptr;
		}
        
        pointer operator->() const
        {
			return ptr;
		}
        
        _Self& operator++()
        {
			ptr++;
            return *this;
        }

        _Self operator++(int)
        {
            _Self _tmp = *this;
			ptr++;
            return _tmp;
        }
        
        _Self& operator--()
        {
            ptr--;
            return *this;
        }
        
        _Self operator--(int)
        {
            _Self _tmp = *this;
			ptr--;
            return _tmp;
        }

		reference operator[](const difference_type& n) const
		{
			return ptr[n];
		}

		_Self& operator+=(const difference_type& n)
		{
			ptr += n;
			return *this;
		}

		_Self operator+(const difference_type& n) const
		{
			return _Self(ptr + n);
		}

		_Self& operator-=(const difference_type& n)
		{
			ptr -= n;
			return *this;
		}

		_Self operator-(const difference_type& n) const
		{
			return _Self(ptr -n);
		}

        bool operator==(const _Self& x) const
        { return ptr == x.ptr; }

        bool operator!=(const _Self& x) const
        { return ptr != x.ptr; }

		bool operator<(const _Self& x) const
        { return ptr < x.ptr; }

		bool operator>(const _Self& x) const
        { return ptr > x.ptr; }

		bool operator<=(const _Self& x) const
        { return ptr <= x.ptr; }

		bool operator>=(const _Self& x) const
        { return ptr >= x.ptr; }
		
		difference_type operator-(const _Self& x) const
		{
			return ptr - x.ptr;
		}

		const pointer& base() const
		{
			return ptr;
		}

    };

	template <typename T>
	_vector_iterator<T> operator+(typename _vector_iterator<T>::difference_type n, const _vector_iterator<T>& v)
	{
		return _vector_iterator<T>(v.base() + n);
	}

	// ############## vector const iterator ###########################################################
    template<typename T>
    struct _vector_const_iterator
    {
        typedef _vector_const_iterator<T>			_Self;
		typedef _vector_iterator<T>					iterator;
        
        typedef T                                   value_type;
        typedef ptrdiff_t                           difference_type;
        typedef const T*							pointer;
        typedef const T&							reference;
        typedef std::random_access_iterator_tag     iterator_category;

		pointer ptr;

		_vector_const_iterator() : ptr() {}
		_vector_const_iterator(const pointer& x) : ptr(x) {}
		_vector_const_iterator(const iterator& x) : ptr(x.ptr) {}
        
        reference operator*() const
        {
			return *ptr;
		}
        
        pointer operator->() const
        {
			return ptr;
		}
        
        _Self& operator++()
        {
			ptr++;
            return *this;
        }

        _Self operator++(int)
        {
            _Self _tmp = *this;
			ptr++;
            return _tmp;
        }
        
        _Self& operator--()
        {
            ptr--;
            return *this;
        }
        
        _Self operator--(int)
        {
            _Self _tmp = *this;
			ptr--;
            return _tmp;
        }

		reference operator[](const difference_type& n) const
		{
			return ptr[n];
		}

		_Self& operator +=(const difference_type& n)
		{
			ptr += n;
			return *this;
		}

		_Self operator+(const difference_type& n) const
		{
			return _Self(ptr + n);
		}

		_Self& operator-=(const difference_type& n)
		{
			ptr -= n;
			return *this;
		}

		_Self operator-(const difference_type& n) const
		{
			return _Self(ptr -n);
		}

		bool operator==(const _Self& x) const
        { return ptr == x.ptr; }

        bool operator!=(const _Self& x) const
        { return ptr != x.ptr; }

		bool operator<(const _Self& x) const
        { return ptr < x.ptr; }

		bool operator>(const _Self& x) const
        { return ptr > x.ptr; }

		bool operator<=(const _Self& x) const
        { return ptr <= x.ptr; }

		bool operator>=(const _Self& x) const
        { return ptr >= x.ptr; }
		
		difference_type operator-(const _Self& x) const
		{
			return ptr - x.ptr;
		}

		const pointer& base() const
		{
			return ptr;
		}
    };

	template <typename T>
	_vector_const_iterator<T> operator+(typename _vector_const_iterator<T>::difference_type n, const _vector_const_iterator<T>& v)
	{
		return _vector_const_iterator<T>(v.base() + n);
	}










	template <typename T>
	bool operator==(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename T>
	bool operator!=(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() != rhs.base(); }
	
	template <typename T>
	bool operator<(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename T>
	bool operator>(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename T>
	bool operator<=(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename T>
	bool operator>=(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename T>
	typename _vector_iterator<T>::difference_type operator-(const _vector_iterator<T>& lhs, const _vector_const_iterator<T>& rhs)
	{ return lhs.base() - rhs.base(); }











	// ############## vector class ##############################################################
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
	// ########## Member types ##########
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

	    typedef _vector_iterator<T>							iterator;
        typedef _vector_const_iterator<T>					const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

	protected:
		allocator_type		_allocator;
		pointer				_start;
		pointer				_finish;
		pointer				_end_of_storage;

		pointer _allocate(size_type n)
		{ return n != 0 ? _allocator.allocate(n) : 0; }

		void _deallocate(pointer p, size_type n)
		{
			if (p)
				_allocator.deallocate(p, n);
		}

		void _destroy(iterator first, iterator last)
		{
			for(; first != last; first++)
				this->_allocator.destroy(first.base());
		}
		
		void _range_check(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("vector::_range_check");
		}

		size_type _check_len(size_type n, const char* s) const
		{
			if (max_size() - size() < n)
				throw std::length_error(s);

    		const size_type len = size() + ft::max(size(), n);
    		return (len < size() || len > max_size()) ? max_size() : len;
		}

		void _erase_at_end(pointer ptr)
		{
			this->_destroy(iterator(ptr), iterator(this->_finish));
			this->_finish = ptr;
		}

		void _insert_aux(iterator position, const T& x)
		{
			if (this->_finish != this->_end_of_storage)
			{
				this->_allocator.construct(this->_finish, *(this->_finish - 1));
				++this->_finish;

				T x_copy = x;

				// TODO :  std::copy_backward  바꿔야함 
				//std::copy_backward(position.base(), this->_finish - 2, this->_finish - 1);
				iterator first(position.base());
				iterator last(this->_finish - 2);
				iterator result(this->_finish - 1);
				
				while (last != first)
					*(--result) = *(--last);
				// 바꿨는데 아직 제대로 동작하는지 확인필요 
				
				*position = x_copy;
			}
			else
			{
				const size_type len = _check_len(size_type(1), "vector::_M_insert_aux");
            	const size_type elems_before = position - begin();
            	pointer new_start(this->_allocate(len));
            	pointer new_finish(new_start);
			
            	try
            	{   
					this->_allocator.construct(new_start + elems_before, x);
					new_finish = 0;
                	new_finish = std::uninitialized_copy(this->_start, position.base(), new_start);
                	++new_finish;
                	new_finish = std::uninitialized_copy(position.base(), this->_finish, new_finish);
				}
				catch(...)
            	{
					if (!new_finish)
						this->_allocator.destroy(new_start + elems_before);
					else
						this->_destroy(iterator(new_start), iterator(new_finish));
					this->_deallocate(new_start, len);
					throw;  // TODO  확인필요
				}

				this->_destroy(iterator(this->_start), iterator(this->_finish));
				this->_deallocate(this->_start, this->_end_of_storage - this->_start);

				this->_start = new_start;
				this->_finish = new_finish;
				this->_end_of_storage = new_start + len;
			}
		}


	public:
    // ########## (constructor) ##########
		//default (1)
		explicit vector(const allocator_type& alloc = allocator_type());
		/*
		//fill (2)
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		//range (3)
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		//copy (4)
		vector(const vector& x);
		*/

	// ########## (destructor) ##########
		~vector();
	
	// ########## operator= ##########
		/*
		//copy (1)
 		vector& operator=(const vector& x);
		 */

	// ########## Iterators: ##########
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

	// ########## Capacity: ##########
		size_type size() const;
		size_type max_size() const;
		/*
		void resize(size_type n, value_type val = value_type());
		*/
		size_type capacity() const;
		bool empty() const;
		/*
		void reserve(size_type n);
		*/

	// ########## Element access: ##########
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

	// ########## Modifiers: ##########
		/*
		//range (1)
		template <class InputIterator>
  		void assign(InputIterator first, InputIterator last);
		//fill (2)
		void assign(size_type n, const value_type& val);
		*/
		void push_back(const value_type& val);
		void pop_back();
		/*
		//single element (1)
		iterator insert(iterator position, const value_type& val);
		//fill (2)
    	void insert(iterator position, size_type n, const value_type& val);
		//range (3)
		template <class InputIterator>
    	void insert(iterator position, InputIterator first, InputIterator last);
		*/
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector& x);
		void clear();
		

	// ########## Allocator: ##########
		/*
		allocator_type get_allocator() const;
		*/
	};



	// ########## (constructor) ##########
	//default (1)
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc)
	: _allocator(alloc), _start(0), _finish(0), _end_of_storage(0)
	{}
	/*
	//fill (2)
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	//range (3)
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	//copy (4)
	vector(const vector& x);
	*/

	// ########## (destructor) ##########
	template <class T, class Alloc>
	vector<T, Alloc>::~vector()
	{
		this->_destroy(iterator(this->_start), iterator(this->_finish));
		this->_deallocate(this->_start, this->_end_of_storage - this->_start);
	}
	
	// ########## operator= ##########
	/*
	//copy (1)
	vector& operator=(const vector& x);
	*/

	// ########## Iterators: ##########
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
	{ return iterator(this->_start); }
	
	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
	{ return const_iterator(this->_start); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
	{ return iterator(this->_finish); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
	{ return const_iterator(this->_finish); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
	{ return reverse_iterator(end()); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
	{ return const_reverse_iterator(end()); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
	{ return reverse_iterator(begin()); }
	
	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
	{ return const_reverse_iterator(begin()); }
	
	// ########## Capacity: ##########
	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
	{ return size_type(this->_finish - this->_start); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
	{ return this->_allocator.max_size(); }
	/*
	void resize(size_type n, value_type val = value_type());
	*/
	template <class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
	{ return size_type(this->_end_of_storage - this->_start); }

	template <class T, class Alloc>
	bool vector<T, Alloc>::empty() const
	{ return begin() == end(); }
	/*
	void reserve(size_type n);
	*/

	// ########## Element access: ##########
	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)
	{ return *(this->_start + n); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type n) const
	{ return *(this->_start + n); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
	{
		this->_range_check(n);
		return (*this)[n];
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
	{
		this->_range_check(n);
		return (*this)[n];
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::front()
	{ return *begin(); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
	{ return *begin(); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::back()
	{ return *(end() - 1); }

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
	{ return *(end() - 1); }

	// ########## Modifiers: ##########
	/*
	//range (1)
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	//fill (2)
	void assign(size_type n, const value_type& val);
	*/
	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& val)
	{
		if (this->_finish != this->_end_of_storage)
		{
			this->_allocator.construct(this->_finish, val);
			this->_finish++;
		}
		else
		{
			_insert_aux(end(), val);
		}
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::pop_back()
	{
		(this->_finish)--;
		this->_allocator.destroy(this->_finish);
	}
	/*
	//single element (1)
	iterator insert(iterator position, const value_type& val);
	//fill (2)
	void insert(iterator position, size_type n, const value_type& val);
	//range (3)
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last);
	*/
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
	{
		if (position + 1 != end())
		{
			// TODO : 직접 짜야함 
			std::copy(position + 1, end(), position);
		}
		this->_finish--;
		this->_allocator.destroy(this->_finish);
		return position;
	}
	
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		if (first != last)
		{
			if (last != end())
			{
				// TODO : 직접 짜야함
				std::copy(last, end(), first);
			}
			this->_erase_at_end(first.base() + (end() - last));
		}
		return first;
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::swap(vector& x)
	{
		ft::swap(this->_start, x._start);
		ft::swap(this->_finish, x._finish);
		ft::swap(this->_end_of_storage, x._end_of_storage);

		// TODO : 확인필요
		ft::swap(this->_allocator, x._allocator);
        //allocator_type tmp = this->_allocator;
        //this->_allocator = x._allocator;
        //x._allocator = tmp;
	}
	
	template <class T, class Alloc>
	void vector<T, Alloc>::clear()
	{ _erase_at_end(this->_start); }

	// ########## Allocator: ##########
	/*
	allocator_type get_allocator() const;
	*/

// ########## Non-member function overloads ##########
	/*
	//(1)
	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//(2)
	template <class T, class Alloc>
  	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//(3)
	template <class T, class Alloc>
  	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//(4)
	template <class T, class Alloc>
  	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//(5)
	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	//(6)
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	*/

	/*
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
	*/

} // end namespace ft 

#endif
