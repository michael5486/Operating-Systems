#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	//Open file
	file = fopen("BACKING_STORE.bin", "rb");
	if (!file)
	{
		printf("Unable to open file");
		return;
	}
	
	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	//Allocate memory
	buffer=(char *)malloc(fileLen+1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                                fclose(file);
		return;
	}

	//Read file contents into buffer
	fread(buffer, fileLen, 1, file);
	
	printf("buffer: %s", buffer);
	
	fclose(file);



	free(buffer);
}