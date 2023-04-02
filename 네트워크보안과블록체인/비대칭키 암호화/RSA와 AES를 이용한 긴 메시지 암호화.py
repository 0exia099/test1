"""
 Project : RSA와 AES를 이용한 긴 메시지 암호화
 Author : 심상혁
 Date of first create : April 3, 2023
 Major features:
   -길이가 긴 메시지를 AES를 이용하여 암호화 하고 RSA를 이용해 AES의 키를 암호화
   -RSA와 AES로 암호화 한 내용을 복호화 하여 출력
 Date of last update : April 3, 2023
 Revised contesnt : 
   -v1.0 : April 3, 2023
        * first create
"""

from cryptography.fernet import Fernet
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding

class SecretMessageSender:
    def __init__(self, msg, aes_key, public_key=None):
        self.__msg = msg
        self.__aes_key = aes_key
        self.__public_key = public_key
    
    def msg_encryption(self):
        if (self.__aes_key == None) or (self.__msg == None) or (self.__public_key == None):
            return None
        f = Fernet(self.__aes_key)
        enc_msg = f.encrypt(self.__msg)
        enc_key = self.__public_key.encrypt(
            self.__aes_key,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )
        return enc_msg, enc_key
    
    def set_public_key(self, public_key):
        self.__public_key = public_key
    
    def set_public_key_from_pem(self, file_name):
        with open(file_name, 'rb') as key_file:
            self.__public_key = serialization.load_pem_public_key(
                key_file.read(),
                backend=default_backend()
            )

class SecretMessageReceiver:
    def __init__(self, enc_msg, enc_key, private_key=None):
        self.__enc_msg = enc_msg
        self.__enc_key = enc_key
        self.__private_key = private_key
    
    def msg_decryption(self):
        if (self.__enc_key == None) or (self.__enc_msg == None) or (self.__private_key == None):
            return None
        
        aes_key = self.__private_key.decrypt(
            self.__enc_key,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None
            )
        )
        decrypt_f = Fernet(aes_key)
        msg = decrypt_f.decrypt(self.__enc_msg)
        
        return msg, aes_key
    
    def set_private_key(self, private_key):
        self.__private_key = private_key
    
    def set_private_key_from_pem(self, file_name):
        with open(file_name, 'rb') as key_file:
            self.__private_key = serialization.load_pem_private_key(
                key_file.read(),
                password=None,
                backend=default_backend()
            )

msg = bytes(input('평문 메시지 : '), 'utf-8')

key = Fernet.generate_key()
secret_message_sender = SecretMessageSender(msg=msg, aes_key=key)
secret_message_sender.set_public_key_from_pem('public_key.pem')

received_msg, received_key = secret_message_sender.msg_encryption()

secret_message_receiver = SecretMessageReceiver(enc_msg=received_msg, enc_key=received_key)
secret_message_receiver.set_private_key_from_pem('private_key.pem')

decryption_msg, decryption_key = secret_message_receiver.msg_decryption()
print('복호화 결과 :', str(decryption_msg, 'utf-8'))
