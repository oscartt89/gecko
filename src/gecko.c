#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "structs.h"
#include "commonFunctions.h"
#include "dictionaryFunctions.h"

int main(int ac, char** av){
    if(ac!=3){
        terror("USE: gecko seqFileX.IN seqFileX.IN");
    }

    uint64_t nEntriesX = 0;
    hashentry *entriesX;
    uint64_t nEntriesY = 0;
    hashentry *entriesY;

    pthread_t thX,thY;
    DictionaryArgs argsX,argsY;

    fprintf(stdout, "av[1]: %s\n", av[1]);
    argsX.seqFile=strdup(av[1]);
    fprintf(stdout, "argsX.seqFile: %s\n", argsX.seqFile);
    argsX.nEntries=&nEntriesX;
    pthread_create(&thX,NULL,dictionary,(void*)(&argsX));

    argsY.seqFile=strdup(av[2]);
    argsY.nEntries=&nEntriesY;
    pthread_create(&thY,NULL,dictionary,(void*)(&argsY));

    //Wait:
    pthread_join(thX,(void **)&entriesX);
    pthread_join(thY,(void **)&entriesY);

    free(argsX.seqFile);
    free(argsY.seqFile);

//    char wordString[33];
//	wordString[32] = '\0';
//    uint64_t i,j;
//	for(i=0;i<nEntriesX;i++){
//		showWord(&entriesX[i].w, wordString);
//		fprintf(stdout, "Words(%" PRIu64 "):%s Repetitions: %" PRIu64 " Positions: ", i, wordString, entriesX[i].num);
//        for(j=0;j<entriesX[i].num;j++){
//            fprintf(stdout,"(%" PRIu64 ",%" PRIu64 ") ",entriesX[i].locs[j].pos,entriesX[i].locs[j].seq);
//        }
//        fprintf(stdout, "\n");
//	}

    uint64_t i;
	for(i=0;i<nEntriesX;i++){
        free(entriesX[i].locs);
    }
    free(entriesX);
    for(i=0;i<nEntriesY;i++){
        free(entriesY[i].locs);
    }
    free(entriesY);

    return 0;
}