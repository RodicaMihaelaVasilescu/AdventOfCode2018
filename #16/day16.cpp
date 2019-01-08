#include <bits/stdc++.h>
using namespace std;

struct Register
{
    int opcode = 0;
    vector<int> reg{ 0, 0, 0, 0};
};

vector<Register> before;
vector<Register> instruction;
vector<Register> after;

Register addr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] + a.reg[b.reg[1]];      ///rC = rA + rB
    return a;
}
Register addi(Register a, Register b)
{

    a.reg[b.reg[2]] = a.reg[b.reg[0]] + b.reg[1];            ///rC = rA + vB
    return a;
}
Register mulr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] * a.reg[b.reg[1]];     ///rC = rA * rB
    return a;
}
Register muli(Register a, Register b){

    a.reg[b.reg[2]] = a.reg[b.reg[0]] * b.reg[1];           ///rC = rA * vB
    return a;
}
Register banr(Register a, Register b)
{

    a.reg[b.reg[2]] = a.reg[b.reg[0]] & a.reg[b.reg[1]];    ///rC = rA & rB
    return a;
}
Register bani(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] & b.reg[1];            ///rC = rA & vB
    return a;
}
Register borr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] | a.reg[b.reg[1]];    ///rC = rA | rB
    return a;
}
Register bori(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] | b.reg[1];           ///rC = rA | vB
    return a;
}
Register setr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]];                      ///rC = rA
    return a;
}
Register seti(Register a, Register b)
{
    a.reg[b.reg[2]] = b.reg[0];                             ///rC = vA
    return a;
}
Register gtir(Register a, Register b)
{
    a.reg[b.reg[2]] = b.reg[0] > a.reg[b.reg[1]];           ///rC = vA > rB
    return a;
}
Register gtri(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] > b.reg[1];           ///rC = rA > vB
    return a;
}
Register gtrr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] > a.reg[b.reg[1]];   ///rC = rA > rB
    return a;
}
Register eqir(Register a, Register b)
{
    a.reg[b.reg[2]] = b.reg[0] == a.reg[b.reg[1]];         ///rC = vA == rB
    return a;
}
Register eqri(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] == b.reg[1];         ///rC = rA == vB
    return a;
}
Register eqrr(Register a, Register b)
{
    a.reg[b.reg[2]] = a.reg[b.reg[0]] == a.reg[b.reg[1]];  ///rC = rA == rB
    return a;
}

int main()
{
    ifstream cin("in.txt");
    ofstream cout("out.txt");
    string inputLine;
    int noOfEmptyLines = 0;

    while(getline(cin, inputLine)){

        if(noOfEmptyLines >= 2)
        {
            ///the rest of the input belongs to second part
            break;
        }

        if (inputLine == "")
        {
            noOfEmptyLines++;
            continue;
        }

        noOfEmptyLines = 0;

        istringstream iss(inputLine);
        vector<string> s((istream_iterator<string>(iss)), istream_iterator<string>());

        Register x;
        if(s[0] == "Before:")
        {
            x.reg = {inputLine[9] - '0', inputLine[12] - '0', inputLine[15] - '0', inputLine[18] - '0' };
            before.push_back(x);

        }
        else if(s[0] == "After:")
        {
            x.reg = {inputLine[9] - '0', inputLine[12] - '0', inputLine[15] - '0', inputLine[18] - '0' };
            after.push_back(x);
        }
        else
        {
            x.reg = {stoi(s[1]), stoi(s[2]), stoi(s[3])};
            instruction.push_back(x);
        }
    }

    int answerPart1 = 0;
    for(int i = 0; i < before.size(); i++)
    {
        Register r;
        int nr = 0;

        r = addr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after [i].reg[2] && r.reg[3] == after[i].reg[3]? nr++ : 0;

        r = addi(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = mulr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = muli(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = banr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = bani(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = borr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = bori(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = setr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = seti(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = gtir(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = gtri(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = gtrr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = eqir(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = eqri(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        r = eqrr(before[i], instruction[i]);
        r.reg[0] == after[i].reg[0] && r.reg[1] == after[i].reg[1] && r.reg[2] == after[i].reg[2] && r.reg[3] == after[i].reg[3] ? nr++ : 0;

        nr < 3 ? : answerPart1++;
    }
    cout <<"Part1: " << answerPart1 << endl;

    ///Part2
    instruction.clear();
    while(getline(cin, inputLine))
    {
        if (inputLine == "")
        {
            continue;
        }

        istringstream iss(inputLine);
        vector<string> s((istream_iterator<string>(iss)), istream_iterator<string>());

        Register x;
        x.opcode = stoi(s[0]);
        x.reg = {stoi(s[1]), stoi(s[2]), stoi(s[3])};
        instruction.push_back(x);
    }


    /** Obs.

    I used another program to generate a map based on my input,
    therefore the part2 of this solution is based in my own input

    map <int, string> opcodeInstruction;
    opcodeInstruction[0] = "banr";
    opcodeInstruction[1] = "addr";
    opcodeInstruction[2] = "eqri";
    opcodeInstruction[3] = "setr";
    opcodeInstruction[4] = "gtrr";
    opcodeInstruction[5] = "bori";
    opcodeInstruction[6] = "gtir";
    opcodeInstruction[7] = "seti";
    opcodeInstruction[8] = "borr";
    opcodeInstruction[9] = "bani";
    opcodeInstruction[10] = "eqir";
    opcodeInstruction[11] = "eqrr";
    opcodeInstruction[12] = "gtri";
    opcodeInstruction[13] = "addi";
    opcodeInstruction[14] = "muli";
    opcodeInstruction[15] = "mulr";

    **/

    Register r;
    for(int i = 0; i < instruction.size(); i++)
    {
       if(instruction[i].opcode == 0)
       {
           r = banr(r, instruction[i]);
       }
       if(instruction[i].opcode == 1)
       {
           r = addr(r, instruction[i]);
       }
       if(instruction[i].opcode == 2)
       {
           r = eqri(r, instruction[i]);
       }
       if(instruction[i].opcode == 3)
       {
           r = setr(r, instruction[i]);
       }
        if(instruction[i].opcode == 4)
       {
           r = gtrr(r, instruction[i]);
       }
       if(instruction[i].opcode == 5)
       {
           r = bori(r, instruction[i]);
       }
       if(instruction[i].opcode == 6)
       {
           r = gtir(r, instruction[i]);
       }
       if(instruction[i].opcode == 7)
       {
           r = seti(r, instruction[i]);
       }
        if(instruction[i].opcode == 8)
       {
           r = borr(r, instruction[i]);
       }
       if(instruction[i].opcode == 9)
       {
           r = bani(r, instruction[i]);
       }
       if(instruction[i].opcode == 10)
       {
           r = eqir(r, instruction[i]);
       }
       if(instruction[i].opcode == 11)
       {
           r = eqrr(r, instruction[i]);
       }
        if(instruction[i].opcode == 12)
       {
           r = gtri(r, instruction[i]);
       }
       if(instruction[i].opcode == 13)
       {
           r = addi(r, instruction[i]);
       }
       if(instruction[i].opcode == 14)
       {
           r = muli(r, instruction[i]);
       }
       if(instruction[i].opcode == 15)
       {
           r = mulr(r, instruction[i]);
       }
    }

    cout <<"Part2: " << r.reg[0];
    return 0;
}
