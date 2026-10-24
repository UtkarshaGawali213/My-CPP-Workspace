#include<iostream>
using namespace std;
int binary_search(int a[],int n,int x)
{
int first=0,last=n-1,mid;
while (first<=last)
{
 mid=(first+last)/2;
if (a[mid]==x) return (mid);
else if (a[mid]<x) first =mid+1;
else last =mid-1;    
}
    return (-1);

}
int main()
{
int a[50];
int n;
cout<<"How many element";
cin>>n;
cout<<"Enter"<<n<<"element";
for(int i=0;i<n
;i++)
{
    cin>>a[i];
}
int x;
cout<<"enter element to search";
cin>>x;
int location=binary_search(a,n,x);
if(location==-1)cout<<"element not found";
else cout<<"elements found at index:"<<location;
return(0);
}
/*PS D:\Utkarsha> cd "d:\Utkarsha\" ; if ($?) { g++ binary_search.cpp -o binary_search } ; if ($?) { .\binary_search }
How many element6
Enter6element 1 2 3 4 5 6
enter element to search4
elements found at index:3
PS D:\Utkarsha> */