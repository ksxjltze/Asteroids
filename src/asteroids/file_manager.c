#include "file_manager.h"

FILE* Asteroids_Open_File(const char* path, const char* mode)
{
	FILE* fptr = NULL;
	errno_t err = fopen_s(&fptr, path, mode);
	if (err == 0)
		printf("File %s opened.\n", path);
	else
		printf("File %s not opened.\n", path);

	return fptr;

}

void Asteroids_Close_File(FILE* file)
{
	errno_t err = fclose(file);
	if (err == 0)
		printf("File closed.\n");
	else
		printf("File not closed.\n");

}