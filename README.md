# Nearest Neighbor
## Introduction
Comparing different nearest neighbor algorithms such as locality sensitive hashing and k-d trees 
## Benchmarks
Times do not account for any precomputations done before solving queries. 
### Small (~100, D = 7)
Algorithm | Time | 
--- | --- | 
`bruteforce` | 0.0003618
`bruteforce_threaded` | 0.001845
`k-d tree` | 

### Medium (~10,000, D = 100)
Algorithm | Time | 
--- | --- | 
`bruteforce` | 0.0098936
`bruteforce_threaded` | 0.0033703 
`k-d tree` | 

### Large (~10 million, D = 250)
Algorithm | Time (s) | 
--- | --- | 
`bruteforce` | 2.35953
`bruteforce_threaded` | 0.344837
`k-d tree` | 
