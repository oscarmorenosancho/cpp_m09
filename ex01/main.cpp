/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/20 19:09:14 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <iostream>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

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
		std::cerr << RED"Error: " << e.what() << RESET << std::endl;
	}
	return 0;
}
