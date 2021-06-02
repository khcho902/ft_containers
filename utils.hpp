/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 02:42:03 by kycho             #+#    #+#             */
/*   Updated: 2021/06/02 20:30:13 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	struct true_type {};
	struct false_type {};

	template <typename T>
	struct is_integer
	{
		typedef false_type type;
	};

	template <>
	struct is_integer<bool>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<char>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<wchar_t>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<signed char>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<unsigned char>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<short>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<unsigned short>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<int>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<unsigned int>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<long>
	{
		typedef true_type type;
	};

	template <>
	struct is_integer<unsigned long>
	{
		typedef true_type type;
	};

	template <typename T>
	void swap(T& x, T& y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	template <typename T>
	const T& max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	// TODO : 별로 필요없어보임 지울지 고려해야함.
	template <typename Arg, typename Result>
	struct unary_function
	{
		typedef Arg argument_type;
		typedef Result result_type;
	};

	template <typename Pair>
	struct Select1st : public unary_function<Pair, typename Pair::first_type>
	{
		typename Pair::first_type& operator()(Pair& x) const
		{ return x.first; }
		
		const typename Pair::first_type& operator()(const Pair& x) const
		{ return x.first; }
	};

} // end namespace ft 

#endif
