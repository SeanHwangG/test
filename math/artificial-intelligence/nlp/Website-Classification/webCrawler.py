import urlparse
import mechanize

url = "http://facebook.com/"
depth = 1

def scraper(root, steps):
    urls = [root]
    visited = [root]
    counter = 0
    while counter < steps:
        step_url = scrapeStep(urls)
        urls = []
        for u in step_url:
            if u not in visited:
                urls.append(u)
                visited.append(u)
        counter += 1

    return visited

def scrapeStep(root):
    result_urls = []
    br = mechanize.Browser()
    br.set_handle_robots(False)
    br.addheaders = [('User-agent', 'Firefox')]

    for url in root:
        try:
            br.open(url)
            for link in br.links():
                new_url = urlparse.urljoin(link.base_url, link.url)
                result_urls.append(new_url)
        except Exception as e:
            print str(e)
    return result_urls


print scraper(url , depth)