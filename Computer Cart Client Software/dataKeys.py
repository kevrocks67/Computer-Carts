#This file defines the keys for listview dict adapter
path_to_file = "data.txt"
data_file = open(path_to_file, 'r')
array = []

for row in data_file:
    array.append(row)

#print(array)
data_file.close()


sql_data = {
    line: {'name': line,
           'is_selected': False} for line in array}