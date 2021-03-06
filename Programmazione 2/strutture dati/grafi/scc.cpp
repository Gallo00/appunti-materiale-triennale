/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 

Esercizi su Grafi

Esercizio 6: Componenti Fortemente connesse via matrici di adiacenza
*/
#include <iostream>
#include <ctime>
#include <math.h>
#include "stack.cpp"
using namespace std;

#define W 0
#define G 1
#define B 2
#define inf len+1


template <class H> class MGraph {
	private:
		int len, n, m;
		/* 	n numero di nodi effettivo, 
			m numero di archi effettivo, 
			len numero massimo di nodi
		*/
		int **M; //Matrice di adiacenza
		int **tM; //Matrice di Adiacenza del Grafo Trasposto
		int t;
		H **K;	 // Matrice degli indici 
		int *d, *p, *f, *c, *r;
		int current_root;
		//Pila <int> stack; //Stack che andrà a contenere gli (indici corrispondenti ai) 
							//nodi, ordinati 
							// usando il vettore f, per la DFS sul grafo trasposto
		
		
		int findIndex(H x) {
		// Associa un indice al nodo (se esiste)
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		void printPath(int x) {
			if(x==-1) return;
			if(p[x]==-1) cout << x; 
			else {
				printPath(p[x]);
				cout << "->" << x; 
			}
		}
		
	public:
		Pila <int> stack; //Temporaneamente public
		
		MGraph(int len) {
			this->len = len;
			n = m = 0;
			d = new int[len]; /* vettore delle distanze 
								(dalla sorgente) 
								*/	
			p = new int[len]; // vettore dei precedenti
			f = new int[len];
			c = new int[len];
			r = new int[len]; // vettore delle radici
				// Serve per le componenti fort. connesse
			
			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			
			tM = new int*[len];
			for(int i=0; i<len; i++) {
				tM[i] = new int[len];
				for(int j=0; j<len; j++)
					tM[i][j] = 0;
			}
		}
		
		MGraph<H>* addNode(H k) {
			if(n==len) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}
		
		
		MGraph<H>* addEdge(H x, H y) {
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]) {
				M[i][j] = 1;
				m++;
			}
			return this;
		}
		
		void print() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++) {
					if(M[i][j]) cout << *K[j] << " ";
				} 
				cout << endl;
			}
		}
			
		void DFSVisit(int v) {
			c[v] = G;
			d[v] = t++;
			r[v] = current_root;
			for(int u=0; u<n; u++) {
				if(M[v][u]==1) {
					if(c[u]==W) {
						p[u]=v;
						DFSVisit(u);
					}
				}
			}
			c[v] = B;
			f[v] = t++;
			stack.Push(v);
		}
		
		void DFS() {
			t = 0;
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			for(int i=0; i<n; i++)
				if(c[i]==W) {
					current_root = i;
					DFSVisit(i);
				}
		}
		
		void printStamps()	{
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" 
					<< " : " << "(" << d[i] << ", " << f[i] << ")\n";
				} 
				cout << endl;
		}
		
		void Transpose()	{
			for(int i=0; i<len; i++)	
				//tM[i] = new int[len]; 
				for(int j=0; j<len; j++) 
					tM[i][j]=M[j][i];	
		}
		
		void printT() {
			for(int i=0; i<n; i++) {
				cout << "(" << i << ", " << *K[i] << ")" << " : ";
				for(int j=0; j<n; j++) {
					if(tM[i][j]) cout << *K[j] << " ";
				} 
				cout << endl;
			}
		}
		
		void tDFSVisit(int v) {
			c[v] = G;
			r[v] = current_root;
			//cout << "Valore attuale del campo current root:" << current_root <<endl;
			for(int u=0; u<n; u++) {
				if(tM[v][u]==1) {
					if(c[u]==W) {
						p[u]=v;
						tDFSVisit(u);
					}
				}
			}
			c[v] = B;
		}
		
		void tDFS() {
			for(int i=0; i<n; i++) {
				c[i] = W;
				p[i] = -1;
			}
			while (!stack.PilaVuota()) {
				int i=stack.Pop(); 
				if(c[i]==W) {
					current_root = i;
					tDFSVisit(i);
				}
			}
		}
		
		void printSSC()	{
			cout << "Componenti fortemente connesse: \n";
			int flag=0;
			
			for (int i=0; i<n; i++)	{
				for(int j=0; j<n;j++)
					if (r[j]==i) { flag=1; cout << j << " ";} 
				if (flag) {
					cout <<endl; 
					flag=0; 
					}
				}
		}
};

int main() {
	MGraph<char> *Gr = new MGraph<char>(9);
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0');
	Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	Gr->DFS();
	Gr->stack.StampaPila();
	
	//MGraph<char> *tGr = new MGraph<char>(9);
	Gr->Transpose(); 
	Gr->printT();
	Gr->tDFS(); 
	Gr->printSSC();	
	return 0;
}