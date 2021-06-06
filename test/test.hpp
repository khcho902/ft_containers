/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 01:51:52 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 20:24:08 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include <iostream>
# include <cmath>

# ifdef STD

#  include <list>
#  include <vector>
#  include <map>
#  include <stack>
#  include <queue>
#  include <set>

#  define LIST std::list
#  define VECTOR std::vector
#  define MAP std::map
#  define STACK std::stack
#  define QUEUE std::queue
#  define SET std::set
#  define MULTIMAP std::multimap

#  define MSG " ** std containers result! ** "

# else

#  include "../list.hpp"
#  include "../vector.hpp"
#  include "../map.hpp"
#  include "../stack.hpp"
#  include "../queue.hpp"
#  include "../set.hpp"
#  include "../multimap.hpp"

#  define LIST ft::list
#  define VECTOR ft::vector
#  define MAP ft::map
#  define STACK ft::stack
#  define QUEUE ft::queue
#  define SET ft::set
#  define MULTIMAP ft::multimap

#  define MSG " ** my containers result! ** "

# endif

void test_list(void);
void test_vector(void);
void test_map(void);
void test_stack(void);
void test_queue(void);
void test_set(void);
void test_multimap(void);

#endif
