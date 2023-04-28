for((i=10000;i<=100000;i+=10000))
do
    #rm "./output/bst_ros$i.out" &> /dev/null
    for((k=1;k<=20;k++))
    do
        ./gen_ros $i | ./bst_3 >> "./output/bst_ros$i.out"
        ./gen_ros $i | ./splay_3 >> "./output/splay_ros$i.out"
        ./gen_ros $i | ./rb_3 >> "./output/rb_ros$i.out"
    done

done