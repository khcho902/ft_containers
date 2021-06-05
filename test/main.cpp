/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:43:55 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 01:52:22 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int main (void)
{

    // ## List ##
    test_list();

    // ## Vector ##
    std::cout << "     <<< Vector test start >>>" << std::endl;
    std::cout << "     <<< Vector test end >>>" << std::endl;


    // ## Map ##
    std::cout << "     <<< Map test start >>>" << std::endl;
    std::cout << "     <<< Map test end >>>" << std::endl;


    // ## Stack ##
    std::cout << "     <<< Stack test start >>>" << std::endl;
    std::cout << "     <<< Stack test end >>>" << std::endl;


    // ## Queue ##
    std::cout << "     <<< Queue test start >>>" << std::endl;
    std::cout << "     <<< Queue test end >>>" << std::endl;

  

  return 0;
}
