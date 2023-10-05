import itertools
import random
import sys
import timeit
from matplotlib import pyplot as plt

def BruteForce_Sorting(input_size, timeout):
    input_data = [random.randrange(1, 100) for i in range(input_size)]
    print("Input: ", input_data)

    start_time = timeit.default_timer()

    print("waiting for ouput ...")
    for p in itertools.permutations(input_data):
        if all(p[i] <= p[i + 1] for i in range(len(p) - 1)) and (timeit.default_timer() - start_time) < timeout:
            print("Output: ", list(p))
            return timeit.default_timer() - start_time

    # If the timeout is reached and no sorted permutation is found
    print("Time over - Execution terminated.")
    return float('inf')



if __name__ == "__main__":
    input_size = 10
    timeout = 1 * 60  # 5 minutes = 300 seconds
    execution_times=[]
    input_sizes = range(1,11)
    for input_size in input_sizes:
        print(f"Running with input size {input_size}...")
        execution_time = BruteForce_Sorting(input_size,timeout) # call funcion with different input size
        execution_times.append(execution_time)

        plt.plot(input_sizes, execution_times, marker='o')
        plt.xlabel('Input Size')
        plt.ylabel('Execution Time (seconds)')
        plt.title('Execution Time vs. Input Size')
        plt.grid(True)
        plt.show()