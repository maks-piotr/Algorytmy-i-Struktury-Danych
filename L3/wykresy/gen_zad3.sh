for((i=100;i<=10000;i+=100))
do
    rm "./output/zad3/select3_$i.out" &> /dev/null
    rm "./output/zad3/select5_$i.out" &> /dev/null
    rm "./output/zad3/select7_$i.out" &> /dev/null
    rm "./output/zad3/select9_$i.out" &> /dev/null
    
    for((k=1;k<=$1;k++))
    do
        ./gen_los_select $i > /tmp/tmp1
        cat /tmp/tmp1 | ./select_k 3 >> "./output/zad3/select3_$i.out"
        cat /tmp/tmp1 | ./select_k 5 >> "./output/zad3/select5_$i.out"
        cat /tmp/tmp1 | ./select_k 7 >> "./output/zad3/select7_$i.out"
        cat /tmp/tmp1 | ./select_k 9 >> "./output/zad3/select9_$i.out"
    done

done