/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:22 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/13 18:14:40 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>
#include <iomanip>
#include <sstream>
#include <algorithm>

Date::Date(std::string s) : badInputError()
{
	struct tm	tm;
	memset( &tm, 0, sizeof(tm));
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
	badCastError(), inputFile(inputFile)
{
	if (!inputFile)
		logError(ERR_OPEN_FAIL, NULL);
	if (LoadInput())
		return ;
	if (LoadData())
		return ;
}

BitcoinExchange::~BitcoinExchange()
{
}

int BitcoinExchange::logError(const char *msg, const char *msg2)
{
	std::cerr << "Error: ";
	if (msg)
		std::cerr << msg;
	if (msg2)
		std::cerr << " " << msg2;
	std::cerr << std::endl;
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
			splitLineToMap(line, ',', dataMap);
		cnt++;
	}
	dataFile.close();
	return (0);
}

int	BitcoinExchange::LoadInput()
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
			splitLineToMap(line, '|', inputMap);
		cnt++;
	}
	dataFile.close();
	return (0);
}

void BitcoinExchange::splitLineToMap(const std::string& s, char c,
	std::map<Date, float>& dst)
{
	std::string::size_type pos = s.find(c);
	std::string::size_type len = s.length();
	if (pos != std::string::npos) {
		std::string head;
		std::string tail;
		head = s.substr(0, pos);
		tail = s.substr(pos + 1, len - pos);
		try
		{
			Date date = castDate(head);
			float amount  = castAmount(tail);
			std::pair<Date, float> p(date, amount);
			dst.insert(p);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return ;
		}
	}
}

Date	BitcoinExchange::castDate(const std::string& s)
{
	Date dateValue(s);
	return (dateValue);
}

float	BitcoinExchange::castAmount(const std::string& s)
{
	int   amountIntValue;
	float amountFloatValue;
	bool	intCastFail = false;
	bool	floatCastFail =false;

	try
	{
		amountIntValue = stoi(s);
	}
	catch(const std::exception& e)
	{
		intCastFail = true;
	}
	try
	{
		amountFloatValue = stof(s);
	}
	catch(const std::exception& e)
	{
		floatCastFail = true;
		if (!intCastFail)
			amountFloatValue = static_cast<float>(amountIntValue);
	}
	if (intCastFail && floatCastFail)
	{
		logError(ERR_BAD_INPUT, s.c_str());
		throw badCastError;
	}
	return (amountFloatValue);
}

std::ostream& BitcoinExchange::print(std::ostream& os) const
{
	// os << "Date | Value" << std::endl;
	// os << inputMap;
	os << "Date | Value" << std::endl;
	os << dataMap;
	return (os);
}

std::ostream& operator<<(std::ostream& os, const std::pair<Date, float>& d)
{
	os << d.first << " | ";
	os << std::fixed << std::setprecision(2);
	os << d.second << std::endl;
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
