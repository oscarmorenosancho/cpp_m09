/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/15 17:15:35 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Erro: Usage: ";
		std::cerr << argv[0] << " list_of_operands_or_operators";
		std::cerr << std::endl;
	}
	try
	{
		RPN calculator(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
