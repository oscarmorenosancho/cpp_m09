/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:51 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/16 20:44:56 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RPN_HPP_
# define  _RPN_HPP_
# define ERR_INVAL_ARG "invalid argument"
# define ERR_TOO_FEW_OP "too few operands in stack"
# define ERR_DIV_BY_0 "division by zero"
# include <string>
# include <stack>
# include <algorithm>
# include <exception>
# include <iostream>

class RPN : public std::stack<std::string>
{
private:
	std::runtime_error invalidArgument;
	std::runtime_error tooFewOperands;
	std::runtime_error divisionByZero;
	void	iterSplit(const std::string & s);
	void	takeToken(const std::string& token);
	int		topToOp();
	void	unaryOperation(int aOp, char operation);
	void	binaryOperation(int aOp, int bOp, char operation);
	static int stoi(const std::string & s);
	template<typename T>
	static std::string to_string(const T & value);
public:
	RPN(const char *arg);
	~RPN();
	RPN(const RPN& b);
	RPN& operator=(const RPN& b);
	std::ostream& print(std::ostream& os);
};

#endif
