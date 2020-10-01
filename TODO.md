* low pass filter the temperature read on the optotune sensor before using it for the current compensation
  This would prevent the 0.0625 temperature bit noise to be transmitted in the current
* analogue inout B is not currently programmed/used. Can be programmed as an analgue input for ramps
* ADC for the intensity scaling. It should map 0V to 0b and 10V to 2**16, but it is not the case.
* Test analogue input functionnalities
* commands to switch on/off intensity and temperature compensation
* programm the ethernet chip
* Fix python script crashing when streaming data from the lens. It seems to be an issue when a lot of measures are asked from the lens and python misses a couple and stopped. The lens is still working in backrground so not an issue with the driver itself.
* Figure out why sometimes the lens temperature read through the lens driver takes random values. It could be that the Dsub cablr is not optimal and there are some signal corruption. 
* Measure temperature drift with the atoms. Fix the temperature for a long time and see where the cloud is. Then change temperature and see what change in the current must be applied to have the cloud back at the same place.
* Measure thermal lensing parameters by an other way. For example we can look at what the change in waist is after thermalisation time. That would give us one of the two coefficients (mA/W). 
  Then we could measure the low pass filter timescale by measuring the 90% rise time or a similar value. 
* The beam waist fitted by the camera depends of the intensity level, so it is difficult to have a reliable measure for two very different intensities.
* Measure the cloud displacement per milliamps. If the sequence is stable, this can be done by transporting the cloud to a different current value and see where the cloud goes.