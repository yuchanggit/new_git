# encoding: utf-8

# learn from here
# http://tech.marsw.tw/blog/2014/09/03/getting-started-with-python-in-ten-minute


# 0
"""
print "Hello World"
"""

# 1
"""
x = 3
x += 2
x -= 1 
print x
x,y = 99.99,5 
print x,y
"""

# 2
"""
my_list = []
my_list.append(1) 
my_list.append(2) 


my_list2 = [55.55,"Hi",3,99,22278,222]
my_list2[0]=333.333

#print len(my_list),sum(my_list),my_list2.count(222)
#print my_list2[0],my_list2[-1],my_list2[1:3],my_list2[2:]  

print my_list2[0],my_list2[-3],my_list2[1:4],my_list2[3:]
"""

# 3

"""
passwd={'Mars':00000,'Mark':56680,'Apple':333,'Hello':444}
passwd['Happy']=9999     
passwd['Smile']=123456

#del passwd['Mars']
#passwd['Mark']=passwd['Mark']+1

print passwd
#print passwd.keys()
#print passwd.get('Tony') 
#print passwd.get('Apple')
"""

# 4
"""
admins = set()
users= set()
users.add('Smile')
users.add('Tony')
users.add('Happy')
users.add('Sherry')
users.add('Allen')
users.add('Andy')
users.add('Mars')


#users = {'Smile', 'Tony', 'Happy', 'Sherry' ,'Allen', 'Andy' , 'Mars'}
admins.add('ihc')
admins.add('Mars')

print admins & users
print admins | users
print admins ^ users
print admins - users   
print users - admins 
"""


"""
users = set()  
#users  = {'Smile', 'Tony'}
users.add('Smile')
users.add('Tony')
print users
"""

# 5
"""
s = "Hello"  
s += 'World'
s1 = "HelloWorld".replace("ll","1")
s2 = "Hello"[0]+"i" 
print s,s1,s2,len(s)
"""

# 6
"""
s3 = "This is a sentence. I am Yu-hsiang Chang"
s3_split=s3.split(' ')
print s3_split
"""

# 7
# skip the practice Chinese word

# 8
"""
x=2**3
y=3/2
s="3"
print ord('a'),ord('c'),chr(ord('a')+2) 
print y,int(s)/2,float(s)/2,3%2
print str(x+y),str(x)+str(y)
"""

# 9
"""
my_list=[]

for i in range(0,10):  

      my_list.append(i+1)
      
print my_list
"""

"""
my_list=[]
for i in range(0,10): 

    my_list.append(i*3)
#      print my_list
print my_list

if my_list[0]==1 and len(my_list)<10:
      my_list[0]+=1
      print "1 state"

elif (18 in my_list) or not(len(my_list)==10):
      print "2 state"
      print "range(i,j) is i~j-1"

else:
      print "3 state"  
      print "none of above"
for i in my_list:      
      print i,         
print
"""

# 10

"""
def my_function(x,y):
    return x-10,y+10
x,y = my_function(10,20)
print x,y
"""

# 11
"""

class Student:  
    def __init__(self, name, grade, age):  
        self.name = name  
        self.grade = grade  
        self.age = age  
    def set_name(self, name):  
        self.name = name  


student_objects=[]
student_objects.append( Student('john', 'B', 15) )
student_objects.append( Student('dave', 'A', 12) )
student_objects.append( Student('jane', 'A', 10) )
student_objects[0].set_name('John')

for i in student_objects:
    print i.name,i.grade,i.age 
"""


# 12

"""
import sys
from time import time
sys.stdout.write( str(time()) + "\n" )
"""

# 13

"""
import sys
file_in = file('db.txt','r')
file_out = file('copy.txt','w')
for line in file_in:
    for i in range(0,len(line)):
        if line[i]!="\n":
            sys.stdout.write(line[i]+',')
        else:
            sys.stdout.write(line[i])
        file_out.write(line[i])

sys.stdout.write("\n")
file_in.close()
file_out.close()
"""

"""
# db.txt
1111
2222
ssss
wwww
5555
"""

# 14

""""
def my_divide():
    try:
        10 / 0 # make wrong 

    except ZeroDivisionError:
        print "cannot divide zero"
    else: 
        print "no wrong"
    finally:
        print "execute this line anyway"
my_divide()
"""

# 15

"""
class Student:  
    def __init__(self, name, grade, age):  
        self.name = name  
        self.grade = grade  
        self.age = age  
    def set_name(self, name):  
        self.name = name  

student_objects=[]
student_objects.append( Student('john', 'B', 15) )
student_objects.append( Student('dave', 'A', 12) )
student_objects.append( Student('jane', 'A', 10) )

student_objects.sort(key=lambda i: i.age,reverse=True) 
for i in student_objects:
    print i.name,i.grade,i.age 
print

from operator import attrgetter 

student_objects.sort(key=attrgetter('grade', 'age'),reverse=True)  
for i in student_objects:
    print i.name,i.grade,i.age 
print
"""

# 16

import os
import sys

os.system('cp -r test_copy_dir /afs/cern.ch/user/y/yuchang/www/test_website')

#os.system('rm -r test_copy_dir_2')
os.system('mkdir test_copy_dir_2')
os.system('mv  test_copy_dir_2 /afs/cern.ch/user/y/yuchang/www/test_website')






