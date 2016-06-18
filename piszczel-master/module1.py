import os
import time

input_file = open('notes.txt', 'r')
content = str(input_file.read())
#replacement section
content = content.replace('dis4', '311')
content = content.replace('ais4', '466')
content = content.replace('gis4', '415')
content = content.replace('dis5', '622')

content = content.replace('dis5', '622')

content = content.replace('c4', '261')
content = content.replace('d4', '293')
content = content.replace('e4', '330')
content = content.replace('f4', '349')
content = content.replace('g4', '392')
content = content.replace('a4', '440')
content = content.replace('h4', '494')
content = content.replace('c5', '523')
content = content.replace('d5', '587')

#writting results
output_file = open('music.txt', 'w')
output_file.write(content)
output_file.close()

#executing
os.execv('Piszczel.exe',['music.txt'])
#os.execl('Piszczel.exe')
#time.sleep(10)