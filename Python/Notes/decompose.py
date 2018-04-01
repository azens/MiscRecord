soup = BeautifulSoup(data,'lxml')
map(lambda f:f.decompose(),soup.findAll('script'))
map(lambda f:f.decompose(),soup.findAll('style'))