#include<bits/stdc++.h>
using namespace std;

string getAddr(fstream &fin,string n){
    // int no;
    string no,name,addr;

    while(!fin.eof()){
        fin >> no >> name >> addr;
        if(no == n) {
            fin.seekg(0,ios::beg);
            return addr;
        }
    }
    fin.seekg(0,ios::beg);
    return "NAN";
}


int main(){

    fstream ic,st,lt;
    ic.open("ic.txt");
    st.open("symtab.txt");
    lt.open("littab.txt");

    ofstream mct;
    mct.open("machine_code.txt");

    string lc,opcode,op1,op2,mc = "";

    cout << "\n\n\t---- MACHINE CODE ----\n";
    cout << "LC" << "\t" << "OPCODE" << "\t" << "OP1" << "\t" << "OP2" << "\t" << "MC" << "\n";

    while(!ic.eof())
    {
        ic >> lc >> opcode >> op1 >> op2;

        if(opcode.substr(1,2) == "AD" || (opcode.substr(1,2) == "DL" && opcode.substr(4,2) == "02")){       //  AD and DS statements dont have machine code
            mc = "--- No Machine Code ---";
        }
        else if(opcode.substr(1,2) == "DL"){																// DC statements
            mc = "00\t0\t00" + op1.substr(3,1);
        }
        else{
            if(op2 == "NAN"){
                if(op1 == "NAN")
                	mc = opcode.substr(4,2) + "\t0\t000";
                else
                	mc = opcode.substr(4,2) + "\t" + getAddr(st,op1.substr(3,1)) + "\t000";				// will be in form (C,1) etc
            }
            else{
                if(op2.substr(1,1) == "L"){
                    mc = opcode.substr(4,2) + "\t" + op1.substr(1,1) + "\t" + getAddr(lt,op2.substr(3,1));		// literal tab	// will be in form (1) (L,1)
                }
                else
                	mc = opcode.substr(4,2) + "\t" + op1.substr(1,1) + "\t" + getAddr(st,op2.substr(3,1));		// symbol tab
            }
        }

        cout << lc << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << mc << "\n";
        mct << lc << "\t" << mc << "\n";
    }

    return 0;
}
