for((i=100;i<=10000;i+=100))
do
    rm "./output/zad5/quick_select$i.out" &> /dev/null
    rm "./output/zad5/dual_quick_select$i.out" &> /dev/null
    rm "./output/zad5/quick$i.out" &> /dev/null
    rm "./output/zad5/dual_quick$i.out" &> /dev/null
    for((k=1;k<=$1;k++))
    do
        ./gen_los $i > /tmp/tmp1
        cat /tmp/tmp1 | ./quick_select >> "./output/zad5/quick_select$i.out"
        cat /tmp/tmp1 | ./quick >> "./output/zad5/quick$i.out"
        cat /tmp/tmp1 | ./dual_quick_select >> "./output/zad5/dual_quick_select$i.out"
        cat /tmp/tmp1 | ./dual_quick >> "./output/zad5/dual_quick$i.out"
    done
done