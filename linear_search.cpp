#include<iostream>
using namespace std;
int linear_search(int a[], int n, int x) 
{
    for (int i=0; i<n; i++)
    {
        if(a[i]==x)
        return(i);

    }
    return(-1);
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
int location=linear_search(a,n,x);
if(location==-1)cout<<"element not found";
else cout<<"elements found at index:"<<location;
return(0)
}
/*PS D:\Utkarsha> cd "d:\Utkarsha\" ; if ($?) { g++ linear_search.cpp -o linear_search } ; if ($?) { .\linear_search }
How many element5
Enter5element 10 20 30 40 50
enter element to search20
elements found at index:1
PS D:\Utkarsha> */