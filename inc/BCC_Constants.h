/*
 * BCC_Constants.h
 Author	  : sds
 Copyright   : Copyright (c) 2010-2018 steshenko.d.s@gmail.com
 ============================================================================
 */

#ifndef BCC_CONSTANTS_H_
#define BCC_CONSTANTS_H_
// My Constants
_LIT(KStartTextLine, "Server started\tBatteryChargeCounter v.1.1.9");
_LIT(KServerName, "BatteryChargeCountServer");
_LIT(KLogPath, "\\Data\\BatteryChargeCounter\\");
_LIT(KSettingsPath, "\\Data\\BatteryChargeCounter\\Settings\\");
_LIT(KLogName, "BCCLog.txt");
_LIT(KReReadFileName, "ReReadSettings.txt");
_LIT(KReReadNewFileName, "ReReadSettings_Done.txt");
//since 1.1.7
_LIT(KFileExtension, ".txt");

//- Enumerations for EPSHWRMBatteryLevel(Battery level of device) 
_LIT(KBatteryLevelUnknown, "BatteryLevelUnknown");
//Uninitialized or some other error.
_LIT(KBatteryLevelLevel0, "BatteryLevelLevel0");
//Lowest battery level.
_LIT(KBatteryLevelLevel1, "BatteryLevelLevel1");
_LIT(KBatteryLevelLevel2, "BatteryLevelLevel2");
_LIT(KBatteryLevelLevel3, "BatteryLevelLevel3");
_LIT(KBatteryLevelLevel4, "BatteryLevelLevel4");
_LIT(KBatteryLevelLevel5, "BatteryLevelLevel5");
_LIT(KBatteryLevelLevel6, "BatteryLevelLevel6");
_LIT(KBatteryLevelLevel7, "BatteryLevelLevel7");
//Highest battery level.

//- Enumerations for EPSHWRMBatteryStatus(Battery status of device) 
_LIT(KBatteryStatusUnknown, "BatteryStatusUnknown");
//Uninitialized or some other error.
_LIT(KBatteryStatusOk, "BatteryStatusOk");
//This can also be used during charging.
_LIT(KBatteryStatusLow, "BatteryStatusLow");
//Show note to user "Battery low".
_LIT(KBatteryStatusEmpty, "BatteryStatusEmpty");
//BatteryStatusEmpty Show "recharge battery" note to user.

//- Enumerations for EPSHWRMChargingStatus(Charging status of device)
_LIT(KChargingStatusError, "ChargingStatusError");
//Some error has occurred when charger is connected or charging.  
_LIT(KChargingStatusNotConnected, "ChargingStatusNotConnected");
//Charger not connected/uninitialized.
_LIT(KChargingStatusCharging, "ChargingStatusCharging");
//Device is charging.
_LIT(KChargingStatusNotCharging, "ChargingStatusNotCharging");
//Charger is connected, device not charging.
_LIT(KChargingStatusAlmostComplete, "ChargingStatusAlmostComplete");
//Device is charging.
_LIT(KChargingStatusChargingComplete, "ChargingStatusChargingComplete");
//Charging completed.
_LIT(KChargingStatusChargingContinued, "ChargingStatusChargingContinued");
//Charging continued after brief interruption.
//

#endif /* BCC_CONSTANTS_H_ */
