//============================================================================
// Name        : 31365_Assembler_Pass1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<bits/stdc++.h>
using namespace std;

struct OPTAB{
    string opcode;
    string mclass;
    string mnemonic;
};

OPTAB OP[18] {
    {"STOP","IS","00"},
    {"ADD","IS","01"},
    {"SUB","IS","02"},
    {"MULT","IS","03"},
    {"MOVER","IS","04"},
    {"MOVEM","IS","05"},
    {"COMP","IS","06"},
    {"BC","IS","07"},
    {"DIV","IS","08"},
    {"READ","IS","09"},
    {"PRINT","IS","10"},
    {"START","AD","01"},
    {"END","AD","02"},
    {"ORIGIN","AD","03"},
    {"EQU","AD","04"},
    {"LTORG","AD","05"},
    {"DS","DL","01"},
    {"DC","DL","02"}
};

struct SYMTAB{
    int no;
    string sname,addr;
};

SYMTAB ST[10];

struct LITTAB{
    int no;
    string lname,addr;
};

LITTAB LT[10];

struct POOLTAB{
    int no;
    string lno;
};

POOLTAB PT[10];

bool presentST(string name){                                                            // check in symbol table
    for(int i = 0;i < 10;i++){
        if(ST[i].sname == name)
        	return true;
    }
    return false;
}

int getSTId(string name){											// get symbol table id
    for(int i = 0;i < 10;i++){
        if(ST[i].sname == name)
        	return i;
    }
    return -1;
}

bool presentLT(string name){
    for(int i = 0;i < 10;i++){
        if(LT[i].lname == name) return true;
    }
    return false;
}

int getLTId(string name){
    for(int i = 0;i < 10;i++){
        if(LT[i].lname == name)
        	return i;
    }
    return -1;
}

string getOPClass(string name){
    for(int i = 0;i < 18;i++){
        if(OP[i].opcode == name)
        	return OP[i].mclass;
    }
    return "-1";
}

string getOPCode(string name){
    for(int i = 0;i < 18;i++){
        if(OP[i].opcode == name)
        	return OP[i].mnemonic;
    }
    return "-1";

}

string getRegCode(string name){
    if(name == "AREG") return "1";
    if(name == "BREG") return "2";
    if(name == "CREG") return "3";
    if(name == "DREG") return "4";
    return "-1";
}

string getConditionCode(string name){
    if(name == "LT") return "1";
    if(name == "LE") return "2";
    if(name == "EQ") return "3";
    if(name == "GT") return "4";
    if(name == "GE") return "5";
    if(name == "ANY") return "6";
    return "-1";
}

int main(){

    ifstream fin;
    fin.open("input.txt");
    if(!fin.is_open()){
        cout << "Could not open input file properly" << "\n";
        return 0;
    }

    ofstream ic,lt,st,pt;
    ic.open("ic.txt");
    lt.open("littab.txt");
    st.open("symtab.txt");
    pt.open("pooltab.txt");

    string IC,lc,label,opcode,op1,op2;
    int LC = 0,scnt = 0,lcnt = 0,pcnt = 0,nlcnt = 0;

    cout << "LABEL" << "\t" << "OPCODE" << "\t" << "OP1" << "\t" << "OP2" << "\t" << "LC" << "\t" << "IC" << "\n";

    while(!fin.eof()){
        fin >> label >> opcode >> op1 >> op2;

        IC = "(" + getOPClass(opcode) + "," + getOPCode(opcode) + ")\t";

        if(opcode == "START"){
            lc = "---";
            if(op1 != "NAN"){
                LC = stoi(op1);																// LC is used to store the address given in START or ORIGIN eg, START 100, 100 is stored in LC
                IC += "(C," + op1 + ")\tNAN";
            }
            else IC += "NAN\tNAN";
        }

        if(opcode == "EQU" && label != "NAN"){
            lc = "---";
            IC += "NAN\tNAN";

            if(presentST(label)){																// entry already present in symbol table, without address
                ST[getSTId(label)].addr = ST[getSTId(op1)].addr;								// we change the address of label as given by op1
            }
            else{
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = ST[getSTId(op1)].addr;
                scnt++;
            }
        }

        else if(label != "NAN"){
            if(presentST(label)){
                ST[getSTId(label)].addr = to_string(LC);
            }
            else{
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        if(opcode == "ORIGIN")
        {
            lc = "---";
            char op;

            if(op1.find('+') != string::npos){                          // string::npos returns end of string, so op1.find('+') will return the index of '+' if it is present
                op = '+';
            }
            else op = '-';

            string token1 = "",token2 = "";
            int i;
            for(i = 0;i < op1.size();i++){
                if(op1[i] == op)
                	break;
                token1 += op1[i];
            }
            for(i = i+1;i < op1.size();i++){
                token2 += op1[i];
            }

            if(op == '+'){
                // cout << token1 << " " << ST[getSTId(token1)].addr << " " << token2 << "\n";
                LC = stoi(ST[getSTId(token1)].addr) + stoi(token2);
            }
            else {
                // cout << token1 << " " << ST[getSTId(token1)].addr << " " << token2 << "\n";
                LC = stoi(ST[getSTId(token1)].addr) - stoi(token2);
            }
            IC += "(S," + to_string(ST[getSTId(token1)].no) + ")" + op + token2 + "\tNAN";
        }

        if(opcode == "LTORG")
        {
            cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t";
            for(int i = lcnt - nlcnt;i < lcnt;i++){										// nlcnt is count of literals whose address is already assigned
                lc = to_string(LC);
                LC++;
                LT[i].addr = lc;
                IC = "(DL,01)\t(C,";
                IC += LT[i].lname[2];
                IC += ")\tNAN";

                if(i == lcnt-1)
                    cout << lc << "\t" << IC << "\n";
                else
                    cout << lc << "\t" << IC << "\n\t\t\t\t";

                ic << lc << "\t" << IC << "\n";
            }

            PT[pcnt].no = pcnt + 1;
            PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
            pcnt++;
            nlcnt = 0;
            continue;
        }

        if(opcode == "END")
        {
            lc = "---";
            IC += "NAN\tNAN";

            cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << "\n\t\t\t\t";
            ic << lc << "\t" << IC << "\n";

            if(nlcnt){
                for(int i = lcnt - nlcnt;i < lcnt;i++){
                    lc = to_string(LC);
                    LC++;
                    LT[i].addr = lc;
                    IC = "(DL,01)\t(C,";
                    IC += LT[i].lname[2];
                    IC += ")\tNAN";

            // cout << "lc: " << lc << " IC: " << IC << "\n";
                    if(i == lcnt-1)
                        cout << lc << "\t" << IC << "\n";
                    else
                        cout << lc << "\t" << IC << "\n\t\t\t\t";
                    ic << lc << "\t" << IC << "\n";
                }

                PT[pcnt].no = pcnt + 1;
                PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
                pcnt++;
                nlcnt = 0;
            }
            break;
        }

        if(opcode == "DC" || opcode == "DS"){
            lc = to_string(LC);

            if(opcode == "DC"){
                IC += "(C," + op1[1];
                IC += ")\tNAN";
                LC++;
            }
            else{
                IC += "(C," + op1 + ")\tNAN";
                LC += stoi(op1);
            }
        }

        if(opcode != "START" && opcode != "END" && opcode != "EQU" && opcode != "ORIGIN" && opcode != "LTORG" && opcode != "DC" && opcode != "DS"){
            lc = to_string(LC);
            LC++;

            if(op2 == "NAN"){
                if(op1 == "NAN"){
                    IC += "NAN\tNAN";
                }
                else{
                    if(presentST(op1)){
                        IC += "(S," + to_string(ST[getSTId(op1)].no);
                        IC += ")\tNAN";
                    }
                    else{
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op1;
                        ST[scnt].addr = lc;
                        IC += "(S," + to_string(ST[getSTId(op1)].no);
                        IC += ")\tNAN";
                    }
                }

            }

            else{                                                                  // both operands are present
                if(opcode == "BC")
                	IC += "(" + getConditionCode(op1) + ")\t";
                else
                	IC += "(" + getRegCode(op1) + ")\t";

                if(op2[0] == '='){
                    LT[lcnt].no = lcnt + 1;
                    LT[lcnt].lname = op2;
                    LT[lcnt].addr = lc;
                    lcnt++;
                    nlcnt++;
                    IC += "(L," + to_string(lcnt) + ")";
                }
                else{
                    if(presentST(op2)){
                        IC += "(S," + to_string(ST[getSTId(op2)].no);
                        IC += ")";
                    }
                    else{
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op2;
                        // ST[scnt].addr = lc;
                        IC += "(S," + to_string(ST[getSTId(op2)].no);
                        IC += ")";
                        scnt++;
                    }
                }

            }
        }

        cout << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << "\n";
        ic << lc << "\t" << IC << "\n";
    }

    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "_____SYMBOL TABLE______" << "\n";
    cout << "SNO \t SNAME \t SADDR" << "\n";
    for(int i = 0;i < scnt;i++){
        cout << ST[i].no << " \t " << ST[i].sname << " \t " << ST[i].addr << "\n";
        st << ST[i].no << " \t " << ST[i].sname << " \t " << ST[i].addr << "\n";
    }

    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "_____LITERAL TABLE______" << "\n";
    cout << "LNO \t LNAME \t LADDR" << "\n";
    for(int i = 0;i < lcnt;i++){
        cout << LT[i].no << " \t " << LT[i].lname << " \t " << LT[i].addr << "\n";
        lt << LT[i].no << " \t " << LT[i].lname << " \t " << LT[i].addr << "\n";
    }

    cout << "\n---------------------------------------------------------------------------------------\n";
    cout << "_____POOL TABLE______" << "\n";
    cout << "PNO \t LNO" << "\n";
    for(int i = 0;i < pcnt;i++){
        cout << PT[i].no << " \t " << PT[i].lno << "\n";
        pt << PT[i].no << " \t " << PT[i].lno << "\n";
    }

    cout << "\n---------------------------------------------------------------------------------------\n";

    return 0;
}
