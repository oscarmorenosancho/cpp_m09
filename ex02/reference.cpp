/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:55:01 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 11:30:28 by omoreno-         ###   ########.fr       */
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
Container& copyOfRange(Iterator begin, Iterator end)
{
	return *new Container(begin,end);
}

template <class Iterator, class Container>
void insertionSort(Container& col, int p, int q)
{
	for (int i = p; i < q; i++)
	{
		int tempVal = col[i + 1];
		int j = i + 1;
		while (j > p && col[j - 1] > tempVal) {
			col[j] = col[j - 1];
			j--;
		}
		col[j] = tempVal;
	}
}

template <class Iterator, class Container>
void merge(Container& col, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	Container& LA = *new Container((col.begin() + p), (col.begin() + q + 1));
	Container& RA = *new Container((col.begin() + q + 1), (col.begin() + r + 1));
	int lI = 0;
	int rI = 0;
	for (int i = p; i < r + 1; i++)
	{
		if (rI == n2)
			col[i] = LA[lI++];
		else if (lI == n1)
			col[i] = RA[rI++];
		else if (RA[rI] > LA[lI])
			col[i] = LA[lI++];
		else
			col[i] = RA[rI++];
	}
	delete &LA;
	delete &RA;
}

template <class Iterator, class Container>
void sort(Container& col, int p, int r) {
	if (r - p > K) {
		int q = (p + r) / 2;
		sort<Iterator>(col, p, q);
		sort<Iterator>(col, q + 1, r);
		merge<Iterator>(col, p, q, r);
	} else
		insertionSort<Iterator>(col, p, r);
}

int main(int argc, char **argv)
{
	std::vector<int> col;
	for (int i = 1; i < argc; i++)
	{
		int temp = std::atoi(argv[i]);
		col.push_back(temp);
	}
	std::cout << "at the begining: ";
	print_vector(col.begin(), col.end());
	sort<std::vector<int>::iterator>(col, 0, col.size() - 1);
	std::cout << "at the end: ";
	print_vector(col.begin(), col.end());
	return (0);
}
