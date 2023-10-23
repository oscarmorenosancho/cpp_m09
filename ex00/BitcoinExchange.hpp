/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:34:09 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_

# include <Colors.hpp>
# include <iostream>
# include <fstream>
# include <string>
# include <ctime>
# include <map>
# include <typeinfo> //for linux
# include <Date.hpp>
# include <CustomExcepts.hpp>

class BitcoinExchange
{
private:
	std::map<Date, float> dataMap;
	std::bad_cast		badCastError;
	InvalidValueError	invalidValueError;
	NotPositiveError	notPositiveError;
	TooLargeError		tooLargeError;
	CsvLoadError		csvLoadError;
	AlreadyCatchedError	alreadyCatchedError;
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
	std::ostream& print(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const std::pair<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const std::map<Date, float>& d);
std::ostream& operator<<(std::ostream& os, const BitcoinExchange& d);

#endif
