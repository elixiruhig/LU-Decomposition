#! /bin/bash

myarr=("10" "20" "50" "100" "200" "300" "400" "500" "1000" "2000") # "2500" "3000") # "1000")
t_arr=("1" "2" "3" "4" "8" "16" "32" "64")
#echo ${myarr[@]}
: > parallel_output.txt
: > sequential_output.txt
: > parallel_pthread_output.txt
: > n_list.csv
: > p_list.csv
: > s_list.csv
: > t_list.csv
: > pthread_list.csv
for str in "${myarr[@]}"; do
	#echo $str;
	echo $str >> n_list.csv
	make parallel_openmp N=$str T=2 #>> parallel_output.txt
	
	#var_p="$({ time ./parallel_openmp ; } 2>&1 > /dev/null)"
	var_p="$({ time ./parallel_openmp ; } 2>&1 >> parallel_output.txt)"
	
	#echo $var_p >> parallel_output.txt
	
	real=${var_p#*real}
	
	real=${real%%s*}
	
	#real=$(echo $real | bc)
	echo "real=$real"
	
	
	min=${real%%m*}
	min=$(echo $min | bc)
	echo "min=$min"
	
	sec=${real#*m}
	
	sec=${sec%%.*}
	sec=$(echo $sec | bc)
	echo "sec=$sec"
	
	usec=${real#*.}
	usec=$(echo $usec | bc)

	time=$[$usec + $sec * 1000 + $min * 60000]
	
	
	echo $time >> p_list.csv
	
	#vjnefokvefkbmekmbemtb
	make parallel_pthread #>> parallel_output.txt
	
	var_p="$({ time ./parallel_pthread $str 2 ; } 2>&1 >> parallel_pthread_output.txt)"
	
	#echo $var_p >> parallel_pthread_output.txt
	
	real=${var_p#*real}
	
	real=${real%%s*}
	
	#real=$(echo $real | bc)
	echo "real=$real"
	
	
	min=${real%%m*}
	min=$(echo $min | bc)
	echo "min=$min"
	
	sec=${real#*m}
	
	sec=${sec%%.*}
	sec=$(echo $sec | bc)
	echo "sec=$sec"
	
	usec=${real#*.}
	usec=$(echo $usec | bc)

	time=$[$usec + $sec * 1000 + $min * 60000]
	
	
	echo $time >> pthread_list.csv
	
	make seq N=$str #>> sequential_output.txt
	var_s="$({ time ./sequential ; } 2>&1 >> sequential_output.txt)"
	#echo $var_s >> sequential_output.txt
	real=${var_s#*real}
	
	real=${real%%s*}
	#real=$((10#$real))
	#real=$(echo $real | bc)
	
	
	
	min=${real%%m*}
	min=$(echo $min | bc)
	
	
	sec=${real#*m}
	
	sec=${sec%%.*}
	sec=$(echo $sec | bc)
	
	usec=${real#*.}
	usec=$(echo $usec | bc)
	time=$[$usec + $sec * 1000 + $min * 60000]
	echo $time >> s_list.csv
	make clean
done

python python_script.py


: > p_list.csv
: > pthread_list.csv
: > t_list.csv

for str in "${t_arr[@]}"; do
	echo $str >> t_list.csv
	make parallel_openmp N=1000 T=$str #>> parallel_output.txt
	
	var_p="$({ time ./parallel_openmp ; } 2>&1 > /dev/null)"
	
	#echo $var_p >> parallel_output.txt
	
	real=${var_p#*real}
	
	real=${real%%s*}
	
	#real=$(echo $real | bc)
	echo "real=$real"
	
	
	min=${real%%m*}
	min=$(echo $min | bc)
	echo "min=$min"
	
	sec=${real#*m}
	
	sec=${sec%%.*}
	sec=$(echo $sec | bc)
	echo "sec=$sec"
	
	usec=${real#*.}
	usec=$(echo $usec | bc)

	time=$[$usec + $sec * 1000 + $min * 60000]
	
	
	echo $time >> p_list.csv
	
	
	#sldjvndvwdn
	
	make parallel_pthread #>> parallel_output.txt
	
	var_p="$({ time ./parallel_pthread 1000 $str ; } 2>&1 > /dev/null)"
	
	#echo $var_p >> parallel_output.txt
	
	real=${var_p#*real}
	
	real=${real%%s*}
	
	#real=$(echo $real | bc)
	echo "real=$real"
	
	
	min=${real%%m*}
	min=$(echo $min | bc)
	echo "min=$min"
	
	sec=${real#*m}
	
	sec=${sec%%.*}
	sec=$(echo $sec | bc)
	echo "sec=$sec"
	
	usec=${real#*.}
	usec=$(echo $usec | bc)

	time=$[$usec + $sec * 1000 + $min * 60000]
	
	
	echo $time >> pthread_list.csv
	make clean
done

python python_script2.py
