/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:16 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/20 10:59:03 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PMERGE_ME_HPP_
# define _PMERGE_ME_HPP_

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

template <class Iterator, class Container>
Container& insertionSort(const Container& unsorted);
template <class Iterator, class Container>
Container& merge(Container& lA, Container& rA);
template <class Iterator>
void print_range(Iterator begin, Iterator end);
template <class Iterator, class Container>
Container& sort(Container& unsorted, unsigned int K);

#include <PmergeMe.cpp>

#endif
