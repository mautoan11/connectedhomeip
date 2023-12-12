from matter_chip_tool_adapter.adapter import Adapter
import binascii
import codecs
import base64
import subprocess
import parse
import json

dir = "/home/nuc6/Work/chip-tool/"

result = subprocess.run([dir+"chip-tool", "onoff", "toggle", "1111", "3"], stdout=subprocess.PIPE)
out = result.stdout.decode('utf-8')
print(out)


lines = out.split('\n')
print(len(lines))

format_string = "[{}][{}]{}:{}:{}"
json_string = ""
for line in lines:
    a = parse.parse(format_string, line)
    if a == None: continue
    if a[3] != 'DMG': continue
    if a[4].find('ICR moving to') == 1: continue
    if a[4].find('Received Command Response Status') == 1: continue
    if a[4].find('All ReadHandler-s are clean') ==1: continue
    if a[4].find('InvokeResponseMessage =') ==1: continue
    json_string += a[4].replace('\t',"")

    print(a)
print('\n\n',json_string,'\n\n')
while json_string[-1]!='}':
    json_string = json_string[0:len(json_string)-1]
print('\n\n',json_string,'\n\n')
json_string = json_string.replace('=',':')
json_string = json_string.replace('[','[{').replace(']','}]')
print('\n\n',json_string,'\n\n')


S = list(json_string)
for i in range(len(S)):
    if S[i] == ':':
        j = i-1
        while j>=1:
            if S[j] == ' ' and S[j-1]!=' ':
                S[j] = '\"'
            if S[j] != ' ' and S[j-1]==' ':
                S[j-1] = '\"'
                break
            j-=1
        # j = i+1
        # while j<=len(S)-2:
        #     if S[j] == ' ' and S[j-1]!=' ':
        #         S[j] = '\"'
        #         break
        #     if S[j] != ' ' and S[j-1]==' ':
        #         S[j-1] = '\"'
        #     j+=1

s = "".join(S)
print('\n\n',s,'\n\n')
data = json.loads(s)
print(data)
