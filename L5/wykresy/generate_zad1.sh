for((i=100;i<=1000;i+=100))
do
    rm "./output/merge$i.out" &> /dev/null
    rm "./output/quick$i.out" &> /dev/null
    rm "./output/insert$i.out" &> /dev/null
    rm "./output/dual_quick$i.out" &> /dev/null
    rm "./output/hybrid$i.out" &> /dev/null
    rm "./output/heap$i.out" &> /dev/null
    for((k=1;k<=$1;k++))
    do
        ./gen_losowy $i | ./merge >> "./output/merge$i.out"
        ./gen_losowy $i | ./quick >> "./output/quick$i.out"
        ./gen_losowy $i | ./insert >> "./output/insert$i.out"
        ./gen_losowy $i | ./dual_quick >> "./output/dual_quick$i.out"
        ./gen_losowy $i | ./hybrid >> "./output/hybrid$i.out"
        ./gen_losowy $i | ./hybrid >> "./output/heap$i.out"
    done

done
