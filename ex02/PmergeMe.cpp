/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:21 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:09:31 by omoreno-         ###   ########.fr       */
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

MyList& MyList::sort()
{
	MyList& sorted = ::sort<MyList::iterator>(*this, K);
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

MyVector& MyVector::sort()
{
	MyVector& sorted = ::sort<MyVector::iterator>(*this, K);
	return (sorted);
}

void MyVector::print()
{
	::print_range<MyVector::iterator>(this->begin(), this->end());
}
