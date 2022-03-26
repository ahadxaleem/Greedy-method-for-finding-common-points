#define __STDC_WANT_LIB_EXT1__ 1
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//file pointer
FILE* ptr;
//for storing beginning and ending time
clock_t begin, end;
//total execution time
int exectime = 0;

//for calculating maximum common points
void maxCommonPnt(int min,int max) {
	begin = clock();
	//to store frequency of every point
	int* freq;
	freq = malloc(max*sizeof(int));
	//temporary min max points
	int tempmin, tempmax;
	//to store maximum frequency and common point
	int maxfreq=0,commonpnt=0;
	int i;
	//initializing freq array to 0
	for (i = min; i < max; i++) {
		freq[i] = 0;
	}
	end = clock();
	exectime += end - begin;
	//seeking file pointer to the top
	fseek(ptr, 0, SEEK_SET);
	while (!feof(ptr)) {
		//accessing min and max pots of each interval
		fscanf_s(ptr, "%d", &tempmin);
		fscanf_s(ptr, "%d", &tempmax);
		begin = clock();
		int j;
		//calculating freq of each pnt
		for (j = tempmin+1; j < tempmax; j++) {
			freq[j]++;
		}
		end = clock();
		exectime += end - begin;
	}
	begin = clock();
	int k;
	//finding maximum frequency
	for (k = min + 1; k < max; k++) {
		if (freq[k] > maxfreq) {
			maxfreq = freq[k];
			commonpnt = k;
		}
	}
	printf("The maximum number of intervals = %d\n", maxfreq);
	printf("The interval include point = %d\n", commonpnt);
	free(freq);
}

//driver program to run above functions
void main() {
	begin = clock();
	int min,max;
	char filename[20];
	//file accessing mode
	char mode[] = "r";
	printf("Enter file name : ");
	fgets(filename, sizeof(filename), stdin);
	int i=0;
	//calculating input size
	while (filename[i] != '\n') {
		i++;
	}
	//getting filename to a proper format
	filename[i] = '.';
	strcat_s(filename,sizeof(filename), "txt");
	errno_t err = fopen_s(&ptr,filename, mode);
	end = clock();
	exectime += end - begin;
	if (err)
		printf_s("The file %s was not opened\n",filename);
	else
	{
		fscanf_s(ptr, "%d", &min);
		fscanf_s(ptr, "%d", &max);
		int tempmin, tempmax;
		//getting maximum points min and max column
		while (!feof(ptr)) {
			fscanf_s(ptr, "%d", &tempmin);
			fscanf_s(ptr, "%d", &tempmax);
			if (tempmin < min) {
				min = tempmin;
			}
			if (tempmax > max)
			{
				max = tempmax;
			}
			
		}
		printf("Brute force program for finding max number of interval\n");
		maxCommonPnt(min, max);//function call
		fclose(ptr);
		end = clock();
		exectime += end - begin;
		//printing execution time
		printf("Time for finding the maximum number : %d ms", exectime);
	}
}