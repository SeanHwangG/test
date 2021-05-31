"""
 NOTE: change line # 8,9 27-30 to connect DB
 
 F Column: Checks in DB
 G Column: Common Name
 H Column: Server Name
"""
excel_loc = "test.xls"
sheet_name = "test"

from xlutils.copy import copy
from xlrd import open_workbook
from getCNSN import getCNSN
import psycopg2

book_r = open_workbook(excel_loc)
sheet_r = book_r.sheet_by_name(sheet_name)

book_w = copy(book_r)
sheet_w = book_w.get_sheet(0)

URL = [sheet_r.cell_value(r, 0) for r in range(sheet_r.nrows)]

index = 0

try:
    conn = psycopg2.connect("dbname='postgres'\
                               user='postgres'\
                               host='localhost'\
                           password='password'")
except Exception as e:
    print e
    print "unable to connect to the database"
    exit()

for url in URL:
    index += 1
    if index == 1:
       continue

    cnsn = getCNSN(url)
    cur = conn.cursor()

    cur.execute("select count(cn) from https where cn = '%s'" % (str(cnsn[0]) + "' or cn = '" + str(cnsn[1])))
    conn.commit()

    contains = "O"
    if '0' in str(cur.fetchall()):
        contains = "X"

    sheet_w.write(index - 1, 5, contains)
    sheet_w.write(index - 1, 6, cnsn[0])
    sheet_w.write(index - 1, 7, cnsn[1])

    if index % 500 == 5:
        print "STILL GETTING CN, SN"
        book_w.save(excel_loc)

print "FINISHED"
book_w.save(excel_loc)
