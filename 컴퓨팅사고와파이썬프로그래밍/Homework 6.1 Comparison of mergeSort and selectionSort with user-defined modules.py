"""
 Project : Homework 6.1 Comparison of mergeSort and selectionSort with user-defined modules
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : April 5, 2023
 Major features:
   -MyList.py와 MySortings.py의 함수를 사용하여 중복되지 않는 정수형 난수에 대한 선택정렬과 병합 정렬을 실행, 실행에 걸린 시간 측정
 Date of last update : April 5, 2023
 Revised contesnt : 
   -v1.0 : April 5, 2023
        * first create
"""
import time
import MyList, MySortings # 사용자 정의 모듈 import
while True:
    size = int(input("\nsize of list (0 to terminate) = "))
    if(size == -1): # -1입력시 종료
        break
    L = []
    MyList.genRandList(L, size) # 중복되지 않는 정수형 난수 리스트 생성
    print("List (size : {}) before merge sorting : ".format(size))
    MyList.printListSample(L, 10, 2)  # 리스트 샘플 출력
    t1 = time.time()
    MySortings.mergeSort(L) # 병합정렬, 시간측정
    t2 = time.time()
    print("\nList (size : {}) after merge sorting : ".format(size))
    MyList.printListSample(L, 10, 2)  # 병합정렬 후 리스트 샘플 출력
    print("Merge sorting for list of {} integers took {} sec".format(size, t2-t1))
    MyList.shuffleList(L) # 리스트 셔플
    print("\nList (size : {}) before selection sorting : ".format(size))
    MyList.printListSample(L, 10, 2)  # 셔플된 리스트 샘플 출력
    t1 = time.time()
    MySortings.selectionSort(L) # 선택정렬, 시간측정
    t2 = time.time()
    print("\nList (size : {}) after selection sorting : ".format(size))
    MyList.printListSample(L, 10, 2)  # 선택정렬 후 리스트 샘플 출력
    print("Selection sorting for list of {} integers took {} sec".format(size, t2-t1))
