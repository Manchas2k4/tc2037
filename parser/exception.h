// =================================================================
//
// File: exception.h
// Author: Pedro Perez
// Description: This file contains the definition of the different
//				exceptions that we will use throughout the semester.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include <cstdio>

/*********** Exception ***********/
class Exception : public std::exception {
protected:
	std::string text;

public:
	Exception() throw();
	~Exception() throw();
	virtual const char* what() const throw();
};

Exception::Exception() throw ()
	: text("Basic exception") {
}

Exception::~Exception() throw () {}

const char* Exception::what() const throw() {
	return text.c_str();
}

/*********** InputFileError ***********/
class InputFileException : public Exception {
public:
	InputFileException() throw();
};

InputFileException::InputFileException() throw () {
		text = std::string("InputFileException");
}

/*********** IllegalAction ***********/
class SyntaxException : public Exception {
public:
	SyntaxException() throw();
};

SyntaxException::SyntaxException() throw () {
		text = std::string("SyntaxException");
}

#endif
