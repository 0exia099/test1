"""
 Project : 비트코인 주소 생성
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -개인키를 입력받아 비트코인 주소를 생성.
   -공개키의 크기를 줄이기 위해 압축방식 사용
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

from Crypto.Hash import RIPEMD160
import base58check
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
    d = int("".join(['0x', input('개인키 입력? ')]), 16)
    
    e2 = generate_public_key(d)
    
    public_key_hash = generate_public_key_hash(e2)
    print(f'공개키 hash = {public_key_hash}')
    
    bitcoin_address = generate_bitcoin_address(public_key_hash)
    str_bitcoin_address = str(bitcoin_address, 'utf-8')
    print(f'비트코인 주소 = {str_bitcoin_address}')
