/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:45:39 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:04:32 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MERGE_INSERT_HPP_
#define _MERGE_INSERT_HPP_

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

template <class Iterator, class Container>
Container& insertionSort(const Container& unsorted);
template <class Iterator, class Container>
Container& merge(Container& lA, Container& rA);
template <class Iterator, class Container>
void print_range(Iterator begin, Iterator end);
template <class Iterator, class Container>
Container& sort(Container& unsorted, unsigned int K);

#include <merge_insert.tpp>

#endif
