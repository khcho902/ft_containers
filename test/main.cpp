/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:43:55 by kycho             #+#    #+#             */
/*   Updated: 2021/06/07 00:48:27 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int main (void)
{
    std::cout << MSG << "\n" << std::endl;

    // ## List ##
    test_list();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Vector ##
    test_vector();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Map ##
    test_map();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Stack ##
    test_stack();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Queue ##
    test_queue();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Set ##
    test_set();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Multimap ##
    test_multimap();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

    // ## Multiset ##
    test_multiset();
    std::cout << 
    "-------------------------------------------------------------------------"
    << std::endl;

  return 0;
}
