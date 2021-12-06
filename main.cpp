//Big Integer Library

#include<iostream>
#include<cstring>
#include<string>
using namespace std;

bool isgreater(string A,string B)
{
	int count=0;
	for(int i=0;i<A.length();i++)
 	{
 		if(A[i]=='0')
 		{
 			count++;
		}
		else
		{
			break;
		}
	}
	A=A.substr(count);
	count=0;
	for(int i=0;i<B.length();i++)
 	{
 		if(B[i]=='0')
 		{
 			count++;
		}
		else
		{
			break;
		}
	}
	B=B.substr(count);
	if(A.length() > B.length())
	{
		return true;	
	}
	else if(A.length() < B.length())
	{
		return false;
	}	
	else if(A.length()==B.length())
	{
		for(int i=0;i<A.length();i++)
		{
			if(A[i]>B[i])
			{
				return true;
			}
			if(A[i]<B[i])
			{
				return false;
			}
		}
	}
	return true;
}



string add(string A,string B)
{
	string temp;
	if (isgreater(A,B))
    {
       temp=A;
	   A=B;
	   B=temp;
	}
 
    string res="";
 
    int n1=A.length(),n2=B.length();
    int diff=n2-n1; 
    int c=0;
  
    for(int i=n1-1;i>=0;i--)
    {
        int sum =((A[i]-'0')+(B[i+diff]-'0')+c);
        res.push_back(sum%10+'0');
        c=sum/10;
    }
 
    for(int i=n2-n1-1;i>=0;i--)
    {
        int sum=((B[i]-'0')+c);
        res.push_back(sum%10+'0');
        c=sum/10;
    }
 
    if(c>0)
    {
	    res.push_back(c+'0');
	}
	
	string newres;
	for(int i=res.length()-1;i>=0;i--)
	{
		newres.push_back(res[i]);
	}
    return newres;
}

string subtract(string A,string B)
{
	string temp;
	if(A==B)
	{
		return "0";
	}
    if(!isgreater(A,B))
    {
    	temp=A;
    	A=B;
    	B=temp;
	}
    int n1=A.length(),n2=B.length();
	int diff=n1-n2,c=0;
 	string res="";

    for(int i=n2-1;i>=0;i--) 
	{
        int subtract=((A[i+diff]-'0')-(B[i]-'0')-c);
        if (subtract<0) 
		{
            subtract=subtract+10;
            c=1;
        }
        else
        {
		    c=0;
 		}
        res.push_back(subtract+'0');
    }

    for(int i=n1-n2-1;i>=0;i--) 
	{
        if (A[i]=='0' && c) 
		{
            res.push_back('9');
            continue;
        }
        int subtract=((A[i]-'0')-c);
        if (i>0 || subtract>0)
        {
            res.push_back(subtract+'0');
        }
		c=0;
    }
    int count=0;
	string newres;
	
	for(int i=res.length()-1;i>=0;i--)
	{
		newres.push_back(res[i]);
	}
	for(int i=0;i<newres.length();i++)
 	{
 		if(newres[i]=='0')
 		{
 			count++;
		}
		else
		{
			break;
		}
	}
	newres=newres.substr(count);
    return newres;
}



string multiply(string A, string B) 
{
	if(A=="0"||B=="0") 
   	{
		return "0";
   	}
   	string product(A.size() + B.size(), 0);
   	for (int i=A.size()-1;i>=0;i--) 
   	{
      	for(int j=B.size()-1;j>=0;j--) 
		{
            int n=(A[i]-'0')*(B[j]-'0')+product[i+j+1];
            product[i+j+1]=n%10;
            product[i+j]+=n/10;
		}
   	}
   	for(int i=0;i<product.size();i++) 
   	{
      product[i]+='0';
   	}
   	int count=0;
   	for(int i=0;i<product.length();i++)
 	{
 		if(product[i]=='0')
 		{
 			count++;
		}
		else
		{
			break;
		}
	}
	product=product.substr(count);
	return product;
}

string expo(string A,long long int X)
{
	string res="1";
	while(X>0)
	{
		if(X&1)
		{
			res=multiply(A,res);
		}
		A=multiply(A,A);
		X=X>>1;
	}
	return res;
}


string calc(string expr)
{
	int pos,i,l,r;
	string X,Y,temp;
	for(i=0;i<expr.size();i++)
	{
		if(expr[i]=='x')
		{
			pos=i;
			l=pos-1;
			r=pos;
			while(l>0 && expr[l-1]-'0'>=0 && expr[l-1]-'0'<=9)
			{
				l--;
			}
			while(r<expr.size()-1 && expr[r+1]-'0'>=0 && expr[r+1]-'0'<=9)
			{
				r++;
			}
			X=expr.substr(l,pos-l);
			Y=expr.substr(pos+1,r-pos);
			temp=multiply(X,Y);
			expr.erase(l,r-l+1);
			expr.insert(l,temp);
			i=0;		
		}		
	}
	for(i=0;i<expr.size();i++)
	{
		if(expr[i]=='+')
		{
			pos=i;
			l=pos-1;
			r=pos;
			while(l>0 && expr[l-1]-'0'>=0 && expr[l-1]-'0'<=9)
			{
				l--;
			}
			while(r<expr.size()-1 && expr[r+1]-'0'>=0 && expr[r+1]-'0'<=9)
			{
				r++;
			}
			X=expr.substr(l,pos-l);
			Y=expr.substr(pos+1,r-pos);
			temp=add(X,Y);
			expr.erase(l,r-l+1);
			expr.insert(l,temp);
			i=0;		
		}	
	}
	for(i=0;i<expr.size();i++)
	{
		if(expr[i]=='-')
		{
			pos=i;
			l=pos-1;
			r=pos;
			while(l>0 && expr[l-1]-'0'>=0 && expr[l-1]-'0'<=9)
			{
				l--;
			}
			while(r<expr.size()-1 && expr[r+1]-'0'>=0 && expr[r+1]-'0'<=9)
			{
				r++;
			}
			X=expr.substr(l,pos-l);
			Y=expr.substr(pos+1,r-pos);
			temp=subtract(X,Y);
			expr.erase(l,r-l+1);
			expr.insert(l,temp);
			i=0;		
		}	
	}
	return expr;
}


string division(string A,string B)
{
	string temp;
	if((A==B) || (B.length()==1 && B[0]=='0'))
	{
		return "0";
	}
	if(!isgreater(A,B))
	{
		return A;
	}
	int i=0;
	temp="";
	string temp2;
	temp.push_back(A[i]);
	while(isgreater(B,temp))
	{
		i++;
		temp.push_back(A[i]);
	}
	while(A.size() > i)
	{
		while(isgreater(temp,B))
		{
			temp=subtract(temp,B);
		}
		i++;
		if(i<A.size())
		{
			temp.push_back(A[i]);
		}
	}
	int count=0;
	if(temp.length()>1)
	{
		for(int i=0;i<temp.length()-1;i++)
	 	{
	 		if(temp[i]=='0')
	 		{
	 			count++;
			}
			else
			{
				break;
			}
		}
	}
	temp=temp.substr(count);
	return temp;
}
	

string gcd(string A,string B)
{
	cout<<A<<"\t"<<B<<endl;
	if(B[0]=='0')
    {
		return A;
	}  
	return gcd(B, division(A,B));
}


string fact(int A)
{
	string res="1",temp,temp2;
	int i;
    for(int i=2;i<=A;i++)
    {
		temp="";
		if(i<10)
        {
			temp.push_back(i+'0');
		}
		else
		{
			int k=i;
			while(k>0)
			{
				temp2="";
				temp2.push_back(k%10+'0');
				temp.insert(0,temp2);
				k=k/10;
			}
		}
		res=multiply(temp,res);
	}
    return res;
}


int main()
{
	int option;
	while(true)
	{
		cout<<"Enter an option:\n1.Exponentiation\n2.GCD\n3.Factorial\n4.Calculate expression\n";
		cin>>option;
		string A,B;
		long long int X;
		switch(option)
		{	
			case 1: cout<<"Enter the base and exponent:\n";
					cin>>A>>X;
					cout<<"Answer: "<<expo(A,X)<<endl;
					break;
					
			case 2: cout<<"Enter the numbers:\n";			
					cin>>A>>B;
					cout<<"GCD is: "<<gcd(A,B)<<endl;
					break;
					
			case 3: cout<<"Enter the number:\n";
					cin>>X;
					cout<<"Answer: "<<fact(X)<<endl;
					break;
			
			case 4: cout<<"Enter the expression string:\n";			
					cin>>A;
					cout<<"The answer to the expression is: "<<calc(A)<<endl;
					break;			
		}
	}
	return 0;
}
