/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:54:36 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <iostream>
#include <Colors.hpp>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << RED"Error: Usage: ";
		std::cerr << argv[0] << " \"list_of_operands_or_operators\"";
		std::cerr << std::endl;
		return (1);
	}
	try
	{
		RPN calculator(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED"Error: " << e.what() << RESET << std::endl;
	}
	return 0;
}
