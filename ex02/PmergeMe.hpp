/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:16 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/20 13:23:57 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PMERGE_ME_HPP_
# define _PMERGE_ME_HPP_

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

class PmergeMe
{
private:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe&);
	PmergeMe& operator=(PmergeMe&);
public:
	template <class Iterator, class Container>
	static Container& insertionSort(const Container& unsorted);
	template <class Iterator, class Container>
	static Container& merge(Container& lA, Container& rA);
	template <class Iterator>
	static void print_range(Iterator begin, Iterator end);
	template <class Iterator, class Container>
	static Container& sort(Container& unsorted, unsigned int K);
};

#include <PmergeMe.cpp>

#endif
