/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:22 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/11 13:32:09 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>

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
	while(std::getline(dataFile, line)){ //read data from file object and put it into string.
		std::cout << line << "\n"; //print the data of the string
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
	while(std::getline(dataFile, line)){ //read data from file object and put it into string.
		std::cout << line << "\n"; //print the data of the string
	}
	dataFile.close();
	return (0);
}
