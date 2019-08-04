from openpyxl import Workbook
import subs as s

def write(filename):
    lines=0
    book = Workbook()
    sheet = book.active
    title = [['Name',
              'Content',
              '%',
              'State',
              'Molar Wt',
              'Fr. Pt',
              'B. Pt',
              'Comments',
              'Performance']]
    for t in title:
        sheet.append(t)
        lines+=1
    for y in range(len(s.arr)): #enter n number of rows
        vals = [[s.arr[y].name,
                s.arr[y].cont[0][0],
                s.arr[y].cont[0][1],
                s.arr[y].form,
                s.arr[y].mWt,
                s.arr[y].fPt,
                s.arr[y].bPt,
                s.arr[y].cmnts]]
        for v in vals:
            sheet.append(v)
            lines+=1
        for q in range(len(s.arr[y].pfrm)):
            sheet.cell(row=lines,column=9+q).value=s.arr[y].pfrm[q]
        for n in range(1,len(s.arr[y].cont)):
            lines +=1
            sheet.cell(row=lines,column=2).value= s.arr[y].cont[n][0]
            sheet.cell(row=lines,column=3).value= s.arr[y].cont[n][1]    
    book.save(filename+'.xlsx')
