/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/
#ifndef banksH
#define banksH
/******************************************************************************/
typedef struct _BANK {
	struct _BANK *next;
	S16 type;
    S16 bank;
    S32 org;
    S32 maxsize;
	U8 *buffer,*ptr,*end;
    char *label;
} BANK;

enum _BANK_TYPE {
	BANKTYPE_RAM,
	BANKTYPE_ROM,
	BANKTYPE_CHR,

	BANKTYPE_TOTAL,
};
/******************************************************************************/
#define BANK_OFFSET(bank) GET_BUF_OFFSET((bank)->buffer,(bank)->ptr)
#define BANK_OFFSET_OF(bank,ptr) GET_BUF_OFFSET((bank)->buffer,ptr)
#define BANK_REMAINING(bank,ptr) GET_BUF_OFFSET(ptr,(bank)->end)
#define MAX_BANKCOUNT	4096
#define MAX_BANKSIZE	65536
/******************************************************************************/
extern char szPadding[65],*szPadPtr;
extern int bankCounts[BANKTYPE_TOTAL];
extern BANK *banks,*bankPtr,*curBank,ramBank;       

extern S32 bankSizes[BANKTYPE_TOTAL];
extern char *szBankTypes[];
/******************************************************************************/
BOOL 	FASTCALL InitBanks(void);
void 	FASTCALL FreeBanks(void);
BANK *	FASTCALL FindBank(char *label);
void 	FASTCALL SetBank(S16 type, char *label);


#define CheckCurBank()            \
{                                 \
	if(!curBank)                  \
    	fatal(FTL_NOACTIVEBANK);  \
}
#define CheckRomBank()            \
{                                 \
	if(!curBank)                                \
    	fatal(FTL_NOACTIVEBANK);                \
	if(curBank->type != BANKTYPE_ROM)           \
    	fatal(FTL_NOTROMBANK,curBank->label);   \
}
#define CheckChrBank()                          \
{                                               \
	if(!curBank)                                \
    	fatal(FTL_NOACTIVEBANK);                \
	if(curBank->type != BANKTYPE_CHR)           \
    	fatal(FTL_NOTCHRBANK,curBank->label);   \
}


void 	FASTCALL LabelBank(char *label);
  
void 	FASTCALL AlignCode(int align);
S32 	FASTCALL GetBankOffset(void);
S32 	FASTCALL GetBankSpace(void);

void 	FASTCALL BankWrite(U8 *data, S32 size);
void 	FASTCALL BankFill(U8 c, S32 size);
void 	FASTCALL BankSeekFwd(S32 size);
void 	FASTCALL BankSeek(S32 dest);
void 	FASTCALL BankSeekIntVect(S32 dest);
void 	FASTCALL BankPutB(S8 code);
void 	FASTCALL BankPutW(S16 code);
void 	FASTCALL BankWriteIntVect(S16 code);
void 	FASTCALL BankPutL(S32 code);

U32 	FASTCALL CountBanksize(int type);
void 	FASTCALL FWriteBanks(int type, FILE *f);

BOOL 	FASTCALL IncBin(char *filename, S32 maxsize);
char    FASTCALL GetPadChar(void);

U32 	FASTCALL GetBankIndex(BANK *bank, int banksize);

U32      GetBankBinOffset(BANK *bank);
long     GetBankBinLength(BANK *bankOfPtr, U8 *ptr, BANK *bankSpan);
/******************************************************************************/
#endif
/******************************************************************************/
