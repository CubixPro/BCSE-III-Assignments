
def compare(tuple1, tuple2):
    return all(x==y for x,y in zip(tuple1, tuple2))

def solve(leftJug, rightJug, initialState, targetState):

    queue = []
    queue.append([initialState])

    while(len(queue) != 0):

        currPath = queue.pop(0)
        currState = currPath[len(currPath)-1]

        if(compare(currState, targetState)):
            return currPath
        
        else:

            # now need to perform actions based on the currState

            # if a jug is empty we can fill the jug
            nextState = ()
            if(currState[0] == 0): 
                nextState += (leftJug, currState[1])
                copyPath = currPath.copy()
                copyPath.append(nextState)
                queue.append(copyPath)
            
            nextState = ()
            if(currState[1] == 0):
                nextState = (currState[0], rightJug)
                copyPath = currPath.copy()
                copyPath.append(nextState)
                queue.append(copyPath)
            
            nextState = ()
            if(currState[0] != 0):
            
                # we can empty the jug or can transfer the content to another jug

                #empty the jug
                nextState = (0, currState[1])
                copyPath = currPath.copy()
                copyPath.append(nextState)
                queue.append(copyPath)


                nextState = ()
                if(currState[1] != rightJug): #if not full

                    #transfer

                    transferAmount = rightJug - currState[1]
                    if(currState[0] <= transferAmount):
                        rightJugContent = currState[1] + currState[0]
                        leftJugContent = 0
                        nextState = (leftJugContent, rightJugContent)
                        copyPath = currPath.copy()
                        copyPath.append(nextState)
                        queue.append(copyPath)
                    
                    else:

                        rightJugContent = rightJug
                        leftJugContent = currState[0] - transferAmount
                        nextState = (leftJugContent, rightJugContent)
                        copyPath = currPath.copy()
                        copyPath.append(nextState)
                        queue.append(copyPath)
            
            nextState = ()
            if(currState[1] != 0):

                #empty the jug
                nextState = (currState[0], 0)
                copyPath = currPath.copy()
                copyPath.append(nextState)
                queue.append(copyPath)

                nextState = ()
                if(currState[0] != leftJug): #if not full

                    transferAmount = leftJug - currState[0]
                    if(currState[1] <= transferAmount):
                        leftJugContent = currState[0] + currState[1]
                        rightJugContent = 0
                        nextState = (leftJugContent, rightJugContent)
                        copyPath = currPath.copy()
                        copyPath.append(nextState)
                        queue.append(copyPath)
                    
                    else:

                        leftJugContent = leftJug
                        rightJugContent = currState[1] - transferAmount
                        nextState = (leftJugContent, rightJugContent)
                        copyPath = currPath.copy()
                        copyPath.append(nextState)
                        queue.append(copyPath)
                    


            
            
            




if __name__ == "__main__":

    # frame the question 
    # jug sizes 3,4 to be found 2 at smaller jug
    #<left, right>  (0,0) is initial state....(2,0)


    leftJug = 3
    rightJug = 4

    initialState = (0,0)
    targetState = (2,0)

    print(solve(leftJug, rightJug, initialState, targetState))