filename=$BASH_ARGV
rp=`realpath $filename`
c=".c"
cplpl=".cpp"
if [[ `echo $rp | grep .c$ -o` == "$c" ]]
then
	gcc $rp
	out=`realpath a.out`
	exec $out
elif [[ `echo $rp | grep .cpp$ -o` == "$cplpl" ]]
then
	g++ $rp -std=c++11
	out=`realpath a.out`
	exec $out
fi