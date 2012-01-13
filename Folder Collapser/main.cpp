#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

int main()
{
	unsigned int l;
	char tempFileName[L_tmpnam];
	char dirCommand[1024] = "dir /s /a:-d-s /b >>";
	char copyCommand[10240] = "copy \"";
	FILE *tempFile;

	l = strlen(copyCommand);

		// create a file with the contents of the folder and it's subfolders.
	tmpnam(tempFileName);	// create a name for a temporary file and save it in tempFileName.
	strcat(dirCommand,tempFileName);	// complement the dirCommand whith the file name.
	system(dirCommand);	// send the command to the system.

		// create destination folder.
	system("md c:\\collapseFolderTemporaryFolder");

		// copy the files
	if(tempFile = fopen(tempFileName,"r"))	// if you can open the temporary file.
	{
		while(fgets(&copyCommand[l],10240-l,tempFile))
		{
			sprintf(&copyCommand[strlen(copyCommand)-1],"\" c:\\collapseFolderTemporaryFolder");
			cout<<copyCommand<<endl;
			system(copyCommand);
		}

		fclose(tempFile);
		if(remove(tempFileName))
			cerr<<"could not delete file "<<tempFileName<<"."<<endl;
	}
	else
		cerr<<"could not open file "<<tempFileName<<"for reading."<<endl;

	system("PAUSE");
	return 0;
}