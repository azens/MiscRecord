def convert(path):
    l=path.split('/')
    t=len(l)-2
    print t
    s=''
    for x in range(t):
        s+='/..'
    s=s[1:]
    print s
    f=open(path,'r')
    data=f.read()
    f.close()
    ff=open(path,'w')
    ff.write(data.replace('href="','href="'+s).replace('src="','src="'+s))
    ff.close()
path='www.guotu56.com/neiyi/index.html'
convert(path)