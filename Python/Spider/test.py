import threading
import urllib

def saveImg(imgUrl,fileName):
    user_agent = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'
    headers = {'User-Agent':user_agent}
    try:
        req = urllib2.Request(imgUrl,headers=headers)
        res = urllib2.urlopen(req,timeout=5)
        data = res.read()
    except socket.timeout as e:
        print "saveImgTimeOut"
        return False
    f = open(fileName,'wb')
    f.write(data)
    f.close()
    
class threadDownload(threading.Thread):
    def __init__(self,que,no):
        threading.Thread.__init__(self)
        self.que = que
        self.no = no
    def run(self):
        while True:
            if not self.que.empty():
                saveImg(self.que.get(),'os'+str(self.no)+'.jpg')
            else:
                break

def saveToFile(FileName,srcList):
    a=0
    srcTuple = (srcList)
    FileName = 'os'+FileName.strip()
    res = mkdir(FileName)
    if res == False:
        return False
    #os.mkdir(FileName)
    os.chdir(FileName)
    que = Queue.Queue()
    for sl in srcList:
        que.put(sl)
    for a in range(0,srcList.__len__()):
        threadD = threadDownload(que,a)
        threadD.start()
        #print threading.enumerate()
    while threading.active_count() != 0:
        if threading.active_count() == 1:
            print FileName+"  is Done"
            return True
            



 
