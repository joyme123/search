#encoding: utf-8
import xlrd
import xdrlib,sys
reload(sys)
sys.setdefaultencoding("utf-8")

def open_excel(file = 'file.xls'):
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception,e:
        print str(e)

def excel_table_byindex(file='file.xls',colnameindex=0,by_index=0):
    data = open_excel(file)
    table = data.sheets()[by_index]
    nrows = table.nrows     
    ncols = table.ncols 
    colnames = table.row_values(colnameindex)
    list = []
    for rownum in range(1,nrows):
        row = table.row_values(rownum)
        if row:
            app = {}
            for i in range(len(colnames)):
                app[colnames[i]] = str(row[i])
            list.append(app)
    return list

def main():
    print 'read and transform...'
    tables = excel_table_byindex('file_1.xls',8)
    f = file("cn.txt","w+")

    for row in tables:
        
        first = True
        for k in row.keys():
            if first:
                f.write(row[k])
                first = False
            else:
                f.write("|")
                f.write(row[k])
        f.write('\n')


if __name__=="__main__":
    main()
