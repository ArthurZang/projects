#include "common_structure_slist.h"

void SListHeaderInit(PSLIST_HEADER pSListHead)
{
	pSListHead->next.next = NULL;
	pSListHead->depth = 0;
}

unsigned short  SListGetDepth(PSLIST_HEADER pSListHead)
{
	return pSListHead->depth;
}

PSINGLE_LINK_ENTRY SListGetFirstEntry(PSLIST_HEADER pSListHead)
{
	return pSListHead->next.next;
}

PSINGLE_LINK_ENTRY SListGetLastEntry(PSLIST_HEADER pSListHead)
{
	PSINGLE_LINK_ENTRY pTempEntry;

	pTempEntry = &(pSListHead->next);
	while(pTempEntry->next){
		pTempEntry = pTempEntry->next;
	}
	return pTempEntry;
}

void SListPushEntry(PSLIST_HEADER pSListHead, PSINGLE_LINK_ENTRY pEntry)
{
	pEntry->next = pSListHead->next.next;
	pSListHead->next.next = pEntry;
	pSListHead->depth++;
}

void SListPushEntryAtBack(PSLIST_HEADER pSListHead, PSINGLE_LINK_ENTRY pEntry)
{
	PSINGLE_LINK_ENTRY pTempEntry;

	pTempEntry = SListGetLastEntry(pSListHead);
	pTempEntry->next = pEntry;
	pEntry->next = NULL;
	pSListHead->depth++;
}


unsigned char SListPopEntryByLink(PSLIST_HEADER pSListHead, PSINGLE_LINK_ENTRY pEntry)
{
	PSINGLE_LINK_ENTRY pTempEntry;

	pTempEntry = &(pSListHead->next);
	while(pTempEntry){
		if(pTempEntry->next==pEntry){
			pTempEntry->next = pEntry->next;
			pSListHead->depth--;
			return 1;
		}
		pTempEntry = pTempEntry->next;
	}
	return 0;
}

void SListReplaceEntry(PSLIST_HEADER pSListHead, PSINGLE_LINK_ENTRY pNewEntry, PSINGLE_LINK_ENTRY pOldEntry)
{
	PSINGLE_LINK_ENTRY pTempEntry;

	pTempEntry = &(pSListHead->next);
	while(pTempEntry){
		if(pTempEntry->next == pOldEntry){
			pTempEntry->next = pNewEntry;
			pNewEntry->next = pOldEntry->next;
			return;
		}
		pTempEntry = pTempEntry->next;
	}
}



PSINGLE_LINK_ENTRY SListGetEntryByIndex(PSLIST_HEADER pSListHead, unsigned short index)
{
	PSINGLE_LINK_ENTRY pTempEntry;
	unsigned short i;

	if(index > pSListHead->depth)
		return NULL;

	pTempEntry = &(pSListHead->next);
	for(i=0; i<index; i++){
		if(pTempEntry)
			pTempEntry = pTempEntry->next;
		
	}
	return pTempEntry;
}




void SListPushEntryByIndex(PSLIST_HEADER pSListHead, PSINGLE_LINK_ENTRY pEntry, unsigned short index)
{
	PSINGLE_LINK_ENTRY pTempEntry;
	unsigned short i;
	
	if(index >= pSListHead->depth)
		SListPushEntryAtBack(pSListHead, pEntry);

	for(i=0; i<index; i++)
		pTempEntry = pTempEntry->next;

	pEntry->next = pTempEntry->next;
	pTempEntry->next = pEntry;
	pSListHead->depth++;
}


