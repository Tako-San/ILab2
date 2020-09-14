

with open('web.txt', 'w') as web:
    for i in range(300):
        web.write(str(i) + ' ' + str(10*i) + '\n')
