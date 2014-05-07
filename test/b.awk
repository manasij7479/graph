BEGIN{
    FILENAME=ARGV[1];
    while(getline s<FILENAME)
    {
	x=index(s," ");
	if(x!=0)
	{
	    tmp1=substr(s,1,x-1);
	    tmp2=substr(s,x+1,length(s));
	    #print tmp;
	    system("g++ " tmp1);
	    system("./a.out");
	    if($0==$tmp2)
		print tmp1":OK";
	    else
		print tmp1":ERROR";
	    #print tmp2;
	    #print " ";
	    #print out;
	}
	#print x;
    }
    #print s;
}