const { Worker } = require('worker_threads');
const path = require('path');

worker = new Worker(path.resolve('worker.js'));
setTimeout(() => {}, 5000);
