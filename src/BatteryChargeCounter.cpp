/*
 ============================================================================
 Name		: BatteryChargeCounter.cpp
 Author	  : sds
 Copyright   : Copyright (c) 2010-2017 steshenko.d.s@gmail.com
 Description : Exe source file
 ============================================================================
 v.1.1.2	NEW	-in pkg file set all txt files source as sis folder
				 and moved them there
 v.1.0.5	NEW	-KServerName changed
 v.1.0.4	TODO	-add battery observer class?
 -some length check in buf.Copy in WriteToLogL function
 -remove COEUTILS since it makes app weird exit 
 -add some backup function, in .pkg? to save/restore log file
 v.1.0.3	TODO	-So, maybe make fs.Connect() once per srv start? 
 */
//  Include Files  
#include "BatteryChargeCounter.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>	// Console
// My Include Files
#include "SimpleServer.h"	//for serverpart
#include <BCC_Constants.h> //MyConstants
//#include "SimpleServer.cpp"	//for serverpart
//  Constants
//_LIT(KTextConsoleTitle, "Console");
//_LIT(KTextFailed, " failed, leave code = %d");
//_LIT(KTextPressAnyKey, " [press any key]\n");


//  Global Variables
//LOCAL_D CConsoleBase* console; // write all messages to this

//  Local Functions

LOCAL_C void MainL()
	{
	// add your program code here, example code below
	//
		CSimpleServer* server = new (ELeave) CSimpleServer();
		CleanupStack::PushL(server);
		server->StartL(KServerName);
		CActiveScheduler::Start();
		CleanupStack::PopAndDestroy(server);
	//
	//	console->Write(_L("test output\n"));
	}

LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	MainL();

	// Delete active scheduler
	CleanupStack::PopAndDestroy(scheduler);
	}

//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();\

	/*
	 // Create output console
	 TRAPD(createError, console = Console::NewL(KTextConsoleTitle, TSize(
	 KConsFullScreen, KConsFullScreen)));
	 if (createError)
	 return createError;
	 */
	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());
	/*
	 if (mainError)
	 console->Printf(KTextFailed, mainError);
	 console->Printf(KTextPressAnyKey);
	 console->Getch();

	 delete console;
	 */

	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}

