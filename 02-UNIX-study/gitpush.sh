#!/bin/sh
D=date "+%Y%m%d%H%M%S" 
git add .
git commit -m echo $D
git push  
