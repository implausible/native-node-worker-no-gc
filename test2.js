require('./worker');
setTimeout(() => {
  let terminatingIterations = 3;
  let usedBeforeGC = Number.MAX_VALUE;
  let nondecreasingIterations = 0;
  for ( ; ; ) {
    global.gc();
    var usedAfterGC = process.memoryUsage().heapUsed;
    if (usedAfterGC >= usedBeforeGC) {
      nondecreasingIterations++;
      if (nondecreasingIterations >= terminatingIterations) {
        break;
      }
    }
    usedBeforeGC = usedAfterGC;
  }
}, 5000);
