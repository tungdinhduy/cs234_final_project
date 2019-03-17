# CS234 Final Project - Suffix Array for Maximal Unique Matches #

## Personal Information ##

**Full Name:** Tung Duy Dinh

**Student Id:** 862 123 203

**Email:** tdinh040@ucr.edu

**Research Interests:** Machine Learning, Computer Vision

## Report ##

My project is writen in C++ which support the `class` object.
In addition, C++ support `vector` and `set` data structure which can avoid memory leaking more effectively instead of using `pointer`.

The user gives the 2 lengths of the 2 DNA sequence to generate random DNA sequences with 4 nucleotide types: A, T, G, C by  using `rand()` function and `ctime` library.
Then the 2 sequence are concated as follow: `<dna1>#<dna>$`.
Next, the new string is feed into `SuffixArray` object to create Suffix Array for that string.

### Suffix Array ###
Contain a table with 4 columns:
- Position: the position of character in a sequence
- Suffix: sorted suffix strings of a sequence
- LCP: Longest commone prefix among suffix strings
- isSeq2: boolean value whether the suffix string contain the second DNA sequence

Sort table based on the suffix string by re-implement sort function in C++ with the compare function `string.compare()`

### Longest Common Prefix Array (LCP) ###
An array denote the number of equal head-characters of 2 adjacent prefix strings.
For example:

| LCP | Suffix String |
|-----|---------------|
| 0   | AT            |
| 2   | ATATTAT       |
| 2   | ATTAT         |
| 0   | T             |

### Maximal Unique Matches ###
I use sliding window to find the maximal unique matches on the LCP array.
I denote `top` and `bot` as the position of the sliding window on LCP array.
Here is the algorithm I implement:
```
PROCEDURE GetAllMaximalUniqueMatches():
  top = 1st_row
  bot = 2nd_row
  max = 0
  WHILE (bot != end) DO:
    IF (isTwoSeqExist(top, bot) DO:
      min = Min(LCP(top + 1, bot))
      IF (min > max) DO:
        max = min
        ClearOldLcpPos()
        AddLcpPos()
      ELSE IF (min == max) DO:
        AddLcpPos()
      END IF
    END IF
    SlideWindow(top, bot)
  END WHILE
END PROCEDURE
```
## Reference ##

https://www.youtube.com/playlist?list=PLDV1Zeh2NRsCQ_Educ7GCNs3mvzpXhHW5
