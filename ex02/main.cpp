/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:30:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:06:07 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <PmergeMe.hpp>

unsigned int	MyList::K = 2;
unsigned int	MyVector::K = 2;

int main(int argc, char **argv)
{
	MyList& lst = *new MyList();
	MyVector& vec = *new MyVector();
	for (int i = 1; i < argc; i++)
	{
		int temp = std::atoi(argv[i]);
		lst.push_back(temp);
		vec.push_back(temp);
	}
	std::cout << "at the begining: ";
	vec.print();
	{
		MyVector& res = vec.sort();
		delete &vec;
		std::cout << "at the end: ";
		print_range(res.begin(), res.end());
		delete &res;
	}
	{
		MyList& res = lst.sort();
		delete &res;
	}
	return (0);
}
