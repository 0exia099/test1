import time
import hashlib

class Bitcoin_POW:
    def __init__(self, msg, target_bits):
        self.msg = msg
        self.target = int(("".join([target_bits[2:], '0' * (2 * (int(target_bits[:2], 16) - 3))])).zfill(64), 16)
        self.nonce = 1
    
    def get_target(self):
        return self.target
    
    def get_nonce(self):
        max_nonce = 2**32
        start = time.time()
        while True:
            extra_nonce = str(int(time.time()))
            for nonce in range(max_nonce):
                h = hashlib.sha256()
                h.update(("".join([self.msg, extra_nonce, str(nonce)])).encode())
                hash_result = h.hexdigest()
                end = time.time()
                if int(hash_result,16) < self.target:
                    self.nonce = nonce
                    ex_time = end - start
                    result = "".join(['0x', hash_result])
                    return result, extra_nonce, nonce, ex_time
        

msg = input('- 메시지의 내용? ')
target_bits = input('- Target bits? ')

bp = Bitcoin_POW(msg, target_bits)
result, extra_nonce, nonce, ex_time = bp.get_nonce()
print(f'- Target: {bp.get_target():#066x}\n- 메시지: {msg}, Extra nonce: {extra_nonce}, nonce: {nonce}')
print(f'- 실행 시간: {ex_time}')
print(f'- Hash result: {result}')