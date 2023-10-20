/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:21 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/20 13:23:48 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <PmergeMe.hpp>

PmergeMe::PmergeMe(){}
PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(PmergeMe&){}
PmergeMe& PmergeMe::operator=(PmergeMe&){return(*this);}

template <class Iterator>
void PmergeMe::print_range(Iterator begin, Iterator end)
{
	if (begin != end)
	{
		std::cout << *begin;
		begin++;
	}
	while(begin != end)
	{
		std::cout << ", " << *begin;
		begin++;
	}
	std::cout << std::endl;
}

template <class Iterator, class Container>
Container& PmergeMe::insertionSort(const Container& unsorted)
{
	int q = unsorted.size();
	Container& ret = *new Container(unsorted.begin(), unsorted.end());
	Iterator itI = ret.begin();
	for (int i = 0; i < q - 1; i++, itI++)
	{
		int j = i + 1;
		Iterator itJ = itI;
		itJ++;
		int tempVal = *itJ;
		Iterator itJdec = itJ;
		itJdec--;
		while (j > 0 && *itJdec > tempVal)
		{
			*itJ = *itJdec;
			itJ--;
			j--;
			itJdec = itJ;
			itJdec--;
		}
		*itJ = tempVal;
	}
	return (ret);
}

template <class Iterator, class Container>
Container& PmergeMe::merge(Container& lA, Container& rA)
{
	int totalSize = lA.size() + rA.size();
	Container &ret = *new Container();
	Iterator lIt = lA.begin();
	Iterator rIt = rA.begin();
	Iterator lEnd = lA.end();
	Iterator rEnd = rA.end();
	for (int i = 0; i < totalSize; i++)
	{
		if (rIt == rEnd)
			ret.push_back(*(lIt++));
		else if (lIt == lEnd)
			ret.push_back(*(rIt++));
		else if (*rIt > *lIt)
			ret.push_back(*(lIt++));
		else
			ret.push_back(*(rIt++));
	}
	return (ret);
}

template <class Iterator, class Container>
Container& PmergeMe::sort(Container& unsorted, unsigned int K)
{
	if (unsorted.size() > K)
	{
		int q = unsorted.size() / 2;
		Iterator middle = unsorted.begin();
		for (int i=0; i < q; i++)
			middle++;
		Container& lA = *new Container(unsorted.begin(), middle);
		Container& rA = *new Container(middle, unsorted.end());
		Container& sortedL = sort<Iterator>(lA, K);
		delete &lA;
		Container& sortedR = sort<Iterator>(rA, K);
		delete &rA;
		Container& ret = merge<Iterator>(sortedL, sortedR);
		delete &sortedL;
		delete &sortedR;
		return (ret);
	}
	else
	{
		Container& ret = insertionSort<Iterator>(unsorted);
		return (ret);
	}
}

