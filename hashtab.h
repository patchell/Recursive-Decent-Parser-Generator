//**********************************
// HashTab.h
//
// Implementation of a hash table
// that can be used to store any
// type of object, based on class Bin
//
// Created October 9, 2012
// Copyright (C) 2012
// by James Patchell
//
//**********************************

#ifndef HASHTAB__H
#define HASHTAB__H

class SymbolTab;

class printFormat
{
public:
	int m_numberOfFields;
	char* m_pFieldNames;
public:
	printFormat();
	~printFormat();
};
//----------------------
// base class for symbols
//----------------------

class Bin {
	Bin *m_pNext;
	Bin *m_pPrev;
	char *m_pName;
public:
	Bin();
	Bin(const char *s);
	~Bin();
	inline void SetNext(Bin* n) { m_pNext = n; }
	inline void SetPrev(Bin* p) { m_pPrev = p; }
	inline Bin* GetNext(void) { return m_pNext; }
	inline Bin* GetPrev(void) { return m_pPrev; }
	inline virtual char *GetName(void);
	inline virtual void SetName(const char* pName) {
		int l = (int)strlen(pName) + 1;
		m_pName = new char[l];
		strcpy_s(m_pName, l, pName);
	}
	virtual int Compare(const char* name) {
		int rV = 0;
		if (strcmp(m_pName, name) == 0) rV = 1;
		return rV;
	}
	virtual void Print(FILE *pOut);
};

class Bucket
{
	Bin* m_pHead;
	Bin* m_pTail;
public:
	Bucket() {
		m_pHead = 0;
		m_pTail = 0;
	}
	virtual ~Bucket() {}
	void Add(Bin* pSym);
	Bin* Find(const char* pName);
	void Delete(Bin* pSym);
	void Unlink(Bin* pSym);
	inline void SetHead(Bin* pH) { m_pHead = pH; }
	inline Bin* GetHead() { return m_pHead; }
	inline void SetTail(Bin* pT) { m_pTail = pT; }
	inline Bin* GetTail() {return m_pTail;}
};

class SymbolTab
{
	int Hash(const char* name);
protected:
	int m_nElements;	//total number of elements in table
	int m_tSize;	//depth of table
	Bucket *m_pTab;	//pointer to table
public:
	SymbolTab(int size);
	virtual ~SymbolTab();
	virtual Bin *FindSymbol(const char *name);
	virtual void AddSymbol(Bin *pSym);
	virtual void DelSymbol(Bin *pSym);
	virtual void PrintTable(FILE *pOut);
	inline int GetNumElements() { return m_nElements; }
	inline int GetTableSize() { return m_tSize; }
	inline Bucket* GetTable() { return m_pTab; }
};

#endif
