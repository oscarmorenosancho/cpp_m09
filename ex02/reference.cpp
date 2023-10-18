/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:55:01 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/18 20:51:33 by omoreno-         ###   ########.fr       */
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
void insertionSort(Container& A, int p, int q)
{
	// std::cout << "\t\tA before insertion sort: ";
	// print_vector(A.begin(), A.end());
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
	// std::cout << "\t\tA after insertion sort: ";
	// print_vector(A.begin(), A.end());
	// Container& temp = copyOfRange<Iterator, Container>
	// 					((A.begin() + p), (A.begin() + q + 1));
	// std::cout << "\t\ttemp after insertion sort: ";
	// print_vector(temp.begin(), temp.end());
	// delete &temp;
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
	// std::cout << "\tmerging\n";
	// std::cout << "\tLA: ";
	// print_vector(LA.begin(), LA.end());
	// std::cout << "\tRA: ";
	// print_vector(RA.begin(), RA.end());
	int RIDX = 0;
	int LIDX = 0;
	// std::cout << "\tfrom p: " << p << " to r: " << r << "\n";
	for (int i = p; i < r + 1; i++) {
		if (RIDX == n2)
		{
			// std::cout << "i: " << i << "/ R reach end: " << n2 << ", copy LA["<< LIDX << "] with " << LA[LIDX] << " to A[" << i << "]\n";
			A[i] = LA[LIDX];
			LIDX++;
		}
		else if (LIDX == n1)
		{
			// std::cout << "i: " << i << "/ L reach end: " << n1 << ", copy RA["<< RIDX << "] with " << RA[RIDX] << " to A[" << i << "]\n";
			A[i] = RA[RIDX];
			RIDX++;
		}
		else if (RA[RIDX] > LA[LIDX])
		{
			// std::cout << "i: " << i << "/ RA["<< RIDX << "] with " << RA[RIDX] << " > LA[" << LIDX << "] with " << LA[LIDX] << " copy LA[inx] to A[" << i << "] \n";
			A[i] = LA[LIDX];
			LIDX++;
		}
		else
		{
			// std::cout << "i: " << i << "/ RA["<< RIDX << "] with " << RA[RIDX] << " < LA[" << LIDX << "] with " << LA[LIDX] << " copy RA[inx] to A[" << i << "] \n";
			A[i] = RA[RIDX];
			RIDX++;
		}
	}
	delete &LA;
	delete &RA;
	// std::cout << "\tA after merge : ";
	// print_vector(A.begin() + p, A.begin() + r + 1);
}

template <class Iterator, class Container>
void sort(Container& A, int p, int r) {
	if (r - p > K) {
		// std::cout << "A before sort-merge: ";
		// print_vector(A.begin() + p, A.begin() + r + 1);
		int q = (p + r) / 2;
		sort<Iterator>(A, p, q);
		sort<Iterator>(A, q + 1, r);
		merge<Iterator>(A, p, q, r);
		// std::cout << "A after: sort-merge ";
		// print_vector(A.begin() + p, A.begin() + r + 1);
	} else {
		// std::cout << "A before insert sort: ";
		// print_vector(A.begin() + p, A.begin() + r + 1);
		insertionSort<Iterator>(A, p, r);
		// std::cout << "A after insert sort: ";
		// print_vector(A.begin() + p, A.begin() + r + 1);
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// int arrInt[] = { 10, 2, 5, 1, 6, 7, 3, 8, 4, 9, 12, 15, 11, 16, 17, 13, 18, 14, 19};
	// std::vector<int> A;
	// unsigned int len = sizeof(arrInt)/sizeof(int);
	// for (unsigned int i = 0; i < len; i++)
	//  	A.push_back(arrInt[i]);
	std::vector<int> A;
	for (int i = 1; i < argc; i++)
	{
		int temp = std::atoi(argv[i]);
		A.push_back(temp);
	}
	std::cout << "at the begining: ";
	print_vector(A.begin(), A.end());
	sort<std::vector<int>::iterator>(A, 0, A.size() - 1);
	std::cout << "at the end: ";
	print_vector(A.begin(), A.end());
	return (0);
}
