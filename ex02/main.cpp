/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:30:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/20 11:04:48 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <PmergeMe.hpp>

int main(int argc, char **argv)
{
	std::list<int>& lst = *new std::list<int>();
	std::vector<int>& vec = *new std::vector<int>();
	for (int i = 1; i < argc; i++)
	{
		int temp = std::atoi(argv[i]);
		lst.push_back(temp);
		vec.push_back(temp);
	}
	std::cout << "at the begining: ";
	print_range<std::vector<int>::iterator>(vec.begin(), vec.end());
	{
		std::vector<int>& res = sort<std::vector<int>::iterator>(vec,2);
		delete &vec;
		std::cout << "at the end: ";
		print_range<std::vector<int>::iterator>(res.begin(), res.end());
		delete &res;
	}
	{
		std::list<int>& res = sort<std::list<int>::iterator>(lst, 2);
		delete &lst;
		delete &res;
	}
	return (0);
}
