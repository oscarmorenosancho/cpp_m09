/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:12:36 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:19:03 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Date.hpp>
#include <CustomDefs.hpp>

Date::Date() : badInputError()
{
}

Date::Date(std::string s) : badInputError()
{
	struct tm	tm;
	std::memset( &tm, 0, sizeof(tm));
    if(strptime(s.c_str(), "%Y-%m-%d", &tm) == NULL)
		throw badInputError;
	year = 1900 + tm.tm_year;
	month = 1 + tm.tm_mon;
	day = tm.tm_mday;
	joined = year * 10000 + month * 100 + day;
}

Date::~Date()
{

}

Date::Date(const Date& b)
{
	year = b.year;
	month = b.month;
	day = b.day;
	joined = b.joined;
}

Date& Date::operator=(const Date& b)
{
	year = b.year;
	month = b.month;
	day = b.day;
	joined = b.joined;
	return (*this);
}

std::ostream& Date::print(std::ostream& os) const
{
	os << std::fixed << std::setprecision(0) << std::setw(4) << std::setfill('0');
	os << year;
	os << "-";
	os << std::fixed << std::setprecision(0) << std::setw(2) << std::setfill('0');
	os << month;
	os << "-";
	os << std::fixed << std::setprecision(0) << std::setw(2) << std::setfill('0');
	os << day;
	return (os);
}

bool Date::operator==(const Date&b) const
{
	return (!this->operator!=(b));
}

bool Date::operator!=(const Date&b) const
{
	return (joined != b.joined);
}

bool Date::operator>(const Date&b) const
{
	return (joined > b.joined);
}

bool Date::operator<(const Date&b) const
{
	return (joined < b.joined);
}

bool Date::operator>=(const Date&b) const
{
	return (joined >= b.joined);
}

bool Date::operator<=(const Date&b) const
{
	return (joined <= b.joined);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return (d.print(os));
}

