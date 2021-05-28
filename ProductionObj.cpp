#include "Global.h"

CProductionObj::CProductionObj()
{
	m_pNext = 0;
	m_pPrev = 0;
	m_pSymbol = 0;
}

CProductionObj::~CProductionObj()
{

}

void CProductionObj::Print(FILE *pOut, int Indent)
{
	char* IndS = new char[10];
	int i;

	for (i = 0; i < Indent; ++i)
		IndS[i] = ' ';
	IndS[i] = 0;
	fprintf(pOut,"%s%s\n", IndS, m_pSymbol->GetName());
	delete[] IndS;
}

