/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/16 20:43:45 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: Usage: ";
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
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
