class Stack(object):

    def __init__(self):
        """Initialize an empty stack"""
        self.items = []

    def push(self, item):
        """Push new item to stack"""
        self.items.append(item)

    def pop(self):
        """Remove and return last item"""
        # If the stack is empty, return None
        # (it would also be reasonable to throw an exception)
        if not self.items:
            return None

        return self.items.pop()

    def peek(self):
        """See what the last item is"""
        if not self.items:
            return None
        return self.items[-1]


class MaxStack(Stack):
    def __init__(self):
        """Initialize an empty stack"""
        self.maxes = Stack()
        super(MaxStack, self).__init__()

    def push(self, item):
        """Push new item to stack"""
        if not self.maxes.peek() or item >= self.maxes.peek():
            self.maxes.push(item)
        super(MaxStack, self).push(item)

    def pop(self):
        """Remove and return last item"""
        # If the stack is empty, return None
        # (it would also be reasonable to throw an exception)
        if self.peek() and self.maxes.peek() == self.peek():
            self.maxes.pop()

        return super(MaxStack, self).pop()

    def peek(self):
        """See what the last item is"""
        return super(MaxStack, self).peek()

    def get_max(self):
        return self.maxes.peek()

mymax = MaxStack()
mymax.push(1)
mymax.push(2)
print(mymax.get_max()) #2
mymax.push(3)
mymax.push(3)
mymax.push(4)
print(mymax.get_max()) #4
mymax.push(1)
mymax.push(3)
print(mymax.get_max()) # 4
mymax.pop()
print(mymax.get_max()) # 4
mymax.pop()
print(mymax.get_max()) #4
mymax.pop()
print(mymax.get_max()) # 3
mymax.pop()
print(mymax.get_max())
