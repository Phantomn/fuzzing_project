import os
import random
import string
import subprocess
import time

MAX_INPUT_SIZE = 256
NUM_ITERATIONS = 10
OUT_DIR = "outputs"

def generate_input():
    return ''.join(random.choices(string.ascii_uppercase + string.digits, k=MAX_INPUT_SIZE))

def main(target):
    if not os.path.exists(target):
        print("Target executable does not exist!")
        return

    if not os.path.exists(OUT_DIR):
        os.makedirs(OUT_DIR)

    for i in range(NUM_ITERATIONS):
        input_data = generate_input()
        out_file = os.path.join(OUT_DIR, f"output_{i}.txt")

        with open(out_file, "w") as f_out:
            proc = subprocess.Popen([target], stdin=subprocess.PIPE, stdout=f_out, stderr=f_out)
            try:
                proc.communicate(input_data.encode(), timeout=5)
            except subprocess.TimeoutExpired:
                proc.kill()
                f_out.write("\n-- Timeout --")

        if proc.returncode != 0:
            print(f"Crash on iteration {i} with input: {input_data}")

if __name__ == "__main__":
    executable_path = "./bof"  # replace with your target executable
    main(executable_path)
