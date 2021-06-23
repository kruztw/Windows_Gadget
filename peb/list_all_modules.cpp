#include <stdio.h>
#include <Windows.h>

#include "teb32.h"

void ListAllModule()
{
	struct PEB_* peb = (struct PEB_ *)__readfsdword(0x30);
	LIST_ENTRY* listHead = &(peb->Ldr->InMemoryOrderModuleList);

	for (LIST_ENTRY* work = listHead->Flink; work != listHead; work = work->Flink) {
		LDR_DATA_TABLE_ENTRY* entry = CONTAINING_RECORD(work, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		printf("Module %-30ls was loaded, base address is %p\n", entry->BaseDllName.Buffer, entry->DllBase);
	}
}

int main()
{
	ListAllModule();
	getchar();
}
