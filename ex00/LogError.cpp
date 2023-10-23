/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogError.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:51 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 10:41:47 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <LogError.hpp>
#include <Colors.hpp>
#include <CustomDefs.hpp>

LogError::LogError(){}
LogError::~LogError(){}
LogError::LogError(const LogError&){}
LogError& LogError::operator=(const LogError&){return (*this);}

int	LogError::print(const char *msg, const char *msg2)
{
	std::cerr << RED"Error: ";
	if (msg)
		std::cerr << msg;
	if (msg2)
		std::cerr << " " << msg2;
	std::cerr << RESET << std::endl;
	return (1);
}
