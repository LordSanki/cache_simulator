./sim_cache 32 2048 4 0 4096 8 traces/gcc_trace.txt > output/valid6.txt
./sim_cache 16 1024 8 0 8192 4 traces/go_trace.txt > output/valid7.txt
./sim_cache 32 1024 8 256 0 0 traces/perl_trace.txt > output/valid8.txt
./sim_cache 128 1024 2 1024 4096 4 traces/gcc_trace.txt > output/valid9.txt
./sim_cache 64 8192 2 1024 16384 4 traces/perl_trace.txt > output/valid10.txt
diff -iyw --suppress-common-lines output/valid6.txt test_cases/Validation6_PartB.txt
diff -iyw  --suppress-common-lines output/valid7.txt test_cases/Validation7_PartB.txt
diff -iyw  --suppress-common-lines output/valid8.txt test_cases/Validation8_PartB.txt
diff -iyw  --suppress-common-lines output/valid9.txt test_cases/Validation9_PartB.txt
diff -iyw  --suppress-common-lines output/valid10.txt test_cases/Validation10_PartB.txt
