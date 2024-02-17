#!/bin/bash

SUCCESS=0
FAIL=0
COUNT=0
RES=""

declare -a test=(
"VAR text.txt"
)

test()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_cat.log
    RES="$(diff -s test_s21_cat.log test_cat.log)"
    (( COUNT++ ))
    if [ "$RES" == "Files test_s21_cat.log and test_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "$FAIL $SUCCESS $COUNT SUCCES $t"
    else
      (( FAIL++ ))
        echo "$FAIL $SUCCESS $COUNT FAIL $t"
    fi
    rm test_s21_cat.log test_cat.log
}

for var1 in b e n s t v
do
    for i in "${test[@]}"
    do
        var="-$var1"
        test $i
    done
done

for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        if [ $var1 != $var2 ]
        then
            for i in "${test[@]}"
            do
                var="-$var1 -$var2"
                test $i
            done
        fi
    done
done

for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${test[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    test $i
                done
            fi
        done
    done
done

for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            for var4 in b e n s t v
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${test[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        test $i
                    done
                fi
            done
        done
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNT"