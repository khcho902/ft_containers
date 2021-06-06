/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:45:24 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 15:30:09 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

#include "list.hpp"

namespace ft
{
	// ############## queue class ##############################################
	template <class T, class Container = ft::list<T> >
	class queue
	{
	public:
	// ########## Member types ##########
		typedef T											value_type;
		typedef Container									container_type;
		typedef size_t										size_type;
	
	protected:
		container_type c;

	public:
	// ########## Member functions ##########
		explicit queue(const container_type& ctnr = container_type())
			: c(ctnr)
		{}

		bool empty() const
		{ return c.empty(); }

		size_type size() const
		{ return c.size(); }

		value_type& front()
		{ return c.front(); }
		const value_type& front() const
		{ return c.front(); }

		value_type& back()
		{ return c.back(); }
		const value_type& back() const
		{ return c.back(); }

		void push(const value_type& val)
		{ c.push_back(val); }

		void pop()
		{ c.pop_front(); }

		template <class _T, class _Container>
  		friend bool operator==(const queue<_T, _Container>& lhs,
		  					const queue<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool operator<(const queue<_T, _Container>& lhs,
							const queue<_T, _Container>& rhs);
	};

// ########## Non-member function overloads ##########
	//(1)	
	template <class T, class Container>
  	bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return lhs.c == rhs.c; }
	//(2)	
	template <class T, class Container>
  	bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return !(lhs == rhs); }
	//(3)	
	template <class T, class Container>
	bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return lhs.c < rhs.c; }
	//(4)	
	template <class T, class Container>
	bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return !(rhs < lhs); }
	//(5)	
	template <class T, class Container>
	bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return rhs < lhs; }
	//(6)	
	template <class T, class Container>
	bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
	{ return !(lhs < rhs); }

} // end namespace ft 

#endif
