비트코인의 Bloomfilter를 구현하는 1.py
메시지와 타겟bits를 입력받아 nonce를 구하는 비트코인마이닝을 구현하는 2.py
extra nonce의 값은 str(int(현재 시간))을 사용하며
SHA256(메시지 + extra nonce + nonce)가 타겟보다 작도록하는 nonce를 구한다.
