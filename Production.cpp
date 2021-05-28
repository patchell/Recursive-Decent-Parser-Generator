#include "Global.h"

CProduction::CProduction()
{
	m_pSymbol = 0;
	m_pHead = 0;
	m_pTail = 0;
	m_pNext = 0;
	m_pPrev = 0;
}

CProduction::~CProduction()
{

}

void CProduction::AddRHStoTail(CRHside* pP)
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

void CProduction::Print(FILE* pOut,int Indent)
{
	CRHside* pRH = m_pHead;
	char* IndS = new char[256];
	int i;

	for (i = 0; i < Indent; ++i) IndS[i] = ' ';
	IndS[i] = 0;
	fprintf(pOut, "%s%s\n", IndS, m_pSymbol->GetName());
	Indent++;
	while (pRH)
	{
		pRH->Print(pOut, Indent);
		pRH = pRH->GetNext();
	}
	delete[] IndS;
}