BEGIN{
    while(getline s<ARGV[1])
    {
	x=index(s," ");
	if(x!=0)
	{
	    tmp1=substr(s,1,x-1);
	    tmp2=substr(s,x+1,length(s));
	    #print tmp;
	    system("g++ " tmp1);
	    system("./a.out>f.txt");
	    getline out<"f.txt";
	    if(out==tmp2)
		print tmp1":OK";
	    else
		print tmp1":ERROR";
	    #print tmp2;
	    #print " ";
	    #print out;
	    system("rm f.txt");
	}
	#print x;
    }
    #print s;
}