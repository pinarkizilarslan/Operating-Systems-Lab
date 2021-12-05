#include <unistd.h>
#include <stdio.h>

extern int etext, edata;
int globlVar=1;

int main() {

	char c, *s;
	int localVar=6;

	printf("\tpageSize = %u\n", getpagesize());	// Function that returns the pageSize size
	printf("\t&globlVar\t = %p\n", &globlVar);	// Address of the globlVar segment
	printf("\t&localVar\t = %p\n", &localVar);	// Address of the localVar segment
	printf("\t&main()\t\t = %p\n", &main);	// Address of the main
	printf("\ttext-seg end\t = %p\n", &etext);	// Address of the text segment
	printf("\tdata-seg end\t = %p\n", &edata);    // Address of the data segment
	printf("\theap-seg end\t = %p\n\n\n", sbrk(0)); // Address of the current end of the heap
    	
	printf("Enter memory location in hex (start with 0x): ");
	fflush(stdout);	// To move buffered data to console or disk
	scanf("0x%p", &s);	// Memory address is requested
	printf("Reading %p: ", s);
	fflush(stdout);
	c=*s;
	
	printf("%d\n", c);
	printf("Writing %d back to %p: ", c, s);
	fflush(stdout);
	*s = c;
	
	printf("ok\n");
}
