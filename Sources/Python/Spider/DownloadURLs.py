# -*- coding: utf-8 -*-  


import os
import re
import Queue 
import urllib
import urllib2 
import threading  


import subprocess
# from bs4 import BeautifulSoup


# f=open('item3.txt','r')

# lines=f.readlines()
# f.close()
# total = []
# start=0

# def GetImage(url,filename):
    # try:
        # link=urllib2.urlopen(url)
    # except: print filename+' timeout';return
    # print filename
    # if link:
        # ff=open(filename,'wb')
        # try:
            # buffer=link.read()
        # except:print 'fail';return
        # ff.write(buffer)
        # ff.close()

def download(url):
    filename=url.replace('http://','')
    path=filename.split('/')
    path='/'.join(path[0:-1])
    if not os.path.exists(path):os.makedirs(path)
    if os.path.exists(filename) or os.path.exists(filename+".html"):return
    # GetImage(url,filename)
    # cmd = 'wget --header=\"accept-encoding:gzip\" '+url+' -O '+filename
    cmd = 'wget '+url+' -O '+filename
    # cmd = 'curl --compressed -o '+filename+' '+url
    subprocess.call(cmd)
    # urllib.urlretrieve(url, filename, callbackfunc)
    
    

class Download(threading.Thread):  
    def __init__(self,que):  
        threading.Thread.__init__(self)  
        self.que=que  
    def run(self):  
        while True:  
            if not self.que.empty():  
                print('-----%s------'%(self.name))  
                download(self.que.get())
                # os.system('wget '+self.que.get())  
            else:  
                break  
  
f=open('item3.txt','r')
link=f.readlines()[0:1000]
f.close()

num = 10

que=Queue.Queue()  
for l in link:  
    que.put(l[:-1])  
for i in range(num):  
    d=Download(que)  
    d.start()  
  


    
