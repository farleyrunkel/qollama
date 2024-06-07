import requests
from PyQt6.QtCore import QObject, pyqtSignal
from bs4 import BeautifulSoup, Tag, NavigableString
import re
import os
import json
import time
import logging
import base64
# 配置日志记录
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

class WebScraper(QObject):
    scraped_data = pyqtSignal(str)

    def __init__(self):
        super().__init__()

    def scrape_website(self, url):
        logging.debug(f"开始爬取网站: {url}")
        response = requests.get(url)
        html_content = response.text
        soup = BeautifulSoup(html_content, 'html.parser')

        links = [a['href'] for a in soup.find_all('a', class_=True, href=True)]
        logging.debug(f"提取到的链接数量: {len(links)}")

        modelfiles_links = ["https://openwebui.com" + link for link in links if link.startswith('/modelfiles?category')]
        logging.debug(f"筛选后的 /modelfiles 链接数量: {len(modelfiles_links)}")

        # modelfiles_links = modelfiles_links[:2]
        logging.debug(f"限制后的 /modelfiles 链接: {modelfiles_links}")

        for link in modelfiles_links:
            logging.debug(f"开始爬取分类页面: {link}")
            categories_links = self.scrape_category(link)
            logging.debug(f"分类页面提取到的链接: {categories_links}")

            for category_link in categories_links:
                logging.debug(f"开始爬取模型页面: {category_link}")
                model_data = self.scrape_model(category_link)
                logging.debug(f"模型页面提取的数据: {model_data}")
                self.scraped_data.emit(f"Model Data: {model_data}\n")
                time.sleep(1)

    def scrape_category(self, url):
        logging.debug(f"开始爬取分类页面: {url}")
        response = requests.get(url)
        html_content = response.text
        soup = BeautifulSoup(html_content, 'html.parser')

        links = [a['href'] for a in soup.find_all('a', class_=True, href=True)]
        logging.debug(f"提取到的分类页面链接数量: {len(links)}")

        model_links = ["https://openwebui.com" + link for link in links if link.startswith('/m')]
        logging.debug(f"筛选后的模型链接数量: {len(model_links)}")

        # model_links = model_links[:2]
        logging.debug(f"限制后的模型链接: {model_links}")

        return model_links

    def scrape_model(self, url):
        logging.debug(f"开始爬取模型页面: {url}")
        response = requests.get(url)
        html_content = response.text
        soup = BeautifulSoup(html_content, 'html.parser')
        body = soup.find('body')

        with open("page_content.html", "w", encoding="utf-8") as file:
            file.write(html_content)

        img = body.find('img', src=True, class_=True, alt=True)

        r00 = img.parent.parent
        r01 = r00.next_sibling
        name = r01.next.next.next.next
        logging.debug(f"提取到的名称: {name.text}")

        intro = name.parent.find_all('div')[-1]
        logging.debug(f"提取到的简介: {intro.text}")

        r0 = r00.parent

        def get_next_sibling_tag(tag):
            sibling = tag.find_next_sibling()
            while sibling and not isinstance(sibling, Tag):
                sibling = sibling.find_next_sibling()
            return sibling

        r1 = get_next_sibling_tag(r0)

        r10 = r1.next_element

        tag_name_section = r1.find_all('div')[0]
        tag_name = tag_name_section.find('div').text.strip()
        latest_version = tag_name_section.find_all('div')[1].text.strip()

        creator_section = r1.find_all('div')[4]
        creator_label = creator_section.find('div').text.strip()
        creator_name = creator_section.find('a').text.strip()
        creator_href = creator_section.find('a')['href']

        downloads_section = r1.find_all('div')[7]
        downloads_label = downloads_section.find('div').text.strip()
        downloads_count = downloads_section.find_all('div')[1].text.strip()

        logging.debug(f"Tag Name: {tag_name}")
        logging.debug(f"Latest Version: {latest_version}")
        logging.debug(f"{creator_label}: {creator_name}")
        logging.debug(f"Creator Link: {creator_href}")
        logging.debug(f"{downloads_label}: {downloads_count}")

        r2 = body.find_all('div', class_='my-2')[1]
        categories = r2.find_all('a')
        logging.debug(f"提取到的类别: {[a.text for a in categories]}")

        r3 = r2.next_sibling
        content = body.find('pre')
        logging.debug(f"提取到的内容: {content.text}")

        if not os.path.exists('models'):
            os.makedirs('models')
        # 保存为图片文件

        def extract_before_colon(data):
            # 使用 split 方法以冒号为分隔符拆分字符串
            parts = data.split(':')
            
            # 返回冒号前的部分
            return parts[0]
        
        with open(os.path.join('models', f'{extract_before_colon(latest_version.strip())}.json'), 'w', encoding='utf-8') as f:
            json.dump({
                'url': 'url',
                'name': name.text.strip(),
                'intro': intro.text.strip(),
                'tag': latest_version,
                'author': creator_name,
                'download': downloads_count,
                'categories': [a.text.strip() for a in categories],
                'content': content.text.strip(),
                'image': img['src']
            }, f, ensure_ascii=False, indent=4)
            f.write('\n')
        logging.debug('保存成功')
        # 休眠一秒，避免被封IP
        time.sleep(3)

def create_scraper():
    return WebScraper()

scraper = create_scraper()
scraper.scraped_data.connect(lambda data: print("Scraped Data:\n", data))

scraper.scrape_website("https://openwebui.com/")
