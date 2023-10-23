/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:22 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:45:57 by omoreno-         ###   ########.fr       */
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
#include <CustomDefs.hpp>
#include <LogError.hpp>
#include <ScalarConverter.hpp>

BitcoinExchange::BitcoinExchange(const char *inputFile) :
	badCastError(),
	inputFile(inputFile)
{
	if (!inputFile)
		LogError::print(ERR_OPEN_FAIL, NULL);
	if (LoadData())
		return ;
	if (LoadInputAndConvert())
		return ;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& b) :
	badCastError(b.badCastError)
{
	this->dataMap = b.dataMap;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& b)
{
	this->dataMap = b.dataMap;
	return (*this);
}

int	BitcoinExchange::LoadData()
{
	int cnt = 0;
	std::string line;
	std::ifstream dataFile;
	dataFile.open(DATA_CSV,std::ios::in);
	if (! dataFile.is_open())
		return (LogError::print(ERR_OPEN_FAIL, DATA_CSV));
	while(std::getline(dataFile, line))
	{
		try
		{
			if (cnt > 0)
				splitLineToMap(line, ',', dataMap, false);
		}
		catch(const std::exception& e)
		{
			return (LogError::print(e.what(), DATA_CSV));
		}
		cnt++;
	}
	dataFile.close();
	if (dataMap.size() < 1)
		return (LogError::print(ERR_EMPTY_DATA, NULL));
	return (0);
}

int	BitcoinExchange::LoadInputAndConvert()
{
	int cnt = 0;
	std::string line;
	std::ifstream dataFile;
	dataFile.open(inputFile,std::ios::in);
	if (! dataFile.is_open())
		return (LogError::print(ERR_OPEN_FAIL, inputFile));
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
		head = ScalarConverter::trim(s.substr(0, pos));
		tail = ScalarConverter::trim(s.substr(pos + 1, len - pos));
		Date date;
		if (tail.length() < 1)
			throw invalidValueError;
		try
		{
			date = castDate(head);
		}
		catch(const InvalidValueError& e)
		{
			LogError::print(e.what(), head.c_str());
			throw alreadyCatchedError;
		}
		float amount;
		try
		{
			amount  = castAmount(tail, restrictive);
		}
		catch(const std::bad_cast& e)
		{
			LogError::print(e.what(), tail.c_str());
			throw alreadyCatchedError;
		}
		catch(const InvalidValueError& e)
		{
			LogError::print(e.what(), tail.c_str());
			throw alreadyCatchedError;
		}
		return (*new std::pair<Date, float>(date, amount));
	}
	throw invalidValueError;
}


void BitcoinExchange::splitLineToMap(const std::string& s, char c,
	std::map<Date, float>& dst, bool restrictive)
{
	try
	{
		std::pair<Date, float>&p = splitLineToPair(s, c, restrictive);
		dst.insert(p);
		delete &p;
	}
	catch(const AlreadyCatchedError& e)
	{
		throw csvLoadError;
	}
	catch(const std::bad_cast& e)
	{
		LogError::print(ERR_BAD_INPUT, s.c_str());
		throw csvLoadError;
	}
	catch(const InvalidValueError& e)
	{
		LogError::print(ERR_BAD_INPUT, s.c_str());
		throw csvLoadError;
	}
	catch(const std::exception& e)
	{
		LogError::print(e.what(), NULL);
		throw csvLoadError;
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
			std::cout << ERR_BEFORE_1ST;
			std::cout << std::endl;
			return ;
		}
		found--;
		std::cout << toString(f * found->second);
		std::cout << std::endl;
		return ;
	}
	catch(const AlreadyCatchedError& e)
	{
		;
	}
	catch(const std::bad_cast& e)
	{
		LogError::print(ERR_BAD_INPUT, s.c_str());
	}
	catch(const std::exception& e)
	{
		LogError::print(e.what(), NULL);
	}
}

Date	BitcoinExchange::castDate(const std::string& s)
{
	Date dateValue(s);
	return (dateValue);
}

float	BitcoinExchange::castAmount(const std::string& s, bool restrictive)
{
	float	ret = 0.0;
	switch (ScalarConverter::identify(s))
	{
	case ScalarConverter::TYPE_LONG:
		{
			if (s.length()>10)
				throw invalidValueError;
			int amountIntValue;
			long int amountLongValue = ScalarConverter::toLong(s);
			amountIntValue = static_cast<int>(amountLongValue);
			if (amountIntValue != amountLongValue)
				throw invalidValueError;
			ret = static_cast<float>(amountIntValue);
		}
		break;
	case ScalarConverter::TYPE_FLOAT:
		ret = ScalarConverter::toFloat(s);
		break;
	case ScalarConverter::TYPE_DOUBLE:
		ret = static_cast<float>(ScalarConverter::toDouble(s));
		break;
	default:
		throw invalidValueError;
	}
	if (ret == INFINITY || ret == -INFINITY || ret == NAN || ret == -NAN)
		throw invalidValueError;
	if (restrictive && ret < 0.0)
		throw notPositiveError;
	if (restrictive && ret > 1000.0)
		throw tooLargeError;
	return (ret);
}

std::ostream& BitcoinExchange::print(std::ostream& os) const
{
	os << "Date | Value" << std::endl;
	os << dataMap;
	return (os);
}

int BitcoinExchange::stol(const std::string& s)
{
	std::string ts = ScalarConverter::trim(s);
	if (ts.length() < 1)
		throw invalidValueError;
	std::ostringstream oss;
	long l;
	std::istringstream(ts) >> l;
	std::string rev;
	oss << l;
	if (oss.str() != ts)
		throw invalidValueError;
	int i = static_cast<int>(l);
	return i;
}

float BitcoinExchange::stof(const std::string& s)
{
	std::string ts = ScalarConverter::trim(s);
	if (ts.length() < 1)
		throw invalidValueError;
	float	i;
	std::istringstream(ts) >> i;
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
