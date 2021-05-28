#pragma once

class CSetObj
{
	CSetObj* m_pNext;
	CSetObj* m_pPrev;
	char* m_pName;
	int m_ID;
public:
	CSetObj();
	~CSetObj();
	inline void SetNext(CSetObj* pN) { m_pNext = pN; }
	inline CSetObj* GetNext() { return m_pNext; }
	inline void SetPrev(CSetObj* pP) { m_pPrev = pP; }
	inline CSetObj* GetPrev() { return m_pPrev; }
	inline void SetName(const char* n) {
		size_t l = (size_t)strlen(n) + 1;
		m_pName = new char[l];
		strcpy_s(m_pName, l, n);
	}
	inline const char* GetName() { return m_pName; }
	inline void SetID(int id) { m_ID = id; }
	inline int GetID() { return m_ID; }
};

