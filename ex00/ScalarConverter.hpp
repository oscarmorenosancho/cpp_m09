/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:13:40 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 12:27:06 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCALARCONVERTER_HPP_
# define _SCALARCONVERTER_HPP_

#include <string>
#define NON_DISPLAY "Non displayable"
#define IMPOSSIBLE "impossible"

class ScalarConverter
{
private:
	typedef struct s_counts
	{
		size_t alphas;
		size_t digits;
		size_t signs;
		size_t exps;
		size_t floats;
		size_t dots;
		size_t spaces;
	}	t_counts;
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter& b);
	ScalarConverter& 	operator=(const ScalarConverter& b);
	static t_counts		counts(std::string value);
	static void			split_exp(std::string value,
									std::string& man, std::string& exp);
public:
	typedef enum e_type
	{
		TYPE_INVALID,
		TYPE_LONG,
		TYPE_FLOAT,
		TYPE_DOUBLE
	}	t_type;
	static std::string	trim(const std::string value);
	static t_type		identify_exp(std::string value);
	static t_type		identify(std::string value);
	static long int		toLong(std::string trimmed);
	static float		toFloat(std::string trimmed);
	static double		toDouble(std::string trimmed);
	std::string			toString(const int& value);
	std::string			toString(const float& value);
	std::string			toString(const double& value);
};

#endif
