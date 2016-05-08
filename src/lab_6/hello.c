#include <stdio.h>
#include <string.h>

int main()
{
	char * str1 = "pipe";
	char * str2 = "lspiper";
	char * str3 = "pip";
	
	printf(strstr(str2,str1));

	return 0;
}
