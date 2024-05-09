import random

if __name__ == '__main__':
    N = [1000, 10000, 10000000] 
    Q = [10, 1500, 500]
    M = [500, 500, 500]
    D = [3, 100, 500]
    names = ['small', 'med', 'large']

    for n, q, m, d, name in zip(N, Q, M, D, names):
        
        if name == 'large':
            break

        file_path = './data/{}'.format(name)
        with open(file_path, 'w') as f:
            for _ in range(n):
                f.write(" ".join([str(random.randint(-m, m)) for _ in range(d)]) + '\n')
        
        file_path = './data/{}-q'.format(name)
        with open(file_path, 'w') as f:
            for _ in range(q):
                f.write(" ".join([str(random.randint(-m, m)) for _ in range(d)]) + '\n')
    
    
