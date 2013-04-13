//	Copyright (C) 2008, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Folder Collapser.
 *
 *	Folder Collapser is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Folder Collapser is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Folder Collapser.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

const unsigned int MAX_PATH_LENGTH = 10240;
const unsigned int MAX_NAME_LENGTH = 1024;

int main()
{	
	char contentsListName[L_tmpnam];
	char dirCommand[1024] = "dir /s /a:-d-s /b >>";

	FILE *contentsList;
	FILE *sourceFile;
	FILE *destinationFile;

	char sourceFileName[MAX_PATH_LENGTH];
	char destinationFileName[MAX_NAME_LENGTH] = "c:\\collapseFolderTemporaryFolder\\";
	const unsigned int l = strlen(destinationFileName);
	char c;
	char *p;

		// create a file with the contents of the folder and it's subfolders.
	tmpnam(contentsListName);	// create a name for a temporary file and save it in contentsListName.
	strcat(dirCommand,contentsListName);	// complement the dirCommand with the file name.
	system(dirCommand);	// send the command to the system.

		// create destination folder.
	system("md c:\\collapseFolderTemporaryFolder");

		// copy the files
	if(contentsList = fopen(contentsListName,"r"))	// if you can open the contentsList file.
	{
			// use the contentsList file.
		while(fgets(sourceFileName,MAX_PATH_LENGTH,contentsList))	// for each file name in the list.
		{
			for(p = sourceFileName ; *p != '\n' ; ++p)	// find the end of the name.
				;
			*p = '\0';	// replace newline with null.
			while(*--p != '\\')	// find the first backslash from the end.
				;
			++p;	// move to point to the start of the name.
			strncpy(&destinationFileName[l],p,MAX_NAME_LENGTH-l);	// prepare the destination file name.
			if(sourceFile = fopen(sourceFileName,"r"))
			{
				if(destinationFile = fopen(destinationFileName,"w"))
				{
					while((c = fgetc(sourceFile)) != EOF)	// for each character in source file.
						fputc(c,destinationFile);	// copy it to destination file.
					fclose(destinationFile);	// close destination file.
				}
				else
					cerr<<"could not open file "<<destinationFileName<<" for writing."<<endl;	// notify for error.
				fclose(sourceFile);	// close source file.
			}
			else
				cerr<<"could not open file "<<sourceFileName<<" for reading."<<endl;	// notify for error.
		} // end while

			// once you have finished using the contentsList file,
		fclose(contentsList);	// close it
		if(remove(contentsListName))	// and delete it.
			cerr<<"could not delete file "<<contentsListName<<"."<<endl;	// notify on failure to delete.
	}
	else	// if you can't open the contentsList file.
		cerr<<"could not open file "<<contentsListName<<" for reading."<<endl;	// notify for error.

	system("PAUSE");
	return 0;
} // end function main
