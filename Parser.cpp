#include "Global.h"

CParser::CParser()
{
	unGetBuf = 0;
	mLine = 1;
}

CParser::~CParser()
{

}

void CParser::LexUnGet(int c)
{
	unGetBuf = c;
}

int CParser::LexGet(FILE* pIN)
{
	int c;

	if (unGetBuf)
	{
		c = unGetBuf;
		unGetBuf = 0;
	}
	else
	{
		c = fgetc(pIN);
	}
	return c;
}

int CParser::Lexer(FILE* pIn)
{
	return 0;
}

void CParser::Parser(FILE* pIN)
{

}

//**********************************************
// Expect
//
// This function is used to check that we get
// the token that we Expect.
//
// parameters:
//	Lookahead..Current lookahead token
//	token....this is the token we Expect
//	pIN.....Input file
// return value:
//	reutns the next Lookahead token (>0)
//	reutnrs 0 or negative if we did not get what we Expected
//*********************************************

int CParser::Expect(int Lookahead, int token, FILE *pIN)
{
	if (Accept(Lookahead, token))
		Lookahead = Lexer(pIN);
	else
	{
		fprintf(stderr, "Line %d: Unexpected Token:Got %d Expected %d\n", mLine, Lookahead, token);
		exit(1);
	}
	return Lookahead;
}

//********************************************
// Accept
//
// This function compares the token you want
// versus the token that is current.  If they
// match, then we get another token.
// If not, then just return.
//
// parameter:
//	Lookahead..The current lookahead token
//	token.....this is the token we want
//	pIN.......pointer to input file
//
// return value:
//	returns the new token value (>0)
//	returns 0 or negative if we don't get the token we want
//**********************************************

int CParser::Accept(int Lookahead, int token)
{
	int rv;

	if (token == Lookahead)
		rv = 1;
	else
		rv = 0;
	return rv;
}


int CParser::TokenLookup(const char* pName, TOKENS* pTokens)
{
	int i;
	int rV = 0;

	for (i = 0; pTokens[i].pTokenName; ++i)
	{
		if (strcmp(pTokens[i].pTokenName, pName) == 0)
		{
			rV = pTokens[i].Token;
			break;
		}
	}
	return rV;
}

int CParser::IsValidToken(int Tokenval, TOKENS* pToke)
{
	int i;
	int rv = 0;

	for (i = 0; pToke[i].pTokenName; ++i)
	{
		if (Tokenval == pToke[i].Token)
			rv = 1;
	}
	return rv;
}