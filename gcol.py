class GraphNode:

    def __init__(self, label):
        self.label = label
        self.neighbors = set()
        self.color = None

a = GraphNode('a')
b = GraphNode('b')
c = GraphNode('c')
d = GraphNode('d')
e = GraphNode('e')
f = GraphNode('f')

a.neighbors.add(b)
a.neighbors.add(d)
a.neighbors.add(e)
a.neighbors.add(f)

b.neighbors.add(d)
b.neighbors.add(a)
b.neighbors.add(c)

c.neighbors.add(b)
c.neighbors.add(d)
c.neighbors.add(f)

d.neighbors.add(a)
d.neighbors.add(b)
d.neighbors.add(c)

e.neighbors.add(a)

f.neighbors.add(a)
f.neighbors.add(c)

graph = [a, b, c, d, e, f]


def color(g, d):
    n = g[0]
    n.color = 0
    q = []
    for x in n.neighbors:
        q.insert(0, x)
    prev_col = 0
    while len(q) > 0:
        n = q.pop()
        if not isinstance(n, GraphNode):
            #is color
            prev_col = n
            continue
        prev_col = (prev_col + 1) % (d+1)
        n.color = prev_col
        for nb in n.neighbors:
            once = False
            if nb.color == None:
                if not once:
                    q.insert(0, n.color)
                q.insert(0, nb)

color(graph, 4)
for n in graph:
    print ("%s: %s" % (n.label, n.color))



