/**************************************************/
/* Welcome to HW10 for CSCI 370 Spring 2022 @ UND
/* Program simulates placing data into 4 types of
/* caches: fully associative, direct mapped, 2-way
/* set associative, & 4-way set associative. 64K of
/* memory assumed (65536), 4096 words each per cache.
/* Reports cahce miss count for 500 random addresses.
/* By Kevin Jordan ID: 1301006 kevin.jordan@und.edu
/**************************************************/

#include <stdio.h>
#include <stdlib.h>

struct word16 {
    int words[16];
};

struct word32 {
    int words[32];
};

struct set2 {
    struct word16 words[128];
    int line[128];
};

struct set4 {
    struct word16 words[64];
    int line[64];
};

struct fullAssoc {
    struct word32 offset[128];
    int tag[128];
} cache1;

struct dirMap {
    struct word32 words[128];
    int line[128];
} cache2;

struct twoWay {
    struct set2 set[2];
} cache3;

struct fourWay {
    struct set4 set[4];
} cache4;

int *D2BIN(int memoryLocation) {
    int i;
    static int binary[16];
    for (i=0; i<16; i++) {
        binary[i] = 0;
    }
    if (memoryLocation == 0) binary[0] = 0;
    for (i=0; memoryLocation>0; i++) {
        binary[i] = (memoryLocation % 2);
        memoryLocation /= 2;
    }
    return binary;
}

int BIN2D(int binary[], int bitsFlag) {
    int dec=0, m=1, i;
    if (bitsFlag == 0) {
        for (i=5; i<16; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 1) {
        for (i=0; i<5; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 2) {
        for (i=12; i<16; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 3) {
        for (i=5; i<12; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 4) {
        for (i=0; i<4; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 5) {
        for (i=6; i<16; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    else if (bitsFlag == 6) {
        for (i=4; i<6; i++) {
            dec += binary[i] * m;
            m *= 2;
        }
    }
    return dec;
}

int FULLASSOCMISS(int tag, struct fullAssoc cache1) {
    int miss1=1;
    for (int i=0; i<128; i++) {
        if (tag == cache1.tag[i]) {
            miss1 = 0;
            break;
        }
    }
    return miss1;
}

int DIRMAPMISS(int tag2, int line2, struct dirMap cache2) {
    int miss2=1;
    if (tag2 == cache2.line[line2]) miss2=0;
    else cache2.line[line2] = tag2;
    return miss2;
}

int TWOWAYMISS(int tag3, int set3, struct twoWay cache3) {
    int miss3=1;
    for (int i=0; i<128; i++) {
        if (tag3 == cache3.set[set3].line[i]) {
            miss3 = 0;
            break;
        }
    }
    return miss3;
}

int FOURWAYMISS(int tag4, int set4, struct fourWay cache4) {
    int miss4=1;
    for (int i=0; i<64; i++) {
        if (tag4 == cache4.set[set4].line[i]) {
            miss4 = 0;
            break;
        }
    }
    return miss4;
}

int main(void) {
    int memoryLocation;
    int *binary;
    int tag1, offset1, miss1, fuAsMissCnt=0;
    float missRatio1;
    int tag2, line2, word2, dirMapMissCnt=0;
    float missRatio2;
    int tag3, set3, word3, miss3, twoWayMissCnt=0;
    float missRatio3;
    int tag4, set4, word4, miss4, fourWayMissCnt=0;
    float missRatio4;
    for (int i=0; i<128; i++) {
        cache1.tag[i] = 0;
    }
    for (int i=0; i<128; i++) {
        cache3.set[0].line[i] = 0;
        cache3.set[1].line[i] = 0;
    }
    for (int i=0; i<64; i++) {
        cache4.set[0].line[i] = 0;
        cache4.set[1].line[i] = 0;
        cache4.set[2].line[i] = 0;
        cache4.set[3].line[i] = 0;
    }
    srand(1994);
    for (int i=0; i<500; i++) {
        memoryLocation = (rand() % 65536);
        binary = D2BIN(memoryLocation);
        /* //Uncomment to print 16 bit memory address in binary and decimal
        for (int i=15; i>=0; i--) {
            printf("%d", binary[i]);
        }
        printf(" : %d\n", memoryLocation);
        */
        /* Fully Associative Cache */
        tag1 = BIN2D(binary, 0);
        offset1 = BIN2D(binary, 1);
        /* //Uncomment for cache bit map scheme
        printf("Full Assoc Tag: %d Offset: %d\n", tag1, offset1);
        */
        miss1 = FULLASSOCMISS(tag1, cache1);
        fuAsMissCnt += miss1;
        if (miss1 == 1) {
            for (int i=0; i<128; i++) {
                if (cache1.tag[i] == 0) {
                    cache1.tag[i] = tag1;
                    break;
                }
            }
        }
        /* Direct Mapped Cache */
        tag2 = BIN2D(binary, 2);
        line2 = BIN2D(binary, 3);
        word2 = BIN2D(binary, 1);
        /*  //Uncomment for cache bit map scheme
        printf("Direct Map Tag: %d Line: %d Word: %d\n", tag2, line2, word2);
        */
        dirMapMissCnt += DIRMAPMISS(tag2, line2, cache2);
        /* 2-way Set Associative Cache */
        tag3 = BIN2D(binary, 0);
        set3 = binary[4];
        word3 = BIN2D(binary, 4);
        /* //Uncomment for cache bit map scheme
        printf("2-way Tag: %d Set: %d Word: %d\n", tag3, set3, word3);
        */
        miss3 = TWOWAYMISS(tag3, set3, cache3);
        twoWayMissCnt += miss3;
        if (miss3 == 1) {
            for (int i=0; i<128; i++) {
                if (cache3.set[set3].line[i] == 0) {
                    cache3.set[set3].line[i] = tag3;
                    break;
                }
            }
        }
        /* 4-way Set Associative Cache */
        tag4 = BIN2D(binary, 5);
        set4 = BIN2D(binary, 6);
        word4 = BIN2D(binary, 4);
        /* //Uncomment for cache bit map scheme
        printf("4-way Tag: %d Set: %d Word: %d\n", tag4, set4, word4);
        */
        miss4 = FOURWAYMISS(tag4, set4, cache4);
        fourWayMissCnt += miss4;
        if (miss4 == 1) {
            for (int i=0; i<64; i++) {
                if (cache4.set[set4].line[i] == 0) {
                    cache4.set[set4].line[i] = tag4;
                    break;
                }
            }
        }
    }
    missRatio1 = fuAsMissCnt*0.2;
    printf("Fully Associative Miss Ratio (percent): %f\n", missRatio1);
    missRatio2 = dirMapMissCnt*0.2;
    printf("Direct Mapped Miss Ratio (percent): %f\n", missRatio2);
    missRatio3 = twoWayMissCnt*0.2;
    printf("2-way Set Associative Miss Ratio (percent): %f\n", missRatio3);
    missRatio4 = fourWayMissCnt*0.2;
    printf("4-way Set Associative Miss Ratio (percent): %f\n", missRatio4);
/*
    for (int i=0; i<64; i++) {
        printf("%d %d ", cache4.set[0].line[i], cache4.set[1].line[i]);
        printf("%d %d\n", cache4.set[2].line[i], cache4.set[3].line[i]);
    }*/
    return 0;
}
