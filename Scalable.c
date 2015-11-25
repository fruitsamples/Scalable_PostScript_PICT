/*	File:		Template.c	Contains:	Scalable PostScript PICT:  Shows how you can use the PostScript clip in				combination with the QuickDraw clipping region to make PostScript code that				scales at run-time.  Has some limitations, but a useful technique.	Written by: 		Copyright:	Copyright � 1984-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				7/26/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				*/#include "PrintComments.h"#include<Quickdraw.h>#include<Fonts.h>#include<Windows.h>#include<TextEdit.h>#include<Dialogs.h>#include<Menus.h>#include<Scrap.h>PicHandle DoPicture(void);Handle StuffInHandle(const Str255 theString);/*------ main ----------------------------------------------------------------------------*/PicHandle myPicture;void main(){	GrafPort myPort;	InitGraf(&qd.thePort);	OpenPort(&myPort);	InitFonts();	InitWindows();	InitMenus();	TEInit();	InitDialogs(nil);	InitCursor();  	myPicture = DoPicture();   				// make and publish our picture} /* main *//*------ DoPicture ----------------------------------------------------------------------*/PicHandle DoPicture (void){	Rect myRect;	PicHandle thePicHandle;	GrafPort myPort;	long scrapResult;	unsigned long thePictureSize;	short theFont, textSize = 14;	Handle myHandle;		const Str255 myString = 	     "\pclippath pathbbox 4 copy moveto lineto 4 1 roll exch moveto exch lineto stroke\r";	OpenPort(&myPort);	SetRect(&myRect,0,0,200,200);	thePicHandle = OpenPicture(&myRect);	ClipRect(&myRect);		MoveTo(22,22);	LineTo(55,55);	LineTo(58,22);	LineTo(22,58);		GetFNum ("\pTimes", &theFont);	TextFont (theFont);	TextSize (textSize);		SetRect(&myRect,50,50,100,150);	ClipRect(&myRect);		MoveTo(0,0);	LineTo(0,0);				// flush the QuickDraw changes to the clip		PicComment(PostScriptBegin,0,NULL);	myHandle = StuffInHandle(myString);	PicComment(PostScriptHandle,myString[0],myHandle);	DisposeHandle(myHandle);	PicComment(PostScriptEnd,0,NULL); 	SetRect(&myRect,0,0,200,200);	ClipRect(&myRect);		MoveTo(100,50);	DrawString("\pA wonderful test");		ClosePicture();	ClosePort(&myPort);		thePictureSize = GetHandleSize((Handle)thePicHandle);	ZeroScrap();	HLock((Handle)thePicHandle);	scrapResult = PutScrap(GetHandleSize((Handle)thePicHandle),'PICT',StripAddress(*thePicHandle));	HUnlock((Handle)thePicHandle);	KillPicture(thePicHandle);			// don't forget to clean up after yourself		return thePicHandle;}  /* InitPicture *//*------ StuffInHandle ----------------------------------------------------------------------*/Handle StuffInHandle(const Str255 theString){	Handle theHandle = NewHandle(theString[0]);	HLock(theHandle);	BlockMove((Ptr)&theString[1],*theHandle,theString[0]);	HUnlock(theHandle);	return(theHandle);}