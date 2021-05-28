#include "Global.h"

enum {TOKEN_EOF,
	TOKEN_ID=256,
	TOKEN_ASSIGN,	// 257
	TOKEN_SPECIAL	// 258
};


TOKENS LanguageTokens[] = {
	{"=",'='},
	{"*",'*'},
	{"+",'+'},
	{"-",'-'},
	{";",';'},
	{"(",'('},
	{")",')'},

	{NULL,0}
};

CRecDecParGen::CRecDecParGen():CParser()
{
	int i;

	LexBufIndex = 0;
	for (i = 0; i < 1024; ++i) LexBuff[i] = 0;
	m_pHead = 0;
	m_pTail = 0;
	m_pSymbol = 0;
	m_pSymbolTable = new SymbolTab(31);
	mLine = 1;
}

CRecDecParGen::~CRecDecParGen()
{
	delete m_pSymbolTable;
}

int CRecDecParGen::IsAlphaOrNum(int c)
{
	int rV = 0;

	if (isalnum(c) || '_' == c)
		rV = 1;
	return rV;
}

int CRecDecParGen::IsWhiteSpace(int c)
{
	int rv = 0;

	if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
		rv = 1;
	return rv;
}

int CRecDecParGen::Lexer(FILE* pIN)
{
	int rV = 0;
	int c;
	int loop = 1;

	LexBufIndex = 0;
	LexBuff[0] = 0;
	while (loop)
	{
		c = LexGet(pIN);
		switch (c)
		{
		case EOF:
			rV = TOKEN_EOF;
			loop = 0;
			break;
		case '\n':
			++mLine;
			break;
		case ' ':
		case '\r':
		case '\t':	//white space
			break;
		case ';':
			LexBuff[0] = c;
			LexBuff[1] = 0;
			rV = c;
			loop = 0;
			break;
		case '\'':
			c = LexGet(pIN);
			while (c != '\'')
			{
				LexBuff[LexBufIndex++] = c;
				c = LexGet(pIN);
			}
			LexBuff[LexBufIndex] = 0;
			rV = TokenLookup(LexBuff,LanguageTokens);
			if( rV > 0)
				rV = TOKEN_SPECIAL;
			else
			{
				fprintf(stderr, "Bad Keyword %s\n",LexBuff);
				exit(1);
			}
			loop = 0;
			break;
		case '-':
			LexBuff[LexBufIndex++] = c;
			c = LexGet(pIN);
			LexBuff[LexBufIndex++] = c;
			if ('>' == c)
			{
				loop = 0;
				rV = TOKEN_ASSIGN;
				LexBuff[LexBufIndex] = 0;
			}
			else
			{
				LexBuff[LexBufIndex] = 0;
				fprintf(stderr, "Error:Lexer Bad Token char String (%s)\n", LexBuff);
				exit(1);
			}
			break;
		default:	//identifier
			if (!IsWhiteSpace(c) && IsAlphaOrNum(c))
			{
				int loopDF;

				LexBuff[LexBufIndex++] = c;
				c = LexGet(pIN);
				loopDF = 1;
				while (loopDF)
				{
					if (! IsWhiteSpace(c) && IsAlphaOrNum(c))
					{
						LexBuff[LexBufIndex++] = c;
						c = LexGet(pIN);
					}
					else
					{
						LexBuff[LexBufIndex] = 0;
						LexUnGet(c);
						loopDF = 0;
					}
				}
				rV = TOKEN_ID;
				loop = 0;
			}
			else
			{
				fprintf(stderr,"Line %d: Something is screwy, I got a %c\n", mLine, c);
				exit(1);
			}
			break;
		}
	}
	return rV;
}

void CRecDecParGen::Parser(FILE* pIn)
{
	//---------------------------------
	//	grammer -> productions eof
	//          -> eof
	//
	//	productionws -> production productions
	//				 -> empty
	//
	//	production -> LHside RHsideList ';'
	//
	//	LHside -> id
	//
	//	RHsideList -> RHside RHsideList
	//             -> empty
	//
	//	RHside -> '->' ObjList
	//	
	//	ObjList -> Object ObjList
	//			->empty
	//
	//	Object -> id
	//		   -> ';'
	//---------------------------------
	int Lookahead;
	//grammer->productions eof
	//	->eof
	//	;

	Lookahead = Lexer(pIn);
	if (Lookahead == TOKEN_ID)
	{
		Lookahead = Productions(pIn, Lookahead);
		Expect(Lookahead, TOKEN_EOF,pIn);
	}
	fprintf(stdout, "Done Parsing\n");
}

int CRecDecParGen::Productions(FILE* pIN, int Lookahead)
{

	CProduction* pP = new CProduction;
	Lookahead = Production(pIN, Lookahead,pP);
	switch (Lookahead)
	{
	case TOKEN_ID:
		Lookahead = Productions(pIN, Lookahead);
		break;
	case TOKEN_EOF:
		break;
	default:
		fprintf(stderr, "Line %d Productions:UnExpected Token:%d\n", mLine, Lookahead);
		break;
	}
	return Lookahead;
}

int CRecDecParGen::Production(FILE* pIN, int Lookahead, CProduction *pP)
{
	// Production->LHside RHsideList ';';

	Lookahead = LHside(pIN, Lookahead,pP);
	Lookahead = RHsideList(pIN, Lookahead, pP,0);
	Lookahead = Expect(Lookahead,';',pIN);
	AddProductionToTail(pP);
	return Lookahead;
}

int CRecDecParGen::LHside(FILE* pIN, int Lookahead, CProduction *pP)
{
	Symbol* pSym;

	switch (Lookahead)
	{
	case TOKEN_ID:
		pSym = AddSymbol(LexBuff);
		pSym->SetToken(Lookahead);
		pSym->SetLeftSide(1);
		pP->SetSymbol(pSym);
		Lookahead = Expect(Lookahead, TOKEN_ID, pIN);
		break;
	default:
		fprintf(stderr, "LHside::?????\n");
		break;
	}
	return Lookahead;
}

int CRecDecParGen::RHsideList(FILE* pIN, int Lookahead, CProduction *pP,int Rule)
{
	//RHsideList->RHside RHsideList
	//	        ->
	//	         ;
	Rule++;

	Lookahead = RHside(pIN, Lookahead,pP,Rule);
	switch (Lookahead)
	{
	case TOKEN_ASSIGN:
		Lookahead = RHsideList(pIN, Lookahead,pP,Rule);
		break;
	case ';':
		break;
	default:
		fprintf(stderr, "RHSideList:UnExpected Token:%d\n", Lookahead);
		break;
	}
	return Lookahead;
}

int CRecDecParGen::RHside(FILE* pIN, int Lookahead, CProduction *pP, int Rule)
{
	//	RHside -> ObjList ;

	Symbol *pSym;
	char* rS = new char[256];
	CRHside* pRH;

	Lookahead = Expect(Lookahead, TOKEN_ASSIGN, pIN);
	pRH = new CRHside;
	pP->AddRHStoTail(pRH);
	sprintf_s(rS, 10, "RULE%d", Rule);
	pSym = new Symbol(rS);
	pSym->SetNotInGrammer();;
	pRH->SetSymbol(pSym);
	Lookahead = ObjList(pIN, Lookahead, pRH);
	delete[] rS;
	return Lookahead;
}

int CRecDecParGen::ObjList(FILE* pIN, int Lookahead, CRHside* pRH)
{
	//	ObjList->Object ObjList
	//		   ->
	//			;

	Lookahead = Object(pIN, Lookahead,pRH);

	switch (Lookahead)
	{
	case TOKEN_ID:
	case TOKEN_SPECIAL:
		Lookahead = ObjList(pIN, Lookahead, pRH);
		break;
	case TOKEN_ASSIGN:
	case ';':
		break;
	default:
		fprintf(stderr, "ObjectList:UnExpected Token:%d\n", Lookahead);
		break;
	}
	return Lookahead;
}

int CRecDecParGen::Object(FILE* pIN, int Lookahead, CRHside *pRH)
{
	CProductionObj* pPO;
	Symbol* pSym;

	switch (Lookahead)
	{
	case TOKEN_ID:
		pPO = new CProductionObj;
		pSym = AddSymbol(LexBuff);
		pSym->SetToken(Lookahead);
		pSym->SetRightSide(1);
		pPO->SetSymbol(pSym);
		pRH->AddProductionObjToTail(pPO);
		Lookahead = Expect(Lookahead, TOKEN_ID, pIN);
		break;
	case ';':
		break;
	case TOKEN_SPECIAL:
		pPO = new CProductionObj;
		pSym = AddSymbol(LexBuff);
		pSym->SetToken(Lookahead);
		pSym->SetRightSide(1);
		pPO->SetSymbol(pSym);
		pRH->AddProductionObjToTail(pPO);
		Lookahead = Expect(Lookahead, TOKEN_SPECIAL, pIN);
		break;
	default:
		fprintf(stderr, "Line %d:Object:UnExpected Token:%d  %s\n", mLine, Lookahead, LexBuff);
		break;
	}
	return Lookahead;
}

int CRecDecParGen::Expect(int Lookahead, int Token, FILE* pIN)
{
	Lookahead = CParser::Expect(Lookahead, Token, pIN);
	return Lookahead;
}

void CRecDecParGen::AddProductionToTail(CProduction* pP)
{
	if (m_pTail)
	{
		m_pTail->SetNext(pP);
		pP->SetPrev(m_pTail);
		m_pTail = pP;
	}
	else
	{
		m_pTail = pP;
		m_pHead = pP;
	}
}

void CRecDecParGen::Print(FILE* pOut,int Indent)
{
	CProduction* pP = m_pHead;

	while (pP)
	{
		pP->Print(pOut,Indent);
		pP = pP->GetNext();
	}
}

int CRecDecParGen::FindTerminals()
{
	int i;
	Symbol* pSym;
	int rv = 0;
	int n;
	Bucket* pBuck;

	pBuck = m_pSymbolTable->GetTable();
	n = m_pSymbolTable->GetTableSize();
	for (i = 0; i < n; ++i)
	{
		pSym = (Symbol *)pBuck[i].GetHead();
		while (pSym)
		{
			if (!pSym->GetLeftSide() && pSym->GetRightSide())
				pSym->SetTerminak(1);
			pSym = (Symbol *)pSym->GetNext();
		}
	}
	return rv;
}

Symbol* CRecDecParGen::AddSymbol(const char* pName)
{
	Symbol* pSym = 0;

	pSym = (Symbol *) m_pSymbolTable->FindSymbol(pName);
	if (pSym == NULL)
	{
		pSym = new Symbol(pName);
		m_pSymbolTable->AddSymbol(pSym);
	}
	return pSym;
}
