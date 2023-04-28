for((i=100;i<=10000;i+=100))
do
    rm "./output/select$i.out" &> /dev/null
    rm "./output/random_select$i.out" &> /dev/null
    for((k=1;k<=$1;k++))
    do
        ./gen_los_k $i $(($i/2)) > /tmp/tmp1
        cat /tmp/tmp1 | ./select >> "./output/select$i.out"
        cat /tmp/tmp1 | ./rand_select >> "./output/random_select$i.out"
    done

done