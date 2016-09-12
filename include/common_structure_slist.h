#ifndef _COMMON_STRUCTURE_SLIST_H_
#define _COMMON_STRUCTURE_SLIST_H_

#include "common_structure.h"

typedef  struct _SLIST_HEADER
{
    SINGLE_LINK_ENTRY next;
    unsigned short depth;
    unsigned short sequence;
}
SLIST_HEADER,  *PSLIST_HEADER;

#define  SListGetFirstEntry(ListHead)                       (ListHead)->Next.Next
#define  SListGetNextEntry(Entry)                           (Entry)->Next
//#define  SListGetEntryByIndex                               AnscSListSearchEntryByIndex
#define  SListGetDepth(ListHead)                          (ListHead)->Depth


#endif
