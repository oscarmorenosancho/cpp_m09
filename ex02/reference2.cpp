/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference2.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:55:01 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 13:24:08 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

int K = 2;

template <class Iterator>
void print_vector(Iterator begin, Iterator end)
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
	int p = 0;
	int q = unsorted.size();
	Container& ret = *new Container(unsorted.begin(), unsorted.end());
	for (int i = p; i < q - 1; i++)
	{
		int tempVal;
		{
			std::vector<int>::iterator it = ret.begin() + i + 1;
			tempVal = *it;
		}
		int j = i + 1;
		Iterator itJ = ret.begin() + j;
		Iterator itJdec = itJ - 1;
		while (j > p && *itJdec > tempVal)
		{
			*itJ = *itJdec;
			j--;
			itJ = ret.begin() + j;
			itJdec = itJ - 1;
		}
		*itJ = tempVal;
	}
	return (ret);
}

template <class Iterator, class Container>
Container& merge(const Container& lA, const Container& rA)
{
	int lN = lA.size();
	int rN = rA.size();
	int total = lN + rN;
	Container &ret = *new Container();
	int rI = 0;
	int lI = 0;
	for (int i = 0; i < total; i++)
	{
		if (rI == rN)
			ret.push_back(lA[lI++]);
		else if (lI == lN)
			ret.push_back(rA[rI++]);
		else if (rA[rI] > lA[lI])
			ret.push_back(lA[lI++]);
		else
			ret.push_back(rA[rI++]);
	}
	return (ret);
}

template <class Iterator, class Container>
Container& sort(Container& unsorted)
{
	if (unsorted.size() > (unsigned int)K)
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

int main(int argc, char **argv)
{
	std::vector<int>& col = *new std::vector<int>();
	for (int i = 1; i < argc; i++)
	{
		int temp = std::atoi(argv[i]);
		col.push_back(temp);
	}
	std::cout << "at the begining: ";
	print_vector(col.begin(), col.end());
	std::vector<int>& res = sort<std::vector<int>::iterator>(col);
	delete &col;
	std::cout << "at the end: ";
	print_vector(res.begin(), res.end());
	delete &res;
	return (0);
}
