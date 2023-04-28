for((i=1000;i<=5000;i+=1000))
do
    #rm "./output/bst_los$i.out" &> /dev/null
    for((k=1;k<=20;k++))
    do
        ./gen_ciagi $i $i | ./LCS >> "./output/LCS$i.out"
    done

done