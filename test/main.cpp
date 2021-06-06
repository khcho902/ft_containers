/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 21:43:55 by kycho             #+#    #+#             */
/*   Updated: 2021/06/06 17:32:16 by kycho            ###   ########.fr       */
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
    test_stack();
    std::cout << "\n\n";

    // ## Queue ##
    test_queue();
    std::cout << "\n\n";

    // ## Set ##
    test_set();
    std::cout << "\n\n";

  return 0;
}
