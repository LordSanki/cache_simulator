./sim_cache 32 1024 4 1 1 go_trace.txt > valid5.txt
./sim_cache 64 8192 2 1 0 gcc_trace.txt > valid4.txt
./sim_cache 32 4096 4 0 1 perl_trace.txt > valid3.txt
./sim_cache 128 2048 8 0 1 go_trace.txt > valid2.txt
./sim_cache 16 16384 1 0 0 gcc_trace.txt > valid1.txt
diff -iyw --suppress-common-lines valid5.txt ValidationRun5.txt
diff -iyw  --suppress-common-lines valid4.txt ValidationRun4.txt
diff -iyw  --suppress-common-lines valid3.txt ValidationRun3.txt
diff -iyw  --suppress-common-lines valid2.txt ValidationRun2.txt
diff -iyw  --suppress-common-lines valid1.txt ValidationRun1.txt
