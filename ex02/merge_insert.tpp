/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_insert.tpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:45:02 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:07:14 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <merge_insert.hpp>

template <class Iterator>
void print_range(Iterator begin, Iterator end)
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
Container& insertionSort(const Container& unsorted)
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
Container& merge(Container& lA, Container& rA)
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
Container& sort(Container& unsorted, unsigned int K)
{
	if (unsorted.size() > K)
	{
		int q = unsorted.size() / 2;
		Iterator middle = unsorted.begin();
		for (int i=0; i < q; i++)
			middle++;
		Container& lA = *new Container(unsorted.begin(), middle);
		Container& rA = *new Container(middle, unsorted.end());
		Container& sortedL = sort<Iterator>(lA);
		delete &lA;
		Container& sortedR = sort<Iterator>(rA);
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
