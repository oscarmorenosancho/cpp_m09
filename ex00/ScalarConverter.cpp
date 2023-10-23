/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:13:45 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 12:27:33 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <ScalarConverter.hpp>
#include <stdlib.h>

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& b)
{
	(void)b;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& b)
{
	(void)b;
	return (*this);
}

std::string	ScalarConverter::trim(const std::string value)
{
	std::string res = "";
	size_t start = 0;
	size_t end = value.length();

	if (end == 0)
		return (res);
	else
		end--;
	while (value[start] && start < end && value[start] <= ' ')
		start++;
	while (end >= 0 && start < end && value[end] <= ' ')
		end--;
	for (size_t i = start; i <= end; i++)
		res += value[i];
	return (res);
}

ScalarConverter::t_counts	ScalarConverter::counts(std::string value)
{
	ScalarConverter::t_counts	counts;
	size_t						i;
	size_t						len = value.length();

	counts.alphas = 0;
	counts.digits = 0;
	counts.exps = 0;
	counts.floats = 0;
	counts.signs = 0;
	counts.spaces = 0;
	counts.dots = 0;
	for (i = 0; i < len; i++)
	{
		char c = value[i];
		if (c <= ' ')
		{
			counts.spaces++;
			continue;
		}
		if (c >= '0' && c <= '9')
		{
			counts.digits++;
			continue;
		}
		if (c == 'e' || c == 'E')
		{
			counts.exps++;
			continue;
		}
		if (c == 'f' || c == 'F')
		{
			counts.floats++;
			continue;
		}
		if (c == '+' || c == '-')
		{
			counts.signs++;
			continue;
		}
		if (c == '.')
		{
			counts.dots++;
			continue;
		}
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			counts.alphas++;
			continue;
		}
	}
	return (counts);
}

void ScalarConverter::split_exp(std::string value, std::string& man, std::string& exp)
{
	size_t	i = 0;
	bool	e_found = false;

	man = "";
	exp = "";
	while (value[i])
	{
		if (value[i] == 'e' || value[i] == 'E')
			e_found = true;
		else
		{
			if (!e_found)
				man += value[i];
			else
				exp += value[i];
		}
		i++;
	}	
}

ScalarConverter::t_type	ScalarConverter::identify_exp(std::string value)
{
	std::string	man;
	std::string	exp;

	split_exp(value, man, exp);
	t_counts man_counted = counts(man);
	t_counts exp_counted = counts(exp);
	if (man_counted.signs > 1 || (man_counted.signs == 1 && !(man[0] == '-' || man[0] == '+'))
		|| (exp_counted.signs > 1 || (exp_counted.signs == 1 && !(exp[0] == '-' || exp[0] == '+')))
		|| exp_counted.dots > 0 || man_counted.floats > 0)
		return (TYPE_INVALID);
	if (exp_counted.floats == 0)
		return (TYPE_DOUBLE);
	if (exp_counted.floats == 1 && (exp[exp.length()-1] == 'f' || (exp[exp.length()-1] == 'F')))
		return (TYPE_FLOAT);
	return (TYPE_INVALID);
}

ScalarConverter::t_type	ScalarConverter::identify(std::string value)
{
	if (value == "inf" || value == "-inf" || value == "+inf" ||
		value == "nan" || value == "-nan" || value == "+nan")
			return (TYPE_DOUBLE);
	if (value == "inff" || value == "-inff" || value == "+inff" ||
		value == "nanf" || value == "-nanf" || value == "+nanf")
			return (TYPE_FLOAT);
	t_counts counted = counts(value);
	if (counted.spaces > 0 || counted.alphas > 0 || counted.exps > 1
		|| counted.floats > 1 || counted.dots > 1 || counted.signs > 2)
		return (TYPE_INVALID);
	if (counted.exps == 0)
	{
		if (counted.floats == 0 && counted.digits > 0
			&& (counted.signs == 0 || (counted.signs == 1 && (value[0] == '-' || value[0] == '+')))
			&& counted.dots == 0)
			return (TYPE_LONG);
		if (counted.floats == 1
			&& (value[value.length()-1] == 'f' || (value[value.length()-1] == 'F'))
			&& (counted.signs == 0 || (counted.signs == 1 && (value[0] == '-' || value[0] == '+')))
			&& counted.dots < 2)
			return (TYPE_FLOAT);
		if (counted.floats == 0
			&& (counted.signs == 0 || (counted.signs == 1 && (value[0] == '-' || value[0] == '+')))
			&&	counted.dots < 2)
			return (TYPE_DOUBLE);
	}
	return (identify_exp(value));
}

long int	ScalarConverter::toLong(std::string trimmed)
{
	long	lV = std::atol(trimmed.c_str());
	return (lV);
}

float		ScalarConverter::toFloat(std::string trimmed)
{
	float	fV = std::atof(trimmed.c_str());
	return (fV);
}

double		ScalarConverter::toDouble(std::string trimmed)
{
	char* pEnd;
	double	dV = std::strtod(trimmed.c_str(), &pEnd);
	return (dV);
}

std::string ScalarConverter::toString(const int& value)
{
    std::ostringstream oss;
    oss << value;
	return (oss.str());
}

std::string ScalarConverter::toString(const float& value)
{
    std::ostringstream oss;
	oss << std::fixed << std::setprecision(2);
    oss << value;
	std::string s = oss.str();
	std::string::iterator it = s.begin();
	std::string::iterator ite = s.end();
	while (it != ite && *it!='.')
		it++;
	if (it == ite)
		return s;
	if (it[1]=='0' && it[2]=='0')
		return (std::string(s.begin(), it));
	if (it[1]!='0' && it[2]=='0')
		return (std::string(s.begin(), it + 2));
	return (std::string(s.begin(), it + 3));
}

std::string ScalarConverter::toString(const double& value)
{
    std::ostringstream oss;
	oss << std::fixed << std::setprecision(2);
    oss << value;
	std::string s = oss.str();
	std::string::iterator it = s.begin();
	std::string::iterator ite = s.end();
	while (it != ite && *it!='.')
		it++;
	if (it == ite)
		return s;
	if (it[1]=='0' && it[2]=='0')
		return (std::string(s.begin(), it));
	if (it[1]!='0' && it[2]=='0')
		return (std::string(s.begin(), it + 2));
	return (std::string(s.begin(), it + 3));
}
