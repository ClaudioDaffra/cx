
#include "malgorithm.h"

#include <string.h>

// ******************
// NEXT PERMUTATION
// ******************

//  https://www.geeksforgeeks.org/find-the-next-lexicographically-greater-word-than-a-given-word/

static void perm_swap(char *a,char *b) 
{ 
    if( *a != *b ) 
    {
        *a^=*b; 
        *b^=*a; 
        *a^=*b;
    }    
}
// permutation reverse 
static void perm_rev(char* s,int l,int r) 
{ 
    while(l<r)
    {        
        perm_swap(&s[l++],&s[r--]);
    }
} 
// permutation binary search  
static int perm_bsearch (char* s,int l,int r,int key) 
{ 
    int index = -1; 
    while(l<=r) 
    { 
        int mid = l+(r-l)/2; 
        if(s[mid]<=key)
        {            
            r=mid-1;
        }        
        else
        { 
            l=mid+1; 
            if(index = -1 || s[index]<=s[mid])
            {                
                index = mid; 
            }
        } 
    } 
    return index; 
} 
  
int next_permutation(char* s) 
{ 
    int len = strlen(s), i=len-2; 
    while(i>=0 && s[i]>=s[i+1]) 
    {
       --i; 
    }
    if(i<0) 
    {
        return 0; 
    }
    else
    { 
        int index=perm_bsearch(s,i+1,len-1,s[i]); 
        perm_swap(&s[i],&s[index]); 
        perm_rev(s,i+1,len-1); 
        return 1; 
    } 
} 

// ******************
// PREV PERMUTATION
// ******************

//  http://www.cplusplus.com/reference/algorithm/reverse/

static void perm_reverse(char *s,int from,int to)
{
    char* first=s+from;
    char* last =s+strlen(s); 

    while ((first!=last)&&( *first!=*--last)) 
    {
        perm_swap(first,last);
        ++first;
    }    
}

//  https://www.geeksforgeeks.org/lexicographically-previous-permutation-in-c/

int prev_permutation(char* s) 
{ 
    // Find index of the last element of the string 
    int n = strlen(s) - 1; 

    int i = n; 
    
    // controlla che il range sia ordinato
    
    while (i > 0 && s[i - 1] <= s[i]) i--; 

    // if string is sorted in ascending order 
    // we're at the last permutation 

    if (i <= 0) return 0; 

    // Note - str[i..n] is sorted in ascending order 
    // Find rightmost element's index that is less 
    // than str[i - 1]
    
    int j = i - 1; 
    
    j++; // fix in C ( not in C++ with reverse)
    
    while (j + 1 <= n && s[j + 1] <= s[i - 1]) j++; 

    // Swap character at i-1 with j
    
    char temp ;
    temp = s[i - 1];
    s[i - 1] = s[j] ;
    s[j] = temp ;

    // Reverse the substring [i..n]
    
    perm_reverse(s,i,strlen(s) );

    return 1; 
} 
 
 
 
/**/


