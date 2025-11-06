Description 

The goal was to improve the code using vectorization techniques and analyze how each optimization step affects compiler behavior and performance.
Three optimized versions of the original timestep.c were created:

timestep_opt1.c

timestep_opt2.c

timestep_opt3.c

Each version includes additional OpenMP SIMD directives and optimizations for better parallelization.


student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ likwid-perfctr -C 0 -g FLOPS_DP ./stream_triad 
--------------------------------------------------------------------------------
CPU name:       Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz
CPU type:       Intel Core SandyBridge processor
CPU clock:      3.29 GHz
--------------------------------------------------------------------------------
Minimum dt is 0.016964
--------------------------------------------------------------------------------
Group 1: FLOPS_DP
+--------------------------------------+---------+------------+
|                 Event                | Counter | HWThread 0 |
+--------------------------------------+---------+------------+
|           INSTR_RETIRED_ANY          |  FIXC0  |  217800791 |
|         CPU_CLK_UNHALTED_CORE        |  FIXC1  |  843766740 |
|         CPU_CLK_UNHALTED_REF         |  FIXC2  |  843765219 |
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |          0 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |   90266844 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          0 |
+--------------------------------------+---------+------------+

+-------------------------+------------+
|          Metric         | HWThread 0 |
+-------------------------+------------+
|   Runtime (RDTSC) [s]   |     0.5387 |
|   Runtime unhalted [s]  |     0.2563 |
|       Clock [MHz]       |  3292.4613 |
|           CPI           |     3.8740 |
|       DP [MFLOP/s]      |   167.5545 |
|     AVX DP [MFLOP/s]    |          0 |
|     Packed [MUOPS/s]    |          0 |
|     Scalar [MUOPS/s]    |   167.5545 |
| Vectorization ratio [%] |          0 |
+-------------------------+------------+

student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make clean
rm -rf ./stream_triad ./stream_triad.o ./timer.o ./main.o ./timestep.o
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o main.o main.c
main.c:10:22: optimized: loop vectorized using 32 byte vectors
main.c:20:15: missed: statement clobbers memory: mymindt_6 = timestep (10000000, 9.800000000000000710542735760100185871124267578125e+0, 9.499999999999999555910790149937383830547332763671875e-1, &celltype, &H, &U, &V, &dx, &dy);
/usr/include/x86_64-linux-gnu/bits/stdio2.h:112:10: missed: statement clobbers memory: __printf_chk (1, "Minimum dt is %lf\n", mymindt_6);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timestep_opt1.o timestep_opt1.c
timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt1.c:11:7: missed: couldn't vectorize loop
timestep_opt1.c:11:7: missed: not vectorized: control flow in loop.
timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt1.c:12:22: missed: statement clobbers memory: wavespeed_58 = sqrt (_9);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timer.o timer.c
timer.c:9:5: missed: statement clobbers memory: clock_gettime (1, tstart_cpu_2(D));
timer.c:14:5: missed: statement clobbers memory: clock_gettime (1, &tstop_cpu);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_triad main.o timestep_opt1.o timer.o -lm
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ likwid-perfctr -C 0 -g FLOPS_DP ./stream_triad 
--------------------------------------------------------------------------------
CPU name:       Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz
CPU type:       Intel Core SandyBridge processor
CPU clock:      3.29 GHz
--------------------------------------------------------------------------------
Minimum dt is 0.016964
--------------------------------------------------------------------------------
Group 1: FLOPS_DP
+--------------------------------------+---------+------------+
|                 Event                | Counter | HWThread 0 |
+--------------------------------------+---------+------------+
|           INSTR_RETIRED_ANY          |  FIXC0  |  217811550 |
|         CPU_CLK_UNHALTED_CORE        |  FIXC1  |  833117496 |
|         CPU_CLK_UNHALTED_REF         |  FIXC2  |  833114601 |
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |          0 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |   90399669 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          0 |
+--------------------------------------+---------+------------+

+-------------------------+------------+
|          Metric         | HWThread 0 |
+-------------------------+------------+
|   Runtime (RDTSC) [s]   |     0.5292 |
|   Runtime unhalted [s]  |     0.2530 |
|       Clock [MHz]       |  3292.4646 |
|           CPI           |     3.8249 |
|       DP [MFLOP/s]      |   170.8353 |
|     AVX DP [MFLOP/s]    |          0 |
|     Packed [MUOPS/s]    |          0 |
|     Scalar [MUOPS/s]    |   170.8353 |
| Vectorization ratio [%] |          0 |
+-------------------------+------------+



--timestep.opt1--

This compilation enabled loop vectorization using 256-bit vectors, but the performance analysis with LIKWID shows that the program still executes only scalar double-precision operations without AVX vectorization on the Intel Core i3-2120 processor.




student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make clean
rm -rf ./stream_triad ./stream_triad.o ./timer.o ./main.o ./timestep.o
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o main.o main.c
main.c:10:22: optimized: loop vectorized using 32 byte vectors
main.c:20:15: missed: statement clobbers memory: mymindt_6 = timestep (10000000, 9.800000000000000710542735760100185871124267578125e+0, 9.499999999999999555910790149937383830547332763671875e-1, &celltype, &H, &U, &V, &dx, &dy);
/usr/include/x86_64-linux-gnu/bits/stdio2.h:112:10: missed: statement clobbers memory: __printf_chk (1, "Minimum dt is %lf\n", mymindt_6);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timestep_opt2.o timestep_opt2.c
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:11:7: missed: couldn't vectorize loop
timestep_opt2.c:11:7: missed: not vectorized: control flow in loop.
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:12:22: missed: statement clobbers memory: wavespeed_58 = sqrt (_9);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timer.o timer.c
timer.c:9:5: missed: statement clobbers memory: clock_gettime (1, tstart_cpu_2(D));
timer.c:14:5: missed: statement clobbers memory: clock_gettime (1, &tstop_cpu);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_triad main.o timestep_opt2.o timer.o -lm
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ likwid-perfctr -C 0 -g FLOPS_DP ./stream_triad 
--------------------------------------------------------------------------------
CPU name:       Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz
CPU type:       Intel Core SandyBridge processor
CPU clock:      3.29 GHz
--------------------------------------------------------------------------------
Minimum dt is 0.016964
--------------------------------------------------------------------------------
Group 1: FLOPS_DP
+--------------------------------------+---------+------------+
|                 Event                | Counter | HWThread 0 |
+--------------------------------------+---------+------------+
|           INSTR_RETIRED_ANY          |  FIXC0  |  224542642 |
|         CPU_CLK_UNHALTED_CORE        |  FIXC1  |  851207302 |
|         CPU_CLK_UNHALTED_REF         |  FIXC2  |  851200680 |
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |          0 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |   90404124 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          0 |
+--------------------------------------+---------+------------+

+-------------------------+------------+
|          Metric         | HWThread 0 |
+-------------------------+------------+
|   Runtime (RDTSC) [s]   |     0.5391 |
|   Runtime unhalted [s]  |     0.2585 |
|       Clock [MHz]       |  3292.4814 |
|           CPI           |     3.7908 |
|       DP [MFLOP/s]      |   167.7072 |
|     AVX DP [MFLOP/s]    |          0 |
|     Packed [MUOPS/s]    |          0 |
|     Scalar [MUOPS/s]    |   167.7072 |
| Vectorization ratio [%] |          0 |
+-------------------------+------------+

--timestep_opt2--

The code shows successful loop vectorization reports from the compiler, but LIKWID measurements confirm that execution still relies entirely on scalar double-precision operations without any effective AVX vectorization on the Intel Core i3-2120 processor.



student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make clean
rm -rf ./stream_triad ./stream_triad.o ./timer.o ./main.o ./timestep.o
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o main.o main.c
main.c:10:22: optimized: loop vectorized using 32 byte vectors
main.c:20:15: missed: statement clobbers memory: mymindt_6 = timestep (10000000, 9.800000000000000710542735760100185871124267578125e+0, 9.499999999999999555910790149937383830547332763671875e-1, &celltype, &H, &U, &V, &dx, &dy);
/usr/include/x86_64-linux-gnu/bits/stdio2.h:112:10: missed: statement clobbers memory: __printf_chk (1, "Minimum dt is %lf\n", mymindt_6);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timestep_opt3.o timestep_opt3.c
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:10:7: missed: couldn't vectorize loop
timestep_opt3.c:10:7: missed: not vectorized: control flow in loop.
timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
timestep_opt3.c:11:29: missed: statement clobbers memory: wavespeed_58 = sqrt (_9);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timer.o timer.c
timer.c:9:5: missed: statement clobbers memory: clock_gettime (1, tstart_cpu_2(D));
timer.c:14:5: missed: statement clobbers memory: clock_gettime (1, &tstop_cpu);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_triad main.o timestep_opt3.o timer.o -lm
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ likwid-perfctr -C 0 -g FLOPS_DP ./stream_triad 
--------------------------------------------------------------------------------
CPU name:       Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz
CPU type:       Intel Core SandyBridge processor
CPU clock:      3.29 GHz
--------------------------------------------------------------------------------
Minimum dt is 0.016964student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make clean
rm -rf ./stream_triad ./stream_triad.o ./timer.o ./main.o ./timestep.o
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ make
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o main.o main.c
main.c:10:22: optimized: loop vectorized using 32 byte vectors
main.c:20:15: missed: statement clobbers memory: mymindt_6 = timestep (10000000, 9.800000000000000710542735760100185871124267578125e+0, 9.499999999999999555910790149937383830547332763671875e-1, &celltype, &H, &U, &V, &dx, &dy);
/usr/include/x86_64-linux-gnu/bits/stdio2.h:112:10: missed: statement clobbers memory: __printf_chk (1, "Minimum dt is %lf\n", mymindt_6);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timestep_opt2.o timestep_opt2.c
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:11:7: missed: couldn't vectorize loop
timestep_opt2.c:11:7: missed: not vectorized: control flow in loop.
timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
timestep_opt2.c:12:22: missed: statement clobbers memory: wavespeed_58 = sqrt (_9);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed   -c -o timer.o timer.c
timer.c:9:5: missed: statement clobbers memory: clock_gettime (1, tstart_cpu_2(D));
timer.c:14:5: missed: statement clobbers memory: clock_gettime (1, &tstop_cpu);
gcc -g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd -march=native -mtune=native -mprefer-vector-width=256 -fopt-info-vec-optimized -fopt-info-vec-missed -o stream_triad main.o timestep_opt2.o timer.o -lm
student@itcenter-lab128:~/Desktop/lab6/parallelProgramming$ likwid-perfctr -C 0 -g FLOPS_DP ./stream_triad 
--------------------------------------------------------------------------------
CPU name:       Intel(R) Core(TM) i3-2120 CPU @ 3.30GHz
CPU type:       Intel Core SandyBridge processor
CPU clock:      3.29 GHz
--------------------------------------------------------------------------------
Minimum dt is 0.016964
--------------------------------------------------------------------------------
Group 1: FLOPS_DP
+--------------------------------------+---------+------------+
|                 Event                | Counter | HWThread 0 |
+--------------------------------------+---------+------------+
|           INSTR_RETIRED_ANY          |  FIXC0  |  224542642 |
|         CPU_CLK_UNHALTED_CORE        |  FIXC1  |  851207302 |
|         CPU_CLK_UNHALTED_REF         |  FIXC2  |  851200680 |
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |          0 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |   90404124 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          0 |
+--------------------------------------+---------+------------+

+-------------------------+------------+
|          Metric         | HWThread 0 |
+-------------------------+------------+
|   Runtime (RDTSC) [s]   |     0.5391 |
|   Runtime unhalted [s]  |     0.2585 |
|       Clock [MHz]       |  3292.4814 |
|           CPI           |     3.7908 |
|       DP [MFLOP/s]      |   167.7072 |
|     AVX DP [MFLOP/s]    |          0 |
|     Packed [MUOPS/s]    |          0 |
|     Scalar [MUOPS/s]    |   167.7072 |
| Vectorization ratio [%] |          0 |
+-------------------------+------------+  217793802 |
|         CPU_CLK_UNHALTED_CORE        |  FIXC1  |  837491745 |
|         CPU_CLK_UNHALTED_REF         |  FIXC2  |  837487233 |
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |          0 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |   90398080 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          0 |
+--------------------------------------+---------+------------+

+-------------------------+------------+
|          Metric         | HWThread 0 |
+-------------------------+------------+
|   Runtime (RDTSC) [s]   |     0.5382 |
|   Runtime unhalted [s]  |     0.2544 |
|       Clock [MHz]       |  3292.4766 |
|           CPI           |     3.8453 |
|       DP [MFLOP/s]      |   167.9788 |
|     AVX DP [MFLOP/s]    |          0 |
|     Packed [MUOPS/s]    |          0 |
|     Scalar [MUOPS/s]    |   167.9788 |
| Vectorization ratio [%] |          0 |
+-------------------------+------------+

--timestep_opt3--

The compiler reports several loops vectorized with 256-bit vectors, but LIKWID confirms that execution still uses only scalar double-precision operations, with no AVX vectorization achieved on the Intel Core i3-2120 processor.
