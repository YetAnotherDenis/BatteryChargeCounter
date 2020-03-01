/*
 ============================================================================
 Name		: SimpleServer.cpp
 Author	  : sds
 Copyright   : Copyright (c) 2010-2018 steshenko.d.s@gmail.com

 ============================================================================
 v.1.1.9	FIXED EFileShareAny to EFileWrite
 v.1.1.8	FIXED Use CleanupClosePushL() and CleanupStack::PopAndDestroy()
				  so that fsSession is still closed
					if any of the User::LeaveIfError() functions leave
 v.1.1.7	REFACTORING 	-RFs links moved to global variables 
 so no need to create new one when log writes occurs			 
 v.1.1.5	NEW	-no startup log writes if version.txt presistent 
 v.1.0.8	FIXED	-ServerStarted writed in log before LevelValues
 v.1.0.7	NEW	-ReadParametrsL() moved to batteryobserver.cpp
 v.1.0.4	-Initial kinda blind version
 TODO	-Not really understand where write start/stop
 and how to include observer class
 */
//#include <BatteryChargeCounter.h>
#include <e32base.h>
#include <HWRMPowerStateSDKPSKeys.h>	//for battery observer
#include <batteryobserver.h>	//for battery observer
#include <SimpleServer.h>	//for serverpart
#include <f32file.h>	//fileserver + efsrv.lib
#include <BCC_Constants.h> //MyConstants
//since 1.17
//  Global Variables
//LOCAL_D RFs fsSrvSession;

//1.0.4 44 letters?
//_LIT(KStopTextLine, "Server stopped");

LOCAL_D void ServerWriteToLogL(const TDesC& aText)
	{
	RFs fsSrvSession;
	CleanupClosePushL(fsSrvSession);
	User::LeaveIfError(fsSrvSession.Connect());
	TFileName fn;
	User::LeaveIfError(fsSrvSession.SessionPath(fn));
	TParse p;
	p.Set(fn, NULL,NULL);
	fn = p.Drive();
	fn.Append(KSettingsPath);
	fsSrvSession.MkDirAll(fn);
	fn.Append(_L("version.txt"));
	RFile file;
	CleanupClosePushL(file);
	TInt res = file.Open(fsSrvSession, fn, EFileRead);
	if (KErrNone == res)//
		{
		file.Close();
		}
	else //if version.txt NOT exists
		{
		fn = p.Drive();
		fn.Append(KLogPath);
		//User::LeaveIfError(fs.MkDirAll(fn));//program just closed by herself
		fsSrvSession.MkDirAll(fn);
		fn.Append(KLogName);

		res = file.Create(fsSrvSession, fn, EFileShareAny|EFileWrite);
		if (KErrAlreadyExists == res)
			{
			res = file.Open(fsSrvSession, fn, EFileShareAny|EFileWrite);
			}
		else
			{
			User::LeaveIfError(res);
			}
		//ok we get file about to write timestamp and text in one line
		TBuf<96> textlogline;//44+46+4+fortune?
		TTime CurrDateTime;
		CurrDateTime.HomeTime();
		_LIT( KDateTimeFmt, "%/0%1%/1%2%/2%3%/3\t%-B%:0%J%:1%T%:2%S%:3%+B\t" );
		//46 letters 
		CurrDateTime.FormatL(textlogline, KDateTimeFmt);
		textlogline.Append(aText);
		textlogline.Append(_L("\r\n"));//4 symbols or 2 characters?
		TBuf8<96> buf;//44+46+4+fortune?
		buf.Copy(textlogline);//1.0.4 TODO some kind of textlogline.left(98)?
		TInt FilePosition;
		file.Seek(ESeekEnd, FilePosition);
		file.Write(FilePosition + 1, buf);
		file.Close();
		};//if .. version.txt 
	CleanupStack::PopAndDestroy(&file);
	fsSrvSession.Close();
	CleanupStack::PopAndDestroy(&fsSrvSession);
	}

/////////////
CSimpleServer::CSimpleServer() :
	CServer2(EPriorityStandard)
	{
	ServerWriteToLogL(KStartTextLine);//once
	iBatteryStatusObserver = CBatteryStateObserver::NewL(KPSUidHWRMPowerState,
			KHWRMBatteryStatus);
	iBatteryLevelObserver = CBatteryStateObserver::NewL(KPSUidHWRMPowerState,
			KHWRMBatteryLevel);
	iChargingStatusObserver = CBatteryStateObserver::NewL(KPSUidHWRMPowerState,
			KHWRMChargingStatus);
	}

//////////////
CSimpleServer::~CSimpleServer()
	{
	//try battery
	//delete the observers
	if (iBatteryStatusObserver)
		{
		//iBatteryStatusObserver->WriteToLogL(KStopTextLine);//it never will be the case?
		delete iBatteryStatusObserver;
		iBatteryStatusObserver = NULL;
		}
	if (iBatteryLevelObserver)
		{
		delete iBatteryLevelObserver;
		iBatteryLevelObserver = NULL;
		}
	if (iChargingStatusObserver)
		{
		delete iChargingStatusObserver;
		iChargingStatusObserver = NULL;
		}
	//end battery		
	}

//////////////
/*
 void CSimpleServer::StartL()
 {
 StartL(KServerName);
 }
 */

//////////////
void CSimpleServer::StartL(const TDesC& aName)
	{
	CServer2::StartL(aName);
	}

//////////////	
CSession2* CSimpleServer::NewSessionL(const TVersion&
/*aVersion*/, const RMessage2& /*aMessage*/) const
	{

	return NULL;
	}

