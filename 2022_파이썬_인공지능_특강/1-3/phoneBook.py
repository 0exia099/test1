class PhoneBook:
    def __init__(self):
        self.__contact = {}
        
    def __str__(self):
        msg = ""
        for key, value in self.__contact.items():
            msg += f"{key}\n"
            msg+=f"전화번호: {value[0]}\n"
            msg+=f"e-mail: {value[1]}\n"
        return msg
    
    def add(self, name, phone=None, email=None):
        self.__contact[name]=(phone,email)
        return
        
    def get(self, name):
        return self.__contact[name]
    
pb = PhoneBook()
pb.add("Cho", phone="010-1234-5678", email="cho@yu.ac.kr")
pb.add("Kim", phone="010-2345-6789", email = "lee@korea.com")
print(pb)
print(f"Cho의 주소록 = { pb.get('Cho') }")