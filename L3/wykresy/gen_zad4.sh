for((i=1000;i<=100000;i+=1000))
do
    rm "./output/zad4/bin_search$i.out" &> /dev/null
    
    for((k=1;k<=$1;k++))
    do
        ./gen_bin_random $i | ./bin_search >> "./output/zad4/bin_search$i.out"
    done

done