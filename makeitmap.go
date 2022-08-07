func topologicalSort(graph map[string][]string) []string {
    var (
        visited = make(map[string]bool)
        result  = make([]string, 0)
    )
    for key := range graph {
        if !visited[key] {
            visited[key] = true
            visit(key, graph, &result)
        }
    }
    return result
}
