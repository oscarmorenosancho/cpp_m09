/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomExcepts.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:24:49 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:32:02 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUSTOMEXCEPTS_HPP_
# define _CUSTOMEXCEPTS_HPP_
# include <stdexcept>

class InvalidValueError : public std::runtime_error
{
public:
	InvalidValueError();
	virtual ~InvalidValueError() _NOEXCEPT;
	InvalidValueError(const InvalidValueError&);
};

class NotPositiveError : public std::runtime_error
{
public:
	NotPositiveError();
	virtual ~NotPositiveError() _NOEXCEPT;
	NotPositiveError(const NotPositiveError&);
};

class TooLargeError : public std::runtime_error
{
public:
	TooLargeError();
	virtual ~TooLargeError() _NOEXCEPT;
	TooLargeError(const TooLargeError&);
};

class CsvLoadError : public std::runtime_error
{
public:
	CsvLoadError();
	virtual ~CsvLoadError() _NOEXCEPT;
	CsvLoadError(const CsvLoadError&);
};

class AlreadyCatchedError : public std::runtime_error
{
public:
	AlreadyCatchedError();
	virtual ~AlreadyCatchedError() _NOEXCEPT;
	AlreadyCatchedError(const AlreadyCatchedError&);
};

#endif
