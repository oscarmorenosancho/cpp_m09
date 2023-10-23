/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogError.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:28 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 10:39:15 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOGERROR_HPP_
# define _LOGERROR_HPP_
# include <iostream>
# include <string>

class LogError
{
private:
	LogError();
	~LogError();
	LogError(const LogError& b);
	LogError& operator=(const LogError& b);
public:
	static int	print(const char *msg, const char *msg2);
};

#endif
