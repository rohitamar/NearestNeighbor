import random

if __name__ == '__main__':
    N = 10000
    Q = 1
    M = 500
    D = 100

    with open('med', 'w') as f:
        for _ in range(N):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    with open('med-q', 'w') as f:
        for _ in range(Q):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    
