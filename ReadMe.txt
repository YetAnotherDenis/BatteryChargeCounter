Battery Charge Counter - simple solution
for my beloved n97 mini
(c) 2010-2018 steshenko.d.s@gmail.com

This serverapp has no GUI. 
Auto start during OS boot.
Will log all types of battery status events in text file
?\Data\BatteryChargeCounter\BCCLog.txt

- Enumerations for EPSHWRMBatteryLevel(Battery level of device) 
BatteryLevelUnknown Uninitialized or some other error.  
BatteryLevelLevel0 Lowest battery level.  
BatteryLevelLevel1   
BatteryLevelLevel2   
BatteryLevelLevel3   
BatteryLevelLevel4   
BatteryLevelLevel5   
BatteryLevelLevel6   
BatteryLevelLevel7 Highest battery level.
 
- Enumerations for EPSHWRMBatteryStatus(Battery status of device) 
BatteryStatusUnknown Uninitialized or some other error.  
BatteryStatusOk This can also be used during charging.  
BatteryStatusLow Show note to user "Battery low".  
BatteryStatusEmpty Show "recharge battery" note to user.  
 
- Enumerations for EPSHWRMChargingStatus(Charging status of device)
ChargingStatusError Some error has occurred when charger is connected or charging.  
ChargingStatusNotConnected Charger not connected/uninitialized.  
ChargingStatusCharging Device is charging.  
ChargingStatusNotCharging Charger is connected, device not charging.  
ChargingStatusAlmostComplete Charging almost completed.  
ChargingStatusChargingComplete Charging completed.  
ChargingStatusChargingContinued Charging continued after brief interruption.
