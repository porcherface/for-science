#include "quicksort.h"

void QuickSortRic(QSR_TYPE list[], int beg, int end, QSR_TYPE follower[]){
    QSR_TYPE piv; QSR_TYPE tmp;   QSR_TYPE tmp2; QSR_TYPE piv2;

    int  l,r,p;

    while (beg<end)    // This while loop will substitude the second recursive call
    {
        l = beg; p = (beg+end)/2; r = end;

        piv = list[p];
        piv2=follower[p];

        while (1)
        {
            while ( (l<=r) && ( QSR_COMPARE(list[l],piv) <= 0 ) ) l++;
            while ( (l<=r) && ( QSR_COMPARE(list[r],piv)  > 0 ) ) r--;

            if (l>r) break;

            tmp=list[l]; list[l]=list[r]; list[r]=tmp;
            tmp2=follower[l]; follower[l]=follower[r]; follower[r]=tmp2;
            if (p==r) p=l;

            l++; r--;
        }

        list[p]=list[r]; list[r]=piv;
        follower[p]=follower[r]; follower[r]=piv2;
        r--;

        // Select the shorter side & call recursion. Modify input param. for loop
        if ((r-beg)<(end-l))
        {
            QuickSortRic(list, beg, r, follower);
            beg=l;
        }
        else
        {
            QuickSortRic(list, l, end,follower);
            end=r;
        }
    }
}

//  quickSort
//
//  This public-domain C implementation by Darel Rex Finley.
//
//  * Returns YES if sort was successful, or NO if the nested
//    pivots went too deep, in which case your array will have
//    been re-ordered, but probably not sorted correctly.
//
//  * This function assumes it is called with valid parameters.
//
//  * Example calls:
//    quickSort(&myArray[0],5); // sorts elements 0, 1, 2, 3, and 4
//    quickSort(&myArray[3],5); // sorts elements 3, 4, 5, 6, and 7

bool quickSortOpt(QSR_TYPE *arr, QSR_TYPE *foll, int elements) {

#define  MAX_LEVELS  1000
	
	int  beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R;
	QSR_TYPE piv,fiv;

	beg[0] = 0; end[0] = elements;
	while (i >= 0) {
		L = beg[i]; R = end[i] - 1;
		if (L<R) {
			
			piv = arr[L]; if (i == MAX_LEVELS - 1) return false;
			fiv = foll[L];
			
			while (L<R) {
				while (arr[R] >= piv && L < R) R--; if (L < R){
					arr[L++] = arr[R]; foll[L++] = foll[R];
				}
				while (arr[L] <= piv && L < R) L++; if (L < R){
					arr[R--] = arr[L]; foll[R--] = foll[L];
				}
			}
			arr[L] = piv;
			foll[L] = fiv;

			beg[i + 1] = L + 1; 
			end[i + 1] = end[i];
			end[i++] = L;
		}
		else {
			i--;
		}
	}
	return true;
}
