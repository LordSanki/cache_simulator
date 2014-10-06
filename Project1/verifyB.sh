./sim_cache 32 2048 4 0 4096 8 gcc_trace.txt > valid6.txt
./sim_cache 16 1024 8 0 8192 4 go_trace.txt > valid7.txt
./sim_cache 32 1024 8 256 0 0 perl_trace.txt > valid8.txt
./sim_cache 128 1024 2 1024 4096 4 gcc_trace.txt > valid9.txt
./sim_cache 64 8192 2 1024 16384 4 perl_trace.txt > valid10.txt
diff -iyw --suppress-common-lines valid6.txt Validation6_PartB.txt
diff -iyw  --suppress-common-lines valid7.txt Validation7_PartB.txt
diff -iyw  --suppress-common-lines valid8.txt Validation8_PartB.txt
diff -iyw  --suppress-common-lines valid9.txt Validation9_PartB.txt
diff -iyw  --suppress-common-lines valid10.txt Validation10_PartB.txt
