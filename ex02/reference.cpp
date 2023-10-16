/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reference.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:55:01 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/16 23:21:34 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int K = 2;

void print_vector(std::vector<int>::iterator begin, std::vector<int>::iterator end)
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

std::vector<int>& copyOfRange(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	return *new std::vector<int>(begin,end);
}

void insertionSort(std::vector<int>& A, int p, int q) {
    for (int i = p; i < q; i++) {
        int tempVal = A[i + 1];
        int j = i + 1;
        while (j > p && A[j - 1] > tempVal) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tempVal;
    }
    std::vector<int>& temp = copyOfRange(A.begin() + p, A.begin() + q +1);
	print_vector(temp.begin(), temp.end());
	delete &temp;
}

void merge(std::vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int>& LA = copyOfRange(A.begin() + p, A.begin() + q +1);
    std::vector<int>& RA = copyOfRange(A.begin() + q+1, A.begin() + r +1);
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

void sort(std::vector<int>& A, int p, int r) {
    if (r - p > K) {
        int q = (p + r) / 2;
        sort(A, p, q);
        sort(A, q + 1, r);
        merge(A, p, q, r);
    } else {
        insertionSort(A, p, r);
    }
}

int main(int argc, char **argv)
{
	std::vector<int> A = { 2, 5, 1, 6, 7, 3, 8, 4, 9 };
	std::cout << "at the begining: ";
	print_vector(A.begin(), A.end());
	sort(A, 0, A.size() - 1);
	std::cout << "at the end: ";
	print_vector(A.begin(), A.end());
	return (0);
}
