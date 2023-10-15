/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:30:51 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/15 15:43:00 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RPN_HPP_
# define  _RPN_HPP_
class RPN : std::stack<char>
{
private:
public:
	RPN(int argc, char const *argv[]);
	~RPN();
};

#endif