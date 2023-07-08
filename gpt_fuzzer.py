import random
import string

def generate_input(length):
    # Generate a string of random characters
    return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(length))

def test_target(input):
    try:
        # Run the target function with the generated input
        target_function(input)
    except Exception as e:
        # If an exception is raised, log the input and the exception
        print(f'Input: {input}')
        print(f'Exception: {str(e)}')

def fuzzer(iterations, input_length):
    for _ in range(iterations):
        input = generate_input(input_length)
        test_target(input)

# Run the fuzzer
fuzzer(10000, 50)