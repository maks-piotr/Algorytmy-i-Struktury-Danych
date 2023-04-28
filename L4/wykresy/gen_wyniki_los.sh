for((i=10000;i<=100000;i+=10000))
do
    #rm "./output/bst_los$i.out" &> /dev/null
    for((k=1;k<=20;k++))
    do
        ./gen_los $i | ./bst_3 >> "./output/bst_los$i.out"
        ./gen_los $i | ./splay_3 >> "./output/splay_los$i.out"
        ./gen_los $i | ./rb_3 >> "./output/rb_los$i.out"
    done

done