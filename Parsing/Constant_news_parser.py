import schedule
import re
import requests
from bs4 import BeautifulSoup

URL = 'https://russia24.pro/news/'
HEADERS = {'user-agent': 
           'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36',
          'accept': '*/*'}

news = []
control_id = []
i = 0

def get_html(url, params = None):
    r = requests.get(url, headers=HEADERS, params=params)
    return r

def parsing_text():
    html = get_html(news[len(news) - 1]['link'])
    if html.status_code == 200:
        soup = BeautifulSoup(html.text, 'html.parser')
        item1 = soup.find('div', class_='r24_text').get_text()
        pattern = r"^( *)"
        news[len(news) - 1]['article'] = item1
        news[len(news) - 1]['article'] = re.sub(pattern, "", news[len(news) - 1]['article'])
    else:
        news.pop()

def get_content(html):
    soup = BeautifulSoup(html, 'html.parser')
    items = soup.find_all('div', class_='r24_article')

    for item in items:
        news.append({'title' : item.find('div', class_='r24_body').find('span').get_text(),
                     'link' : item.find('div', class_='r24_body').find('a').get('href'),
                     'date' : item.find('time').get_text(),
                    })
        id = news[len(news) - 1]['link'][-10:][:9]
        if len(control_id) == 0 or control_id.count(id) == 0:
            control_id.append(id)
            parsing_text()
        else:
            news.pop()

def parse():
    html = get_html(URL)
    if html.status_code == 200:
        get_content(html.text)


def job():
    global i
    parse()
 
    while i < len(news):
        print(news[i]['title'])
        print(" ")
        print(news[i]['article'])
        print(" ")
        print(news[i]['link'])
        print(" ")
        print(news[i]['date'])
        print("------------------------------------------")
        i += 1

schedule.every(5).seconds.do(job)
#schedule.every(30).minutes.do(job)

while True:
    schedule.run_pending()