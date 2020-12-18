#include <iostream>

using namespace std;

class fraction{
public:
	int nume,deno;
	fraction();
	fraction(int,int);
	void simplify();
	void display();	
};

class MixedFraction{
public:
	int whole;
	fraction part;
	MixedFraction();
	MixedFraction(int);
	MixedFraction(int,int);
	MixedFraction(int,int,int);
	void display();
	MixedFraction times(MixedFraction);
};

int main(){
	MixedFraction m2(8,7), m;
	
	m.display();
	m2.display();
	m = m2.times(m2);

	m.display();
	//m.display();
	//m.display();
	//m.display();
	return 0;
}

void fraction::simplify(){
	int n = nume, d=deno,r;

	while(d>0){
		r = n%d;
		n = d;
		d = r;
	}

	nume = nume/n;
	deno = deno/n;
}

void fraction::display(){
	cout<<nume<<"/"<<deno<<endl;
}

fraction::fraction(){
	nume = 0;
	deno = 1;
}

fraction::fraction(int n,int d){
	nume = n;
	deno = d;
}

MixedFraction::MixedFraction(){
	whole = 0;
	cout<<"default"<<endl;
}
MixedFraction::MixedFraction(int w){
	whole = w;
}
MixedFraction::MixedFraction(int n,int d):whole(0),part(n,d){
	//whole = 0;
}
MixedFraction::MixedFraction(int w,int n,int d):whole(w),part(n,d){
	//whole = w;
}
void MixedFraction::display(){
	cout<<whole<<" ";
	part.display();
}
MixedFraction MixedFraction::times(MixedFraction mf){
	MixedFraction ans;

	ans.part.nume = (part.deno*whole+part.nume)*(mf.part.deno*mf.whole+mf.part.nume);
	ans.part.deno = part.deno*mf.part.deno;
	
	ans.part.simplify();

	ans.whole = ans.part.nume/ans.part.deno;
	ans.part.nume = ans.part.nume%ans.part.deno;

	return ans;

}

