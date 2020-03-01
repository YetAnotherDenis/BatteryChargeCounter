/*
 * batteryobserver.h
 *
 *  Created on: Mar 23, 2015
 *      Author: Administrator
 *
 *	Mod for BatteryChargeCounter.cpp
 *	by sds on: May 25, 2017
 *	Copyright (c) 2010-2018 steshenko.d.s@gmail.com
 *============================================================================
 *	v.1.0.4	-Initial kinda blind version 
 TODO	-check threads priority
 *
 */

#ifndef BATTERYOBSERVER_H_
#define BATTERYOBSERVER_H_

//  INCLUDES
#include <e32base.h>
#include <e32property.h>
#include <f32file.h>	//fileserver + efsrv.lib
class CBatteryStateObserver : public CActive
	{
	enum
		{
		EPriority = 0
		//TODO check how it comares to server priority wich is some foreground task?
		};
public:
	static CBatteryStateObserver* NewL(const TUid aUid, const TUint32 aKey);
	virtual ~CBatteryStateObserver();
	void WriteToLogL(const TDesC& aText);//TODO If we will use it from main thread or move it to private?
//	void ReadParametrsL();
	//void WriteSettingsInLog();

private:
	CBatteryStateObserver(const TUid aUid, const TUint32 aKey);
	void ConstructL();
	void RunL();
	void DoCancel();
	//void CheckReReadSettings();

private:
	RProperty iProperty;
	const TUid iUid;
	const TUint32 iKey;


	};

#endif /* BATTERYOBSERVER_H_ */
