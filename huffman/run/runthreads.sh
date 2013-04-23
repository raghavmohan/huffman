#! /bin/sh
#declare -a nums=(1 2 10 100 300)
#declare -a nums
nums[0]=1
nums[1]=2
nums[2]=10
nums[3]=100
nums[4]=300

for i in {0..4}
do
  #$(./parakram-csr/parakram-csr-block -s 14 > out.txt)
  #a=$(cat out.txt | grep "generation_time")
  #b=$(cat out.txt | grep "construction_time")
  #c=$(cat out.txt | grep "mean_time")
  #d=$(cat out.txt | grep "harmonic_mean_TEPS")
  #e=$(cat out.txt | grep "Mtime")
  echo "i: $i \t nums[$i]: ${nums[i]}"
  #echo -e "NUMTHREADS: $i \t$a \t$b \t$c\t$d\t$e"
  #   echo -e "NUMTHREADS: $i \tGeneration Time: $a \tConstruction Time: $b \tBfs Time: $c\tharmonic_mean_TEPS: $d"
  #   echo "SPEEDUP: $speedup"
done
