import os
from os import listdir
from os.path import isfile, join
from os import walk
#from parse import *

allTestLablels = []
def GenerateTest(nodeId, endpointId, folder):
    
    mypath = 'examples/all-clusters-app/mytests/Samples/' + folder + '/'
    mypathOutput = 'examples/all-clusters-app/mytests/'
    filenames = []
    for (dirpath, dirnames, filenames_) in walk(mypath):
        filenames.extend(filenames_)
        break
    
    generatedTestFiles = []
    for filename in filenames:
        if filename[len(filename)-4:len(filename)] != 'yaml': continue
        with open(mypath+filename) as f:
            contents = f.read()
        contents = str(contents)
        nodeIdIndex = contents.find('nodeId:') + 8
        clusterIndex = contents.find('cluster:') +9
        endpointIndex = contents.find('endpoint:') + 10
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


    #Handle make file
    makeFilePath = 'Makefile'
    label = f"test_{nodeId}_{endpointId}_{folder}"
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

    for i in range(len(contents)): 
        if contents[i].find('testall:') ==0:
            removingLineIndexs.append(i)
        if contents[i].find(f'test_{nodeId}_{endpointId}:') ==0:
            removingLineIndexs.append(i)


   

    for i in sorted(removingLineIndexs, reverse=True):
        del contents[i]



    if len(contents[-1]) > 0 and contents[-1][-1] != '\n':
        contents.append(f"\n{label}:\n")
    else : contents.append(f"{label}:\n")
    allTestLablels.append(label)
    
    
    for generatedTestFile in generatedTestFiles:
        ss=generatedTestFile.replace('.yaml','')
        ss=f"\t./scripts/tests/yaml/chiptool.py tests {generatedTestFile}\n"
        
        contents.append(ss)
    
    #testall
    testAllString = "testall: "
    testAllString_eachDevice = {}
    for labbb in allTestLablels:
        testAllString += f"{labbb} " 
        vals = labbb.split('_')
        val_key = vals[0] + '_'+vals[1] + '_' + vals[2]

        if labbb.find(f"test_{nodeId}_{endpointId}") !=0: continue

        if val_key not in testAllString_eachDevice:
            testAllString_eachDevice[val_key] = [labbb]
        else: testAllString_eachDevice[val_key].append(labbb)

    
    
    for k,v in testAllString_eachDevice.items():

        ss = k + ':'
        for vv in v:
            ss += ' ' + vv
        ss += '\n' 
        
        contents.append(ss)


    contents.append(testAllString + "\n")
    #testeach endpoint


    text_file = open(makeFilePath, "w")
    for content in contents:
        text_file.write(content)
    text_file.close()

    


GenerateTest(1111,41,'OO')
GenerateTest(1111,42,'OO')
GenerateTest(1111,42,'LVL')
GenerateTest(1111,43,'OO')
GenerateTest(1111,43,'LVL')
GenerateTest(1111,43,'CC')

# config:
#     nodeId: 1111
#     cluster: "On/Off"
#     endpoint: 41