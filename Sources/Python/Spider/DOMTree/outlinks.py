# -*- coding: utf-8 -*-  

import urllib2  
from bs4 import BeautifulSoup 
#定义百度函数
host='http://www.guotu56.com'
url=host+'/neiyi'
def urlparse(data,sub):
    soup=BeautifulSoup(data,'lxml')
    ff=open('test.dot','w')
    ff.write('digraph G{\n')
    ff.write('rankdir=LR\n')
    ff.write('node[fontname="Consolas Italic",color=cyan]\n')
    ff.write('edge[color=green]\n')
    for x in soup.find_all('a'):
        pic=x.get('href')
        # print pic
        if pic==None:continue
        if pic[0]=='#' or pic[0:4]=='java':continue
        elif cmp(pic[0:7],'http://')==0 or cmp(pic[0:8],'https://')==0:
            # print pic
            if pic.endswith('/'):filename=pic+'index.html'
            else:filename=pic+'/index.html'
            # filename=filename.replace('http://','');
        else:
            if not pic.startswith('/'):
                sub=sub.replace('http://','');
                subpath=sub.split('/')
                subpath='/'.join(subpath[0:-1])
                pic=subpath+'/'+pic
            else:pic=host+pic
            if not pic.endswith('.html'):
                filename=pic+'index.html'
            else:filename=pic
            # filename=host+filename
        # print filename
        filename=filename.replace('https://','').replace('http://','')
        print filename
        sub=sub.replace('http://','')
        for x in '.%/':sub=sub.replace(x,'_')
        for x in '.%/&=-? ':filename=filename.replace(x,'_')
        ff.write(sub+'->'+filename+'\n')
    ff.write('}\n')
    ff.close()

# f=open('hostlist.txt','r')
# lines=f.readlines()
# for x in lines[0:1]:
    # if not x:print 'None';continue
    # data=open(x[0:-1]).read()
    # hostparse(data,x[0:-1])
data=urllib2.urlopen(url).read()
urlparse(data,url)
