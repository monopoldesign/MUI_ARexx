#ifndef MAKE_ID
#define MAKE_ID(a,b,c,d) ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif

/* Libraries */
#include <libraries/mui.h>
#include <libraries/gadtools.h> /* for Barlabel in MenuItem */
#include <exec/memory.h>

/* Prototypes */
#include <proto/muimaster.h>
#include <proto/exec.h>
#ifdef __GNUC__
#include <proto/alib.h>
#else
#include <clib/alib_protos.h>
#endif /* __GNUC__ */

#include "LCD-ComGUI.h"

struct ObjApp * CreateApp(void)
{
	struct ObjApp * ObjectApp;

	APTR	GROUP_ROOT_0, GR_grp_1, LA_label_3, obj_aux0, obj_aux1, obj_aux2;
	APTR	obj_aux3;

	if (!(ObjectApp = AllocVec(sizeof(struct ObjApp),MEMF_CLEAR)))
		return(NULL);

	ObjectApp->STR_TX_Receive = NULL;

	LA_label_3 = Label("Received:");

	ObjectApp->TX_Receive = TextObject,
		MUIA_Background, MUII_TextBack,
		MUIA_Frame, MUIV_Frame_Text,
		MUIA_Text_Contents, ObjectApp->STR_TX_Receive,
	End;

	GR_grp_1 = GroupObject,
		MUIA_HelpNode, "GR_grp_1",
		MUIA_Group_Columns, 2,
		Child, LA_label_3,
		Child, ObjectApp->TX_Receive,
	End;

	ObjectApp->STR_Value = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_Value",
		MUIA_String_MaxLen, 4,
	End;

	obj_aux1 = Label2("Value:");

	obj_aux0 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux1,
		Child, ObjectApp->STR_Value,
	End;

	ObjectApp->SL_Value2 = SliderObject,
		MUIA_HelpNode, "SL_Value2",
		MUIA_Frame, MUIV_Frame_Slider,
		MUIA_Slider_Min, 0,
		MUIA_Slider_Max, 100,
		MUIA_Slider_Level, 0,
	End;

	obj_aux3 = Label2("Value2:");

	obj_aux2 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux3,
		Child, ObjectApp->SL_Value2,
	End;

	ObjectApp->BT_Send = SimpleButton("Send ARexx");

	GROUP_ROOT_0 = GroupObject,
		Child, GR_grp_1,
		Child, obj_aux0,
		Child, obj_aux2,
		Child, ObjectApp->BT_Send,
	End;

	ObjectApp->WI_label_0 = WindowObject,
		MUIA_Window_Title, "MUI_ARexx",
		MUIA_Window_ID, MAKE_ID('0', 'W', 'I', 'N'),
		MUIA_Window_SizeGadget, FALSE,
		WindowContents, GROUP_ROOT_0,
	End;

	ObjectApp->App = ApplicationObject,
		MUIA_Application_Author, "M.Volkel",
		MUIA_Application_Base, "MUIAREXX",
		MUIA_Application_Title, "MUI_ARexx",
		MUIA_Application_Version, "$VER: MUI_ARexx V0.1",
		MUIA_Application_Copyright, "(C)2022 M.Volkel",
		MUIA_Application_Description, "ARexx-Test",
		SubWindow, ObjectApp->WI_label_0,
	End;


	if (!ObjectApp->App)
	{
		FreeVec(ObjectApp);
		return(NULL);
	}

	DoMethod(ObjectApp->WI_label_0,
		MUIM_Window_SetCycleChain, ObjectApp->STR_Value,
		ObjectApp->SL_Value2,
		ObjectApp->BT_Send,
		0
		);

	set(ObjectApp->WI_label_0,
		MUIA_Window_Open, TRUE
		);


	return(ObjectApp);
}

void DisposeApp(struct ObjApp * ObjectApp)
{
	MUI_DisposeObject(ObjectApp->App);
	FreeVec(ObjectApp);
}
