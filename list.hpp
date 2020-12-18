#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int display[4][3][4] = 
{
    {{2, 0, 0, 0},{2, 4, 5, 16}, {2, 6, 7, 17}},
    {{2, 0, 0, 0},{2, 1, 1, 1}, {2, 8, 8, 8}},
    {{2, 0, 0, 0},{2, 1, 9, 18}, {2, 10, 11, 19}},
    {{2, 0, 0, 0},{2, 12, 13,20}, {2, 14, 15, 21}}
};

class term{
public:
    int _coef;
    int _expo;
    int _denom;
    int _root;
    int _log;

    void setTerm(int, int, int, int, int);
    void displayTerm();
};

struct node{
    term data;
    node *next;
};

class list{
private:
    int size;
    node *head,*tail;
public:
    list();
    void append(term);
    bool ifInfinity();
    void displayAll();
    void simplify();
    void sort();
    void nestedMultiplication(term);
    void simplifyComponents();

};

void term::displayTerm(){
    int state1, state2, state3, finalstate;
    if(_log > 0)
        state1 = 0;
    else if(_expo == 0)
        state1 = 1;
    else if(_expo == 1)
        state1 = 2;
    else if(_expo > 1)
        state1 = 3;
    
    if(_coef == 0)
        state2 = 0;
    if(_coef == 1)
        state2 = 1;
    if(_coef > 1 || _coef < 0)
        state2 = 2;
    
    if(_denom == 0)
        state3 = 0;
    if(_denom == 1)
        state3 = 1;
    if(_denom > 1)
        state3 = 2;
    if(_root > 1)
        state3 = 3;

    finalstate = display[state1][state2][state3];

    if(finalstate == 0)
        cout<<"0";
    if(finalstate == 1)
        cout<<"1";
    if(finalstate == 2)
        cout<<"infinite";
    if(finalstate == 4)
        cout<<"log("<<_root<<") n";
    if(finalstate == 5)
        cout<<"log("<<_root<<") n/"<<_denom;
    if(finalstate == 6){
        if(_coef > 0){
            if(_expo > 0){
                if(_expo == 1)
                    cout<<_coef<<"n log("<<_log<<") n";
                else
                    cout<<_coef<<"n^"<<_expo<<" log("<<_log<<") n";
            } 
            else 
                cout<<_coef<<" log("<<_log<<") n";
        }
        else{
            if(_expo > 0){
                if(_expo == 1)
                    cout<<-1*_coef<<"n log("<<_log<<") n";
                else
                    cout<<-1*_coef<<"n^"<<_expo<<" log("<<_log<<") n";
            }
            else
                cout<<-1*_coef<<" log("<<_log<<") n";
        }
            
    }
    if(finalstate == 7){
        if(_coef > 0){
            if(_expo > 0){
                if(_expo == 1)
                    cout<<_coef<<"n log("<<_log<<") n/"<<_denom;
                else
                    cout<<_coef<<"n^"<<_expo<<" log("<<_log<<") n/"<<_denom;
            } 
            else 
                cout<<_coef<<" log("<<_log<<") n/"<<_denom;
        }
        else{
            if(_expo > 0){
                if(_expo == 1)
                    cout<<-1*_coef<<"n log("<<_log<<") n/"<<_denom;
                else
                    cout<<-1*_coef<<"n^"<<_expo<<" log("<<_log<<") n/"<<_denom;
            }
            else
                cout<<-1*_coef<<" log("<<_log<<") n/"<<_denom;
        }       
    }
    if(finalstate == 8){
        if(_coef > 0)
            cout<<_coef;
        else
            cout<<-1*_coef;
    }
    if(finalstate == 9)
        cout<<"n/"<<_denom;
    if(finalstate == 10){
        if(_coef > 0)
            cout<<_coef<<"n";
        else
            cout<<-1*_coef<<"n";
    }
    if(finalstate == 11){
        if(_coef > 0)
            cout<<_coef<<"n/"<<_denom;
        else
            cout<<-1*_coef<<"n/"<<_denom;
    }
    if(finalstate == 12)
        cout<<"n^"<<_expo;
    if(finalstate == 13)
        cout<<"(n/"<<_denom<<")^"<<_expo;
    if(finalstate == 14){
        if(_coef > 0)
            cout<<_coef<<"n^"<<_expo;
        else
            cout<<-1*_coef<<"n^"<<_expo;
    }
    if(finalstate == 15){
        if(_coef > 0)
            cout<<_coef<<"(n/"<<_denom<<")^"<<_expo;
        else
            cout<<-1*_coef<<"n^"<<_expo;
    }
    if(finalstate == 16){
        if(_root == 2){
                cout<<" log("<<_root<<") sqrt(n)"; 
        }
        if(_root == 3){
                cout<<" log("<<_root<<") cubert(n)"; 
        }
    }
    if(finalstate == 17){
        if(_root == 2){
            if(_coef > 0)
                cout<<_coef<<" log("<<_root<<") sqrt(n)";
            else
                cout<<-1*_coef<<" log("<<_root<<") sqrt(n)";  
        }
        if(_root == 3){
            if(_coef > 0)
                cout<<_coef<<" log("<<_root<<") cubert(n)";
            else
                cout<<-1*_coef<<" log("<<_root<<") cubert(n)";  
        }
    }
    if(finalstate == 18){
        if(_root == 2){
            cout<<" sqrt(n^"<<_expo<<")";
        }
        if(_root == 3){
             cout<<" cubert(n^"<<_expo<<")"; 
        }
    }
    if(finalstate == 19){
         if(_root == 2){
            if(_coef > 0)
                cout<<_coef<<" sqrt(n)";
            else
                cout<<-1*_coef<<" sqrt(n)";
        }
        if(_root == 3){
             if(_coef > 0)
                cout<<_coef<<" cubert(n)";
            else
                cout<<-1*_coef<<" cubert(n^)";
        }
    }
    if(finalstate == 20){
        if(_root == 2){
            cout<<" sqrt(n^"<<_expo<<")";
        }
        if(_root == 3){
             cout<<" cubert(n^"<<_expo<<")"; 
        }
    }
    if(finalstate == 21){
        if(_root == 2){
            if(_coef > 0)
                cout<<_coef<<" sqrt(n^"<<_expo<<")";
            else
                cout<<-1*_coef<<" sqrt(n^"<<_expo<<")";
        }
        if(_root == 3){
             if(_coef > 0)
                cout<<_coef<<" cubert(n^"<<_expo<<")";
            else
                cout<<-1*_coef<<" cubert(n^"<<_expo<<")";
        }
    }
}

void term::setTerm(int coef, int expo, int deno, int root, int log){
    _coef = coef;
    _expo = expo;
    _denom = deno;
    _root = root;
    _log = log;
}

list::list(){
    head = NULL;
    tail = NULL;
}
void list::append(term n){
    node *tmp = new node;
    tmp->data = n;
    tmp->next = NULL;

    if(head == NULL){
        head = tmp;
        tail = tmp;
        size = 1;
    }
    else{
        tail->next = tmp;
        tail = tail->next;
        size++;
    }
}

bool list::ifInfinity(){
    node *tmp;
    tmp = head;
    while (tmp != NULL){
        if(tmp!=NULL)
            if(tmp->data._denom == 0)
                return true;
        tmp = tmp->next;
    }
    return false;
}

void list::displayAll(){

    if(ifInfinity()){
        cout<<"infinite"<<endl;
        return;
    }
    node *tmp;
    tmp = head;
    while (tmp != NULL){
        tmp->data.displayTerm();
        //cout<<"ceof = "<<tmp->data._coef<<endl;
        tmp = tmp->next;
        if(tmp!=NULL)
            if(tmp->data._coef > 0)
                cout<<" + ";
            else
                cout<<" - ";
    }
    cout<<endl;
}

void list::simplify(){
    if(ifInfinity())
        return;

    bool found;
    node *i, *j, *del;
    i = head;
    del = i;
    while(i!=NULL){
        del = i;
        j = del;
        j = j->next;
        while(j!=NULL){
            found = false;
            if(i->data._expo == j->data._expo &&i->data._denom == j->data._denom &&i->data._root == j->data._root && i->data._log == j->data._log){
                i->data._coef += j->data._coef;
                if(del->next!=NULL){
                    found = true;
                    del->next = del->next->next;
                }
                else{
                    
                }
            }
            if(j->next == NULL)
                break;
            j = j->next;
            if(!found)
                del = del->next;
        }
        if(i->next == NULL)
            break;
        i = i->next;
    }
}

void list::sort(){
    if(head==NULL)
		return;
	else{
		node* i = head;
		while(i!=NULL){
			node* min = i;
			node* j = i->next;
			while(j!=NULL){
				if(j->data._expo>min->data._expo)
					min = j;
				j = j->next;		
			}
			if(min != j){
				term s = i->data;
				i->data = min->data;
				min->data = s;
			}
			i = i->next;

		}
	}
	
}

void list::nestedMultiplication(term a){
    node* tmp = head;
    
    while(tmp!=NULL){
        tmp->data._expo += a._expo;
        tmp = tmp->next;
    }
}

void list::simplifyComponents(){
    node *tmp = head;
    int n, d, r;

    while(tmp!=NULL){
        //simplify exponent
        if(tmp->data._root > 1 && tmp->data._expo > 1){
            n = tmp->data._expo;
            d = tmp->data._root;
            while(d>0){
                r = n%d;
                n = d;
                d = r;
            }
            tmp->data._expo /= n;
            tmp->data._root /= n;
        }
        if(tmp->data._denom > 1 && tmp->data._coef > 1){
            n = tmp->data._coef;
            d = tmp->data._denom;
            while(d>0){
                r = n%d;
                n = d;
                d = r;
            }
            tmp->data._coef /= n;
            tmp->data._denom /= n;
        }
        tmp = tmp->next;
    }
}