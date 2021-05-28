//*****************************************************
// Symbol.h
//
// This is the class that we will be storing symbols
// into
//
// Created November 5, 2012
// Copyright (c) 2012
// by James Patchell
//*****************************************************

#ifndef SYMBOL__H
#define SYMBOL__H

class Symbol:public Bin {
	int m_Terminal;			//what type is the symbol
	int m_RightSide;
	int m_LeftSide;
	int m_NotInGrammer;
	int m_Token;
public:
	Symbol(const char *pName);
	virtual ~Symbol();
	virtual void Print(FILE *pOut);
	int PrintSymbol(char *s, int n);
	inline int IsTerminal() { return m_Terminal; }
	inline void SetTerminak(int Tf) { m_Terminal = Tf; }
	inline int IsNotInGrammar() { return m_NotInGrammer; }
	inline void SetNotInGrammer() { m_NotInGrammer = 1; }
	inline void SetToken(int t) { m_Token = t; }
	inline int GetToken() { return m_Token; }
	inline void SetRightSide(int flag) { m_RightSide = flag; }
	inline int GetRightSide() { return m_RightSide; }
	inline void SetLeftSide(int flag) { m_LeftSide = flag; }
	inline int GetLeftSide() { return m_LeftSide; }
	int FillWithChars(char* s, int ch, int n);
};

#endif
