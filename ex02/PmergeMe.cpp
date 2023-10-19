/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:21 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:28:09 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <PmergeMe.hpp>

MyList::MyList()
{
}

MyList::~MyList()
{
}

std::list<int>& MyList::sort()
{
	std::list<int>& sorted = ::sort<std::list<int>::iterator>(*(std::list<int>*)(this), K);
	return (sorted);
}

void MyList::print()
{
	::print_range<MyList::iterator>(this->begin(), this->end());
}

MyVector::MyVector()
{
}

MyVector::~MyVector()
{
}

std::vector<int>& MyVector::sort()
{
	std::vector<int>& sorted = ::sort<std::vector<int>::iterator>(*(std::vector<int>*)this, K);
	return (sorted);
}

void MyVector::print()
{
	::print_range<MyVector::iterator>(this->begin(), this->end());
}
