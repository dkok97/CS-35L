#!/usr/bin/python

"""

Perfoms same operaion as the POSIX comm comand.
Compares two files and outputs 3 columns (lines unique in file1, lines unique in file2 and common lines.

Created by Dinkar Khattar.
22nd October, 2017.

"""

import sys, string, locale
from optparse import OptionParser

class compare:
    def __init__(self, file1, file2):

        if file1 == '-':
            f1 = sys.stdin
            f2 = open(file2, 'r')
        elif file2 == '-':
            f2 = sys.stdin
            f1 = open(file1, 'r')
        elif file1 == "-" and file2 == "-":
            print ("Both files can't be read from standard input")
            exit()
        else:
            f1 = open(file1, 'r')
            f2 = open(file2, 'r')
            
        self.lines1 = f1.read().split('\n')
        f1.close()

        self.lines2 = f2.read().split('\n')
        f2.close()
      
	del self.lines1[len(self.lines1)-1]
	del self.lines2[len(self.lines2)-1]
  
        self.uniq1 = []
        self.uniq2 = []
        self.commontemp = []
        self.common = []
        self.bigList = []
        self.f1_name=file1
        self.f2_name=file2

    def comm(self):
        list1 = list(self.lines1)
        list2 = list(self.lines2)
        
        sorted_list1 = self.sort(self.lines1)
        sorted_list2 = self.sort(self.lines2)
      
        if sorted_list1!=list1:
            print ("File " + self.f1_name + " is not sorted")
            exit()
        if sorted_list2!=list2:
            print ("File " + self.f2_name + " is not sorted")
            exit()
        
        for i in range(len(list1)):
            for j in range(len(list2)):
                if list2[j]==0:
                    continue
                if list1[i]==list2[j]:
                    self.commontemp.append(list1[i])
                    list1[i]=0
                    list2[j]=0
                    break
        
        l=0
        m=0
        n=0
        
        totalElements = len(self.commontemp) + (len(list1)-len(self.commontemp)) + (len(list2)-len(self.commontemp))
        
        for i in range (0,totalElements):
            if len(self.common)==totalElements:
                break
            
            if m<len(list1):
                if list1[m]==0:
                    self.common.append(self.commontemp[l])
                    self.uniq1.append('\t')
                    self.uniq2.append('\t')
                    m=m+1
                    l=l+1
                    continue
            
            if n<len(list2):
                if list2[n]==0:
                    n=n+1
                    continue
             
            if m<len(list1) and n<len(list2):
                if list1[m]<list2[n]:
                    self.uniq1.append(list1[m])
                    self.common.append('\t')
                    self.uniq2.append('\t')
                    m=m+1
                
                    self.uniq2.append(list2[n])
                    self.common.append('\t')
                    self.uniq1.append('\t')
                    n=n+1
                
                else:
                    self.uniq2.append(list2[n])
                    self.common.append('\t')
                    self.uniq1.append('\t')
                    n=n+1
                
                    self.uniq1.append(list1[m])
                    self.common.append('\t')
                    self.uniq2.append('\t')
                    m=m+1
                    
        if m<len(list1):
            for i in range(m,len(list1)):
                if list1[i]==0:
                    self.common.append(self.commontemp[l])
                    self.uniq1.append('\t')
                    self.uniq2.append('\t')
                    l=l+1
                else:
                    self.uniq1.append(list1[i])
                    self.common.append('\t')
                    self.uniq2.append('\t')
            
        if n<len(list2):
            for i in range(n,len(list2)):
                if list1[i]==0:
                    list1[i]='\t'
                else:
                    self.uniq2.append(list2[i])
                    self.uniq1.append('\t')
                    self.common.append('\t')
                
    def unsort_comm(self):
        list1 = self.lines1
        list2 = self.lines2
        self.bigList=[]
        
        
        for i in range(len(list1)):
            added = False
            for j in range(len(list2)):
                if list2[j]==0:
                    continue
                if list1[i]==list2[j]:
                    self.bigList.append('\t\t' + list1[i])
                    list1[i]=0
                    list2[j]=0
                    added = True
                    break
            if added==False:
                self.bigList.append(list1[i])
        
        for i in range(len(list2)):
            if list2[i]==0:
                continue
            self.bigList.append('\t' + list2[i])
            
    def sort(self,arr):
        for i in range(1, len(arr)):
            key = arr[i]
            j = i-1
            while j >=0 and key.strip() < arr[j].strip() :
                arr[j+1] = arr[j]
                j -= 1
            arr[j+1] = key
        return arr
            
    def printOutput(self, Not1, Not2, Not3):
        if Not1==0:
            self.uniq1 = [''] * len(self.uniq1)
        if Not2==0:
            self.uniq2 = [''] * len(self.uniq2)
        if Not3==0:
            self.common = [''] * len(self.common)
        linesToPrint = []
        for i in range(len(self.common)):
            line = self.uniq1[i]+self.uniq2[i]+self.common[i]
            linesToPrint.append(line.rstrip())
            
        linesToPrint=self.sort(linesToPrint)
        for i in linesToPrint:
	    if i.strip()=='':
                continue
            print (i)
            
    def printOutput_unsort(self, Not1, Not2, Not3):

        if Not1==0:
            i=0
            while i<range(len(self.bigList)):
                if i == len(self.bigList):
                    break
                if self.bigList[i][0] != '\t':
                    del self.bigList[i]
                    i = i-1
                i=i+1
                
        if Not2==0:
            i=0
            while i< range(len(self.bigList)):
                if i == len(self.bigList):
                    break
                if self.bigList[i][0] == '\t' and self.bigList[i][1] != '\t':
                    del self.bigList[i]
                    i = i-1
                i = i+1
                
        if Not3==0:
            i=0
            while i<range(len(self.bigList)):
                if i == len(self.bigList):
                    break
                if self.bigList[i][0] == '\t' and self.bigList[i][1] == '\t':
                    del self.bigList[i]
                    i = i-1
                i = i+1
                
                        
        if Not1==0:
            if Not2==0 or Not3==0:
                for i in range(len(self.bigList)):
                    self.bigList[i] = self.bigList[i].strip()
            else:
                for i in range(len(self.bigList)):
                    if self.bigList[i][0]=='\t' and self.bigList[i][1]=='\t':
                        self.bigList[i] = '\t' + self.bigList[i].strip()
                    else:
                        self.bigList[i] = self.bigList[i].strip()
        elif Not2==0:
            if Not3!=0:
                for i in range(len(self.bigList)):
                    if self.bigList[i][0]=='\t' and self.bigList[i][1]=='\t':
                        self.bigList[i] = '\t' + self.bigList[i].strip()   
                
        for i in self.bigList:
            print i

def main():
    locale.setlocale(locale.LC_ALL, 'C')
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTIONS]... FILE1 FILE2"""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                  action="store_false", dest="col1", default=True,
                  help="suppress column 1")
    parser.add_option("-2",
                  action="store_false", dest="col2", default=True,
                  help="suppress column 2")
    parser.add_option("-3",
                  action="store_false", dest="col3", default=True,
                  help="suppress column 3")
    parser.add_option("-u",
                  action="store_true", dest="unsort", default=False,
                  help="files are unsorted")
    options, args = parser.parse_args()

    try:
        col1 = int(options.col1)
        col2 = int(options.col2)
        col3 = int(options.col3)
        unsort = bool(options.unsort)
    except: 
        parser.error("invalid options")

    if len(args) != 2:
        parser.error("invalid number of arguments")

    input_file1 = args[0]
    input_file2 = args[1]

    try:
        com = compare(input_file1, input_file2)
        if (unsort == False):
            com.comm()
            com.printOutput(col1, col2, col3)
        else:
            com.unsort_comm()
            com.printOutput_unsort(col1, col2, col3)
    except IOError as e:
        errno = e.errno
	strerror = e.strerror
	parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
    

if __name__ == "__main__":
    main()
"""

Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $

"""
