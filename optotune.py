import numpy as np
import pyvisa
class Optotune:
    def __init__(self,pyvisaResourceManager,instrument):
        self.visa=pyvisaResourceManager.open_resource(instrument)
        self.visa.read_termination="\r\n"
        self.visa.write_termination="\n"
        self.visa.delay=20e-3
        self.baud_rate=115200
    def __del__(self):
        self.visa.close()
    def uploadRamp(self,currents):
        N=len(currents)
        self.visa.write(":SOURCE:ARB:SEQ {}".format(N))
        for value in currents:
            self.visa.write("%.3f" % value)