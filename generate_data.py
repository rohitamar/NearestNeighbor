import random

if __name__ == '__main__':
    N = [500] 
    Q = [1]
    M = [500]
    D = [3]
    names = ['med']

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
    
    
