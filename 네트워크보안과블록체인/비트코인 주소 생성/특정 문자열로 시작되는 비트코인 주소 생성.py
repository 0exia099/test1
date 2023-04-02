"""
 Project : 특정 문자열로 시작되는 비트코인 주소 생성
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -입력받은 문자열로 시작하는 주소가 나올때 까지 반복하여 주소생성
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

from Crypto.Hash import RIPEMD160
import base58check
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

def generate_press_public_key(e2):
    x, y = e2
    str_s = f'{x:x}'.zfill(64)
    if y%2 == 0:
        return "".join(['02', str_s])
    else:
        return "".join(['03', str_s])

def generate_public_key_hash(e2):
    press_public_key = generate_press_public_key(e2)
    
    h1 = hashlib.sha256()
    h2 = RIPEMD160.RIPEMD160Hash()
    
    h1.update(bytes.fromhex(press_public_key))
    sha256_1 = h1.hexdigest()
    
    h2.update(bytes.fromhex(sha256_1))
    ripemd160_hash = h2.hexdigest()
    
    extended_ripemd160_hash = "".join(['00', ripemd160_hash])
    
    return extended_ripemd160_hash

def generate_bitcoin_address(public_key_hash):
    h1 = hashlib.sha256()
    h2 = hashlib.sha256()
    
    h1.update(bytes.fromhex(public_key_hash))
    first_hash = h1.hexdigest()
    
    h2.update(bytes.fromhex(first_hash))
    second_hash = h2.hexdigest()
    
    extended_checksum_hash = "".join([public_key_hash, second_hash[:8]])
    bitcoin_address = base58check.b58encode(bytes.fromhex(extended_checksum_hash))
    
    return bitcoin_address

if __name__ == "__main__":
    want_str = input('희망하는 주소의 문자열? ')
    
    while True:
        d = generate_private_key()
        e2 = generate_public_key(d)
    
        public_key_hash = generate_public_key_hash(e2)
        bitcoin_address = generate_bitcoin_address(public_key_hash).decode()
        
        if bitcoin_address[1:].startswith(want_str):
            print(f'개인 키 = {d}')
            print(f'주소 = {bitcoin_address}')
            break
