import subprocess
def download(url,filename):
    cmd = 'wget '+url + ' -O ' + filename
    # print(cmd)
    # cmd = 'curl --compressed -o '+filename+' '+url
    subprocess.call(cmd)
    
# head = 'http://news.baidu.com/ns?word=%E5%A4%A9%E4%B8%8B%E6%97%A0%E8%B4%BC&pn='
# end = '&cl=2&ct=1&tn=news&rn=20&ie=utf-8&bt=0&et=0'
head = 'http://news.baidu.com/ns?word=%28%E5%93%88%E6%B4%BD%E4%BC%9A%20%E4%B8%AD%E4%BF%84%E5%8D%9A%E8%A7%88%E4%BC%9A%20%E4%B8%AD%E5%9B%BD-%E4%BF%84%E7%BD%97%E6%96%AF%E5%8D%9A%E8%A7%88%E4%BC%9A%29&pn='
end ='&cl=2&ct=1&tn=newsdy&rn=20&ie=utf-8&bt=1400256000&et=1495036799'
for i in range(2,34):
    url = head + str(i*20-20)+end
    filename = str(i)+'.html'
    download(url,filename)