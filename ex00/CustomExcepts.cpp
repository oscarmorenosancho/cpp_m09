/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomExcepts.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:40 by omoreno-          #+#    #+#             */
/*   Updated: 2023/10/23 15:32:33 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CustomExcepts.hpp>
# include <CustomDefs.hpp>

InvalidValueError::InvalidValueError() : std::runtime_error(ERR_BAD_INPUT){}
InvalidValueError::~InvalidValueError() _NOEXCEPT{}
InvalidValueError::InvalidValueError(const InvalidValueError&) :
	std::runtime_error(ERR_BAD_INPUT){}
NotPositiveError::NotPositiveError() : std::runtime_error(ERR_NOT_POSITIVE){}
NotPositiveError::~NotPositiveError() _NOEXCEPT{}
NotPositiveError::NotPositiveError(const NotPositiveError&) :
	std::runtime_error(ERR_NOT_POSITIVE){}
TooLargeError::TooLargeError() : std::runtime_error(ERR_TOO_LARGE){}
TooLargeError::~TooLargeError() _NOEXCEPT{}
TooLargeError::TooLargeError(const TooLargeError&) :
	std::runtime_error(ERR_TOO_LARGE){}
CsvLoadError::CsvLoadError() : std::runtime_error(ERR_DATA_CSV){}
CsvLoadError::~CsvLoadError() _NOEXCEPT{}
CsvLoadError::CsvLoadError(const CsvLoadError&) :
	std::runtime_error(ERR_DATA_CSV){}
AlreadyCatchedError::AlreadyCatchedError() : std::runtime_error(ERR_DATA_CSV){}
AlreadyCatchedError::~AlreadyCatchedError() _NOEXCEPT{}
AlreadyCatchedError::AlreadyCatchedError(const AlreadyCatchedError&) :
	std::runtime_error(ERR_DATA_CSV){}
