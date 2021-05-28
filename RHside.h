#pragma once

class CRHside
{
	Symbol *m_pSymbol;
	CRHside* m_pNext;
	CRHside* m_pPrev;
	CProductionObj* m_pHead;
	CProductionObj* m_pTail;
public:
	CRHside();
	~CRHside(); 
	inline void SetNext(CRHside* pN) { m_pNext = pN; }
	inline CRHside* GetNext() { return m_pNext; }
	inline void SetPrev(CRHside* pP) { m_pPrev = pP; }
	inline CRHside* GetPrev() { return m_pPrev; }
	inline void SetTail(CProductionObj* pT) { m_pTail = pT; }
	inline CProductionObj* GetTail() { return m_pTail; }
	inline void SetHead(CProductionObj* pH) { m_pHead = pH; }
	inline CProductionObj* GetHead() { return m_pHead; }
	void AddProductionObjToTail(CProductionObj* pCO);
	void Print(FILE* pOut,int Indent);
	inline void SetSymbol(Symbol* pSym) { m_pSymbol = pSym; }
	inline Symbol* GetSymbol() { return m_pSymbol; }
};

