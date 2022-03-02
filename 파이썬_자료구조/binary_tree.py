from tree import Tree

class BinaryTree(Tree): #Tree클래스 상속 받는다
    def left(self, p): #왼쪽 자식 메소드
        raise NotImplementedError('must be implemented by subclass')
        
    def right(self, p): #오른쪽 자식 메소드
        raise NotImplementedError('must be implemented by subclass')
        
    def sibling(self, p): #형제 노드 구하는 메소드
        parent = self.parent(p)
        if parent is None: #부모가 없으면 루트노드->형제 없음
            return None
        else:
            if p == self.left(parent):
                return self.right(parent)
            else:
                return self.left(parent)
            
    def children(self, p):
        if self.left(p) is not None:
            yield self.left(p)
        if self.right(p) is not None:
            yield self.right(p)
            
    def inorder(self): #이진트리는 inorder가능
        if not self.is_empty():
            for p in self._subtree_inorder(self.root()):
                yield p
    def _subtree_inorder(self, p):
        if not self.left(p) is not None:
            for other in self._subtree_inorder(self.left(p)):
                yield other
        yield p
        if self.right(p) is not None:
            for other in self._subtree_inorder(self.right(p)):
                yield other
                
    def positions(self): #그냥 Tree클래스에서 preorder였던걸 이진 트리에서는 inorder로 변경(오버라이드)
        return self.inorder() #이진 검색 트리에서 inorder로 정렬된 순서로 출력 가능하기 때문