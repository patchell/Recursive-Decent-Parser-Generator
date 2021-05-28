#include "Global.h"

CRHside::CRHside()
{
	m_pNext = 0;
	m_pPrev = 0;
	m_pHead = 0;
	m_pTail = 0;
	m_pSymbol = 0;
}

CRHside::~CRHside()
{

}

void CRHside::AddProductionObjToTail(CProductionObj* pCO)
{
	if (m_pTail)
	{
		m_pTail->SetNext(pCO);
		pCO->SetPrev(m_pTail);
		m_pTail = pCO;
	}
	else
	{
		m_pTail = pCO;
		m_pHead = pCO;
	}
}

void CRHside::Print(FILE* pOut,int Indent)
{
	CProductionObj* pP = m_pHead;
	char* IndS = new char[10];
	int i;
	
	for (i = 0; i < Indent; ++i)
		IndS[i] = ' ';
	IndS[i] = 0;
	fprintf(pOut, "%s%s\n", IndS, m_pSymbol->GetName());
	Indent++;
	while (pP)
	{
		pP->Print(pOut,Indent);
		pP = pP->GetNext();
	}
	delete[]IndS;
}
