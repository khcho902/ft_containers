/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:37:57 by kycho             #+#    #+#             */
/*   Updated: 2021/06/01 21:17:24 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
//# include <iterator>
//# include "iterator.hpp"
//# include "utils.hpp"

namespace ft
{
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

	    typedef _vector_iterator<T>                           iterator;
        typedef _vector_const_iterator<T>                     const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

	public:
    // ########## (constructor) ##########
		/*
		//default (1)
		explicit vector(const allocator_type& alloc = allocator_type());
		//fill (2)
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		//range (3)
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		//copy (4)
		vector(const vector& x);
		*/

	// ########## (destructor) ##########
		/*
		~vector();
		*/
	
	// ########## operator= ##########
		/*
		//copy (1)
 		vector& operator=(const vector& x);
		 */

	// ########## Iterators: ##########
		/*
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		*/

	// ########## Capacity: ##########
		/*
		size_type size() const;
		size_type max_size() const;
		void resize(size_type n, value_type val = value_type());
		size_type capacity() const;
		bool empty() const;
		void reserve(size_type n);
		*/

	// ########## Element access: ##########
		/*
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		*/


	// ########## Modifiers: ##########
		/*
		//range (1)
		template <class InputIterator>
  		void assign(InputIterator first, InputIterator last);
		//fill (2)
		void assign(size_type n, const value_type& val);
		void push_back(const value_type& val);
		void pop_back();
		//single element (1)
		iterator insert(iterator position, const value_type& val);
		//fill (2)
    	void insert(iterator position, size_type n, const value_type& val);
		//range (3)
		template <class InputIterator>
    	void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector& x);
		void clear();
		*/

	// ########## Allocator: ##########
		/*
		allocator_type get_allocator() const;
		*/
	};

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
