/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:15:23 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 10:48:16 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

# include <memory>
# include <utility>
# include <functional>
# include "reverse_iterator.hpp"
# include "rb_tree.hpp"
# include "utils.hpp"

namespace ft
{
    // ############## multimap class ###########################################
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class multimap
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
			friend class multimap;
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
		explicit multimap(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: tree(comp, alloc)
		{}
		//range (2)
		template <class InputIterator>
		multimap(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: tree(comp, alloc)
		{ tree.insert_equal(first, last); }
		//copy (3)
		multimap (const multimap& x)
			: tree(x.tree)
		{}

	// ########## (destructor) ##########
		~multimap() {}

	// ########## operator= ##########
		//copy (1)
		multimap& operator= (const multimap& x)
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
		iterator insert(const value_type& val)
		{ return tree.insert_equal(val); }
		//with hint (2)
		iterator insert(iterator position, const value_type& val)
		{ return tree.insert_equal_(position, val); }
		//range (3)
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{ tree.insert_equal(first, last); }
		
		//(1)
		void erase(iterator position)
		{ tree.erase(position); }
		//(2)
		size_type erase(const key_type& k)
		{ return tree.erase(k);}
		//(3)
		void erase(iterator first, iterator last)
		{ tree.erase(first, last); }
		
		void swap(multimap& x)
		{ tree.swap(x.tree); }

		void clear()
		{ tree.clear(); }

	// ########## Observers: ##########
		key_compare key_comp() const
		{ return tree.key_comp(); }
		value_compare value_comp() const
		{ return value_compare(tree.key_comp()); }

	// ########## Operations: ##########
		iterator find(const key_type& k)
		{ return tree.find(k); }
		const_iterator find(const key_type& k) const
		{ return tree.find(k); }

		size_type count(const key_type& k) const
		{ return tree.count(k); }

		iterator lower_bound(const key_type& k)
		{ return tree.lower_bound(k); }
		const_iterator lower_bound(const key_type& k) const
		{ return tree.lower_bound(k); }

		iterator upper_bound(const key_type& k)
		{ return tree.upper_bound(k); }
		const_iterator upper_bound(const key_type& k) const
		{ return tree.upper_bound(k); }

		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
		{ return tree.equal_range(k); }
		std::pair<iterator,iterator> equal_range(const key_type& k)
		{ return tree.equal_range(k); }


		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator==(const multimap<_Key, _T, _Compare, _Alloc>& lhs,
							const multimap<_Key, _T, _Compare, _Alloc>& rhs);
		
		template <class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator<(const multimap<_Key, _T, _Compare, _Alloc>& lhs,
							const multimap<_Key, _T, _Compare, _Alloc>& rhs);
	};

// ########## Non-member function overloads ##########
	//(1)
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return lhs.tree == rhs.tree; }
	//(2)
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }
	//(3)
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return lhs.tree < rhs.tree; }
	//(4)
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }
	//(5)
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }
	//(6)
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const multimap<Key, T, Compare, Alloc>& lhs, const multimap<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class Key, class T, class Compare, class Alloc>
  	void swap(multimap<Key, T, Compare, Alloc>& x, multimap<Key, T, Compare, Alloc>& y)
	{ x.swap(y); }

} // end namespace ft 

#endif
