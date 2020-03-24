import os
import sys

# argv
# 1 - prog name
# 2 - testd floder
# 3 - prefix tests files names
# 4 - prefix answers files names
# 5 - name file result prog
# 6 - cout of tests

assert(len(sys.argv)==7)

numOfTests = int (sys.argv[6])

print("\n"+sys.argv[1])

for i in range(1, numOfTests+1):
    pathToTest= "./"+sys.argv[2]+"/"+sys.argv[3]+str(i)
    pathToAns = "./"+sys.argv[2]+"/"+sys.argv[4]+str(i)
    pathToRes = "./"+sys.argv[5]

    os.system("./"+sys.argv[1] + " < " + pathToTest + " > "+ pathToRes )

    f = open(pathToTest)
    test = f.read().strip()
    f.close()
    f = open(pathToAns)
    ans = f.read().strip()
    f.close()
    f = open(pathToRes)
    res = f.read().strip()
    f.close()
    print("\nTest #"+str(i) + " " + "SUCCESS" if ans==res else "\nTest #"+str(i) + " " + "FAIL")
    print("Input:")
    print(test)
    print("Expected result:")
    print(ans)
    print("Result:")
    print(res)
    os.remove(pathToRes)
