#define MAX_RAND 1000
#define TEST_CASE 5
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "XYPoly.h"
using std::ofstream;

string generateRandomPoly();

struct TimeCheck{
    string method = "";
    clock_t numTicks;
};

int main(){
    ofstream fout;
    char xyListName[TEST_CASE] = {'P','Q','R','S','T'};
    XYPoly *xyPolyList[TEST_CASE];
    XYPoly *copyPoly;
    xyPolyList[0] = new XYPoly("5x4y3 - 2x3y4 + xy - 6");
    xyPolyList[1] = new XYPoly("-8x3y5 + 4x2y2 - x + y + 1");
    xyPolyList[2] = new XYPoly("8x3 - 6x2y + 2 - 4x");
    xyPolyList[3] = new XYPoly("3xy - 5y5 + 3y3 - y");
    xyPolyList[4] = new XYPoly(generateRandomPoly());

    fout.open("Time Tests.txt", std::ios::app);

    TimeCheck outputs[TEST_CASE];
    cout << "\t\t\tTest Polynomials Outputs\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        cout << xyListName[i] << " = ";

        clock_t start = clock();
            xyPolyList[i]->output();

        outputs[i].numTicks = clock() - start;
            outputs[i].method += xyListName[i];
            outputs[i].method += " output";

    }

    TimeCheck deepCopies[TEST_CASE];
    cout << "\n\n\t\t\tDeep Copy Polynomial Test\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
        copyPoly = new XYPoly(xyPolyList[i]);
        deepCopies[i].numTicks = clock() - start;
            deepCopies[i].method += "Deep Copy of ";
            deepCopies[i].method += xyListName[i];

        cout << "Copied Polynomial of " << xyListName[i] << " is ";
        copyPoly->output();
    }

    TimeCheck equalities[TEST_CASE][TEST_CASE];
    cout << "\n\n\t\t\tPolynomial Equality Checker\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        for(int j = 0; j < TEST_CASE; j++){
            clock_t start = clock();
            bool same = xyPolyList[i]->equalTo(xyPolyList[j]);
            equalities[i][j].numTicks = clock() - start;
                equalities[i][j].method += "Equality between ";
                equalities[i][j].method += xyListName[i];
                equalities[i][j].method += " and ";
                equalities[i][j].method += xyListName[j];
            cout << xyListName[i] << " is " << (same ? "equal to ": "not equal to ") << xyListName[j] << endl << endl;
        }
    }

    TimeCheck scalars[TEST_CASE];
    cout << "\n\t\t\tPolynomial Scalar Multiplication (by 5)\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
            XYPoly *answer = xyPolyList[i]->scalarMultiply(5);
        scalars[i].numTicks = clock() - start;
            scalars[i].method += "Scalar Multiplication by 5 of ";
            scalars[i].method += xyListName[i];

        cout << xyListName[i] << " scaled by 5 (* 5) = ";
        answer->output();
        cout << endl;
    }

    TimeCheck add[TEST_CASE][TEST_CASE];
    cout << "\n\n\t\t\tPolynomial Addition\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        for(int j = 0; j < TEST_CASE; j++){
            clock_t start = clock();
                XYPoly *answer = xyPolyList[i]->add(xyPolyList[j]);
            add[i][j].numTicks = clock() - start;
                add[i][j].method += xyListName[i];
                add[i][j].method += " + ";
                add[i][j].method += xyListName[j];

            cout << xyListName[i] << " + " << xyListName[j] << " = ";
            answer->output();
            cout <<endl;
        }
    }

    TimeCheck sub[TEST_CASE][TEST_CASE];
    cout << "\n\n\t\t\tPolynomial Subtraction\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        for(int j = 0; j < TEST_CASE; j++){
            clock_t start = clock();
                XYPoly *answer = xyPolyList[i]->subtract(xyPolyList[j]);
            sub[i][j].numTicks = clock() - start;
                sub[i][j].method += xyListName[i];
                sub[i][j].method += " - ";
                sub[i][j].method += xyListName[j];

            cout << xyListName[i] << " - " << xyListName[j] << " = ";
            answer->output();
            cout <<endl;
        }
    }

    TimeCheck mul[TEST_CASE][TEST_CASE];
    cout << "\n\n\t\t\tPolynomial Multiplication\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        for(int j = 0; j < TEST_CASE; j++){
            clock_t start = clock();
                XYPoly *answer = xyPolyList[i]->multiply(xyPolyList[j]);
            mul[i][j].numTicks = clock() - start;
                mul[i][j].method += xyListName[i];
                mul[i][j].method += " * ";
                mul[i][j].method += xyListName[j];

            cout << xyListName[i] << " * " << xyListName[j] << " = ";
            answer->output();
            cout <<endl;
        }
    }

    int powers[4] = {5, 10, 20, 30};
    TimeCheck power[TEST_CASE-1][TEST_CASE-1];

    cout << "\n\n\t\t\tPolynomial 5th Power Evaluation\n\n";
    for(int i = 0; i < TEST_CASE-1; i++){
        clock_t start = clock();
            XYPoly *answer = xyPolyList[i]->power(5);
        power[0][i].numTicks = clock() - start;
            power[0][i].method +=  xyListName[i];
            power[0][i].method += " ^ 5";

        cout << xyListName[i] << " ^ 5 = ";
        answer->output();
        cout <<endl;
    }

    cout << "\n\n\t\t\tPolynomial 10th Power Evaluation\n\n";
    for(int i = 0; i < TEST_CASE-1; i++){
        clock_t start = clock();
            XYPoly *answer = xyPolyList[i]->power(10);
        power[1][i].numTicks = clock() - start;
            power[1][i].method +=  xyListName[i];
            power[1][i].method += " ^ 10";

        cout << xyListName[i] << " ^ 10 executed\n\n";
    }

    cout << "\n\n\t\t\tPolynomial 20th Power Evaluation\n\n";
    for(int i = 0; i < TEST_CASE-1; i++){
        clock_t start = clock();
            XYPoly *answer = xyPolyList[i]->power(20);
        power[2][i].numTicks = clock() - start;
            power[2][i].method +=  xyListName[i];
            power[2][i].method += " ^ 20";

        cout << xyListName[i] << " ^ 20 executed\n\n";
    }

    cout << "\n\n\t\t\tPolynomial 30th Power Evaluation\n\n";
    for(int i = 0; i < TEST_CASE-1; i++){
        clock_t start = clock();
            XYPoly *answer = xyPolyList[i]->power(30);
        power[3][i].numTicks = clock() - start;
            power[3][i].method +=  xyListName[i];
            power[3][i].method += " ^ 30";

        cout << xyListName[i] << " ^ 30 executed\n\n";
    }

    string evals[4] = {"(1,1)", "(2,2)", "(-4,3)", "(-2,-1)"};
    TimeCheck eval[4][TEST_CASE];

    cout << "\n\n\t\t\tPolynomial Evaluation for (1,1)\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
            long answer = xyPolyList[i]->evaluate(1,1);
        eval[0][i].numTicks = clock() - start;
            eval[0][i].method += "Evaluation for ";
            eval[0][i].method += xyListName[i];

        cout << xyListName[i] << " (1,1) = " << answer;
        cout << endl << endl;
    }

    cout << "\n\n\t\t\tPolynomial Evaluation for (2,2)\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
            long answer = xyPolyList[i]->evaluate(2,2);
        eval[1][i].numTicks = clock() - start;
            eval[1][i].method += "Evaluation for ";
            eval[1][i].method += xyListName[i];

        cout << xyListName[i] << " (2,2) = " << answer;
        cout << endl << endl;
    }

    cout << "\n\n\t\t\tPolynomial Evaluation for (-4,3)\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
            long answer = xyPolyList[i]->evaluate(-4,3);
        eval[2][i].numTicks = clock() - start;
            eval[2][i].method += "Evaluation for ";
            eval[2][i].method += xyListName[i];

        cout << xyListName[i] << " (-4,3) = " << answer;
        cout << endl << endl;
    }

    cout << "\n\n\t\t\tPolynomial Evaluation for (-2,-1)\n\n";
    for(int i = 0; i < TEST_CASE; i++){
        clock_t start = clock();
            long answer = xyPolyList[i]->evaluate(-2,-1);
        eval[3][i].numTicks = clock() - start;
            eval[3][i].method += "Evaluation for ";
            eval[3][i].method += xyListName[i];

        cout << xyListName[i] << " (-2,-1) = " << answer;
        cout << endl << endl;
    }

    fout << "Time Test Cases for ArrayPolyList Implementation" << endl << endl;
    for(int i = 0; i < TEST_CASE; i++)
        fout << outputs[i].method << "\t\t" << outputs[i].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        fout << deepCopies[i].method << "\t\t" << deepCopies[i].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        for(int j = 0; j < TEST_CASE; j++)
            fout << equalities[i][j].method << "\t\t" << equalities[i][j].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        fout << scalars[i].method << "\t\t" << scalars[i].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        for(int j = 0; j < TEST_CASE; j++)
            fout << add[i][j].method << "\t\t" << add[i][j].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        for(int j = 0; j < TEST_CASE; j++)
            fout << sub[i][j].method << "\t\t" << sub[i][j].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < TEST_CASE; i++)
        for(int j = 0; j < TEST_CASE; j++)
            fout << mul[i][j].method << "\t\t" << mul[i][j].numTicks << " ticks" << endl;
    fout << endl << endl;

    for(int i = 0; i < 4; i++){
        fout << "Polynomial Power for " << powers[i] << endl << endl;
        for(int j = 0; j < TEST_CASE-1; j++){
            fout << power[i][j].method << "\t\t" << power[i][j].numTicks << " ticks" << endl;
        }
    }
    fout << endl << endl;

    for(int i = 0; i < 4; i++){
        fout << "Polynomial Evaluation for " << evals[i] << endl << endl;
        for(int j = 0; j < TEST_CASE; j++){
            fout << eval[i][j].method << "\t\t" << eval[i][j].numTicks << " ticks" << endl;
        }
        fout << endl;
    }
    fout << endl << endl;
    fout.close();
    return 0;
}

string generateRandomPoly(){
    int c, i, j;
    string rtnPoly = "";
    char buff[255];

    // Generates a c value between [-25, 25]
    c = 2 * (rand() % 26) - 25;
    for (int k = 0; k < MAX_RAND; k++){
        i = rand() % 26;
        j = rand() % 26;

        if(i == 0 && j == 0){
            sprintf(buff, "%d", c);
            rtnPoly += buff;

        } else if(i == 0){
            sprintf(buff, "%d", c);
            rtnPoly += buff; rtnPoly += 'y';
            sprintf(buff, "%d", j);
            rtnPoly += buff;

        } else if (j == 0){
            sprintf(buff, "%d", c);
            rtnPoly += buff; rtnPoly += 'x';
            sprintf(buff, "%d", i);
            rtnPoly += buff;

        } else {
            sprintf(buff, "%d", c);
            rtnPoly += buff; rtnPoly += 'x';
            sprintf(buff, "%d", i);
            rtnPoly += buff; rtnPoly += 'y';
            sprintf(buff, "%d", j);
            rtnPoly += buff;
        }

        if(k+1 < MAX_RAND){
            c = 2 * (rand() % 26) - 25;
            if(c >= 0)
                rtnPoly += " + ";
            else{
                rtnPoly += " - ";
                c = abs(c);
            }
        }
    }

    return rtnPoly;
}
