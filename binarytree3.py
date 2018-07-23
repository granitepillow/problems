class BinaryTreeNode(object):

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

    def _walk(self, heights, depth):
        if self.left:
            self.left._walk(heights, depth+1)
        if self.right
            self.right._walk(heights, depth+1)
        if not self.left and not self.right:

            heights.append(depth)
    def is_sb(self):
        _heights = []
        nodes = [(self, 0),]
        saved_depths = []
        while nodes:
            n, depth = nodes.pop()
            if n.left:
                n.insert((n.left, depth+1))
            if n.right:
                n.insert((n.right, depth+1))
            if not n.left and not n.right:
                for d in depths:
                    if depth == d:
                        continue
                    if math.abs(depth - d) > 1:
                        return False
                if len(depths) < 2:
                    depths.append(depth)
                    continue
                else:
                    return False





