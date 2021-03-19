#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


template <class H> struct Nodo
{
	H val;
	Nodo<H>* padre;
	Nodo<H>* sx;
	Nodo<H>* dx;
};


template <class H> class Albero
{
	public:
	Nodo<H>* radice;
	Albero() {radice=NULL;}
	
	Nodo<H>* ricerca(H x)
	{
		Nodo<H>* iter=radice;
		
		while(x!=iter->val)
		{
			if(x<=iter->val)
				iter=iter->sx;
			else 
				iter=iter->dx;
		}
		return iter;
	}
	
	int ricerca_livello(H x)
	{
		Nodo<H>* iter=radice;
		int livello=0;
		
		while(x!=iter->val)
		{
			if(x<=iter->val)
				iter=iter->sx;
			else 
				iter=iter->dx;
			
			livello++;
		}
		return livello;
	}
	void insert(H x);
	
	void canc(H x);
	void trapianta(Nodo<H>* x, Nodo<H>* y)
	{
		if(x==radice) radice=y;
		else if(x==NULL) radice=y;
		else if(x==x->padre->sx) x->padre->sx=y;
		else x->padre->dx=y;
		
		if(y!=NULL)
			y->padre=x->padre;
	}
	
	Nodo<H>* Minimo(Nodo<H>* x)
	{
		Nodo<H>* min=x;
		while(min->sx != NULL)
			min=min->sx;
		return min;
	}
	
	void print(ofstream & f,H x);
};

template <class H> void Albero<H>::insert(H x)
{
	Nodo<H>* nuovo=new Nodo<H>;
	nuovo->val=x;
	nuovo->sx=NULL;
	nuovo->dx=NULL;
	
	Nodo<H>* iter=radice;
	Nodo<H>* pre_iter=NULL;
	
	while(iter!=NULL)
	{
		pre_iter=iter;
		if(x<=iter->val)
		{
			iter=iter->sx;
		}
		else
		{
			iter=iter->dx;
		}
	}
	nuovo->padre=pre_iter;
	if(pre_iter==NULL)
	{
		radice=nuovo;
	}
	else if(x<=pre_iter->val)
	{
		pre_iter->sx=nuovo;
	}
	else 
	{
		pre_iter->dx=nuovo;
	}
}

template <class H> void Albero<H>::canc(H x)
{
	Nodo<H>* iter=ricerca(x);
	if(iter->sx==NULL) trapianta(iter,iter->dx);
	else if(iter->dx==NULL) trapianta (iter,iter->sx);
	else
	{
		Nodo<H>* y=Minimo(iter->dx);
		if(y->padre!=iter)
		{
			trapianta(y, y->dx);
			y->dx=iter->dx;
			y->dx->padre=y;
		}
		trapianta(iter,y);
		y->sx=iter->sx;
		y->sx->padre=y;
	}
	delete iter;
}

template <class H> void Albero<H>::print(ofstream & f,H nodo_livello_x)
{
	int livello=ricerca_livello(nodo_livello_x);
	f<<livello<<" ";
}




int main()
{
	fstream miofile("input.txt",fstream::in);
	ofstream outfile("output.txt");
	
	for(int riga=0; riga<100; riga++)
	{
		string tipo;
		miofile>>tipo;
		int operazioni;
		miofile>>operazioni;
		if(tipo=="int")
		{
			Albero<int> bst;
			for(int i=0; i<operazioni;i++)
			{
				string op;
			    miofile>>op;
			
			    if(op[0]=='i')  //inserimento
			    {
				    string a=op.substr(4,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    int dato_nuovo;
				    ss>>dato_nuovo;
				
			     	bst.insert(dato_nuovo);
			    }
				
				if(op[0]=='c')  //canc
				{
					string a=op.substr(5,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    int dato_da_cancellare;
				    ss>>dato_da_cancellare;
				
			     	bst.canc(dato_da_cancellare);
				}
			}
			
			int nodo_livello_x;
			miofile>>nodo_livello_x;
			bst.print(outfile , nodo_livello_x);
			
			outfile<<endl;
		}
		
		if(tipo=="double")
		{
			Albero<double> bst;
			for(int i=0; i<operazioni;i++)
			{
				string op;
			    miofile>>op;
			
			    if(op[0]=='i')  //inserimento
			    {
				    string a=op.substr(4,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    double dato_nuovo;
				    ss>>dato_nuovo;
				
			     	bst.insert(dato_nuovo);
			    }
				
				if(op[0]=='c')  //canc
				{
					string a=op.substr(5,op.length()-1);
				    stringstream ss;
				    ss<<a;
				    double dato_da_cancellare;
				    ss>>dato_da_cancellare;
				
			     	bst.canc(dato_da_cancellare);
				}
			}
		
			double nodo_livello_x;
			miofile>>nodo_livello_x;
			bst.print(outfile , nodo_livello_x);
			outfile<<endl;
		}
		
	}
}
