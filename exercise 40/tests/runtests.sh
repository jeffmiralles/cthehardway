echo "Running unit tests:"

for i in tests/*_tests
do
    if test -f $i
    then
    	if $./$i 2>> tests/tests.log
    	then
    		$i build/libex29.so print_a_message '"HELasdasdLO String"'
    	else
    		$i build/libex29.so RUN_TESTS
    	fi
    fi
done

echo ""
