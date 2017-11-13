//For groovysh
// groovy.grape.Grape.grab(group:"org.jsoup", module:"jsoup", version:"1.11.1")
//For groovy
@Grab(group="org.jsoup", module="jsoup", version="1.11.1")

import org.jsoup.Jsoup;
Jsoup.connect("http://cnblogs.com").get().select("#post_list > div > div.post_item_body > h3 > a").each {
    println it.text()
}