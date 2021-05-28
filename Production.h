#pragma once

class CProduction
{
	Symbol* m_pSymbol;;
	CProduction* m_pNext;
	CProduction* m_pPrev;
	CRHside* m_pHead;
	CRHside* m_pTail;
public:
	CProduction();
	~CProduction();
	inline void SetNext(CProduction* pN) { m_pNext = pN; }
	inline CProduction* GetNext() { return m_pNext; }
	inline void SetPrev(CProduction* pP) { m_pPrev = pP; }
	inline CProduction* GetPrev() { return m_pPrev; }
	inline void SetHead(CRHside* pH) { m_pHead = pH; }
	inline CRHside* GetHead() { return m_pHead; }
	inline void SetTail(CRHside* pT) { m_pTail = pT;}
	inline CRHside* GetTail() { return m_pTail; }
	inline void SetSymbol(Symbol* pSym) { m_pSymbol = pSym; }
	inline Symbol* GetSymbol() { return m_pSymbol; }
	void AddRHStoTail(CRHside* pP);
	void Print(FILE* pOut, int Indent);
};

