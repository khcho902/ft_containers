/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 18:24:39 by kycho             #+#    #+#             */
/*   Updated: 2021/05/31 02:06:17 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <utility>
# include <functional>
# include "iterator.hpp"
# include "rb_tree.hpp"
# include "utils.hpp"

namespace ft
{
    // ############## map class ################################################
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > > 
	class map
    {
	public:
	// ########## Member types ##########
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;

		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		
        typedef ptrdiff_t									difference_type;
        typedef size_t										size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};
		
	private:
		typedef typename Alloc::template rebind<value_type>::other										_pair_alloc_type;
		typedef rb_tree<key_type, value_type, ft::Select1st<value_type>, key_compare, _pair_alloc_type>	_rb_tree_type;
		_rb_tree_type tree;
	
	public:
		typedef typename _rb_tree_type::iterator					iterator;
		typedef typename _rb_tree_type::const_iterator				const_iterator;
		typedef typename _rb_tree_type::reverse_iterator			reverse_iterator;
		typedef typename _rb_tree_type::const_reverse_iterator		const_reverse_iterator;

	// ########## (constructor) ##########
		//empty (1)
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		//range (2)	
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		//copy (3)	
		map(const map& x);

	// ########## (destructor) ##########
		~map();

	// ########## operator= ##########
		//copy (1)	
		map& operator=(const map& x);

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
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

	// ########## Element access: ##########
		mapped_type& operator[](const key_type& k);

	// ########## Modifiers: ##########
		//single element (1)
		std::pair<iterator,bool> insert(const value_type& val);
		//with hint (2)
		iterator insert(iterator position, const value_type& val);
		//range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		//(1)
		void erase(iterator position);
		//(2)
		size_type erase(const key_type& k);
		//(3)
		void erase(iterator first, iterator last);
		void swap(map& x);
		void clear();

	// ########## Observers: ##########
		key_compare key_comp() const;
		value_compare value_comp() const;

	// ########## Operations: ##########
		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;
		size_type count(const key_type& k) const;
		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;
		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;
		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
		std::pair<iterator,iterator> equal_range(const key_type& k);

	// ########## Allocator: ##########
		allocator_type get_allocator() const;
	
	};

// ########## Non-member function overloads ##########
	//(1)
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);
	//(2)
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);
	//(3)
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);
	//(4)
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);
	//(5)
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);
	//(6)
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs);

	template <class Key, class T, class Compare, class Alloc>
  	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y);


} // end namespace ft 

#endif
