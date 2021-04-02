# No GC performed after shutdown example
`addon.cc` contains a minimal set of code necessary to setup the memory leak. Steps to reproduce:
1. Use `npm install` to build this example repository
2. Use `npm run test1` to see that when a context is cleaned up, native references are excluded from terminating GC
3. Use `npm run test2` to confirm that under ideal conditions, object exported from `addon.cc` is collectable.
