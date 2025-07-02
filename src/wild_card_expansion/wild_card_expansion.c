#include <stdio.h>
#include <dirent.h>

int main (void) {
	struct dirent *pDirent;
	DIR *pDir;
	char	*var = ".";

	pDir = opendir (var);
	if (pDir == NULL) {
		printf ("Cannot open directory '%s'\n", var);
		return 1;
	}
	while ((pDirent = readdir(pDir)) != NULL) {
		if (strncmp(pDirent->d_name, "c", 1) == 0)
			printf ("[%s]\n", pDirent->d_name);
	}
	closedir (pDir);
	return 0;
}
