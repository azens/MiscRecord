import urllib2 
import xmltodict
# from bs4 import BeautifulSoup 
#
url='http://www.baidu.com'
link=urllib2.urlopen(url)
buffer=link.read()
convertedDict = xmltodict.parse(buffer);
jsonStr = json.dumps(convertedDict, indent=1);
print "jsonStr=",jsonStr;
