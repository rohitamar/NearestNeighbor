import random

if __name__ == '__main__':
    N = 100000000
    Q = 1
    M = 150
    D = 250

    with open('large', 'w') as f:
        for _ in range(N):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    with open('large-q', 'w') as f:
        for _ in range(Q):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    
