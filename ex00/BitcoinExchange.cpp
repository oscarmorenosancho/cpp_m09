/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:22 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/12 13:24:18 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>
#include <iomanip>
#include <sstream>

BitcoinExchange::BitcoinExchange(const char *inputFile) : inputFile(inputFile)
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
	std::string line;
	std::ifstream dataFile;
	dataFile.open(DATA_CSV,std::ios::in);
	if (! dataFile.is_open())
		return (logError(ERR_OPEN_FAIL, DATA_CSV));
	while(std::getline(dataFile, line))
	{
		split_line_to_map(line, ',', dataMap);
	}
	dataFile.close();
	return (0);
}

int	BitcoinExchange::LoadInput()
{
	std::string line;
	std::ifstream dataFile;
	dataFile.open(inputFile,std::ios::in);
	if (! dataFile.is_open())
		return (logError(ERR_OPEN_FAIL, inputFile));
	while(std::getline(dataFile, line))
		split_line_to_map(line, '|', inputMap);
	dataFile.close();
	return (0);
}

void BitcoinExchange::split_line_to_map(const std::string& s, char c,
	std::map<std::tm, float>& dst)
{
	std::string::size_type pos = s.find(c);
	std::string::size_type len = s.length();
	if (pos != std::string::npos) {
		std::string head;
		std::string tail;
		head = s.substr(0, pos);
		tail = s.substr(pos, len - pos);
		const std::tm	date = cast_date(head);
		float	amount  = cast_amount(tail);
		dst.emplace(date);
		dst[date] = amount;
	}
}

std::tm	BitcoinExchange::cast_date(const std::string& s)
{
	std::string date_time_format = "%Y/%m/%d";
    std::stringstream ss;
	std::tm dateValue;

	ss << s;
	ss >> std::get_time(&dateValue, date_time_format.c_str());
	return (dateValue);
}

float	BitcoinExchange::cast_amount(const std::string& s)
{
	int   amountIntValue;
	float amountFloatValue;

	amountIntValue = stoi(s);
	try
	{
		amountFloatValue = stof(s);
	}
	catch(const std::exception& e)
	{
		amountFloatValue = static_cast<float>(amountIntValue);
	}
	return (amountFloatValue);
}
