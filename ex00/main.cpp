/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:24:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/15 16:17:05 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <BitcoinExchange.hpp>

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return (BitcoinExchange::logError(ERR_WRONG_ARG, NULL));
	BitcoinExchange bEx(argv[1]);
	return 0;
	
}
