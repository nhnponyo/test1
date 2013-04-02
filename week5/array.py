#!/usr/bin/python
# -*- coding: utf8 -*-


#1차원 배열 
print "1차원 배열"
a= [1,3,5,7,9] 
for i in range(0,len(a)):
	print "a[",i,"]:", a[i]

#2차원 배열
print "2차원 배열"
b = [[1,2,3],[4,5,6],[7,8,9]]

#2차원 배열은 1차원 배열의 배열 
for i in range(0,len(b)):
	print "b[",i,"]:", b[i]

for i in range(0,3):
	for j in range(0,3):
		print "b",i,j,":", b[i][j]

#2차원 배열의 동적 생성?
print "2차원 배열의 동적 생성?"
c =[]
c.append([1,0])
c.append([0,1])
for i in range(0,2):
	for j in range(0,2):
		print "c",i,j,":", c[i][j]


