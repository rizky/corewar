#!/bin/sh

getScriptPath () {
    if [ -d ${0%/*} ]
    then
        abspath=$(cd ${0%/*} && echo $PWD/${0##*/})
        pathOnly=`dirname "$abspath"`
    else
        progdir=`dirname $0`
        cd $progdir
        pathOnly=$PWD
    fi

    echo $pathOnly;
    return
}
norme=$(getScriptPath)"/norm.py"

echo "------------------------------ Checking the norm ------------------------------"
echo "Checking *.c files..."
files=`find ./ -type f \( -name "*.c" \)`
python $norme $files
echo "\nChecking *.h files..."
files=`find ./ -type f -name "*.h"`
python $norme $files
echo "\nChecking Makefiles..."
files=`find ./ -type f -name "Makefile"`
python $norme $files
echo "--------------------------------------------------------------------------------"