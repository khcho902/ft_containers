/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:43:55 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 14:55:33 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int main (void)
{
    std::cout << MSG << "\n" << std::endl;

    // ## List ##
    test_list();
    std::cout << "\n\n";

    // ## Vector ##
    test_vector();
    std::cout << "\n\n";

    // ## Map ##
    test_map();
    std::cout << "\n\n";

    // ## Stack ##
    //std::cout << "     <<< Stack test start >>>" << std::endl;
    //std::cout << "     <<< Stack test end >>>" << std::endl;


    // ## Queue ##
    //std::cout << "     <<< Queue test start >>>" << std::endl;
    //std::cout << "     <<< Queue test end >>>" << std::endl;

  

  return 0;
}
