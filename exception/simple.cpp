#include <Windows.h>
#include <stdio.h>

void handler()
{
	puts("exception occured!");
}

int main(void)
{
	__try
	{
		puts("try1");
		char* p = NULL;
		printf("%c", *p);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		handler();
	}

	return 0;
}