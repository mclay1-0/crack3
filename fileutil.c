#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.

// Constant
const int CAPACITY = 5;

// Initial allocation
int cap = CAPACITY;

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size) {
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	

	// TODO
	// Allocate memory for an array of strings (arr).
	char ** arr = malloc(CAPACITY * sizeof(char*));
	*size = 0;
	char line[1000];
	// Read the file line by line.
	while (!feof(in)) {
	//   Trim newline.
		char *newLine = strchr(line, '\n');
    	if (newLine != NULL) {
        	*newLine = '\0';
    	}
	//   Expand array if necessary (realloc).
		if (*size == cap) {
			cap += CAPACITY;
			arr = realloc(arr, cap * sizeof(char*));
		}
        fgets(line, 1000, in);
	//   Allocate memory for the string (str).
		int length = strlen(line);
		arr[*size] = malloc((length + 1) * sizeof(char*));
	//   Copy each line into the string (use strcpy).
		strcpy(arr[*size], line);
	//   Attach the string to the large array (assignment =).
		(*size)++;
	}
	// Close the file.
	fclose(in);
	
	// Return pointer to the array of strings.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size) {
	for (int i = 0; i < size; i++) {
		if (strstr(lines[i], target) != NULL) {
			return lines[i];
		}
	}
	return NULL;
}

char * linearSearchAA(char *target, char **lines, int size) {
	for (int i = 0; i < size; i++) {
		if (strstr(lines[i], target) == 0) {
			return lines[i];
		}
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size) {
	for (int i = 0; i < size; i++) {
		free(arr[i]);
	}
	free(arr);
}