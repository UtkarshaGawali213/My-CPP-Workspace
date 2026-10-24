#include<iostream>
using namespace std;
class complex{
    private:
    float real;
    float imag;
    public:
    complex(){
        real=0;
        imag=0;
    }
    complex(float r,float i){
        real=r;
        imag=i;
    }
    ~complex(){}
    void display(void)
    {
        cout<<real<<"+"<<imag<<"i"<<endl;
    }
    complex operator+(complex c){
        return complex(real+c.real,imag+c.imag);
    }
    complex operator-(complex c){
        return complex(real-c.real,imag-c.imag);
    }
    complex operator*(complex c){
        return complex(real*c.real,imag*c.imag);
    }
};

int main()
{
 complex c1(3,5),c2(2,4);
 cout<<"first complex no:";
 c1.display();
 cout<<"second complex no:";
 c2.display();
 complex sum=c1+c2;
 cout<<"sum:";
 sum.display();
 complex diff=c1-c2;
 cout<<"diff:";
 diff.display();
 complex prod=c1*c2;
 cout<<"prod:";
 prod.display();
 return 0;
}
/*PS D:\Utkarsha> cd "d:\Utkarsha\" ; if ($?) { g++ complexnum2.cpp -o complexnum2 } ; if ($?) { .\complexnum2 }
first complex no:3+5i
second complex no:2+4i
sum:5+9i
diff:1+1i
prod:6+20i
PS D:\Utkarsha>  */