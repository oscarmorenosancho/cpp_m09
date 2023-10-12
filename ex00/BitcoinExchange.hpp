/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:59 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/12 12:38:30 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_
#define DATA_CSV "data.csv"
#define ERR_OPEN_FAIL "could not open file."
# include <iostream>
# include <fstream>
#include <string>
#include <ctime>
# include <map>

class BitcoinExchange
{
private:
	const char		*inputFile;
	int				LoadData();
	int				LoadInput();
	std::map<std::tm, float> dataMap;
	std::map<std::tm, float> inputMap;
	void split_line_to_map(const std::string& s, char c,
		std::map<std::tm, float>& dst);
	std::tm	cast_date(const std::string& s);
	float	cast_amount(const std::string& s);
	
public:
	BitcoinExchange(const char *inputFile);
	~BitcoinExchange();
	static int logError(const char *msg, const char *msg2);
};

#endif
