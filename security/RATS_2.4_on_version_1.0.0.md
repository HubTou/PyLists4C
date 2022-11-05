# RATS - Rough-Auditing-Tool-for-Security
Analysis performed on [version 1.0.0 source code](https://github.com/HubTou/PyLists4C/tree/1.0.0) with [RATS](https://code.google.com/archive/p/rough-auditing-tool-for-security/) version 2.4:

```
# rats --resultsonly src
src/debug.c:19: High: fixed size local buffer
src/str.c:39: High: fixed size local buffer
src/types/Struct.c:67: High: fixed size local buffer
Extra care should be taken to ensure that character arrays that are allocated
on the stack are used safely.  They are prime targets for buffer overflow
attacks.
```
* src/debug.c:
  * :warning: A masochistic developer could attack his own program with an oversized (1000+ characters) LIST name.
  * :heavy_check_mark: Unlikely, but has been corrected in the next version...
* src/str.c: :heavy_check_mark: There was a real risk of buffer overflow there, but it was noticed and addressed during development.
* src/types/Struct.c: :heavy_check_mark: No risk.

```
src/str.c:130: High: strcat
src/str.c:158: High: strcat
src/types/Struct.c:74: High: strcat
Check to be sure that argument 2 passed to this function call will not copy
more data than can be handled, resulting in a buffer overflow.
```
* src/str.c: :heavy_check_mark: No risk:
  * In the first case, the destination is allocated to handle to handle the source size,
  * And in the second case, the source size is checked to fit in the destination. 
* src/types/Struct.c: :heavy_check_mark: No risk. 

```
src/toArray.c:128: High: strcpy
Check to be sure that argument 2 passed to this function call will not copy
more data than can be handled, resulting in a buffer overflow.
```
:heavy_check_mark: No risk, a STRINGs ARRAY is always allocated to the maximum STRING size of a LIST.

```
src/shuffled.c:11: Medium: random
src/shuffled.c:47: Medium: random
Standard random number generators should not be used to
generate randomness used for security reasons.  For security sensitive
randomness a crytographic randomness generator that provides sufficient
entropy should be used.

src/shuffled.c:39: Medium: srandom
Standard random number generators should not be used to
generate randomness used for security reasons.  For security sensitive
randomness a crytographic randomness generator that provides sufficient
entropy should be used.
```
:heavy_check_mark: No risk, [srandom()](https://www.freebsd.org/cgi/man.cgi?query=random) and [random()](https://www.freebsd.org/cgi/man.cgi?query=random) functions are not used for security reasons.

## Summary
* 1 :warning: minor issue
* 9 :heavy_check_mark: false positives
