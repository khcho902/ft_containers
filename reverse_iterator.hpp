/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:20:33 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 10:39:05 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
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
			Iterator tmp = base_iterator;
			return *--tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(base_iterator - n);
		}

		reverse_iterator& operator++()
		{
			--base_iterator;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--base_iterator;
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n)
		{
			base_iterator -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(base_iterator + n);
		}

		reverse_iterator& operator--()
		{
			++base_iterator;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++base_iterator;
			return tmp;
		}

		reverse_iterator& operator-=(difference_type n)
		{
			base_iterator += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
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


	template<typename IteratorL, typename IteratorR>
    bool operator==(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return lhs.base() == rhs.base(); }

	template<typename IteratorL, typename IteratorR>
    bool operator<(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return rhs.base() < lhs.base(); }

	template<typename IteratorL, typename IteratorR>
    bool operator!=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return !(lhs == rhs); }

	template<typename IteratorL, typename IteratorR>
    bool operator>(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return rhs < lhs; }

	template<typename IteratorL, typename IteratorR>
    bool operator<=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return !(rhs < lhs); }

	template<typename IteratorL, typename IteratorR>
	bool operator>=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
    { return !(lhs < rhs); }


	template<typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ return rhs.base() - lhs.base(); }
}

#endif
