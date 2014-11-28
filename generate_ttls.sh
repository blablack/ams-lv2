#!/bin/bash

for i in ams.lv2/*.ttl 
do 
	newfile=${i/.ttl/} 
	ttl2c $i "${newfile}_ttl.hpp" 
done 

# manifest header does not make sense
rm -rf ams.lv2/manifest_ttl.hpp 

mv ams.lv2/*_ttl.hpp src/	
