//--------------------------------------------
// implementation of symbol type
//
// Created November 5, 2012
// Copyright (c) 2012
// by James Patchell
//-------------------------------------------

#include "Global.h"

//*****************************************************
// Constructor
//
// parameter:
//	pName.....pointer to name of symbol
//
// This class is derived from class Bin.
// So we are passing along the parameter
// to the similar constructor in the base
// class.
//******************************************************

Symbol::Symbol(const char *pName):Bin(pName)
{
	m_Terminal = 0;
	m_LeftSide = 0;
	m_RightSide = 0;
	m_Token = 0;
	m_NotInGrammer = 0;
}

//******************************************************
// destructor
//******************************************************

Symbol::~Symbol()
{
}

//********************************************************
//  Print
//
// parameter:
//	pO.....pointer to output device
//
// This is a virtual function, which over rides the same
// function in the base class.
//*********************************************************

void Symbol::Print(FILE *pO)
{
	char *s = new char[512];
	PrintSymbol(s,512);
	fprintf(pO,"%s\n",s);
	delete[] s;
}

//************************************************************
// PrintSymbol
//
// parameter:
//	s......pointer to string to print the symbol into
//
// returns number of characters printed into s
//************************************************************

int Symbol::PrintSymbol(char *s, int l)
{
	int rv=0;
	int e = 0;

	e += sprintf_s(&s[e], size_t(l - e), "SymBol:%s", GetName());
	e += sprintf_s(&s[e], size_t(l - e), " Terminal->%d", m_Terminal);
	e += sprintf_s(&s[e], size_t(l - e), " LeftSide->%d", m_LeftSide);
	e += sprintf_s(&s[e], size_t(l - e), " RightSide->%d", m_RightSide);
	e += sprintf_s(&s[e], size_t(l - e), " Token->%d", m_Token);
	return rv;
}

int Symbol::FillWithChars(char* s, int ch, int n)
{
	int i = 0;

	for (i = 0; i < n; ++i)
		s[i] = (char)ch;
	return i;
}
