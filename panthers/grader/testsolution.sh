for f in ../data/*.in; do
	echo $f
	if ! ./panthers < $f; then              
		break                             
	fi   
done
