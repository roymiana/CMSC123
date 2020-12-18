#include "loop.hpp"
#include "list.hpp"

string filetoString(string);
void eraseSpace(string&);
string finalT_ofN(loop, list&);
string loopExtractor(loop, string, list&);
string nestedloop(loop, string, list&);

bool ifNested;

int main(){
    string token, filename, finalTime;
	loop a;
    list t_n;
	cin>>filename;
    token = filetoString(filename);
    eraseSpace(token);

    finalTime = loopExtractor(a, token, t_n);
    cout<<"T(n) = "<<finalTime<<endl;
    t_n.sort();
    t_n.simplify();
    t_n.simplifyComponents();
    cout<<"T(n) = ";
    t_n.displayAll();
    
}

string filetoString(string filename){
    string token;
    ifstream file(filename);
	if(file.is_open()){
		getline(file, token, '\0');
	}
    return token;
}

void eraseSpace(string &token){
	token.erase(remove(token.begin(), token.end(), ' '), token.end());
	token.erase(remove(token.begin(), token.end(), '\r'), token.end());
	token.erase(remove(token.begin(), token.end(), '\n'), token.end());
}

string finalT_ofN(loop a, list &time){
    bool twoterms = false;
    term aTerm, bTerm;
    string timeComplexity;
    int _init, _cond, _iter, _totalOper, y, status, ans;
    _totalOper = a.getTotalOperations();
    _init = atoi(a.get_initializer().getValue().c_str());
    _cond = atoi(a.get_condition().getValue().c_str());
    _iter = a.get_iteration().getValue();
    y = a.get_initializer().getCount() + a.get_condition().getCount();
    status = a.getFinalState();
    //cout<<"status = "<<status<<endl;
    if(status == 0){
        ans = _totalOper*(_cond - (_init - 2)) + y;
        aTerm.setTerm(ans, 0, 1, 1, 0);
        timeComplexity = to_string(ans);
    }
    if(status == 1){
        ans = (_totalOper*(_cond/_iter - (_init - 2))) + y;
        aTerm.setTerm(ans, 0, 1, 1, 0);
        timeComplexity = to_string(ans);
    }
    if(status == 2){
        timeComplexity = to_string(_totalOper) 
                        + " log(" 
                        + to_string(_iter) 
                        + ") " 
                        + to_string(_iter);
        ans = _totalOper*(-(_init - 2)) + y;
        aTerm.setTerm(_totalOper, 0, 1, 1, _iter);
        bTerm.setTerm(ans, 0, 1, 1, 0);
        twoterms = true;
        if(ans > 0){
            timeComplexity.append(" + ");
        }
        else{
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));
    }
    if(status == 3){
        ans = _totalOper*(_cond - (_init - 1)) + y;
        aTerm.setTerm(ans, 0, 1, 1, 0);
        timeComplexity = to_string(ans);
    }
    if(status == 4){
        ans = (_totalOper*(_cond/_iter - (_init - 1))) + y;
        aTerm.setTerm(ans, 0, 1, 1, 0);
        timeComplexity = to_string(ans);
    }
    if(status == 5){
        timeComplexity = to_string(_totalOper) 
                        + " log(" 
                        + to_string(_iter) 
                        + ") " 
                        + to_string(_iter);
        ans = _totalOper*(-(_init - 1)) + y;
        aTerm.setTerm(_totalOper, 0, 1, 1, _iter);
        bTerm.setTerm(ans, 0, 1, 1, 0);
        twoterms = true;
        if(ans > 0){
            timeComplexity.append(" + ");
        }
        else{
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));
    }
    if(status == 6){
        timeComplexity = to_string(_totalOper) + "n";
        ans = _totalOper*(-(_init - 2)) + y;
        if(ans > 0){
            bTerm.setTerm(ans, 0, 1, 1., 0);
            timeComplexity.append(" + ");
        }
        else{
            bTerm.setTerm(ans, 0, 1, 1., 0);
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));

        aTerm.setTerm(_totalOper, 1, 1, 1, 0);
        twoterms = true;

    }
    if(status == 7){
        timeComplexity = to_string(_totalOper);
        if(_iter > 1){
            timeComplexity.append("n/");
            timeComplexity.append(to_string(_iter));
        }
        else
            timeComplexity.append("n");
        ans = _totalOper*(-(_init - 2)) + y;
        bTerm.setTerm(ans, 0, 1, 1, 0);
        if(ans > 0){
            timeComplexity.append(" + ");
        }
        else{
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));

        aTerm.setTerm(_totalOper, 1, _iter, 1, 0);
        twoterms = true;

    }
    if(status == 8){
        timeComplexity = to_string(_totalOper) 
                        + " log(" 
                        + to_string(_iter) 
                        + ") n";
        ans = _totalOper*(-(_init - 2)) + y;
        if(ans > 0){
            bTerm.setTerm(ans, 0, 1, 1, 0);
            timeComplexity.append(" + ");
        }
        else{
            bTerm.setTerm(ans, 0, 1, 1, 0);
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));

        aTerm.setTerm(_totalOper, 0, 1, 1, _iter);
        
        twoterms = true;
    }
    if(status == 9){
        timeComplexity = to_string(_totalOper);
        timeComplexity.append("n");
        ans = _totalOper*(-(_init - 1)) + y;
        if(ans > 0){
            bTerm.setTerm(ans, 0, 1, 1, 0);
            timeComplexity.append(" + ");
        }
        else{
            bTerm.setTerm(ans, 0, 1, 1, 0);
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));

        aTerm.setTerm(_totalOper, 1, 1, 1, 0);

        twoterms = true;
    }
    if(status == 10){
        timeComplexity = to_string(_totalOper);
        if(_iter > 1){
            timeComplexity.append("n/");
            timeComplexity.append(to_string(_iter));
        }
        else
            timeComplexity.append("n");
        ans = _totalOper*(-(_init - 1)) + y;
        if(ans > 0){
            bTerm.setTerm(ans, 0, 1, 1, 0);
            timeComplexity.append(" + ");
        }
        else{
            bTerm.setTerm(ans, 0, 1, 1, 0);
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));

        aTerm.setTerm(_totalOper, 1, _iter, 1, 0);
        
        twoterms = true;
    }
    if(status == 11){
        //x(log(c)n-(a-1))+2
        timeComplexity = to_string(_totalOper) 
                        + " log(" 
                        + to_string(_iter) 
                        + ") n";
        ans = _totalOper*(-(_init - 1)) + y;
        if(ans > 0){
            bTerm.setTerm(ans, 0, 1, 1, 0);
            timeComplexity.append(" + ");
        }
        else{
            bTerm.setTerm(ans, 0, 1, 1, 0);
            ans *= -1;
            timeComplexity.append(" - ");
        }
        timeComplexity.append(to_string(ans));
        
        aTerm.setTerm(_totalOper, 0, 1, 1, _iter);
        twoterms = true;
    }
    if(status == 12){
        timeComplexity = equation[12];
        aTerm.setTerm(2, 0, 1, 1, 0);
    }
    if(status == 13){
        timeComplexity = equation[13];
        aTerm.setTerm(1, 0, 0, 1, 0);
    }
    if(status == 14){
        timeComplexity = to_string(_totalOper);
        timeComplexity.append(" sqrt(n) + ");
        timeComplexity.append(to_string(y));
        aTerm.setTerm(_totalOper, 1, 1, 2, 0);
        bTerm.setTerm(y, 0, 1, 1, 0);
        twoterms = true;
    }
    if(status == 15){
        timeComplexity = to_string(_totalOper);
        timeComplexity.append(" cubert(n) + ");
        timeComplexity.append(to_string(y));
        aTerm.setTerm(_totalOper, 1, 1, 3, 0);
        bTerm.setTerm(y, 0, 1, 1, 0);
        twoterms = true;
    }
    if(ifNested)
        time.nestedMultiplication(aTerm);
    time.append(aTerm);
    if(twoterms == true)
        time.append(bTerm);
    
    return timeComplexity;
}

string nestedLoop(loop a, string token, list &time){
	int start, end, next;
	string subLoop, timeComplexity;;

	start = token.find("for");
	end = token.find("}");
	while(token.find("for", start+1) < end){
		start = token.find("for", start+1);
	}
	subLoop = token.substr(start, end-start + 1);
	//cout<<"subLoop: "<<subLoop<<endl;
    a.set_loop(subLoop);
    a.findt_ofN();
    timeComplexity = "(" + finalT_ofN(a, time) + ")";
    //cout<<"("<<timeComplexity<<")";
	token.erase(start, end-start + 1);
	next = token.find("}"); 
	if(next != string::npos)
	    return timeComplexity.append(nestedLoop(a, token, time));
    else
        return timeComplexity;
	//find inner loop
}

string loopExtractor(loop a, string token, list &time){
    ifNested = false;
	int start, end, initStart, next, flag = 0;
	string subLoop, timeComplexity;

	start = token.find("for");
	initStart = start;
	end = token.find("}");

	//for nested LOOPS
	if(token.find("for", start+1) < end){
		while(token.find("for", start+1) < end && token.find("for", start+1) != string::npos){
			start = token.find("for", start+1);
			end = token.find("}", end+1);
			if(flag==0){
				flag = 1;
                ifNested = true;
            }
		}
	}
	
	subLoop = token.substr(initStart, end-initStart + 1); //extract loop
	if(flag){
		
        timeComplexity  = nestedLoop(a, subLoop, time);
        //cout<<"T(n) = "<<timeComplexity<<endl;
    }
    else{
	//cout<<subLoop<<endl; 
    a.set_loop(subLoop);
    a.findt_ofN();
    timeComplexity = "(" + finalT_ofN(a, time) + ")";
    //cout<<"T(n) = "<<timeComplexity<<endl;
    }

	token.erase(initStart, end-initStart + 1); //erases the loop
		//cout<<token<<endl;
	next = token.find("for"); //checks if there is a next loop
		//cout<<"next"<<next<<endl;
	if(next != string::npos){
		//cout<<"pass"<<endl;
        timeComplexity.append(" + ");
		return timeComplexity.append(loopExtractor(a,token, time));
	}
    else
    {
        return timeComplexity;
    }
    
}


