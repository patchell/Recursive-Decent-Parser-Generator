#pragma once

class CSet
{
	char* m_pName;
	CSetObj* m_pHead;
	CSetObj* m_pTail;
public:
	CSet();
	virtual ~CSet();
	void AddToSet(CSetObj* pNewObj);
};

