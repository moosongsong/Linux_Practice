#! /bin/bash


#int main(int argc, char argv){
#for (int i=1;i<argc;i++){
#printf("%s\n", argv[i]);
#}


for var in $(seq $#);do
	echo $var
done

