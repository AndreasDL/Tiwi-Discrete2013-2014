#include <iostream>
using
std::cout;

using std::cin;

using std::endl;

using std::cerr;

#include <fstream>
using std::ostream;

using std::istream;

using std::ifstream;

#include <string>
using std::string;

#include <cmath>
#include <iomanip>
using std::setw;

#include <vector>
using std::vector;


#include "grootgetal.h"	
#include "hulpfuncties.h"	
#include "rekenmachine.h"

#ifndef _RESIDUNOTATIE
#define _RESIDUNOTATIE	

class ResiduNotatie {
private:
    static
    vector < int >
    moduli;

    vector < int >
    residus;


    static
    vector < int >
    initialiseer_moduli();

    void
    initialiseer_residus(const GrootGetal & a);


public:

    ResiduNotatie(const GrootGetal & a) {

        initialiseer_moduli();

        initialiseer_residus(a);

    }

    ResiduNotatie() {

        initialiseer_moduli();

        GrootGetal g;

        initialiseer_residus(g);

    }

    ResiduNotatie(const string & a) {

        initialiseer_moduli();

        GrootGetal g(a);

        initialiseer_residus(g);

    }

    ResiduNotatie operator+(const ResiduNotatie & ander) const;

    ResiduNotatie operator*(const ResiduNotatie & ander) const;

    ResiduNotatie operator*(int) const;


    GrootGetal groot_getal()const;

    friend ostream & operator<<(ostream & uit, const ResiduNotatie & rr) {

        // offset is standaard 7
        // for(int i=.waarde.size(); i<7; i++) uit<<" ";
        uit << endl;

        for (int i = 0; i < rr.moduli.size(); i++) {

            uit << setw(4) << rr.moduli[i] << "  ";

        }
        uit << endl;

        for (int i = 0; i < rr.residus.size(); i++) {

            uit << setw(4) << rr.residus[i] << "  ";

        }
        uit << endl << " == " << rr.groot_getal().
                getalbeeld() << endl << endl;

        return uit; // BELANGRIJK !!
    }

};




vector < int >
        ResiduNotatie::moduli = initialiseer_moduli();

vector < int >
ResiduNotatie::initialiseer_moduli() {

    vector < int >mod;


    string GRENS = "100000000000";

    GrootGetal g(GRENS);

    int GROOTSTE_MODULUS = 49;


    //cout<<endl<<"'vector<int> ResiduNotatie::initialiseer_moduli()' nog niet geimplementeerd."<<endl;

    // vul de vector met moduli verder aan; start bij 49 en voeg telkens
    // een kleiner getal toe (dat onderling ondeelbaar is met alle vorige),
    // tot het product van al deze getallen boven de GRENS uitsteekt.

    GrootGetal product("49");

    int huidig = GROOTSTE_MODULUS;


    while (product.is_kleiner_dan_abs(g) && huidig > 0) {

        huidig--;

        mod.push_back(huidig);

        if (!onderling_ondeelbaar(mod)) {

            mod.pop_back();

        }


    }


    return mod;

}

void
ResiduNotatie::initialiseer_residus(const GrootGetal & a) {

    //cout<<endl<<"'void ResiduNotatie::initialiseer_residus(const GrootGetal & a)' nog niet geimplementeerd."<<endl;

    for (vector < int >::iterator it = moduli.begin(); it != moduli.end();
            it++) {

        residus.push_back(a % *it);

    }

}

GrootGetal ResiduNotatie::groot_getal() const {

    GrootGetal g("0");

    GrootGetal grens(1);

    for (int i = 0; i < residus.size(); i++) {

        int
        getal = residus[i];

        //cout<<getal<<" * ";
        GrootGetal tssn(residus[i]);

        for (int j = 0; j < moduli.size(); j++) {

            if (i != j) {

                getal = (getal * moduli[j]) % moduli[i];

                tssn = tssn * moduli[j];

                //cout<<moduli[j]<<" * ";
            }

        }

        //cout<<endl;
        //cout<<"tussen:"<<tssn<<endl;
        int
        l;

        //cout<<"a="<< tssn.klein_getal() << " c= "<<residus[i] <<" n = "<<moduli[i] << endl;
        los_congruentie_op(getal, residus[i], moduli[i], l);

        //cout<<"l= "<<l<<endl;
        g = g + tssn * l;
        grens = grens * moduli[i];

    }
    //g.verwijder_leidende_nullen();

    return g % grens;
}

ResiduNotatie ResiduNotatie::operator+(const ResiduNotatie & ander) const {

    //cout<<endl<<"'ResiduNotatie ResiduNotatie::operator+(ResiduNotatie)' nog niet geimplementeerd."<<endl;

    GrootGetal g1 = groot_getal();

    GrootGetal g2 = ander.groot_getal() + g1;

    return ResiduNotatie(g2);

}

ResiduNotatie ResiduNotatie::operator*(const ResiduNotatie & ander) const {

    //cout<<endl<<"'ResiduNotatie ResiduNotatie::operator*(ResiduNotatie)' nog niet geimplementeerd."<<endl;
    GrootGetal g1 = groot_getal();

    GrootGetal g2 = ander.groot_getal() * g1;

    return ResiduNotatie(g2);

    return ResiduNotatie();

}

ResiduNotatie ResiduNotatie::operator*(int x) const {

    GrootGetal g1 = groot_getal();

    return ResiduNotatie(g1 * x);

}




// vul zelf nog operator- en operator% aan

#endif	/* 
 */
