#ifndef GUI_FILE_H
#define GUI_FILE_H

/* Types */
#include <exec/types.h>
struct ObjApp
{
	APTR	App;
	APTR	WI_label_0;
	APTR	TX_Receive;
	APTR	STR_Value;
	APTR	SL_Value2;
	APTR	BT_Send;
	char *	STR_TX_Receive;
};


extern struct ObjApp * CreateApp(void);
extern void DisposeApp(struct ObjApp *);

#endif
