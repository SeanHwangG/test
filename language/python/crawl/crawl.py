# coding: utf-8

from selenium import webdriver
from time import sleep


# Do not use chrome driver, because it can only download max 100 files.
driver = webdriver.Firefox()

driver.get("https://domainpunch.com/premium/wordmon.php")
sleep(6)

a = 1           # From this day.
counter = 1     # change this number according to current month.
# if Today is October(10) then counter is 5, if want to download for March (5)

a -= 1
# Change Month
for i in range(counter):
  driver.find_element_by_xpath('//*[@title="Prev"]').click()
  sleep(0.5)

while True:
  a += 1
  try:
    print(a)
    driver.find_element_by_link_text(str(a)).click()
    sleep(5)
    try:
      # Go to 1 - 2000 for next day.
      driver.find_element_by_xpath('//*[@title="First Page"]').click()
    except:
      pass
    sleep(10)
  except:
    # Finish program download is done for that month
    exit()

  # Change list size to 2000
  my_select = webdriver.support.select.Select(driver.find_element_by_xpath('//*[@title="Records per Page"]'))
  my_select.select_by_index(3)
  sleep(5)

  while True:
    # Click Download list
    driver.find_element_by_xpath('//*[@title="Download List"]').click()
    # change to next grid (ex. 0-2000 to 2001- 4000)
    if "disable" in driver.find_element_by_id('next_added-grid-pager').get_attribute("class"):
      break
    driver.find_element_by_xpath('//*[@title="Next Page"]').click()
    sleep(5)
