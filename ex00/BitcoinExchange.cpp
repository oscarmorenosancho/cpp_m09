/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:22 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/22 16:39:16 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <sstream>

Date::Date(std::string s) : badInputError()
{
	struct tm	tm;
	std::memset( &tm, 0, sizeof(tm));
    if(strptime(s.c_str(), "%Y-%m-%d", &tm) == NULL)
	{
		BitcoinExchange::logError(ERR_BAD_INPUT, s.c_str());
		throw badInputError;
	}
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

BitcoinExchange::BitcoinExchange(const char *inputFile) :
	badCastError(),
	notPositiveError(ERR_NOT_POSITIVE),
	tooLargeError(ERR_TOO_LARGE),
	inputFile(inputFile)
{
	if (!inputFile)
		logError(ERR_OPEN_FAIL, NULL);
	if (LoadData())
		return ;
	if (LoadInputAndConvert())
		return ;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& b) :
	badCastError(b.badCastError),
	notPositiveError(b.notPositiveError),
	tooLargeError(b.tooLargeError)
{
	this->dataMap = b.dataMap;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& b)
{
	this->dataMap = b.dataMap;
	return (*this);
}

int BitcoinExchange::logError(const char *msg, const char *msg2)
{
	std::cerr << RED"Error: ";
	if (msg)
		std::cerr << msg;
	if (msg2)
		std::cerr << " " << msg2;
	std::cerr << RESET << std::endl;
	return (1);
}

int	BitcoinExchange::LoadData()
{
	int cnt = 0;
	std::string line;
	std::ifstream dataFile;
	dataFile.open(DATA_CSV,std::ios::in);
	if (! dataFile.is_open())
		return (logError(ERR_OPEN_FAIL, DATA_CSV));
	while(std::getline(dataFile, line))
	{
		if (cnt > 0)
			splitLineToMap(line, ',', dataMap, false);
		cnt++;
	}
	dataFile.close();
	if (dataMap.size() < 1)
		return (logError(ERR_EMPTY_DATA, NULL));
	return (0);
}

int	BitcoinExchange::LoadInputAndConvert()
{
	int cnt = 0;
	std::string line;
	std::ifstream dataFile;
	dataFile.open(inputFile,std::ios::in);
	if (! dataFile.is_open())
		return (logError(ERR_OPEN_FAIL, inputFile));
	while(std::getline(dataFile, line))
	{
		if (cnt > 0)
			splitLineAndConvert(line);
		cnt++;
	}
	dataFile.close();
	return (0);
}

std::pair<Date, float>& BitcoinExchange::splitLineToPair(const std::string& s,
	char c, bool restrictive)
{
	std::string::size_type pos = s.find(c);
	std::string::size_type len = s.length();
	if (pos != std::string::npos) {
		std::string head;
		std::string tail;
		head = s.substr(0, pos);
		tail = s.substr(pos + 1, len - pos);
		Date date = castDate(head);
		float amount  = castAmount(tail, restrictive);
		return (*new std::pair<Date, float>(date, amount));
	}
	throw badCastError;
}


void BitcoinExchange::splitLineToMap(const std::string& s, char c,
	std::map<Date, float>& dst, bool restrictive)
{
	try
	{
		std::pair<Date, float>&p  = splitLineToPair(s, c, restrictive);
		dst.insert(p);
		delete &p;
	}
	catch(const std::bad_cast& e)
	{
		logError(ERR_BAD_INPUT, s.c_str());
	}
	catch(const std::exception& e)
	{
		logError(e.what(), NULL);
	}
}

void BitcoinExchange::splitLineAndConvert(const std::string& s)
{
	try
	{
		std::pair<Date, float>&p  = splitLineToPair(s, '|', true);
		std::map<Date, float>::iterator found = dataMap.upper_bound(p.first);
		const Date d = p.first;
		float f = p.second;
		delete &p;
		std::cout << d << " => ";
		std::cout << toString(f) << " = ";
		if (found == dataMap.begin())
		{
			std::cout << "0, before the first data registerd.";
			std::cout << std::endl;
			return ;
		}
		found--;
		std::cout << toString(f * found->second);
		std::cout << std::endl;
		return ;
	}
	catch(const std::bad_cast& e)
	{
		logError(ERR_BAD_INPUT, s.c_str());
	}
	catch(const std::exception& e)
	{
		logError(e.what(), NULL);
	}
}

Date	BitcoinExchange::castDate(const std::string& s)
{
	Date dateValue(s);
	return (dateValue);
}

float	BitcoinExchange::castAmount(const std::string& s, bool restrictive)
{
	if (s.find_first_of(".eEfF")==std::string::npos)
	{
		int amountIntValue;
		long int amountLongValue = stol(s);
		if (restrictive && amountLongValue < 0)
			throw notPositiveError;
		amountIntValue = static_cast<int>(amountLongValue);
		if (amountIntValue != amountLongValue)
			throw tooLargeError;
		if (restrictive && amountIntValue > 1000)
			throw tooLargeError;
		return (static_cast<float>(amountIntValue));
	}
	else
		return (stof(s));
}

std::ostream& BitcoinExchange::print(std::ostream& os) const
{
	os << "Date | Value" << std::endl;
	os << dataMap;
	return (os);
}

int BitcoinExchange::stol(const std::string & s )
{
    int i;
    std::istringstream(s) >> i;
    return i;
}

float BitcoinExchange::stof(const std::string & s)
{
    float	i;
    std::istringstream(s) >> i;
    return i;
}

std::string BitcoinExchange::toString(const float& value)
{
    std::ostringstream oss;
	oss << std::fixed << std::setprecision(2);
    oss << value;
	std::string s = oss.str();
	std::string::iterator it = s.begin();
	std::string::iterator ite = s.end();
	while (it != ite && *it!='.')
		it++;
	if (it == ite)
		return s;
	if (it[1]=='0' && it[2]=='0')
		return (std::string(s.begin(), it));
	if (it[1]!='0' && it[2]=='0')
		return (std::string(s.begin(), it + 2));
	return (std::string(s.begin(), it + 3));
}

std::ostream& operator<<(std::ostream& os, const std::pair<Date, float>& d)
{
	os << d.first << " | ";
	os << BitcoinExchange::toString(d.second) << std::endl;
	return (os);
}

std::ostream& operator<<(std::ostream& os, const std::map<Date, float>& d) 
{
	std::map<Date, float>::const_iterator it = d.begin();
	std::map<Date, float>::const_iterator ite = d.end();
	while (it != ite)
	{
		os << *it;
		it++;
	}
	return (os);
}


std::ostream& operator<<(std::ostream& os, const BitcoinExchange& d)
{
	return (d.print(os));
}
