

#implement the graph



def bfs(graph, startNode , targetNode):

    queue = []
    #visited = []
    queue.append([startNode])

    while len(queue) != 0:

        currPath = queue.pop(0)
        if(currPath[len(currPath)-1] == targetNode):
            return currPath
        else:
            # append the child in the queue
            if(graph.get(currPath[len(currPath)-1], -1) != -1):
                newPath = currPath.copy()
                for node in graph.get(currPath[len(currPath)-1], -1):
                    newPath = currPath.copy()
                    newPath.append(node)
                    queue.append(newPath)
    
    return -1


def dfs(graph, startNode, targetNode):

    stack = []
    visited = []
    stack.append([startNode])

    while len(stack) != 0:

        currPath = stack.pop()
        if(currPath[len(currPath)-1] == targetNode):
            return currPath
        
        else:
            if(graph.get(currPath[len(currPath)-1], -1) != -1):
                newPath = currPath.copy()
                for node in graph.get(currPath[len(currPath)-1], -1):
                    newPath = currPath.copy()
                    newPath.append(node)
                    stack.append(newPath)

    return -1


if __name__ == "__main__":

    graph =  {

        1 : [8, 5, 2],
        8 : [6, 4, 3],
        2 : [9],
        6 : [10, 7]
    
    }
    print("after bfs: \n" + str(bfs(graph, 1, 10)))
    print("after dfs: \n" + str(dfs(graph, 1, 10)))