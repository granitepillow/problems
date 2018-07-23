class BinaryTreeNode:

    def __init__(self, value):
        self.value = value
        self.left  = None
        self.right = None

    def insert_left(self, value):
        self.left = BinaryTreeNode(value)
        return self.left

    def insert_right(self, value):
        self.right = BinaryTreeNode(value)
        return self.right
    def prnt(self):
        if self.left:
            self.left.prnt()
        if self.right:
            self.right.prnt()
        print self.value

    def is_super(self):
        nodes = []
        node = self
        max_dep = 0
        dep = 1
        while True:
            if node.right:
                nodes.append([node.right, dep])
            if node.left:
                node = node.left
                dep += 1
            else:
                if not node.right:
                    print("Found Leaf %d %d %d" %(max_dep, dep, node.value))
                    if not max_dep:
                        max_dep = dep
                    elif abs(max_dep - dep) > 1:
                        return False
                    elif dep > max_dep:
                        dep = max_dep
                if nodes:
                    node, dep = nodes.pop()
                    dep += 1
                    continue
                return True






tree = BinaryTreeNode(-1)
tree.insert_left(-1)
tree.insert_right(-2)
tree.left.insert_left(-3)
tree.right.insert_left(-5)
tree.left.left.insert_left(-4)


print(tree.is_super())
