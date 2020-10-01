import numpy as np
import matplotlib.pyplot as plt
import pyvisa
import time

from optotune import Optotune

opt = Optotune(pyvisa.ResourceManager(),"ASRL9::INSTR")

current_setpoint = 102.5 # mA
temperature_setpoint = 24 # degrees C
temperature_correction = True
intensity_correction = False


opt.visa.write("SOURCE:CUR {}".format(current_setpoint))
opt.visa.write(":TEMP:PID:SET {}}".format(temperture_setpoint))

if temperature_correction:
    opt.visa.write(":SOURCE:CORR:TEMP:STAT ENA")
else:
    opt.visa.write(":SOURCE:CORR:TEMP:STAT DIS")

if intensity_correction:
    opt.visa.write(":SOURCE:CORR:INT:STAT ENA")
else:
    opt.visa.write(":SOURCE:CORR:INT:STAT DIS")



