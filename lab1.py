import numpy as np
import timeit

def f(i,j):
    return .5 +((i+j)%50 - 30)/50.0

def init():
    W1 = np.zeros((4000, 50176))
    x1 = np.zeros((50176, 1))
    
    for j in range(50176):
        x1[j,0] = f(j,0)
        for i in range(4000):
            W1[i,j] = f(i,j)

    W2 = np.zeros((1000,4000))
    for j in range(4000):
        for i in range(1000):
            W2[i,j] = f(i,j)

    return x1, W1, W2

def loop_compute(x1, W1, W2):
    z1 = np.zeros((4000,1))
    z2 = np.zeros((1000,1))

    for i in range(4000):
        tot = 0
        for j in range(50176):
            tot += W1[i,j]*x1[j,0]
        z1[i,0] = max(0, tot)

    for i in range(1000):
        tot = 0
        for j in range(4000):
            tot += W2[i,j]*z1[j,0]
        z2[i,0] = max(0, tot)

    return np.sum(z2)

def numpy_compute(x1, W1, W2):

    z1 = np.clip(np.matmul(W1,x1), 0, np.inf)
    z2 = np.clip(np.matmul(W2,z1), 0, np.inf)

    return(np.sum(z2))


def C2():
    print("*************************************************")
    print("RUNNING PART C2 Python Iterative Calc. of Network")
    print("*************************************************")
    print("\n\tInitializing Values")
    x1, W1, W2 = init()
    print("\tComputing via loops")
    start=timeit.default_timer()
    S = loop_compute(x1, W1, W2)
    end=timeit.default_timer()
    print("\tCHECK SUM {}".format(S))
    print("\tElapsed Time {}\n".format(str(end-start)))
    return (end-start)


def C3():
    
    print("********************************************")
    print("RUNNING PART C3 Python Numpy Calc of Network")
    print("********************************************")
    print("\n\tInitializing Values")
    x1, W1, W2 = init()
    print("\tComputing via numpy")
    start=timeit.default_timer()
    S = numpy_compute(x1, W1, W2)
    end=timeit.default_timer()
    print("\tCHECKSUM {}".format(S))
    print("\tElapsed Time (sec) {}\n".format(str(end-start)))
    return(end-start)

def main():

    t1 = C2()
    t2 = C3()

    print("\n\tmeasured speedup (C3 vs. C2) {:.2f}".format(t1/t2))


if __name__ == "__main__":
    main()
