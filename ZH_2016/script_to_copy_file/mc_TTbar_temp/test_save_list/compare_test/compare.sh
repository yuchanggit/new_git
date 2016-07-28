#!/bin/sh

test -e file_not_saved.txt  && rm -r file_not_saved.txt  || echo " file_not_saved.txt Not exist" 

number1=`cat file_list_name_0000.txt | wc -l`
echo $number1

number2=`cat file_list_save.txt | wc -l`
echo $number2


for (( i=1; i<=${number1}; i=i+1 ))
do

   echo "scan i=$i for all $number1 file name"
   string1=`head -$i file_list_name_0000.txt | tail -1`
#   echo $string1

   find_flag=false

   for (( j=1; j<=${number2}; j=j+1 ))
   do
#      echo $j
       string2=`head -$j file_list_save.txt | tail -1`

       if  [ $string1 == $string2 ]; then
	   find_flag=true
       fi

   done


   if [ $find_flag == false ]; then 

#       echo "cannot find same $string1"
       echo $string1 >> file_not_saved.txt
   fi 


done


