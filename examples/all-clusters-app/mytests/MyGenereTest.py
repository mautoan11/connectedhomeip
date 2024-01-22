import os
from os import listdir
from os.path import isfile, join
from os import walk
#from parse import *


def GenerateTest(nodeId, endpointId, folder):
    mypath = 'examples/all-clusters-app/mytests/Samples/' + folder + '/'
    mypathOutput = 'examples/all-clusters-app/mytests/'
    filenames = []
    for (dirpath, dirnames, filenames_) in walk(mypath):
        filenames.extend(filenames_)
        break
    print(filenames)
    generatedTestFiles = []
    for filename in filenames:
        with open(mypath+filename) as f:
            contents = f.read()
        contents = str(contents)
        nodeIdIndex = contents.find('nodeId:') + 7
        clusterIndex = contents.find('cluster:') +8
        endpointIndex = contents.find('endpoint:') + 9
        nodeIdIndex_End = nodeIdIndex
        clusterIndex_End = clusterIndex
        endpointIndex_End = endpointIndex
       
        
        while(contents[nodeIdIndex_End] != '\n'): nodeIdIndex_End+=1
        while(contents[clusterIndex_End] != '\n'): clusterIndex_End+=1
        while(contents[endpointIndex_End] != '\n'): endpointIndex_End+=1

        nodeId_ = contents[nodeIdIndex:nodeIdIndex_End]
        clusterId_ = contents[clusterIndex:clusterIndex_End]
        endpoint_ = contents[endpointIndex:endpointIndex_End]

        contents = contents.replace(nodeId_,str(nodeId) , 1)
        contents = contents.replace(endpoint_,str(endpointId) , 1)

        newTestFileName = f"test_{nodeId}_{endpointId}_{filename}"
        text_file = open(mypathOutput + newTestFileName, "w")
        n = text_file.write(contents)
        text_file.close()
        generatedTestFiles.append(newTestFileName)

    makeFilePath = 'Makefile'
    label = f"test_{nodeId}_{endpointId}"
    with open(makeFilePath) as f:
        contents = f.readlines()

    is_Found = False
    removingLineIndexs = []
    for i in range(len(contents)):
        if not is_Found:
            if contents[i].find(label) ==0:
                is_Found = True
                removingLineIndexs.append(i)
                continue
        elif is_Found:
            if contents[i][0] == '\t':
                removingLineIndexs.append(i)
            else: break
    print(removingLineIndexs)

    for i in sorted(removingLineIndexs, reverse=True):
        del contents[i]

    print(contents[-1]," len=", len(contents[-1]))


    if len(contents[-1]) > 0 and contents[-1][-1] != '\n':
        contents.append(f"\n{label}:\n")
    else : contents.append(f"{label}:\n")


    for generatedTestFile in generatedTestFiles:
        contents.append(f"\t{generatedTestFile}\n")
    
    text_file = open(makeFilePath, "w")
    for content in contents:
        text_file.write(content)
    text_file.close()




        


GenerateTest(1111,41,'OO')
GenerateTest(1111,42,'OO')


# config:
#     nodeId: 1111
#     cluster: "On/Off"
#     endpoint: 41