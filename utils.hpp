/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 02:42:03 by kycho             #+#    #+#             */
/*   Updated: 2021/06/03 17:32:46 by kycho            ###   ########.fr       */
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

	template <typename ForwardIterator, typename T>
  	void fill(ForwardIterator first, ForwardIterator last, const T& val)
	{
  		while (first != last) {
    		*first = val;
    		++first;
		}
  	}

	template <typename OutputIterator, typename Size, typename T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& val)
	{
		while (n>0)
		{
			*first = val;
			++first; --n;
		}
		return first;
	}

	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
      			return false;
    		++first1; ++first2;
  		}
  		return true;
	}

	template <typename InputIterator1, typename InputIterator2>
  	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1!=last1)
  		{
    		if (first2==last2 || *first2<*first1)
				return false;
    		else if (*first1<*first2)
				return true;
    		++first1; ++first2;
  		}
  		return (first2!=last2);
	}

	template<typename InputIterator, typename OutputIterator>
  	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first!=last)
		{
			*result = *first;
			++result; ++first;
		}
		return result;
	}

	template <typename BidirectionalIterator1, typename BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
										 BidirectionalIterator1 last,
										 BidirectionalIterator2 result)
	{
		while (last != first)
			*(--result) = *(--last);
		return result;
	}

} // end namespace ft 

#endif
