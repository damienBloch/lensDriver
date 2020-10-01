```
//Below is the SCPI tree of commands that can be used with the Optotune box.
//The part in lower case is optional.
//The case doesn't matter, everything is converted to capital letters before being parsed.
//Units are optional, but only the units present can be used. 
//Only leafs of this tree can be used, e.g. :TEMP:MEASURE? or :SOURCE:CUR 100.
//Commands ending with "?" will return a value.

*IDN? //return identifier for the board. Can be used to see if the board is responsive.
:SYST
    :ERR? // When errors happen, if they can be catched, they will be added to a queue.
	  // This command will pop the first error that happened and return it.
	  // If the board is not responsive at all, it is best to press the reset button and close any software that was trying to communicate with the lens
:TEMPerature //commands related to the temperature regulation of the lens
    :MEASure? //returns the lens temperature in Celsius.
    :PID //commands related to the active temperature pid control.
    	:P? //returns the proportionnal coefficient of the pid.
    	:P <val_P>A/C //sets the proportionnal coefficient of the pid. When the code is uploaded to the board, it will have default value 0.4.
    	:I? //returns the integral coefficient of the pid.
    	:I <val_I>A/C/s //sets the integral coefficient of the pid. When the code is uploaded to the board, it will have default value 0.04.
    	:D? //returns the derivative coefficient of the pid.
    	:D <val_D>S/C*s //sets the integral coefficient of the pid. When the code is uploaded to the board, it will have default value 0.
    	:SETpoint? //returns the setpoint of the pid.
    	:SETpoint <val_setpoint>C //sets the setpoint of the pid. When the code is uploaded to the board, it will have default value 23C.
    	:OUTput?
	:RESet //restart the PID to its initial configuration with an output of 0A. Can be useful to avoid integral windup after the PID has saturated.
	:LIMit
	    :MINimum?
	    :MINimum <val_min>A
	    :MAXimum?
	    :MAXimum <val_max>A
:SOURCE //commands related to the lens coil current source. Changing any parameters of the current source (limits,frequency,range) will force it to constant mode and empty the sequence loaded in the board. 
    :CURrent? //returns the true output current in the lens coil. The value can be different than what is set with CURRENT or ARBITRARY:SEQUENCE if CORRECTION are enabled
    :CURrent <val_current>mA //set target output current. Calling this command forces the current source to be in constant mode.
    :LIMit 
        :MAXimum?
	:MAXimum <val_maximum>mA 
	:MINimum?
	:MINimum <val_minimum>mA
    :RANGE?//not implemented
    :RANGE PM250|PM400 //not implemented. Can be used to change the physical range of the lens from +/-250mA to +/-400mA
    :ARBitrary
        :SEQuence <val_N> //After this function being called, the lens driver expects a sequence <val_current1>\n <val_current2>\n ... <val_currentN>\n that are loaded in the microcontroller SRAM. Loading the sequence forces the current source in constant mode.
	:SEQuence?
	:FREQuency?
	:FREQuency <val_freq>Hz //set the sampling frequency of the sequence
    :MODE? //returns the state of the lens driver
    :MODE CONSTant|ARBitrary //sets the behaviour of the current source.
			     //In constant mode a fixed value is fixed for the lens current (up to thermal corrections) and the trigger is ignored. This is the default state at startup and the default value for the current in this mode is (max+min)/2.
			     //When arbitrary mode is switched on, if the trigger is low, the ouput current is <val_current1>. If the trigger is high, the ouput is <val_currentN>. 
			     //This mode requires a sequence to be loaded first. When the trigger changes from low to high, the board will start output the consecutives <val_current> previously loaded at the frequency :ARB:FREQ. When the trigger changes from high to low, the current output is set back to <val_current1>.
    :CORRection
	:INTensity
	    :INTensity?
	    :FILTINTensity?
	    :STATus? //at start it is enabled
	    :STATus ENAble|DISable
	    :FILTertime?
	    :FILTertime <val_time>s
	    :VOLT2INTensity?
	    :VOLT2INTensity <val_V2I>W/V
	    :INT2CURrent?
	    :INT2CURrent <val_I2C>mA/W
	:TEMPerature
	    :STATus? //not implemented. enabled at start
	    :STATus ENAble|DISable //not implemented
	    :TEMP2CURrent? //return the temperature current compensation coefficient
	    :TEMP2CURrent <val_T2C>mA/C //sets the temperature current compensation coefficient (slope of the equivalent current change when the temperature changes)
```