#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Uncomment to enable debug print. */
//#define ENABLE_DEBUG

/*
 * brief		: creates printable characters
 * param1[in]	: pointer to destination buffer
 * param2[in]	: pointer to source buffer
 * param3[in]	: source buffer length in bytes
 * return		: destination string length
 */
int hexDump(char *desc, void *addr, int len)
{
	int i, count = 0;
	unsigned char code[4];
	unsigned char *pc = (unsigned char*)addr;
	unsigned char *ptr = calloc(sizeof(char), ((len*3)+2));

	if ((desc == NULL) || (len <= 0))
		return -1;

	for (i = 0; i < len; i++) {
		/* Hex code the specific character. */
		sprintf(code, " %02x", pc[i]);
		strcat(ptr, code);
	}

	/* Terminate the string. */
	*(ptr+(i*strlen(code))+1) = '\0';
#ifdef ENABLE_DEBUG
	/* For debug purpose. */
	printf("ArraySize = %d Construct: %s\n", ((len*3)+2), ptr);
#endif
	sprintf(desc, "%s", ptr);
	count = strlen(ptr)+1;
	free(ptr);
	return count;
}

int main (int argc, char *argv[])
{
	char my_str[] = "1234567890";
	char dest[128];
	int x;
	x = hexDump(dest, &my_str, sizeof (my_str));
	printf("Return count = %d, Data = %s\n", x, dest);
	return 0;
}
