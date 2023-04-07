"""
 Project : MySortings
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : April 5, 2023
 Major features:
   -선택정렬을 구현한 함수 selectionSort(L) 제공
   -병합정렬을 구현한 함수 mergeSort(L) 제공, 병합정렬을 위한 _merge(L_left, L_right)
 Date of last update : April 5, 2023
 Revised contesnt : 
   -v1.0 : April 5, 2023
        * first create
"""
# 선택정렬 함수
def selectionSort(L: list):
    for i in range(len(L) - 1): # 리스트의 마지막 빼고 시작
        min = i # 가장 작은 값의 인덱스 초기화
        for j in range(i+1, len(L)):    # 시작 부터 마지막까지 돌면서 가장 작은 값을 가지는 인덱스를 찾는다
            if L[min] > L[j]:
                min = j
        L[i], L[min] = L[min], L[i] # 가장 작은 값과 시작 변경
    return

# 병합정렬에 사용될 _merge함수
def _merge(L_left, L_right):
    L_res = []
    i, j = 0, 0
    len_left, len_right = len(L_left), len(L_right)
    while i < len_left and j < len_right:
        if L_left[i] < L_right[j]:  # 왼쪽이 작으면
            L_res.append(L_left[i]) # 왼쪽 원소 추가
            i += 1
        else: # 오른쪽이 작으면
            L_res.append(L_right[j])  # 오른쪽 원소 추가
            j += 1
    while i < len_left: # 왼쪽리스트가 남았으면
        L_res.append(L_left[i]) # 왼쪽의 나머지 다 추가
        i += 1
    while j < len_right:  # 오른쪽리스트가 남았으면
        L_res.append(L_right[j])  # 오른쪽의 나머지 다 추가
        j += 1
    return L_res

# 병합정렬 함수
def mergeSort(L: list):
    if len(L) < 2:  # 길이가 2 미만이면 정렬할 원소 없음. L[:] 반환
        return L[:]
    else:
        middle = len(L) // 2
        L_left = mergeSort(L[:middle])  # 처음에서 중간 병합 정렬
        L_right = mergeSort(L[middle:]) # 중간에서 마지막 병합 정렬
        L.clear()   # L의 값을 변경시키기위해 L.clear로 비우고 추가하여 함수 밖의 L의 값 변경
        L += _merge(L_left, L_right)  # (정렬된 처음~중간)과 (정렬된 중간~마지막)을 병합
        return L
