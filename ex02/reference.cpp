/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:55:01 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/17 00:51:15 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
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
void insertionSort(Container& A, int p, int q)
{
	for (int i = p; i < q; i++)
	{
		int tempVal = A[i + 1];
		int j = i + 1;
		while (j > p && A[j - 1] > tempVal) {
			A[j] = A[j - 1];
			j--;
		}
		A[j] = tempVal;
	}
	Container& temp = copyOfRange<Iterator, Container>
						((A.begin() + p), (A.begin() + q + 1));
	print_vector(temp.begin(), temp.end());
	delete &temp;
}

template <class Iterator, class Container>
void merge(Container& A, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	Container& LA = copyOfRange<Iterator, Container>
								((A.begin() + p), (A.begin() + q + 1));
	Container& RA = copyOfRange<Iterator, Container>
								((A.begin() + q + 1), (A.begin() + r + 1));
	int RIDX = 0;
	int LIDX = 0;
	for (int i = p; i < r - p + 1; i++) {
		if (RIDX == n2) {
			A[i] = LA[LIDX];
			LIDX++;
		} else if (LIDX == n1) {
			A[i] = RA[RIDX];
			RIDX++;
		} else if (RA[RIDX] > LA[LIDX]) {
			A[i] = LA[LIDX];
			LIDX++;
		} else {
			A[i] = RA[RIDX];
			RIDX++;
		}
	}
	delete &LA;
	delete &RA;
}

template <class Iterator, class Container>
void sort(Container& A, int p, int r) {
	if (r - p > K) {
		int q = (p + r) / 2;
		sort<Iterator>(A, p, q);
		sort<Iterator>(A, q + 1, r);
		merge<Iterator>(A, p, q, r);
	} else {
		insertionSort<Iterator>(A, p, r);
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int arrInt[] = { 2, 5, 1, 6, 7, 3, 8, 4, 9 };
	std::vector<int> A;
	unsigned int len = sizeof(arrInt)/sizeof(int);
	for (unsigned int i = 0; i < len; i++)
	 	A.push_back(arrInt[i]);
	std::cout << "at the begining: ";
	print_vector(A.begin(), A.end());
	sort<std::vector<int>::iterator>(A, 0, A.size() - 1);
	std::cout << "at the end: ";
	print_vector(A.begin(), A.end());
	return (0);
}
