import subprocess
import time
import requests
from bs4 import BeautifulSoup
import re
import json
import pickle
import os
import glob
import sys

# return execute time[sec] (accuracy ≈ 10msec)
def execute(programname,infilename,outfilename):
    with open(infilename,encoding="utf-8",mode="r") as infile:
        with open(outfilename,encoding="utf-8",mode="w") as outfile:
            start = time.perf_counter()
            try:
                subprocess.run(programname,stdin=infile,stdout=outfile,check=True,timeout=5)
            except TimeoutExpired:
                return 5.0
            return time.perf_counter() - start

def getio(programname,website=None):
    if not os.path.exists(".secret/session.pickle"):
        login()
    if website==None:
        with open("config/thismatch.json") as jsonfile:
            config=json.load(jsonfile)
        website="https://atcoder.jp/contests/"+config["contest"]+"/tasks/"+config["taskname"]+"_"+programname
    with open(".secret/session.pickle","rb") as fp:
        (s,csrftoken)=pickle.load(fp)
    samples = BeautifulSoup(s.get(website).content,"html.parser").find_all("pre")
    samples = samples[0:len(samples)//2] #delete english version
    # print(samples)
    isinput=True
    sampleNo=1
    startNo=1 if len(samples)%2==1 else 2 #input sample or IO sample
    for sample in samples[startNo:]:
        with open("io/"+programname+"_"+str(sampleNo)+"_"+("in" if isinput else "out")+".txt",encoding="utf-8",mode="w") as txtfile:
            txtfile.write(re.sub("[\r\n]{2,}", "\n", sample.string))
        isinput = not isinput
        if isinput:
            sampleNo += 1
    print("getio complete.")

def submit(programname):
    if not os.path.exists(".secret/session.pickle"):
        login()
    with open(".secret/session.pickle","rb") as fp:
        (s,csrftoken)=pickle.load(fp)
    with open("config/thismatch.json") as jsonfile:
        config=json.load(jsonfile)
    with open(programname+".cpp",encoding="utf-8") as prog:
        source = prog.read()
    data = {
        "csrf_token": csrftoken,
        "data.LanguageId": "3003", # c++14(gcc 5.4.1)
        "data.TaskScreenName": config["taskname"]+"_"+programname,
        "sourceCode": source
    }
    #print(data)
    r=s.post("https://atcoder.jp/contests/"+config["contest"]+"/submit",data)
    print(r.status_code)
    print("submit complete.")

def cleanio():
    for samplefile in glob.glob("io/*"):
        os.remove(samplefile)
    print("cleanio complete.")

def login():
    loginpage="https://atcoder.jp/login"
    with open(".secret/atcoder_login.json",encoding="utf-8",mode="r") as jsonfile:
        account = json.load(jsonfile)
    s = requests.session()
    csrftoken = BeautifulSoup(s.get(loginpage).text,"html.parser").find_all("input")[0]["value"]
    logindata={
        "csrf_token":csrftoken,
        "password":account["password"],
        "username":account["username"]
    }
    r = s.post(loginpage,logindata)
    with open(".secret/session.pickle","wb") as fp:
        pickle.dump((s,csrftoken),fp)
    print("login complete.")

def issame(file1,file2):
    with open(file1) as fp1:
        with open(file2) as fp2:
            l1=fp1.readline()
            while l1:
                l2=fp2.readline()
                if(l1!=l2):
                    return False
                l1=fp1.readline()
            return True

def judge(programname):
    if not os.path.exists("io/"+programname+"_1_in.txt"):
        getio(programname)
    sampleNo = 1
    (ac,wa,tle)=(0,0,0)
    while os.path.exists("io/"+programname+"_"+str(sampleNo)+"_in.txt"):
        t = execute(programname+".exe","io/"+programname+"_"+str(sampleNo)+"_in.txt","io/"+programname+"_"+str(sampleNo)+"_out_tmp.txt")
        if t>4.0:
            print("sample "+str(sampleNo)+": [TLE]")
            tle+=1
        elif issame("io/"+programname+"_"+str(sampleNo)+"_out.txt","io/"+programname+"_"+str(sampleNo)+"_out_tmp.txt"):
            print("sample "+str(sampleNo)+": [AC] "+str(int(1000*t))+"msec")
            ac+=1
        else:
            print("sample "+str(sampleNo)+": [WA] "+str(int(1000*t))+"msec")
            wa+=1
        sampleNo+=1
    sampleNo-=1
    print(str(sampleNo)+"judges complete.")
    print(str(ac)+"AC,"+str(wa)+"WA,"+str(tle)+"TLE")
    return ac>0 and ac==sampleNo

def uselibrary(programname):
    with open(programname+".cpp") as fp:
        l=fp.readline()
        while l:
            if l.find('#include"lib/')>=0:
                return True
            l=fp.readline()
        return False

def help():
    print("usage:")
    print("./sandbox.py -judge [programname]  : judge program from sample.")
    print("./sandbox.py -submit [programname] : submit program.")
    print("./sandbox.py -cleanio              : delete all files in ./io/ folder")

if len(sys.argv)==1:
    help()
elif sys.argv[1]=="-judge":
    judge(sys.argv[2])
elif sys.argv[1]=="-submit":
    if judge(sys.argv[2]):
        if uselibrary(sys.argv[2]):
            print("using library. submit anyway? [y/N]: ",end="")
            yn=input()
            if not (yn=="y" or yn=="Y"):
                print("submit interrupted.")
                sys.exit()
        submit(sys.argv[2])
    else:
        print("submit interrupted.")
elif sys.argv[1]=="-cleanio":
    print("delete all files in ./io/ folder. [y/N]: ",end="")
    yn=input()
    if yn=="y" or yn=="Y":
        cleanio()
    else:
        print("cleanio interrupted.")
else:
    help()