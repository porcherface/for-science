#ifndef QUICKSORT_H
#define QUICKSORT_H

/********** QuickSort(): sorts the vector 'list[]' **********/

/**** Compile QuickSort for strings ****/
//#define QS_TYPE char*
//#define QS_COMPARE(a,b) (strcmp((a),(b)))

/**** Compile QuickSort for integers ****/
//#define QS_TYPE int
//#define QS_COMPARE(a,b) ((a)-(b))

/**** Compile QuickSort for doubles, sort list in inverted order ****/
#define QSR_TYPE double
#define QSR_COMPARE(a,b) ((a)-(b))

void QuickSortRic(QSR_TYPE list[], int beg, int end, QSR_TYPE follower[]);

bool quickSortOpt(QSR_TYPE *arr, QSR_TYPE *foll, int elements);

#endif // QUICKSORT_H
