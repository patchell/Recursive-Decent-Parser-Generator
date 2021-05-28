//**********************************
// HashTab.cpp
//
// Implementation of a hash table
// that can be used to store any
// type of object.
//
// Created October 9, 2012
// Modified October 14, 2020
// Copyright (C) 2012, 2020
// by James Patchell
//
//**********************************

#include "Global.h"

//------------------------------------
// Bin Class Implementation
//
// After I wrote this, I discovered that
// the Bins in a Hash Table are actually
// called Buckets.  Well, almost the same
// thing.  So, if you are already
// familiar with hash tables, now you
// know I am talking about the same thing.
//------------------------------------

//****************************************
// Constructor
// Zero out all the members
//****************************************

Bin::Bin()
{
	m_pNext = 0;
	m_pPrev = 0;
	m_pName = 0;
}

//***************************************
// Constructor
//
// parameter:
//	s......pointer for the name of this Bin
//***************************************

Bin::Bin(const char *s)
{
	m_pNext = 0;
	m_pPrev = 0;
	size_t l = (size_t)strlen(s) + 1;
	m_pName = new char[l];
	strcpy_s(m_pName, l, s);
}

//*****************************************
// Destructor
//
// If the name has been allocated space,
// makre sure to destroy that as well.
//*****************************************

Bin::~Bin()
{
	if (m_pName) delete[] m_pName;
}

//*********************************************
// GetName
//
// Return the name of this Bin
//*********************************************

char *Bin::GetName()
{
	return m_pName;
}

//********************************************
//  Print
//
// parameter:
//	pOut....pointer to the output stream
//
// This is a virtual function and should be
// over ridden by a function in the top level
// class that will print out pertinent info
//
// this is the default action
//********************************************

void Bin::Print(FILE *pOut)
{
	fprintf(pOut,"%s\n",m_pName);
}

//***************************************
// Implementation of Hash Table Member
// Functions
//***************************************

//-------------------------------------------
// Constructor
//
// parameter:
//	size......number of Bins in the table
//
// Now, don't ask me why, but I heard that
// it is best to use a prime number for the
// number of bins.  I suspect the reason why
// is that we are doing a MOD opertion in
// the hashing function to make sure the
// index ends up in the table.
//
// And if you are like me, you can't
// remember what the prime number are.
// So, here is a list form 0 to 200.
// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
//  31, 37, 41, 43, 47, 53, 59, 61, 67
// 71, 73, 79, 83, 89, 97, 101, 103, 107,
// 109, 113, 127, 131, 137, 139, 149,
// 151, 157, 163, 167, 173, 179, 181,
// 191, 193, 197, 199
//--------------------------------------------

SymbolTab::SymbolTab(int size)
{
	m_pTab = new Bucket [size];
	m_tSize = size;
	m_nElements = 0;
}

//*****************************************************
// Destructor
//
// destroy HashTab and all of its components
//*****************************************************

SymbolTab::~SymbolTab()
{
	if(m_pTab) delete[] m_pTab;
}

//*****************************************************
// FindSym
//
// parameter:
//	name....name of object to find
//
//******************************************************

Bin * SymbolTab::FindSymbol(const char *name)
{
	Bin *pRV=NULL;

	int Index = Hash(name);	//get index from hash of name
	pRV = m_pTab[Index].Find(name);
	return pRV;
}

//***********************************************************
// AddSym
//
// parameter:
//	pSym....pointer to Bin to add to table
//
//***********************************************************

void SymbolTab::AddSymbol(Bin *pSym)
{
	int Index = Hash(pSym->GetName());	//generate index
	if(m_pTab[Index].GetHead() == NULL)	//nobody home
	{
		m_pTab[Index].SetHead(pSym);
		m_pTab[Index].SetTail(pSym);
	}
	else
	{
		Bucket* pB = &m_pTab[Index];
		pB->GetTail()->SetNext(pSym);
		pSym->SetPrev(pB->GetTail());
		pB->SetTail(pSym);
	}
	++m_nElements;	//increment number of symbols
}

//*****************************************************
// DelSym
//
// parameter:
//	pSym.....pointer to symbol to remove
//*****************************************************

void SymbolTab::DelSymbol(Bin *pSym)
{
	int HashValue = Hash(pSym->GetName());
	m_pTab[HashValue].Delete(pSym);
}

//*********************************************************
// Hash
//
// parameter
//	name.....pointer to name to Hash
//
//**********************************************************

int SymbolTab::Hash(const char *name)
{
	unsigned HashVal = 0;
	unsigned TopBits;
	unsigned char *n;

	n = (unsigned char *)name;
	while(*n)
	{
		HashVal = (HashVal << 12) + *n;
		if((TopBits = HashVal & 0xff000000) != 0)
			HashVal = ((TopBits >> 24) ^ HashVal) & 0x00ffffff;
		++n;	//next char please...
	}
	return HashVal % m_tSize;	//returns index in table
}


//***************************************************
// PrinTable
//
// paramter:
//	pOut.....output file stream
//
//*****************************************************

void SymbolTab::PrintTable(FILE *pOut)
{
	char* s = new char[512];
	Bin *pB;
	int i;
	int maxStringLen = 0;
	int l;

	//------------------------------
	// Scan table to find longest
	// name
	//------------------------------
	for (i = 0; i < m_tSize; ++i)
	{
		pB = m_pTab[i].GetHead();
		while (pB)
		{
			l = (int)strlen(pB->GetName());
			if (l > maxStringLen)
				maxStringLen = l;
			pB = pB->GetNext();
		}
	}

	for(i=0;i<m_tSize;++i)
	{
		pB = m_pTab[i].GetHead();
		while(pB)
		{
//			printf("Hey\n");
			pB->Print(pOut);
			pB = pB->GetNext();
		}
	}
}

void Bucket::Add(Bin* pSym)
{
	if (m_pHead)
	{
		m_pTail->SetNext(pSym);
		pSym->SetPrev(m_pTail);
		m_pTail = pSym;
	}
	else
	{
		m_pTail = pSym;
		m_pHead = pSym;
	}
}

Bin* Bucket::Find(const char* pName)
{
	Bin* pBret = 0;
	int loop = 1;
	pBret = m_pHead;
	while (pBret && loop)
	{
		if (pBret->Compare(pName))
			loop = 0;
		else
			pBret = pBret->GetNext();
	}
	return pBret;
}

void Bucket::Delete(Bin* pSym)
{
	Unlink(pSym);
	delete pSym;
}

void Bucket::Unlink(Bin* pSym)
{
	if (m_pHead == pSym)
	{
		m_pHead = pSym->GetNext();
		m_pHead->SetPrev(0);
	}
	else if (m_pTail == pSym)
	{
		m_pTail = pSym->GetPrev();
		m_pTail->SetNext(0);
	}
	else
	{
		pSym->GetNext()->SetPrev(pSym->GetPrev());
		pSym->GetPrev()->SetNext(pSym->GetNext());
	}
}

