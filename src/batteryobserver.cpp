/*
 ============================================================================
 Name		: batteryobserver.cpp
 Author	  : sds
 Copyright   : Copyright (c) 2010-2018 steshenko.d.s@gmail.com
 Description : Exe source file
 ============================================================================
 v.1.1.9	FIXED EFileShareAny to EFileWrite
 v.1.1.8	FIXED Use CleanupClosePushL() and CleanupStack::PopAndDestroy()
				  so that fsSession is still closed
					if any of the User::LeaveIfError() functions leave
 v.1.1.7	REFACTORING 	-RFs links moved to global variables 
			so no need to create new one every time log writes occurs
			NEW	-All ReadSettings and ReRead functionality removed
 v.1.1.2	- reverted to another email
 v.1.0.7	FIXED	-ReadParametrsL() for all three observers 
					 and not for iBatteryStatusObserver only
					 by moving call from SimpleServer.cpp
					 to ConstructL() here
 v.1.0.6	NEW -ReReadSettings.txt at any kind of event
 v.1.0.5	NEW -File ReReadSettings.txt processing added
 v.1.0.4	-Initial kinda blind version 
 TODO	-maybe move fs creation dispose here?
 -some kind of read initial settings function
 then add many TBool private or public properties? to .h file
 -move most of all text messages to LIT instead of L
 */
// My Include Files
#include <f32file.h>	//fileserver + efsrv.lib
#include <HWRMPowerStateSDKPSKeys.h>	//for battery observer
#include "batteryobserver.h"	//for battery observer
#include <BCC_Constants.h> //MyConstants

//since 1.17
//  Global Variables
//LOCAL_D RFs fsReadSession;
//LOCAL_D RFs fsReReadSession;
//LOCAL_D RFs fsLogSession;

/////////////////////////////////////////////////
//try add battery observer
/////////////////////////////////////////////////

/////////////////////////////////////////////////
CBatteryStateObserver::CBatteryStateObserver(const TUid aUid,
		const TUint32 aKey) :
	CActive(EPriority), iUid(aUid), iKey(aKey)
	{
	}

/////////////////////////////////////////////////
CBatteryStateObserver* CBatteryStateObserver::NewL(const TUid aUid,
		const TUint32 aKey)
	{
	CBatteryStateObserver* self =
			new (ELeave) CBatteryStateObserver(aUid, aKey);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

/////////////////////////////////////////////////
void CBatteryStateObserver::ConstructL()
	{
	User::LeaveIfError(iProperty.Attach(iUid, iKey));
	CActiveScheduler::Add(this);
	// initial subscription and process current property value
	//since 1.1.7
	//RunL();
	iProperty.Subscribe(iStatus);
	SetActive();
	}

/////////////////////////////////////////////////	
CBatteryStateObserver::~CBatteryStateObserver()
	{
	Cancel();
	iProperty.Close();
	}

/////////////////////////////////////////////////	
void CBatteryStateObserver::DoCancel()
	{
	iProperty.Cancel();
	}

/////////////////////////////////////////////////
void CBatteryStateObserver::WriteToLogL(const TDesC& aText)
	{
	RFs fsLogSession;
	CleanupClosePushL(fsLogSession);
	User::LeaveIfError(fsLogSession.Connect());
	TFileName fn;
	User::LeaveIfError(fsLogSession.SessionPath(fn));
	TParse p;
	p.Set(fn, NULL,NULL);
	fn = p.Drive();
	fn.Append(KLogPath);
	//User::LeaveIfError(fs.MkDirAll(fn));//program just closed by herself
	fsLogSession.MkDirAll(fn);
	fn.Append(KLogName);
	RFile file;
	CleanupClosePushL(file);
	TInt res = file.Create(fsLogSession, fn, EFileShareAny|EFileWrite);
	if (KErrAlreadyExists == res)
		{
		res = file.Open(fsLogSession, fn, EFileShareAny|EFileWrite);
		//		console->Write(_L("FileExists\n"));
		}
	else
		{
		User::LeaveIfError(res);
		};
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
	CleanupStack::PopAndDestroy(&file);
	fsLogSession.Close();
	CleanupStack::PopAndDestroy(&fsLogSession);
	}



/////////////////////////////////////////////////
void CBatteryStateObserver::RunL()
	{
	//resubscribe before processing new value to prevent missing updates
	iProperty.Subscribe(iStatus);
	SetActive();

	switch (iKey)
		{
		/////////////
		case KHWRMBatteryLevel:
			{
			//KHWRMBatteryLevel updated, do something...
			//since 1.1.7
			//CheckReReadSettings();
			TInt LevelValue;
			iProperty.Get(LevelValue);
			if (LevelValue == EBatteryLevelUnknown) // && (iBatteryLevelUnknown))
				{
				WriteToLogL(KBatteryLevelUnknown);
				};

			if (LevelValue == EBatteryLevelLevel0) // && (iBatteryLevelLevel0))
				{
				WriteToLogL(KBatteryLevelLevel0);
				};

			if (LevelValue == EBatteryLevelLevel1) // && //(iBatteryLevelLevel1))
				{
				WriteToLogL(KBatteryLevelLevel1);
				};

			if (LevelValue == EBatteryLevelLevel2) //&& (iBatteryLevelLevel2))
				{
				WriteToLogL(KBatteryLevelLevel2);
				};

			if (LevelValue == EBatteryLevelLevel3) //&& (iBatteryLevelLevel3))
				{
				WriteToLogL(KBatteryLevelLevel3);
				};

			if (LevelValue == EBatteryLevelLevel4) //&& (iBatteryLevelLevel4))
				{
				WriteToLogL(KBatteryLevelLevel4);
				};

			if (LevelValue == EBatteryLevelLevel5) //&& (iBatteryLevelLevel5))
				{
				WriteToLogL(KBatteryLevelLevel5);
				};

			if (LevelValue == EBatteryLevelLevel6) //&& (iBatteryLevelLevel6))
				{
				WriteToLogL(KBatteryLevelLevel6);
				};

			if (LevelValue == EBatteryLevelLevel7) //&& (iBatteryLevelLevel7))
				{
				WriteToLogL(KBatteryLevelLevel7);
				};
			break;
			}//case

			/////////////	
		case KHWRMBatteryStatus:
			{
			//KHWRMBatteryStatus updated, do something...
			//since 1.1.7
			//CheckReReadSettings();
			TInt StatusValue;
			iProperty.Get(StatusValue);
			if (StatusValue == EBatteryStatusUnknown)
					//&& (iBatteryStatusUnknown))
				{
				WriteToLogL(KBatteryStatusUnknown);
				};

			if (StatusValue == EBatteryStatusOk) //&& (iBatteryStatusOk))
				{
				WriteToLogL(KBatteryStatusOk);
				};

			if (StatusValue == EBatteryStatusLow) //&& (iBatteryStatusLow))
				{
				WriteToLogL(KBatteryStatusLow);
				//CBatteryStateObserver::CheckReReadSettings();//test
				};

			if (StatusValue == EBatteryStatusEmpty)
				{
				//if (iBatteryStatusEmpty)
				//	{
				WriteToLogL(KBatteryStatusEmpty);
				//CBatteryStateObserver::WriteToLogL(KStopTextLine);
				//TODO Initiate correct server shutdown?
				//	};
				};
			break;
			}//case

			/////////////
		case KHWRMChargingStatus:
			{
			//KHWRMChargingStatus updated, do something...
			//since 1.1.7
			//CheckReReadSettings();
			TInt ChrgValue;
			iProperty.Get(ChrgValue);
			if (ChrgValue == EChargingStatusError) //&& (iChargingStatusError))
				{
				WriteToLogL(KChargingStatusError);
				};

			if (ChrgValue == EChargingStatusNotConnected)
					//&& (iChargingStatusNotConnected))
				{
				WriteToLogL(KChargingStatusNotConnected);
				};

			if (ChrgValue == EChargingStatusCharging)
					//&& (iChargingStatusCharging))
				{
				WriteToLogL(KChargingStatusCharging);
				};

			if (ChrgValue == EChargingStatusNotCharging)
					//&& (iChargingStatusNotCharging))
				{
				WriteToLogL(KChargingStatusNotCharging);
				};

			if (ChrgValue == EChargingStatusAlmostComplete)
					//&& (iChargingStatusAlmostComplete))
				{
				WriteToLogL(KChargingStatusAlmostComplete);
				};

			if (ChrgValue == EChargingStatusChargingComplete)
					//&& (iChargingStatusChargingComplete))
				{
				WriteToLogL(KChargingStatusChargingComplete);
				};

			if (ChrgValue == EChargingStatusChargingContinued)
					//&& (iChargingStatusChargingContinued))
				{
				WriteToLogL(KChargingStatusChargingContinued);
				};

			break;
			}
		default:
			break;
		}//switch?
	}

///////////////since 1.1.7
//void CBatteryStateObserver::WriteSettingsInLog()
//	{
//	
//	}//void void WriteSettingsInLog()


//that's all folks
