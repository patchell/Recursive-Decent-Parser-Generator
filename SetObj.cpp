#include "Global.h"

CSetObj::CSetObj()
{
	m_pNext = 0;
	 m_pPrev = 0;
	m_pName = 0;
	m_ID = 0;
}

CSetObj::~CSetObj()
{
	if (m_pName) delete[] m_pName;
}
