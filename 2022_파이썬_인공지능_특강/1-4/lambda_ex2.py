students = ["kim","lee","park","ahn","cho"]
math=[79,80,83,67,77]
eng = [95,88,90,91,92]

print(f"수학최고 = {max(list(zip(students, math)), key=lambda x:x[1])[0]}")
print(f"수학최저 = {min(list(zip(students, math)), key=lambda x:x[1])[0]}")
print(f"영어최고 = {max(list(zip(students, eng)), key=lambda x:x[1])[0]}")
print(f"영어최저 = {min(list(zip(students, eng)), key=lambda x:x[1])[0]}")