# -*- coding: utf-8 -*- 
from StringIO import StringIO

import gzip
import urllib2

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko'
}
def webread(url):
	request = urllib2.Request(url,None,header)
	# request.add_header('Accept-encoding', 'gzip')
	response = urllib2.urlopen(request)
	if response.info().get('Content-Encoding') == 'gzip':
		buf = StringIO( response.read())
		f = gzip.GzipFile(fileobj=buf)
		data = f.read()
		return data

url="http://img.zngirls.com/article/10374/01_s.jpg"
open("index.jpg",'w').write(urllib2.urlopen(urllib2.Request(url,None,header)).read())
