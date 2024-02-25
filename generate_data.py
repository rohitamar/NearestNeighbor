import random

if __name__ == '__main__':
    N = 10
    Q = 1
    M = 500
    D = 4

    with open('small', 'w') as f:
        for _ in range(N):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    with open('small-q', 'w') as f:
        for _ in range(Q):
            f.write(" ".join([str(random.randint(-M, M)) for _ in range(D)]) + '\n')
    
    
