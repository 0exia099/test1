"""
 Project : 전자서명 검증
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -ECDSA알고리즘을 파이썬으로 구현. SECP256K1 타원곡선 사용.
   -메시지와 개인키를 받아 전자서명 생성.
   -메시지, 전자서명, 공개키를 받아 메시지와 전자서명이 일치하는지 확인
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

import os
import random
import time
import hashlib

a = 0
p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
e1 = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798,
      0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8)
q = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141

def extended_euclidian(p, x):
    if x < 0:
        x = x % p
    
    r1, r2 = p, x
    t1, t2 = 0, 1
    
    while r2 > 0:
        t1, t2 = t2, t1 - ((r1 // r2) * t2)
        r1, r2 = r2, r1 % r2
    
    if r1 == 1:
        return t1 % p
    else:
        return None

def elliptical_curve_add(P, Q):
    x1, y1 = P
    x2, y2 = Q
    
    if P == Q:
        slope = ((3 * (x1**2) + a) * extended_euclidian(p, (2 * y1))) % p
    else:
        slope = ((y2 - y1) * extended_euclidian(p, (x2 - x1))) % p
        
    x3 = (slope**2 - x1 - x2) % p
    y3 = (slope * (x1 - x3) - y1) % p
    
    return (x3, y3)

def double_and_add(k, G):
    if k == 0:
        return (0, 0)
    
    result_sum = G
    for value in bin(k)[3:]:
        result_sum = elliptical_curve_add(result_sum, result_sum)
        if value == '1':
            result_sum = elliptical_curve_add(result_sum, G)
    
    return result_sum

def generate_private_key():
    private_key = q
    while private_key >= q:
        random_str = str(os.urandom(16)).join(
            [str(random.random()), str(time.time())])
        random_str = ''.join(random.sample(random_str, len(random_str)))
        private_key = int(hashlib.sha256(random_str.encode()).hexdigest(), 16)
    return private_key

def generate_public_key(d):
    return double_and_add(d, e1)

def sign(message, d):
    h = hashlib.sha256()
    h.update(message.encode())
    
    r = generate_private_key() % (q - 3) + 2
    
    u, v = generate_public_key(r)
    S1 = u % q
    S2 = ((int(h.hexdigest(),16) + d * S1) * extended_euclidian(q, r)) % q
    return S1, S2

def verify(message, S1, S2, e2):
    h = hashlib.sha256()
    h.update(message.encode())
    S2_e = extended_euclidian(q, S2)
    A = (int(h.hexdigest(),16) * S2_e) % q
    B = (S1 * S2_e) % q
    print(f'\tA = {A:#x}')
    print(f'\tB = {B:#x}')
    x, y = elliptical_curve_add(double_and_add(A, e1), double_and_add(B, e2))
    if x % q == S1 % q:
        return True
    else:
        return False

if __name__ == "__main__":
    d = generate_private_key()
    
    e2 = generate_public_key(d)

    M = input("메시지? ")
    S1, S2 = sign(M, d)
    print("1. Sign:")
    print("\tS1 =", hex(S1))
    print("\tS2 =", hex(S2))
    
    print("2. 정확한 서명을 입력할 경우:")
    if verify(M, S1, S2, e2) == True:
        print("검증 성공")
    else:
        print("검증 실패")
    
    print("3. 잘못된 서명을 입력할 경우:")
    if verify(M, S1-1, S2-1, e2) == True:
        print("검증 성공")
    else:
        print("검증 실패")
