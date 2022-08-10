fish_length = [25.4, 26.3, 26.5, 29.0, 29.0, 29.7, 29.7, 30.0, 30.0, 30.7, 31.0, 31.0, 
                31.5, 32.0, 32.0, 32.0, 33.0, 33.0, 33.5, 33.5, 34.0, 34.0, 34.5, 35.0, 
                35.0, 35.0, 35.0, 36.0, 36.0, 37.0, 38.5, 38.5, 39.5, 41.0, 41.0, 9.8, 
                10.5, 10.6, 11.0, 11.2, 11.3, 11.8, 11.8, 12.0, 12.2, 12.4, 13.0, 14.3, 15.0]
fish_weight = [242.0, 290.0, 340.0, 363.0, 430.0, 450.0, 500.0, 390.0, 450.0, 500.0, 475.0, 500.0, 
                500.0, 340.0, 600.0, 600.0, 700.0, 700.0, 610.0, 650.0, 575.0, 685.0, 620.0, 680.0, 
                700.0, 725.0, 720.0, 714.0, 850.0, 1000.0, 920.0, 955.0, 925.0, 975.0, 950.0, 6.7, 
                7.5, 7.0, 9.7, 9.8, 8.7, 10.0, 9.9, 9.8, 12.2, 13.4, 12.2, 19.7, 19.9]

import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'Apple SD Gothic Neo'
plt.rcParams['font.size'] = 14

fish_data = np.column_stack((fish_length, fish_weight)) #넘파이의 colum_stack()으로 길이와 무게 연결(2차원으로)
fish_target = np.concatenate((np.ones(35), np.zeros(14))) #concatenate()로 도미인지 빙어인지 값 배열 연결(1차원으로)

# train_input, test_input, train_target, test_target = train_test_split(
#     fish_data, fish_target, random_state=42)
train_input, test_input, train_target, test_target = train_test_split(
    fish_data, fish_target, stratify=fish_target, random_state=42)   #stratify로 도미와 빙어의 비율에 맞게 적당히 나눔

kn = KNeighborsClassifier()
kn.fit(train_input, train_target)
print(kn.score(test_input, test_target))

distances, indexes = kn.kneighbors([[25, 150]])

#도미쪽 데이터에 25,150인 것이 가까워 보지만 x축 단위와 y축 단위가 달라 실제 값으로는 빙어에 가깝다
plt.scatter(train_input[:,0], train_input[:,1])
plt.scatter(25, 150, marker='^')
plt.scatter(train_input[indexes,0], train_input[indexes,1], marker='D')
plt.xlabel('length')
plt.ylabel('weight')
plt.title("기존에 사용되는 데이터")
plt.show()

plt.scatter(train_input[:,0], train_input[:,1])
plt.scatter(25, 150, marker='^')
plt.scatter(train_input[indexes,0], train_input[indexes,1], marker='D')
plt.xlim((0, 1000))
plt.xlabel('length')
plt.ylabel('weight')
plt.title("x축, y축 단위 일치 시 그래프")
plt.show()

#빙어가 아니라 도미이지만 도미가 아니라고 분류된다.
print("기존 :")
if kn.predict([[25, 150]]) == 1:
    print(f"{25}cm, {150}g은 도미입니다.\n")
else:
    print(f"{25}cm, {150}g은 도미가 아닙니다.\n")
    
#평균과 표준편차를 이용하여 구하자
mean = np.mean(train_input, axis=0)   #각 열의 평균 구하기
std = np.std(train_input, axis=0)   #각 열의 표준편차 구하기

#평균과 표준편차로 표준점수를 구한다 (표준점수 = (특성-평균)/표준편차)
train_scaled = (train_input - mean) / std
new = ([25, 150] - mean) / std

#평균과 표준편차를 이용하여 다시 보면 도미쪽 데이터에 가깝다
# plt.scatter(train_scaled[:,0], train_scaled[:,1])
# plt.scatter(new[0], new[1], marker='^')
# plt.xlabel('length')
# plt.ylabel('weight')
# plt.show()

#구한 표준 점수로 트레이닝
kn.fit(train_scaled, train_target)

test_scaled = (test_input - mean) / std
print(kn.score(test_scaled, test_target))

#새로 구하면 도미로 나온다
print("보완 :")
if kn.predict([new]) == 1:
    print(f"{25}cm, {150}g은 도미입니다.")
else:
    print(f"{25}cm, {150}g은 도미가 아닙니다.")
    
distances, indexes = kn.kneighbors([new])

plt.scatter(train_scaled[:,0], train_scaled[:,1])
plt.scatter(new[0], new[1], marker='^')
plt.scatter(train_scaled[indexes,0], train_scaled[indexes,1], marker='D')
plt.xlabel('length')
plt.ylabel('weight')
plt.title("보완 후 사용되는 데이터")
plt.show()