//playing around with go to find shortest path
//TODO initialize map from file
//TODO multiple goroutines for multiple crawlers?

package main

import "fmt"

type Step struct {
    name  string
    steps int
}

func init_map() map[string][]string {
    m := make(map[string][]string)
    m["Min"] = append(m["Min"], "William", "Jayden", "Omar")
    m["William"] = append(m["William"], "Min", "Noam")
    m["Jayden"] = append(m["Jayden"], "Min", "Amelia", "Ren", "Noam")
    m["Ren"] = append(m["Ren"], "Jayden", "Omar")
    m["Amelia"] = append(m["Amelia"], "Jayden", "Adam", "Miguel")
    m["Adam"] = append(m["Adam"], "Amelia", "Miguel", "Sofia", "Lucas")
    m["Sofia"] = append(m["Sofia"], "Adam")
    m["Miguel"] = append(m["Miguel"], "Amelia", "Adam", "Liam", "Nathan")
    m["Noam"] = append(m["Noam"], "Nathan", "Jayden", "William")
    m["Omar"] = append(m["Omar"], "Ren", "Min", "Scott")
    return m
}

func reconstruct(a string, b string, m map[string]string) []string {
    var steps []string
    current := b
    for {
        steps = append([]string{current}, steps...)
        if current == a {
            break
        }
        current = m[current]
    }
    return steps
}

func find_shortest(a string, b string, m map[string][]string) map[string]string {
    var edges []Step
    var parent = make(map[string]string)

    current := a
    edges = append(edges, Step{current, 0})
    for {
        node := edges[0]
        for _, el := range m[current] {

            if _, ok := parent[el]; ok {
                //already visited
                continue
            }
            edges = append(edges, Step{el, node.steps + 1})
            parent[el] = current
            if el == b {
                return parent
            }
        }
        edges = edges[1:]
        current = node.name
    }
    return nil
}

func main() {
    m := init_map()
    //fmt.Println(m)
    a := "Min"
    b := "Sofia"
    plist := find_shortest(a, b, m)
    //fmt.Println(plist)
    fmt.Println(reconstruct(a, b, plist))

}
