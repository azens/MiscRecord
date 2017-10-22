import urllib2
import re  
import Queue  
import threading  
import os  
class download(threading.Thread):  
    def __init__(self,que):  
        threading.Thread.__init__(self)  
        self.que=que  
    def run(self):  
        while True:  
            if not self.que.empty():  
                print('-----%s------'%(self.name))  
                os.system('wget '+self.que.get())  
            else:  
                break  
  
f=open('item3.txt','r')
link=f.readlines()[0:100]
f.close()

num = 5

que=Queue.Queue()  
for l in link:  
    que.put(l)  
for i in range(num):  
    d=download(que)  
    d.start()  
  
