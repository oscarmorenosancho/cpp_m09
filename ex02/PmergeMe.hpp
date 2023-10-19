/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:37:16 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/19 18:01:39 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PMERGE_ME_HPP_
# define _PMERGE_ME_HPP_
# include <merge_insert.hpp>

class MyList : public std::list<int>
{
private:
	static unsigned int K;
public:
	MyList();
	~MyList();
	MyList& sort();
	void print();
};

class MyVector : public std::vector<int>
{
private:
	static unsigned int K;
public:
	MyVector();
	~MyVector();
	MyVector& sort();
	void print();
};


#endif
