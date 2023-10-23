/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:12:32 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 10:39:09 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DATE_HPP_
# define _DATE_HPP_
# include <iostream>
# include <fstream>
# include <string>
# include <ctime>
# include <map>
# include <exception>
# include <LogError.hpp>

class Date
{
private:
	int year;
	int month;
	int day;
	long int joined;
	std::bad_cast badInputError;
public:
	Date(std::string s);
	~Date();
	Date(const Date& b);
	std::ostream& print(std::ostream& os) const;
	Date& operator=(const Date& b);
	bool operator==(const Date&b) const;
	bool operator!=(const Date&b) const;
	bool operator>(const Date&b) const;
	bool operator<(const Date&b) const;
	bool operator>=(const Date&b) const;
	bool operator<=(const Date&b) const;
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
