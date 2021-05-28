#include <stdio.h>
#include <stdlib.h>

#include "Global.h"

int main(int arcg, char *argv[])
{
	CRecDecParGen* Parser;
	FILE* pIN;

	fopen_s(&pIN,"Test2.gram","r");
	if (pIN == NULL)
	{
		printf("Cannot Open Input File\n");
		exit(1);
	}

	Parser = new CRecDecParGen;
	Parser->Parser(pIN);
	Parser->Print(stdout, 0);
	Parser->FindTerminals();
	Parser->PrintSymbolTable(stdout);
	fclose(pIN);
	delete Parser;
	printf("Done\n");
	return 0;
}
