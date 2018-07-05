#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fpin, *fpout;
	int count, temp;
	char buf[BUFSIZ];

	if(argc < 3) 
	{
		fprintf(stderr, "Usage : fcopy file1 file2\n");
		return -1;
	}
	
	if((fpin = fopen(argv[1], "r")) == NULL)
	{
		perror(argv[1]);
		return -1;
	}
//	printf("file number fpin = %d\n", fpin->_fileno);
			
	if((fpout = fopen(argv[2], "w")) == NULL)
	{
		perror(argv[2]);
		return -1;
	}

	while((count = fread(buf, sizeof(char), BUFSIZ, fpin)) > 0)
		fwrite(buf, sizeof(char), count, fpout);

	fclose(fpin);
	fclose(fpout);
	
	return 0;
}

