/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 01:51:52 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 16:24:08 by kycho            ###   ########.fr       */
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

#  define LIST std::list
#  define VECTOR std::vector
#  define MAP std::map
#  define STACK std::stack
#  define QUEUE std::queue

#  define MSG " ** std containers result! ** "

# else

#  include "../list.hpp"
#  include "../vector.hpp"
#  include "../map.hpp"
#  include "../stack.hpp"
#  include "../queue.hpp"

#  define LIST ft::list
#  define VECTOR ft::vector
#  define MAP ft::map
#  define STACK ft::stack
#  define QUEUE ft::queue

#  define MSG " ** my containers result! ** "

# endif

void test_list(void);
void test_vector(void);
void test_map(void);
void test_stack(void);
void test_queue(void);

#endif
