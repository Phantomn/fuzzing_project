import sys
import os
from pyradamsa import *
import random
import string

def main(target):
    string_pool = string.ascii_uppercase
    _LEN = random.randint(1, 100)
    data = ""
    
    

    while(1):
        for i in range(_LEN):
            if(len(data) >= 100):
                data = ""
            data += random.choice(string_pool)
        payload = str(target) + " " + str(data)
        os.system(payload)

    return

if __name__ == "__main__":
    main(sys.argv[1])