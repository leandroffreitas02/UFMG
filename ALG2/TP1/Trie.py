from Node import Node

class Trie:
    def __init__(self):
        self.root = Node(0)
        self.size = 1

    def Search(self, string):
        CurrentNode = self.root

        for ch in string:
            if ch not in CurrentNode.children.keys():
                return -1
            
            CurrentNode = CurrentNode.children[ch]

        return CurrentNode.Id

    def Insert(self, string):
        CurrentNode = self.root

        for ch in string:
            if ch not in CurrentNode.children.keys():
                CurrentNode.children[ch] = Node(self.size)
                self.size += 1

                return CurrentNode.Id
            
            CurrentNode = CurrentNode.children[ch]