from urllib.request import urlopen
from urllib import parse
from bs4 import BeautifulSoup
from urllib.parse import parse_qs, urlparse


def get_query_field(url, field):
    try:
        return parse_qs(urlparse(url).query)[field]
    except KeyError:
        return []
        
mainurl = "http://localhost/"
print("\n\n\n" + ("*" * 150) + "\n---CRAWL : " + mainurl + "---")
html = urlopen(mainurl) # Insert your URL to extract
bsObj = BeautifulSoup(html.read(), "html.parser")

for link in bsObj.find_all('a'):    #Sayfa içindeki her bi url için
    url = link.get('href')
    print("\t------- Found URL Analyzing: " + url + "-------")
    url_params = dict(parse.parse_qsl(parse.urlsplit(url).query))
    for key in url_params:  #Sayfa içindeki her urlin her parametresi için
        #current_test_key = key
        vulnurl = url + "%26" + key + "=hacked"
        print("\t\t-----HPPed Page and analyze all urls: "+vulnurl)
        html = urlopen(vulnurl) # Insert your URL to extract
        bsObj = BeautifulSoup(html.read(), "html.parser")
        for link in bsObj.find_all('a'):
            url2 = link.get('href')
            varcount = len(get_query_field(url2,key)) #Saldırı yapılan parametrelerin değeri
            if(varcount > 1):
                print("\t\t\t HPP VULNERABLE URL:"+url2 + "\t|With parameter:" + key)
            else:
                print("\t\t\t OK:"+url)
