/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:30:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 13:27:05 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <time.h> 
#include <PmergeMe.hpp>
#include <Colors.hpp>
#define BLOBS   50

template<typename T>
std::string toString(const T & value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

int stoi(const std::string & s)
{
	std::runtime_error err_fail_to_conv("fail to convert: " + s);
    long lV;
    std::istringstream(s) >> lV;
	int iV = static_cast<int>(lV);
	if (iV != lV || ::toString<long>(lV) != s)
		throw err_fail_to_conv;
    return (iV);
}

int main(int argc, char **argv)
{
	std::list<int>& lst = *new std::list<int>();
	std::vector<int>& vec = *new std::vector<int>();
	for (int i = 1; i < argc; i++)
	{
		try
		{
			int temp = ::stoi(argv[i]);
			lst.push_back(temp);
			vec.push_back(temp);
		}
		catch(const std::exception& e)
		{
			delete &vec;
			delete &lst;
			std::cerr << RED"Error: "<< e.what() << std::endl << RESET;
			return (EXIT_FAILURE);
		}
		
	}
	double sortVectorTime;
	double sortListTime;
	size_t size = vec.size();
	int K = (size / BLOBS);
	K = (K < 1) ? 1 : K;
	std::cout << BLUE"Before: ";
	PmergeMe::print_range<std::vector<int>::iterator>
		(vec.begin(), vec.end());
	std::cout << RESET;
	{
		clock_t start_time = clock();
		std::vector<int>& res =	PmergeMe::sort<std::vector<int>::iterator>
			(vec, K);
		clock_t end_time = clock();
		sortVectorTime = (end_time - start_time) * 1.0e6 / CLOCKS_PER_SEC;
		delete &vec;
		std::cout << GREEN"After: ";
		PmergeMe::print_range<std::vector<int>::iterator>
			(res.begin(), res.end());
		std::cout << RESET;
		delete &res;
	}
	{
		clock_t start_time = clock();
		std::list<int>& res = PmergeMe::sort<std::list<int>::iterator>
			(lst, K);
		clock_t end_time = clock();
		sortListTime = (end_time - start_time) * 1.0e6 / CLOCKS_PER_SEC;
		delete &lst;
		delete &res;
	}
	std::cout << YELLOW"Time to process a range of " << size << " elements with std::vector : ";
	std::cout << std::setprecision(17) << sortVectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << size << " elements with std::list : ";
	std::cout << std::setprecision(17) << sortListTime << " us" << std::endl;
	std::cout << RESET;
	return (EXIT_SUCCESS);
}
