#pragma once


class CRecDecParGen :public CParser
{
	char LexBuff[1024];
	int LexBufIndex;
	CProduction* m_pHead;
	CProduction* m_pTail;
	Symbol* m_pSymbol;
	SymbolTab* m_pSymbolTable;
public:
	CRecDecParGen();
	virtual ~CRecDecParGen();
	virtual int Lexer(FILE* pIn);
	virtual void Parser(FILE* pIn);
	virtual int Expect(int Lookahead, int Token, FILE* pIN);
	int Productions(FILE* pIN, int Lookahead);
	int Production(FILE* pIN, int Lookahead, CProduction *pP);
	int LHside(FILE* pIN, int Lookahead,CProduction *pP);
	int RHsideList(FILE* pIN, int Lookahead, CProduction* pP, int Rule);
	int RHside(FILE* pIN, int Lookahead, CProduction* pP, int Rule);
	int ObjList(FILE* pIN, int Lookahead, CRHside* pRH);
	int Object(FILE* pIN, int Lookahead, CRHside* pRH);
	int IsWhiteSpace(int c);
	int IsAlphaOrNum(int c);
	inline void SetHead(CProduction* pH) { m_pHead = pH; }
	inline CProduction* GetHead() { return m_pHead; }
	inline void SetTail(CProduction* pT) { m_pTail = pT; }
	inline CProduction* GetTail() { return m_pTail; }
	inline void SetSymbol(Symbol* pSym) { m_pSymbol = pSym; }
	inline Symbol* GetSymbol() { return m_pSymbol; }
	void AddProductionToTail(CProduction* pP);
	int FindTerminals();
	void Print(FILE* pOut, int Indent);
	inline void PrintSymbolTable(FILE* pOut) { m_pSymbolTable->PrintTable(pOut); }
	Symbol* AddSymbol(const char* pName);
};

static CRecDecParGen* pParser;
inline CRecDecParGen* GetParser() {
	return pParser;
}

