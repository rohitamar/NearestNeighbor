import random

if __name__ == '__main__':
    N = 1000
    Q = 3
    M = 150
    D = 7

    with open('med', 'w') as f:
        for _ in range(N):
            f.write(" ".join([random.randint(-M, M) for _ in range(D)]) + '\n')
    
    with open('med-q', 'w') as f:
        for _ in range(Q):
            f.write(" ".join([random.randint(-M, M) for _ in range(D)]) + '\n')
    
    
