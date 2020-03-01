/*
 ============================================================================
 Name		: SimpleServer.h
 Author	  : sds
 Copyright   : Copyright (c) 2010-2018 steshenko.d.s@gmail.com
 ============================================================================
 v.1.0.4	-Initial kinda blind version 
 */
#ifndef __SIMPLESERVER_H__
#define __SIMPLESERVER_H__

//  INCLUDES
#include <e32base.h>
#include <e32property.h>
//#include <BatteryChargeCounter.h>//?
#include "batteryobserver.h"	//for battery observer

class CSimpleServer : public CServer2
	{
public:
	CSimpleServer();
	virtual ~CSimpleServer();
	//virtual void StartL();//is it for autostart?
	void StartL(const TDesC& aName);//?

private:
	//void StartL(const TDesC& aName);//?
	virtual CSession2* NewSessionL(const TVersion& aVersion,
			const RMessage2& aMessage) const;
	//
	CBatteryStateObserver* iBatteryStatusObserver;
	CBatteryStateObserver* iBatteryLevelObserver;
	CBatteryStateObserver* iChargingStatusObserver;
	};

#endif  // __SIMPLESERVER_H__
