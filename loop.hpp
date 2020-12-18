#include  "state.hpp"

class initializer{
    private:
        string content;
        string value;
        int count;
    public:
        void setInitializer(string);
        string getValue();
        int getCount();
};

class conditions{
    private:
        string content;
        string operation;
        string value;
        int count;
        int i;
    public:
        void setCondition(string);
        string getValue();
        string getOperation();
        int getCount();
        int getI();
};

class iterations{
    private:
        string content;
        string operation;
        int value;
        int count;
    public:
        void setIteration(string);
        string getOperation();
        int getCount();
        int getValue();
};

class operations{
    private:
        string content;
        int count;
    public:
        void setOperations(string);
        int getCount();
};

class loop{
    private:
        initializer _initializer;
        conditions _condition;
        iterations _iteration;
        operations _operation;

        string t_ofN;
        int finalState;
        int totalOperations;
    public:
        void set_initializer(string);
        void set_condition(string);
        void set_iteration(string);
        void set_operation(string);
        void set_totalOperations();
        void set_loop(string);
        void set_nestedLoop(string, string);
        void findt_ofN();
        initializer get_initializer();
        conditions get_condition();
        iterations get_iteration();
        operations get_operation();
        int getFinalState();
        int getTotalOperations();
};


int counter(string a){
	int b = 0;
	int length = a.length();
	for(int i = 0; i< length; i++){
		if(a[i] == '=')
			b++;
		else if(a[i] == '*'){
			b++;
			if(a[i+1] == '=')
				i++;
		}
		else if(a[i] == '/'){
			b++;
			if(a[i+1] == '=')
				i++;
		}
		else if(a[i] == '+'){
			b++;
			if(a[i+1] == '=' || a[i+1] == '+')
				i++;
		}
		else if(a[i] == '-'){
			b++;
			if(a[i+1] == '='|| a[i+1] == '-')
				i++;
		}
		else if(a[i] == '<'){
			b++;
			if(a[i+1] == '=')
				i++;
		}
		else if(a[i] == '>'){
			b++;
			if(a[i+1] == '=')
				i++;
		}
	}
	return b;
}

string findOperator(string a){
    int found;

    found = a.find("<=");
	if(found != string::npos){
		return "<=";
	}
	found = a.find(">=");
	if(found != string::npos){
		return ">=";
	}
	found = a.find("<");
	if(found != string::npos){
		return "<";
	}
	found = a.find(">");
	if(found != string::npos){
		return ">";
	}
}

string findIterator(string a){
    int found;

    found = a.find("++");
	if(found != string::npos){
		return "++";
	}
	found = a.find("--");
	if(found != string::npos){
		return "--";
	}
	found = a.find("+=");
	if(found != string::npos){
		return "+=";
	}
	found = a.find("-=");
	if(found != string::npos){
		return "-=";
	}
    found = a.find("*=");
	if(found != string::npos){
		return "*=";
	}
    found = a.find("/=");
	if(found != string::npos){
		return "/=";
	}
    
}

void initializer::setInitializer(string a){
    int pos;

    content = a;
    if(a.find("n") != string::npos){
        value = "n";
    }
    else{
        pos = a.find("=") + 1;
        value = a.substr(pos,a.length() -1);
    }
    count = counter(a);

    /*
    cout<<content<<endl;
    cout<<value<<endl;
    cout<<count<<endl;
    */
}

string initializer::getValue(){
    return value;
}

int initializer::getCount(){
    return count;
}

void conditions::setCondition(string a){
    int pos, is;
    content = a;
    operation = findOperator(a);
     if(a.find("n") != string::npos){
        value = "n";
    }
    else{
        pos = a.find(operation) + operation.length();
        value = a.substr(pos,a.length() -1);
    }
    count = counter(a);

    is = a.find("i");
    i = 1;
    while(is != string::npos){
        is = a.find("i",is+1);
        if(is != string::npos)
            i++;
    }
    /*
    cout<<content<<endl;
    cout<<operation<<endl;
    cout<<value<<endl;
    cout<<count<<endl;
    */
}

string conditions::getValue(){
    return value;
}

string conditions::getOperation(){
    return operation;
}

int conditions::getCount(){
    return count;
}

int conditions::getI(){
    return i;
}

void iterations::setIteration(string a){
    int pos;
    string Svalue;
    content = a;
    operation = findIterator(a);
    if(operation == "++" || operation == "--"){
        value = 1;
    }
    else{
        pos = a.find(operation) + operation.length();
        Svalue  = a.substr(pos,a.length() -1);
        value = atoi(Svalue.c_str());
    }
    count = counter(a);

    /*
    cout<<content<<endl;
    cout<<operation<<endl;
    cout<<value<<endl;
    cout<<count<<endl;
    */
}

string iterations::getOperation(){
    return operation;
}

int iterations::getCount(){
    return count;
}

int iterations::getValue(){
    return value;
}

void operations::setOperations(string a){
    content = a;
    count = counter(a);
    /*
    cout<<content<<endl;
    cout<<count<<endl;
    */
}

int operations::getCount(){
    return count;
}

void loop::set_initializer(string a){
    int start, end;

    start = a.find("int") + 3;
    end = a.find(";");
    _initializer.setInitializer(a.substr(start, (end-start)));
}

void loop::set_condition(string a){
    int start, end;

    start = a.find(";") + 1;
    end  = a.find(";", start+1);

    _condition.setCondition(a.substr(start, end-start));
}

void loop::set_iteration(string a){
    int start, end;

    start = a.find(";");
    start = a.find(";", start+1) + 1; 
    end = a.find(")");

    _iteration.setIteration(a.substr(start, end-start));
}

void loop::set_operation(string a){
    int start, end;

    start = a.find("{") + 1;
    end = a.find("}") - 1;

    _operation.setOperations(a.substr(start, end-start));
}

void loop::set_totalOperations(){
    totalOperations =   _operation.getCount()
                        +_iteration.getCount()
                        +_condition.getCount();
}                 

void loop::set_loop(string a){
    //cout<<endl;
    set_initializer(a);
    //cout<<endl;
    set_condition(a);
    //cout<<endl;
    set_iteration(a);
    //cout<<endl;
    set_operation(a);

    set_totalOperations();
}

void loop::findt_ofN(){
    int state_one, state_two, state_three;
    if(_condition.getI() > 1){
        if(_condition.getI() == 2)
            finalState = 14;
        if(_condition.getI() == 3)
            finalState = 15;
    }
    else{
    state_one = check_firstState(_initializer.getValue(), _condition.getValue());
    state_two = check_secondState(_condition.getOperation());
    state_three = check_thirdState(_iteration.getOperation());

    //cout<<state_one<<state_two<<state_three<<endl;
    finalState = state[state_one][state_two][state_three];
    }

    t_ofN = equation[finalState];
    //cout<<"T(n) = "<<t_ofN<<endl;
}

initializer loop::get_initializer(){
    return _initializer;
}

conditions loop::get_condition(){
    return _condition;
}

iterations loop::get_iteration(){
    return _iteration;
}

operations loop::get_operation(){
    return _operation;
}

int loop::getFinalState(){
    return finalState;
}
int loop::getTotalOperations(){
    return totalOperations;
}