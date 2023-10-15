/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:51 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/15 17:25:59 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RPN_HPP_
# define  _RPN_HPP_
# define ERR_INVAL_ARG "invalid argument"
# define ERR_TOO_FEW_OP "too few operands in stack"
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
	void takeArgument(const char *arg);
	void unaryOperation(int aOp, char operation);
	void binaryOperation(int aOp, int bOp, char operation);
public:
	RPN(int argc, char const *argv[]);
	~RPN();
	RPN(const RPN& b);
	RPN& operator=(const RPN& b);
	std::ostream& print(std::ostream& os);
};

#endif
