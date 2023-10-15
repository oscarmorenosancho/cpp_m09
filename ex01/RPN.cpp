/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:47 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/15 17:37:35 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>

RPN::RPN(int argc, char const *argv[]):
	invalidArgument(ERR_INVAL_ARG),
	tooFewOperands(ERR_TOO_FEW_OP)
{
	for (int i = 1 ; i < argc; i++)
	{
		takeArgument (argv[i]);
		print(std::cout);
	}
}

RPN::~RPN()
{
}

RPN::RPN(const RPN& b):
	invalidArgument(ERR_INVAL_ARG),
	tooFewOperands(ERR_TOO_FEW_OP)
{
	(void)b;
}

RPN& RPN::operator=(const RPN& b)
{
	(void)b;
	return (*this);
}

void RPN::takeArgument(const char *arg)
{
	std::string strArg(arg);
	if (strArg.length() != 1)
		throw invalidArgument;
	if (strArg.find_first_of("0123456789") != std::string::npos)
		return (push (strArg));
	if (strArg.find_first_of("+-*/") != std::string::npos)
	{
		char operation = strArg[0];
		int aOp;
		int bOp;
		if ((this->size() < 2 && (operation == '*' || operation == '/'))
			|| (this->size() < 1 && (operation == '+' || operation == '-')))
			throw tooFewOperands;
		if (this->size() > 1)
		{
			bOp = stoi(top());
			pop();
		}
		aOp = stoi(top());
		pop();
		if (this->size() > 1)
			return (binaryOperation(aOp, bOp, operation));
		return (unaryOperation(aOp, operation));
	}
	throw invalidArgument;
}

void RPN::unaryOperation(int aOp, char operation)
{
	switch (operation)
	{
	case '+':
		push(std::to_string(aOp));
		break;
	case '-':
		push(std::to_string(-aOp));
		break;
default:
		throw invalidArgument;
		break;
	}
}

void RPN::binaryOperation(int aOp, int bOp, char operation)
{
	switch (operation)
	{
	case '+':
		push(std::to_string(aOp + bOp));
		break;
	case '-':
		push(std::to_string(aOp - bOp));
		break;
	case '*':
		push(std::to_string(aOp * bOp));
		break;
	case '/':
		push(std::to_string(aOp / bOp));
		break;
	default:
		throw invalidArgument;
		break;
	}
}

std::ostream& RPN::print(std::ostream& os)
{
	std::stack<std::string>::container_type::iterator it = c.begin();
	std::stack<std::string>::container_type::iterator ite = c.end();
	while (it != ite)
	{
		os << *it << " ";
		it++;
	}
	os << std::endl;
	return (os);
}

