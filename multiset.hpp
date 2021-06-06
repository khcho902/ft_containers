/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:18:12 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 21:28:24 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include <utility>
# include <functional>
# include "iterator.hpp"
# include "rb_tree.hpp"
# include "utils.hpp"

namespace ft
{
	// ############## multiset class ################################################
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class multiset
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

	// ########## (destructor) ##########

	// ########## operator= ##########

	// ########## Iterators: ##########

	// ########## Capacity: ##########

	// ########## Modifiers: ##########


	// ########## Observers: ##########


	// ########## Operations: ##########


	// ########## Allocator: ##########
		/*
		allocator_type get_allocator() const;
		*/
	
		/*
		template <class _T, class _Compare, class _Alloc>
		friend bool operator==(const multiset<_T, _Compare, _Alloc>& lhs,
							const multiset<_T, _Compare, _Alloc>& rhs);
		
		template <class _T, class _Compare, class _Alloc>
		friend bool operator<(const multiset<_T, _Compare, _Alloc>& lhs,
							const multiset<_T, _Compare, _Alloc>& rhs);
		*/
	};

// ########## Non-member function overloads ##########
	/*
	//(1)
	template <class T, class Compare, class Alloc>
	bool operator==(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return lhs.tree == rhs.tree; }
	//(2)
	template <class T, class Compare, class Alloc>
	bool operator!=(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }
	//(3)
	template <class T, class Compare, class Alloc>
	bool operator<(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return lhs.tree < rhs.tree; }
	//(4)
	template <class T, class Compare, class Alloc>
	bool operator<=(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }
	//(5)
	template <class T, class Compare, class Alloc>
	bool operator>(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }
	//(6)
	template <class T, class Compare, class Alloc>
	bool operator>=(const multiset<T, Compare, Alloc>& lhs, const multiset<T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class T, class Compare, class Alloc>
  	void swap(multiset<T, Compare, Alloc>& x, multiset<T, Compare, Alloc>& y)
	{ x.swap(y); }
	*/

} // end namespace ft 

#endif
