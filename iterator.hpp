/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:20:33 by kycho             #+#    #+#             */
/*   Updated: 2021/05/31 20:48:53 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

//# include <memory>
//# include <iterator>

namespace ft
{
	// TODO : iterator 별도로 만들지 결정해야함 
	/*
	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	class iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
  	};
	*/

	template <class Iterator>
	class reverse_iterator
	{
	protected:
		Iterator										base_iterator;

	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

		//default (1)	
		reverse_iterator() : base_iterator() {}
		//initialization (2)	
		explicit reverse_iterator (iterator_type it) : base_iterator(it) {}
		//copy (3)	
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : base_iterator(rev_it.base()) {}

		iterator_type base() const
		{
			return base_iterator;
		}

		reference operator*() const
		{
			Iterator __tmp = base_iterator;
			return *--__tmp;
		}

		reverse_iterator operator+(difference_type __n) const
		{
			return reverse_iterator(base_iterator - __n);
		}

		reverse_iterator& operator++()
		{
			--base_iterator;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator __tmp = *this;
			--base_iterator;
			return __tmp;
		}

		reverse_iterator& operator+=(difference_type __n)
		{
			base_iterator -= __n;
			return *this;
		}

		reverse_iterator operator-(difference_type __n) const
		{
			return reverse_iterator(base_iterator + __n);
		}

		reverse_iterator& operator--()
		{
			++base_iterator;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator __tmp = *this;
			++base_iterator;
			return __tmp;
		}

		reverse_iterator& operator-=(difference_type __n)
		{
			base_iterator += __n;
			return *this;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type __n) const
		{
			return *(*this + __n);
		}
	};

	//(1)
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	//(2)
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	}
	//(3)
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	//(4)
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(rhs < lhs);
	}
	//(5)
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return rhs < lhs;
	}	
	//(6)
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif
