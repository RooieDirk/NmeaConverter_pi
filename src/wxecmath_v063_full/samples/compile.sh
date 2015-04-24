echo "First of all, you must edit this file"
exit 0

wxpath="/path/of/wx"

# you can now remove the first two lines
#----------------------------------------

currentdir=`pwd`
if [ $# == 1 ]; then
	sample=$1
else
	echo "Name of the sample to compile: "
	read sample
fi

cd $sample
rm -f $sample.elf
g++ ../../lib/*.cpp ./*.cpp `$wxpath/buildgtk/wx-config --libs --cxxflags` -I$currentdir/../../lib -o $sample.elf -finput-charset=iso-8859-1

echo "OK"
