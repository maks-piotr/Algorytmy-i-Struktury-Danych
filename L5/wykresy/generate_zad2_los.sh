for((i=10000;i<=100000;i+=10000))
do
    #rm "./output/bst_los$i.out" &> /dev/null
    for((k=1;k<=20;k++))
    do
        ./gen_losowy $i | ./queue >> "./output/queue$i.out"
    done

done