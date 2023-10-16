/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:47 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/16 20:48:22 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <sstream>

void RPN::iterSplit(const std::string & s)
{
    std::istringstream buf(s);
	std::string token;

	while (getline(buf, token,' '))
		takeToken(token);
}

int RPN::stoi(const std::string & s)
{
    int i;
    std::istringstream(s) >> i;
    return i;
}

template<typename T>
std::string RPN::to_string(const T & value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

RPN::RPN(const char *arg):
	invalidArgument(ERR_INVAL_ARG),
	tooFewOperands(ERR_TOO_FEW_OP),
	divisionByZero(ERR_DIV_BY_0)
{
	iterSplit(std::string(arg));
	print(std::cout);
}

RPN::~RPN()
{
}

RPN::RPN(const RPN& b):
	stack<std::string>(),
	invalidArgument(ERR_INVAL_ARG),
	tooFewOperands(ERR_TOO_FEW_OP),
	divisionByZero(ERR_DIV_BY_0)
{
	(void)b;
}

RPN& RPN::operator=(const RPN& b)
{
	(void)b;
	return (*this);
}

int	RPN::topToOp()
{
	int Op = stoi(top());
	pop();
	return (Op); 
}

void RPN::takeToken(const std::string& token)
{
	if (token.length() < 1)
		return ;
	if (token.length() > 1)
		throw invalidArgument;
	if (token.find_first_of("0123456789") != std::string::npos)
		return (push (token));
	if (token.find_first_of("+-*/") != std::string::npos)
	{
		char operation = token[0];
		int aOp;
		int bOp;
		if ((this->size() < 2 && (operation == '*' || operation == '/'))
			|| (this->size() < 1 && (operation == '+' || operation == '-')))
			throw tooFewOperands;
		bool binOper = (this->size() > 1);
		if (binOper)
			bOp = topToOp();
		aOp = topToOp();
		if (binOper)
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
		push(to_string(aOp));
		break;
	case '-':
		push(to_string(-aOp));
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
		push(to_string(aOp + bOp));
		break;
	case '-':
		push(to_string(aOp - bOp));
		break;
	case '*':
		push(to_string(aOp * bOp));
		break;
	case '/':
		if (bOp == 0)
			throw divisionByZero;
		push(to_string(aOp / bOp));
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

