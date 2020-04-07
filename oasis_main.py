
# OASIS SW version 0.1
# For use with parallel ADC board REV. 1 
# a compiled C-code file "oasis_read_ADC" must be available in the same project folder. 

# This script calls the lower level C code and returns a variable "outs" containing raw data
# out from the ADS8422 ADC. Each 16-bit data sample is presented as 8-bit integer. 

from subprocess import Popen, PIPE 
import time

counter = 0
while True: 
    c_process = Popen("./oasis_read_ADC", stdin = PIPE, stdout = PIPE)
    outs, errs = c_process.communicate()
    print(outs)
    print("-----------------------------------------", counter)
    counter = counter + 1
    
