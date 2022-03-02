from exceptions import Empty

class LinkedQueue: #level order를 위한 연결리스트 큐
    #노드 클래스
    class _Node:
        __slots__ = '_element', '_next'

        def __init__(self, element, next):
            self._element = element
            self._next = next
    ############################################################

    def __init__(self):
        self._head = None
        self._tail = None
        self._size = 0

    def __len__(self):
        return self._size

    def is_empty(self):
        return self._size == 0

    def first(self):
        if self.is_empty():
            raise Empty('Queue is empty')
        return self._head._element

    def dequeue(self):
        if self.is_empty():
            raise Empty('Queue is empty')
        answer = self._head._element
        self._head = self._head._next
        self._size -= 1
        if self.is_empty():
            self._tail = None #큐가 비게되면 tail을 None으로
        return answer

    def enqueue(self, e):
        newest = self._Node(e, None)
        if self.is_empty():
            self._head = newest
        else:
            self._tail._next = newest
        self._tail = newest
        self._size += 1

    def __str__(self):
        A = []
        ptr = self._head
        while ptr is not None:
            A.append(ptr._element)
            ptr = ptr._next
        return f"{str(A)}, front = {A[0]}, rear = {A[-1]}"