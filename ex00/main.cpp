/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:24:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 10:40:17 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <BitcoinExchange.hpp>
#include <CustomDefs.hpp>

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return (LogError::print(ERR_WRONG_ARG, NULL));
	BitcoinExchange bEx(argv[1]);
	return 0;
	
}
