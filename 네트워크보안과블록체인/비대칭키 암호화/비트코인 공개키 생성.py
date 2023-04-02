"""
 Project : 비트코인 공개키 생성
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -랜덤으로 비트코인 개인키를 생성하고 공개키 생성
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

import os
import random
import time
import hashlib

def extended_euclidian(p, x):
    r1, r2 = p, x
    t1, t2 = 0, 1
    
    while r2 > 0:
        t1, t2 = t2, t1 - ((r1 // r2) * t2)
        r1, r2 = r2, r1 % r2
    
    if r1 == 1:
        return t1 % p
    else:
        return None

def elliptical_curve_add(a, p, P, Q):
    x1, y1 = P
    x2, y2 = Q
    
    if P == Q:
        slope = ((3 * (x1**2) + a) * extended_euclidian(p, (2 * y1)%p)) % p
    else:
        slope = ((y2 - y1) * extended_euclidian(p, (x2 - x1)%p)) % p
        
    x3 = (slope**2 - x1 - x2) % p
    y3 = (slope * (x1 - x3) - y1) % p
    
    return (x3, y3)

def double_and_add(a, p, k, G):
    if k == 0:
        return (0, 0)
    
    result_sum = G
    for value in bin(k)[3:]:
        result_sum = elliptical_curve_add(a, p, result_sum, result_sum)
        if value == '1':
            result_sum = elliptical_curve_add(a, p, result_sum, G)
    
    return result_sum
    
a = 0
p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
G = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798, 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8)

private_key = p

while private_key >= p:
    random_str = str(os.urandom(16)).join([str(random.random()), str(time.time())])
    random_str = ''.join(random.sample(random_str,len(random_str)))
    private_key = int(hashlib.sha256(random_str.encode()).hexdigest(), 16)

public_key = double_and_add(a, p, private_key, G)

print(f'개인키(16진수) = {private_key:#x}')
print(f'개인키(10진수) = {private_key}')

print(f'\n공개키(16진수) = ({public_key[0]:#x},\n\t\t  {public_key[1]:#x})')
print(f'\n공개키(10진수) = ({public_key[0]},\n\t\t  {public_key[1]})\n')
