
from subprocess import Popen, PIPE
import time

counter = 0
while True: 
    c_process = Popen("./oasis_read_ADC", stdin = PIPE, stdout = PIPE)
    outs, errs = c_process.communicate()
    print(outs)
    print("-----------------------------------------", counter)
    counter = counter + 1
    
