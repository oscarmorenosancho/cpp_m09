/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/13 18:07:36 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_
# define DATA_CSV "data.csv"
# define ERR_OPEN_FAIL "could not open file."
# define ERR_BAD_INPUT "Error: bad input => "
# define ERR_NOT_POSITIVE "Error: not a positive number."
# define ERR_TOO_LARGE "Error: too large a number."
# include <iostream>
# include <fstream>
# include <string>
# include <ctime>
# include <map>
# include <exception>

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
	std::bad_cast badCastError;
	const char		*inputFile;
	int				LoadData();
	int				LoadInput();
	std::map<Date, float> dataMap;
	std::map<Date, float> inputMap;
	void splitLineToMap(const std::string& s, char c,
		std::map<Date, float>& dst);
	Date	castDate(const std::string& s);
	float	castAmount(const std::string& s);
public:
	BitcoinExchange(const char *inputFile);
	~BitcoinExchange();
	static int logError(const char *msg, const char *msg2);
	std::ostream& print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const std::map<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const BitcoinExchange& d);

#endif
