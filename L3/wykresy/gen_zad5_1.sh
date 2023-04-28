for((i=100;i<=10000;i+=100))
do
    rm "./output/zad5/quick_w$i.out" &> /dev/null
    rm "./output/zad5/quick_select_w$i.out" &> /dev/null
    for((k=1;k<=$1;k++))
    do
        ./gen_ros $i > /tmp/tmp1
        cat /tmp/tmp1 | ./quick_select >> "./output/zad5/quick_select_w$i.out"
        cat /tmp/tmp1 | ./quick_w >> "./output/zad5/quick_w$i.out"
    done
done