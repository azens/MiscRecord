# -*- coding: utf-8 -*-
import scrapy


class ZngirlsSpider(scrapy.Spider):
    name = "zngirls"
    allowed_domains = ["zngirls.com"]
    start_urls = (
        'http://www.zngirls.com/',
    )

    def parse(self, response):
        print(response.url)
        links = response.xpath('//a/@href').extract()
        # for url in links:
            # yield Request(url, callback=self.parse)
        # print(url)
        # filename = response.url.split("/")[-2]
        # with open(filename, 'wb') as f:
            # f.write(response.body)
        # pass
