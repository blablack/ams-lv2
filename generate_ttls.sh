#!/bin/bash

for i in ams.lv2/*.ttl 
do 
	indexCount=0
	newFile=""
	while IFS='' read -r line
	do
		if [[ $line == *"lv2:index"* ]]
		then
			newFile="$newFile\t\tlv2:index $indexCount ; \n"
			indexCount=$((indexCount + 1))
		else
			newFile="$newFile$line\n"
		fi
	done < $i
	echo -e "${newFile::-2}" > $i
done

for i in ams.lv2/*.ttl 
do 
	echo $i
	newfile=${i/.ttl/} 
	ttl2c $i "${newfile}_ttl.hpp" 
done 

# manifest header does not make sense
rm -rf ams.lv2/manifest_ttl.hpp 

mv ams.lv2/*_ttl.hpp src/	
