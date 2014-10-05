./sim_cache 32 2048 4 0 4096 8 gcc_trace.txt > valid6.txt
./sim_cache 16 1024 8 0 8192 4 go_trace.txt > valid7.txt
./sim_cache 32 1024 8 256 0 0 perl_trace.txt > valid8.txt
./sim_cache 128 1024 2 1024 4096 4 gcc_trace.txt > valid9.txt
./sim_cache 64 8192 2 1024 16384 4 perl_trace.txt > valid10.txt
diff -iyw --suppress-common-lines valid5.txt ValidationRun5.txt
diff -iyw  --suppress-common-lines valid4.txt ValidationRun4.txt
diff -iyw  --suppress-common-lines valid3.txt ValidationRun3.txt
diff -iyw  --suppress-common-lines valid2.txt ValidationRun2.txt
diff -iyw  --suppress-common-lines valid1.txt ValidationRun1.txt
