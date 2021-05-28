#pragma once


class CProductionObj
{
	CProductionObj* m_pNext;
	CProductionObj* m_pPrev;
	Symbol* m_pSymbol;
public:
	CProductionObj();
	~CProductionObj();
	inline void SetNext(CProductionObj* n) { m_pNext = n; }
	inline CProductionObj* GetNext() { return m_pNext; }
	inline void SetPrev(CProductionObj* p) { m_pPrev = p; }
	inline CProductionObj* GetPrev() { return m_pPrev;}
	inline void SetSymbol(Symbol *pSym) { m_pSymbol = pSym; }
	inline Symbol* GetSymbol() { return m_pSymbol; }
	void Print(FILE *pOut, int Indent);
};

