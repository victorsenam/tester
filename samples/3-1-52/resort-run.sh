file=${1-'WordFrequencies'}
run=${2-"java-algs4 ${file}"}

javac-algs4 "${file}.java"

time $run < ../../text/clear_1.txt > presult_1.txt
../../corretor/resort < presult_1.txt > result_1.txt
diff -w result_1.txt ../../output/out_1.txt > diff_1.txt
cat diff_1.txt | less

time $run < ../../text/clear_2.txt > presult_2.txt
../../corretor/resort < presult_2.txt > result_2.txt
diff -w result_2.txt ../../output/out_2.txt > diff_2.txt
cat diff_2.txt | less
