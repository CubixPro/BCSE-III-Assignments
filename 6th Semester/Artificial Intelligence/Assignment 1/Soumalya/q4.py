def compare(tuple1, tuple2):
    return all(x==y for x,y in zip(tuple1, tuple2))


def validPoint(nowX, nowY, row, col):

    if(nowX >= 0 and nowX < row):
        if( nowY >= 0 and nowY < col):
            return True
    
    return False

def solve(maze, initialPos, finalPos, moves):

    queue = []
    row = len(maze)
    col = len(maze[0]) 


    currX = initialPos[0]
    currY = initialPos[1]
    queue.append([maze, currX, currY])

    while(len(queue) != 0):

        temp = queue.pop(0)
        currMaze = temp[0]
        currX = temp[1]
        currY = temp[2]

        if(currX == finalPos[0] and currY == finalPos[1]):
            return currMaze
        
        else:

            for move in moves:
                nowX = currX + move[0]
                nowY = currY + move[1]

                if(validPoint(nowX, nowY, row, col) and currMaze[nowX][nowY] == 0):
                    
                    newMaze = currMaze.copy()
                    newMaze[nowX][nowY] = 'R'
                    queue.append([newMaze, nowX, nowY])







if __name__ == "__main__":

    maze = [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 1, 0, 1, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 1, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 1, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    ]

    moves = [[0,1], [1,0], [-1,0], [0,-1]]
    initialPos = (1,1)
    finalPos = (6,2)

    ans = solve(maze,initialPos, finalPos, moves)

    for row in ans:
        print(row)