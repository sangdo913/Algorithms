import re 
text = input()

c = str()
for a in text.split('[')[1:]:
    for s in a.split(']')[0].split(','):
        c += s + ' '

print(c)