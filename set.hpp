/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 21:35:13 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 10:54:01 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include <utility>
# include <functional>
# include "reverse_iterator.hpp"
# include "rb_tree.hpp"
# include "utils.hpp"

namespace ft
{
	// ############## set class ################################################
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
    {
	public:
	// ########## Member types ##########
		typedef T												key_type;
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;
		typedef Alloc											allocator_type;
		
	private:
		typedef typename Alloc::template rebind<key_type>::other										_key_alloc_type;
		typedef rb_tree<key_type, value_type, ft::Identity<value_type>, key_compare, _key_alloc_type>	_rb_tree_type;
		_rb_tree_type tree;
	
	public:
		typedef typename _key_alloc_type::reference				reference;
		typedef typename _key_alloc_type::const_reference		const_reference;
		typedef typename _key_alloc_type::pointer				pointer;
		typedef typename _key_alloc_type::const_pointer			const_pointer;

		typedef typename _rb_tree_type::const_iterator			iterator;
		typedef typename _rb_tree_type::const_iterator			const_iterator;
		typedef typename _rb_tree_type::const_reverse_iterator	reverse_iterator;
		typedef typename _rb_tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename _rb_tree_type::difference_type			difference_type;
        typedef typename _rb_tree_type::size_type				size_type;

	// ########## (constructor) ##########
		//empty (1)
		explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: tree(comp, alloc)
		{}

		//range (2)
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: tree(comp, alloc)
		{ tree.insert_unique(first, last); }
		
		//copy (3)
		set(const set& x)
			: tree(x.tree)
		{}

	// ########## (destructor) ##########
		~set() {}
		
	// ########## operator= ##########
		//copy (1)	
 		set& operator=(const set& x)
		{
			tree = x.tree;
			return *this;
		}
		
	// ########## Iterators: ##########
		iterator begin() { return tree.begin(); }
		const_iterator begin() const { return tree.begin(); }

		iterator end() { return tree.end(); }
		const_iterator end() const { return tree.end(); }

		reverse_iterator rbegin() { return tree.rbegin(); }
		const_reverse_iterator rbegin() const { return tree.rbegin(); }
		
		reverse_iterator rend() { return tree.rend(); }
		const_reverse_iterator rend() const { return tree.rend(); }

	// ########## Capacity: ##########
		bool empty() const { return tree.empty(); }
		size_type size() const { return tree.size(); }
		size_type max_size() const { return tree.max_size(); }

	// ########## Modifiers: ##########
		//single element (1)
		std::pair<iterator,bool> insert(const value_type& val)
		{
			std::pair<typename _rb_tree_type::iterator, bool> p = tree.insert_unique(val);
			return std::pair<iterator, bool>(p.first, p.second);;
		}
		//with hint (2)
		iterator insert(iterator position, const value_type& val)
		{ return tree.insert_unique_(position, val); }
		//range (3)
		template <class InputIterator>
  		void insert(InputIterator first, InputIterator last)
		{ tree.insert_unique(first, last); }
		
  		//(1)
     	void erase(iterator position)
		{ tree.erase(position); }
		//(2)
		size_type erase(const value_type& val)
		{ return tree.erase(val); }
		//(3)
     	void erase(iterator first, iterator last)
		{ tree.erase(first, last); }
		
		void swap(set& x)
		{ tree.swap(x.tree); }

		void clear()
		{ tree.clear(); }

	// ########## Observers: ##########
		key_compare key_comp() const
		{ return tree.key_comp(); }
		value_compare value_comp() const
		{ return tree.key_comp(); }
		
	// ########## Operations: ##########
		iterator find(const value_type& val) const
		{ return tree.find(val); }
		
		size_type count(const value_type& val) const
		{ return tree.find(val) == tree.end() ? 0 : 1; }
		
		iterator lower_bound(const value_type& val) const
		{ return tree.lower_bound(val); }
		
		iterator upper_bound(const value_type& val) const
		{ return tree.upper_bound(val); }

		std::pair<iterator,iterator> equal_range(const value_type& val) const
		{ return tree.equal_range(val); }

	
		template <class _T, class _Compare, class _Alloc>
		friend bool operator==(const set<_T, _Compare, _Alloc>& lhs,
							const set<_T, _Compare, _Alloc>& rhs);
		
		template <class _T, class _Compare, class _Alloc>
		friend bool operator<(const set<_T, _Compare, _Alloc>& lhs,
							const set<_T, _Compare, _Alloc>& rhs);
	};

// ########## Non-member function overloads ##########
	//(1)
	template <class T, class Compare, class Alloc>
	bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return lhs.tree == rhs.tree; }
	//(2)
	template <class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }
	//(3)
	template <class T, class Compare, class Alloc>
	bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return lhs.tree < rhs.tree; }
	//(4)
	template <class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }
	//(5)
	template <class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }
	//(6)
	template <class T, class Compare, class Alloc>
	bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class T, class Compare, class Alloc>
  	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y)
	{ x.swap(y); }

} // end namespace ft 

#endif
