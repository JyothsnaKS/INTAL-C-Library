#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(100+sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(100+3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}
	n = strlen(str);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = (char*)malloc(100+n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
	 	i->s = (char*)malloc(100+n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

//Returns character at a given position in the integer
int val(intal*z,int i){
	int len=strlen(z->s);
	if(i<len-1)
		return z->s[len-i-1]-48;
	return 0;	
}
// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	if(a == NULL)
		return b; //no intal to print
	if(b == NULL)
		return a;
	intal* f1 = create_intal();
	if((a->s[0]=='+'&&b->s[0]=='+')||(a->s[0]=='-'&&b->s[0]=='-')){
		int a_len=strlen(a->s);
		int b_len=strlen(b->s);
		int max = (a_len>=b_len)?a_len:b_len;
		intal* sum = create_intal();
		sum->s=(char*)malloc(100+a_len+b_len);
		int i,j=0,carry=0,temp;
		for(i=0;i<max-1;i++){
			int c1=val(a,i);
			int c2=val(b,i);
			temp=c1+c2+carry;
			carry=0;
			if(temp>9){
				carry=1;
				temp-=10;
			}
			sum->s[j++]=temp+48;
		}
		if(carry)sum->s[j++]=carry+48;
		sum->s[j]='\0';
		int len=strlen(sum->s);
		for(i=0;i<len/2;i++){
			char t=sum->s[i];
			sum->s[i]=sum->s[len-i-1];
			sum->s[len-i-1]=t;
		}
		f1->s=(char*)malloc(100+j+3);
		f1->s[0]=a->s[0];
		strcpy(f1->s+1,sum->s);
		strcpy(sum->s,f1->s);
		delete_intal(&f1);
		return sum;
	}
	else if(a->s[0]=='-'&&b->s[0]=='+'){
		f1->s=(char*)malloc(100+strlen(a->s)+3);
		f1->s[0]='+';
		strcpy(f1->s+1,a->s+1);		
		subtract_intal(b,f1);
	}
	else if(a->s[0]=='+'&&b->s[0]=='-'){
		f1->s=(char*)malloc(100+strlen(b->s)+3);
		f1->s[0]='+';
		strcpy(f1->s+1,b->s+1);	
		subtract_intal(a,f1);		
	}
}

//Function to pad a given number of leading zeroes to the string
intal* padding(intal*z,int max){
	int j,n,k=1;
	n=max;
	j=strlen(z->s)+1;	
	intal* temp = create_intal();
	temp->s=(char*)malloc(100+max+j+1);
	temp->s[0]='+';
	while(j<=n){
		temp->s[k++]='0';
		j++;
	}
	j=1;
	while(z->s[j]!='\0')temp->s[k++]=z->s[j++];
	temp->s[k]='\0';	
	return temp;
}
void m_padding(intal*a,intal*b){
	int a_len=strlen(a->s);
	int b_len=strlen(b->s);
	int max=(a_len>=b_len)?a_len:b_len;
	intal*temp=create_intal();
	if(a_len<b_len){
		temp=padding(a,max);
		strcpy(a->s+1,temp->s+1);
	}
	else if(a_len>b_len){
		temp=padding(b,max);
		strcpy(b->s+1,temp->s+1);
	}
	delete_intal(&temp);
}

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){
	if(a == NULL)
		return b; //no intal to print
	if(b == NULL)
		return a;
	intal* f1 = create_intal();
	intal* f2 = create_intal();	
	intal* t = create_intal();	
	if((a->s[0]=='+'&&b->s[0]=='+')||(a->s[0]=='-'&&b->s[0]=='-')){
		intal* diff = create_intal();
		char sign;
		int a_len=strlen(a->s);
		int b_len=strlen(b->s);
		int max=(a_len>=b_len)?a_len:b_len;
		int i;
		diff->s=(char*)malloc(100+max+3);
		m_padding(a,b);
		
		if(strcmp(a->s+1,b->s+1)>=0){
			sign=a->s[0];
			f1->s=(char*)malloc(100+a_len+3);
			f2->s=(char*)malloc(100+b_len+3);
			read_intal(f1,a->s);
			read_intal(f2,b->s);
		}
		else{
			if(b->s[0]=='+')
				sign='-';
			else sign='+';
			f1->s=(char*)malloc(100+b_len+3);
			f2->s=(char*)malloc(100+a_len+3);
			read_intal(f2,a->s);
			read_intal(f1,b->s);			
		}
		int borrow=0,j=0,temp;
		for(i=0;i<max-1;i++){
			int c1=val(f1,i);
			int c2=val(f2,i);
			temp=c1-c2-borrow;
			borrow=0;
			if(temp<0){
				borrow=1;
				temp+=10;
			}
			diff->s[j++]=temp+48;
		}
		diff->s[j]='\0';
		int len=strlen(diff->s);
		for(i=0;i<len/2;i++){
			char tmp=diff->s[i];
			diff->s[i]=diff->s[len-i-1];
			diff->s[len-i-1]=tmp;
		}
		t->s=(char*)malloc(100+j+3);
		t->s[0]=sign;
		strcpy(t->s+1,diff->s);
		strcpy(diff->s,t->s);
		delete_intal(&f1);delete_intal(&f2);delete_intal(&t);
		return diff;
	}
	else if(a->s[0]=='-'&&b->s[0]=='+'){
		delete_intal(&f2);
		f1->s=(char*)malloc(100+strlen(b->s)+3);
		f1->s[0]='-';
		strcpy(f1->s+1,b->s+1);		
		add_intal(a,f1);
	}
	else if(a->s[0]=='+'&&b->s[0]=='-'){
		delete_intal(&f2);
		f1->s=(char*)malloc(100+strlen(b->s)+3);
		f1->s[0]='+';
		strcpy(f1->s+1,b->s+1);	
		add_intal(a,f1);		
	}
}

// Returns substring between given indices
intal* substring(intal*st,int p,int l) { 
	intal*sub=create_intal();
	sub->s=(char*)malloc(100+strlen(st->s));
	sub->s[0]='+';
	int c = 1;
	while (c <= l && st->s[p+c]!='\0') {
		sub->s[c] = st->s[p+c];
		c++;
	}
	sub->s[c] = '\0';
	return sub;
}

//Computing to the power 10 of a given number 
intal* power(intal*z,int n){ 
	intal* temp = create_intal();
	temp->s=(char*)malloc(100+strlen(z->s)+n+3);
	strcpy(temp->s,z->s);
	int j;
	j=1;
	while(j<=n){
		strcat(temp->s,"0");
		j++;
	}
	return temp;
	
}

//Karatsuba algorithm
intal* karatsuba(intal*a,intal*b){
	long long int m,n;
	intal*r1=create_intal();

	n=strlen(a->s)-1;

	if(n==1){//intial condition
		r1->s=(char*)malloc(100+4);
		r1->s[0]='+';
		sprintf(r1->s+1,"%d",(a->s[1]-'0')*(b->s[1]-'0'));
		return r1;
	}
	
	intal*r2=create_intal();
	intal*r3=create_intal();
	
	if(n%2!=0){ // padding  zero if length of the number is odd
		n++;
		a=padding(a,n+1);
		b=padding(b,n+1);	
	}
	m=n/2;
	
	intal*a1=create_intal();
	intal*a2=create_intal();
	intal*b1=create_intal();
	intal*b2=create_intal();
	intal*a12=create_intal();
	intal*b12=create_intal();
	
	a1=substring(a,0,m);
	b1=substring(b,0,m);
	a2=substring(a,m,n-1);
	b2=substring(b,m,n-1);

	a12=add_intal(a1,a2);
	b12=add_intal(b1,b2);
	m_padding(a12,b12);
	
	r1=karatsuba(a1,b1);
	r2=karatsuba(a2,b2);
	r3=karatsuba(a12,b12);
	
	intal*f1=create_intal();
	intal*f2=create_intal();
	intal*f3=create_intal();
	intal*f4=create_intal();
	intal*f5=create_intal();
	intal*f6=create_intal();

	//computing intermediate results
	f1=power(r1,(n-m)*2);
	f2=subtract_intal(r3,r1);
	f3=subtract_intal(f2,r2);
	f4=power(f3,n-m);
	f5=add_intal(f1,f4);
	f6=add_intal(f5,r2);

	delete_intal(&r1);delete_intal(&r2);delete_intal(&r3);delete_intal(&f1);delete_intal(&f2);delete_intal(&f3);delete_intal(&f4);delete_intal(&f5);delete_intal(&a1);delete_intal(&a2);delete_intal(&b1);delete_intal(&b2);delete_intal(&a12);delete_intal(&b12);
	
	return f6;
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	if(a==NULL || b==NULL)
	return NULL;
	char sign;
	intal* f1 = create_intal();
	intal* f2 = create_intal();	
	intal* temp=create_intal();
	int i=1,j=1;
	
	temp->s=(char*)malloc(100+strlen(a->s)+1);
	temp->s[0]='+';
	while(a->s[i]=='0')i++;
	while(a->s[i]!='\0')temp->s[j++]=a->s[i++];
	temp->s[j]='\0';
	read_intal(f1,temp->s);
	free(temp->s);
	i=1;j=1;
	temp->s=(char*)malloc(100+strlen(b->s)+1);
	temp->s[0]='+';
	while(b->s[i]=='0')i++;
	while(b->s[i]!='\0')temp->s[j++]=b->s[i++];
	temp->s[j]='\0';
	read_intal(f2,temp->s);
	
	if((a->s[0]=='+'&&b->s[0]=='+')||(a->s[0]=='-'&&b->s[0]=='-'))
		sign='+';
	else sign='-';
	
	m_padding(f1,f2);
	intal* ans=create_intal();
	ans=karatsuba(f1,f2);
	
	temp->s=(char*)malloc(100+strlen(ans->s)+1);
	i=1;j=1;
	temp->s[0]=sign;

	while(ans->s[i]=='0')i++;
	while(ans->s[i]!='\0'){
		temp->s[j]=ans->s[i];i++;j++;
	}
	temp->s[j]='\0';
	return temp;
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b){
	if(a==NULL || b==NULL)
		return NULL;
	char sign;
	int a_len=strlen(a->s);
	int b_len=strlen(b->s);
	int max=(a_len>=b_len)?a_len:b_len;

	intal* f1 = create_intal();
	intal* f2 = create_intal();			
	intal* z = create_intal();
	intal* count = create_intal();
	
	count->s=(char*)malloc(100+max+1);
	count->s[0]='+';
	count->s[1]='0';
	count->s[2]='\0';
	intal* constant = create_intal();
	read_intal(constant,"1");
	
	m_padding(a,b);

	if(strcmp(a->s+1,b->s+1)<0)
		return f1;

	z->s=(char*)malloc(100+max+1);
	z->s="+";;
	z=padding(z,max);

	read_intal(f1,a->s);
	read_intal(f2,b->s);
	f1->s[0]='+';
	f2->s[0]='+';
	while(strcmp(f1->s+1,z->s+1)>0 && strcmp(f1->s+1,f2->s+1)>=0 && f1->s[0]=='+'){
		f1=subtract_intal(f1,f2);
		count=add_intal(count,constant);
	}
	if(a->s[0]=='+'&&b->s[0]=='+')
		count->s[0]='+';
	else if(a->s[0]=='-'&&b->s[0]=='-')
		count->s[0]='+';
	else
		count->s[0]='-';
	delete_intal(&f1);delete_intal(&f2);delete_intal(&constant);delete_intal(&z);
	return count;
}

intal* exponent(intal* a,intal* n){
	intal* den=create_intal();
	intal* temp=create_intal();
	intal* z=create_intal();
	intal* fp=create_intal();intal* p=create_intal();
	int n_len=strlen(n->s);
	char last_char=n->s[n_len-1];
	int max=strlen(n->s);
	z->s=(char*)malloc(100+max+3);
	z->s="+1";
	z=padding(z,max-1);
	
	read_intal(den,"+2");
	if(strcmp(n->s,z->s)==0){
		return a;
	}
	n=divide_intal(n,den);
	temp=exponent(a,n);
	fp=multiply_intal(temp,temp);
	
	if(last_char=='1'||last_char=='3'||last_char=='5'||last_char=='7'||last_char=='9'){
		p=multiply_intal(a,fp);
		return p;
	}
	delete_intal(&den);delete_intal(&temp);delete_intal(&z);delete_intal(&p);
	return fp; 
}

intal* brute_exponent(intal* a,intal* n){
	int max=strlen(n->s);	
	intal* z = create_intal();
	intal* p = create_intal();
	intal* fp = create_intal();
	read_intal(p,a->s);
	intal* constant = create_intal();
	read_intal(constant,"1");

	z->s=(char*)malloc(100+max+3);
	z->s="+1";
	z=padding(z,max);

	while(strcmp(n->s+1,z->s+1)>0){
		intal*fn=create_intal();
		fn=subtract_intal(n,constant);
		delete_intal(&n);
		n=create_intal();
		read_intal(n,fn->s);
		delete_intal(&fn);
		fp = create_intal();
		fp=multiply_intal(p,a);
		delete_intal(&p);
		p=create_intal();
		read_intal(p,fp->s);
		delete_intal(&fp);
	}

	delete_intal(&constant);delete_intal(&z);
	return p;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	if(a==NULL || b==NULL || b->s[0]=='-')
		return NULL;
	char sign='+';
	int b_len=strlen(b->s);
	char last_char=b->s[b_len-1];
	if((last_char=='1'||last_char=='3'||last_char=='5'||last_char=='7'||last_char=='9')&&a->s[0]=='-')
		sign='-';
	
	intal* f1 = create_intal();
	intal* f2 = create_intal();	
	read_intal(f1,a->s);
	read_intal(f2,b->s);

	intal* ans=create_intal();
	ans=exponent(f1,f2);

	ans->s[0]=sign;
	return ans;
}
