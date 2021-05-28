#pragma once

typedef struct {
	const char* pTokenName;
	int Token;
} TOKENS;

class CParser
{
	int unGetBuf;
protected:
	int mLine;
public:
	CParser();
	virtual ~CParser();
	virtual int Lexer(FILE *pIn);
	virtual void Parser(FILE* pIN);
	virtual int Expect(int Lookahead, int token, FILE* pI);
	virtual int Accept(int Lookahead, int token);
	virtual int TokenLookup(const char* pName, TOKENS *pTok);
	virtual int IsValidToken(int Tokenval, TOKENS* pToke);
	virtual void LexUnGet(int c);
	virtual int LexGet(FILE* pIN);
};

