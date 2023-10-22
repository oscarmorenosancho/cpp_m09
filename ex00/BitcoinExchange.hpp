/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/22 20:28:28 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_
# define DATA_CSV "data.csv"
# define ERR_WRONG_ARG "needed an argument with a filename to input data."
# define ERR_OPEN_FAIL "could not open file."
# define ERR_BAD_INPUT "bad input =>"
# define ERR_NOT_POSITIVE "not a positive number."
# define ERR_TOO_LARGE "too large a number."
# define ERR_INV_VALUE "invalid value."
# define ERR_EMPTY_DATA "empty conversion database."
# define RESET   "\033[0m"
# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */
# define YELLOW  "\033[33m"      /* Yellow */
# define BLUE    "\033[34m"      /* Blue */
# define MAGENTA "\033[35m"      /* Magenta */
# define CYAN    "\033[36m"      /* Cyan */
# define WHITE   "\033[37m"      /* White */
# include <iostream>
# include <fstream>
# include <string>
# include <ctime>
# include <map>
# include <exception>
# include <typeinfo> //for linux

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

class BitcoinExchange
{
private:
	std::map<Date, float> dataMap;
	std::bad_cast badCastError;
	std::runtime_error invalidValueError;
	std::runtime_error notPositiveError;
	std::runtime_error tooLargeError;
	const char		*inputFile;
	int				LoadData();
	int				LoadInputAndConvert();
	std::pair<Date, float>& splitLineToPair(const std::string& s,
		char c, bool restrictive);
	void splitLineToMap(const std::string& s, char c,
		std::map<Date, float>& dst, bool restrictive);
	void splitLineAndConvert(const std::string& s);
	Date	castDate(const std::string& s);
	float	castAmount(const std::string& s, bool restrictive);
public:
	int stol(const std::string& s);
	float stof(const std::string& s);
	static std::string toString(const float& value);
	BitcoinExchange(const char *inputFile);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& b);
	BitcoinExchange& operator=(const BitcoinExchange& b);
	static int logError(const char *msg, const char *msg2);
	std::ostream& print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const std::map<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const BitcoinExchange& d);

#endif
