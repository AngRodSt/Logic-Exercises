import { performance } from "perf_hooks";

//O(2n) approach two loops
const TwoSum = (arr, sum) => {
  for (let i = 0; i <= arr.length; i++) {
    for (let j = i + 1; j <= arr.length; j++) {
      if (arr[i] + arr[j] === sum) {
        return [i, j];
      }
    }
  }
};

// O(n) approach map -- key -value
const TwoSumImproved = (arr, target) => {
  const prev = {};

  for (let i = 0; i < arr.length; i++) {
    const complement = target - arr[i];
    if (complement in prev) {
      return [prev[complement], i];
    }
    prev[arr[i]] = i;
  }
  return null;
};

//Test
const arr = Array.from({ length: 10000 }, () =>
  Math.floor(Math.random() * 1000)
);
const target = 123;

const t0 = performance.now();
console.log(TwoSum(arr, target));
const t1 = performance.now();
console.log(`BruteForce: ${(t1 - t0).toFixed(3)} ms`);

const t2 = performance.now();
console.log(TwoSumImproved(arr, target));
const t3 = performance.now();
console.log(`HashMap: ${(t3 - t2).toFixed(3)} ms`);
