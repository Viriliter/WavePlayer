#web scrapping code made by Rishabh Bhardwaj
# follow me at http://www.knoobypie.com/about-me/
# folow me on linkedin @https://www.linkedin.com/in/rishabh-bhardwaj-791903171/
# github https://github.com/rishabh3354

# <<<<<<<<-pre-requestie->>>>>>>>>>>>>>>>
# install the following python module:
# pip install requests
# pip install bs4
# output will be in html format, Recommended to save file in html format


import requests
from bs4 import BeautifulSoup
import sys
import json

queries = sys.argv[1:]

query_str = " ".join(queries)
suffix = "&x=09435e1ecfc5954bec2fc8bc50ae7a288a3ea14197cde2ea564b7a8d6883f105"
# print(query_str)
# query_str = input("enter song name\n")
# query_str = "fadded"

for query in queries:
    url = "https://search.azlyrics.com/search.php?q=" + query + suffix

    headers = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0'}

    try:
        response = requests.get(url, timeout=10, headers=headers)

    except requests.ConnectionError as err:
        print("<<<<<< PLEASE CHECK YOUR INTERNET CONNECTION >>>>")
    except requests.Timeout as err:
        print("OOPS!! Timeout Error")
    except requests.RequestException as err:
        print("OOPS!! UNEXPECTED Error")

    else:

        data = response.text

        soup = BeautifulSoup(data, 'lxml')
        boldtag = soup.find_all("td", {"class": "text-left visitedlyr"})

        tags = soup.find_all('a')

        l2 = []
        for x in tags:
            l2.append(x.get('href'))
        song_url = []
        for y in l2:
            if "www.azlyrics.com/lyrics/" in y:
                song_url.append(y)

        boldtag=list(boldtag)

        if len(song_url)!=0:
            sl=[]
            for c in boldtag:
                c=str(c)
                if 'href="https://www.azlyrics.com/lyrics/' in c:
                    sl.append(c)

            song=[]
            artist=[]

            for itm in range(len(sl)):

                kk=sl[itm].split("<b>")
                pp=kk[1].split("</b")
                song.append(pp[0])

                kk2=sl[itm].split("<b>")
                pp2=kk2[2].split("</b>")
                artist.append(pp2[0])

            song_title = []
            song_id = []
            artist_name = []

            finaldata = []
            dictdata = {}

            for counter in range(0, len(song_url)):
                dictdata['song_id'] = str(counter)
                dictdata['song_name'] = str(song[counter])
                dictdata['song_artist'] = str(artist[counter])
                dictdata['song_url'] = str(song_url[counter])
                finaldata.append(dictdata.copy())
            r = json.dumps(finaldata)
            print(r)
            sys.stdout.flush()
            sys.exit()
        else:
            pass
print("lYRICS NOT FOUND")
sys.stdout.flush()
sys.exit()
