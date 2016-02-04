/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/
#ifndef prepbaseH
#define prepbaseH
/******************************************************************************/

/******************************************************************************/
typedef struct {
	char *label;
	char *definition;
} DEFINE;
#define DEFSET_SIZE		32

typedef struct _ENUMCLASS {
	struct _ENUMCLASS *prev;
	char *label;
	PLIST *defList,*defListPtr;
} ENUMCLASS;

/******************************************************************************/
extern PLIST *defList,*defListPtr;
extern ENUMCLASS *enumClasses;
extern BOOL USE_DEFS;
/******************************************************************************/
BOOL FASTCALL AddDefine(char *label, char *definition);
BOOL FASTCALL AddEnum(char *enumclass, char *label, int index);
BOOL FASTCALL DelDefine(char *label);
DEFINE *FASTCALL FindDefine(PLIST *list, char *label);
BOOL FASTCALL HandleMacros(char *label);
/******************************************************************************/
#endif                                      
/******************************************************************************/
