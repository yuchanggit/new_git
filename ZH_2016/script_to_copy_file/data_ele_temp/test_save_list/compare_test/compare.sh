#!/bin/sh

test -e file_not_saved.txt  && rm -r file_not_saved.txt  || echo " file_not_saved.txt Not exist" 

number1=`cat file_list_name_0000.txt | wc -l`
echo $number1

number2=`cat file_list_save.txt | wc -l`
echo $number2


#for (( i=1; i<=${number1}; i=i+1 ))
#for (( i=597; i<=610; i=i+1 ))
for (( i=597; i<=${number1}; i=i+1 ))
do

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

# below are commented 
: '

string_comapre=NCUGlobalTuples_636.root
#string_comapre=NCUGlobalTuples_777.root

for (( i=1; i<=${number1}; i=i+1 ))
do


   string=`head -$i file_list_save.txt | tail -1`


   if [ $string == $string_comapre  ]; then
      echo "find the same string $string_comapre"

   else
      echo "cannot find the same string $string_comapre"
   fi 



#   echo $string
#   head -$i file_list_save.txt | tail -1 
#  echo $i
#	s=$((${s}+${i}))
done

'

