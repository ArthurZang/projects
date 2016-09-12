#ifndef _COMMON_STRUCTURE_H_
#define _COMMON_STRUCTURE_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct _SINGLE_LINK_ENTRY
{
	struct _SINGLE_LINK_ENTRY *next;
}SINGLE_LINK_ENTRY, *PSINGLE_LINK_ENTRY;

typedef  struct _DOUBLE_LINK_ENTRY
{
    struct  _DOUBLE_LINK_ENTRY*     next;
    struct  _DOUBLE_LINK_ENTRY*     last;
}
DOUBLE_LINK_ENTRY,  *PDOUBLE_LINK_ENTRY;

typedef  struct _DLIST_HEADER
{
    DOUBLE_LINK_ENTRY heads;
    unsigned short depth;
    unsigned short sequence;
}
DLIST_HEADER,  *PDLIST_HEADER;


#define  ACCESS_CONTAINER(address, type, field)     \
         ((type*)((PCHAR)(address) - (ULONG)(&((type*)0)->field)))
#define  ACCESS_FIELD_OFFSET(type, field)           \
         (ULONG)(&((type*)0)->field)


#endif



