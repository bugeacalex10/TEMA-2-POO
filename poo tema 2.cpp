#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include "pariuri.h"
#include "rezultate.h"

std::ifstream fin("date.in");

void citire_meciuri(std::ifstream& fin,
std::map<int, std::pair<std::string, std::string>>& meciuri, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int, double>& vect_echipa2)
{
    int index = 1;
    std::string cuvant;

    while (fin >> cuvant)
    {
        if (cuvant == "rezultate")
            break;

        std::string echipa1 = cuvant;
        std::string echipa2;
        double cota_echipa1, cota_egal, cota_echipa2;

        fin >> echipa2 >> cota_echipa1 >> cota_egal >> cota_echipa2;

        meciuri[index] = {echipa1, echipa2};
        vect_echipa1[index] = cota_echipa1;
        vect_egal[index] = cota_egal;
        vect_echipa2[index] = cota_echipa2;
        index++;
    }
}

void citire_rezultate(std::ifstream& fin, std::vector<Rezultate>& rezultate, 
std::map<int, std::pair<std::string, std::string>>& meciuri)
{
    int index = 1;
    while (fin)
    {
        std::string rezultat_meci;
        int nr_faulturi;
        int nr_cartonase_galbene;
        int nr_cartonase_rosii;
        int nr_cornere;
        fin >> rezultat_meci >> nr_faulturi >> nr_cartonase_galbene >> nr_cartonase_rosii >> nr_cornere;
        Rezultate rezultat(index, rezultat_meci, nr_faulturi, nr_cartonase_galbene, nr_cartonase_rosii, nr_cornere);
        rezultate.push_back(rezultat);
        index++;
    }
}

Pariuri* creeazaPariuSimplu(double &miza, std::map<int, std::pair<std::string, std::string>>& meciuri,
std::vector<std::string> &actiuni, std::vector<Rezultate> &rezultate, std::map<int, double>& vect_echipa1,
std::map<int, double>& vect_egal, std::map<int, double>& vect_echipa2) 
{
    std::cout << "meciurile si cotele disponibile sunt: " << std::endl;
    for(const auto& meci : meciuri)
    {
        std::cout << meci.first << ": " << meci.second.first << " vs " << meci.second.second << std::endl;

    }
    std::cout << "introdu id-ul meciului pe care vrei sa pariezi: ";
    int id_meci;
    std::cin >> id_meci;

    for(const auto& meci : meciuri)
    {
        if(meci.first == id_meci)
        {
            std::cout << "alege una dintre urmatoarele actiuni: " << std::endl;
            for(const auto& actiune : actiuni)
            {
                std::cout << actiune << std::endl;
            }
            std::string actiune_aleasa;
            std::cin >> actiune_aleasa;

            if(actiune_aleasa == "rezultat meci")
            {
                std::cout << "alege rezultatul meciului: " << std::endl;
                std::cout << "1. " << meci.second.first << " castiga" << std::endl;
                std::cout << "2. " << "egalitate" << std::endl;
                std::cout << "3. " << meci.second.second << " castiga" << std::endl;

                std::string alegere;
                std::cin >> alegere;

                PariuSimplu* pariu = new PariuSimplu(miza);
                Actiune actiune;
                actiune.tip = echipa;
                actiune.rezultat = rezultate[id_meci - 1].get_rezultat_meci();
                if(alegere == meci.second.first)
                {
                    actiune.cota = vect_echipa1[id_meci];
                }
                else if (alegere == "egalitate")
                {
                    actiune.cota = vect_egal[id_meci];
                }
                else if(alegere == meci.second.second)
                {
                    actiune.cota = vect_echipa2[id_meci];
                }
                actiune.alegere = alegere;

                PariuMeci pariu_meci;
                pariu_meci.vect_actiuni.push_back(actiune);

                pariu->adaugaPariuMeci(pariu_meci);
                
                return pariu;
            }
            else if (actiune_aleasa == "numar faulturi")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;

                std::cout << "introdu numarul de faulturi: ";
                int numar_faulturi;
                std::cin >> numar_faulturi;

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 1 + (numar_faulturi - rezultate[id_meci - 1].get_nr_faulturi()) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_faulturi() - numar_faulturi) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_faulturi());
                    actiune.alegere = std::to_string(numar_faulturi);
                    actiune.cota = 2.5;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cartonase galbene")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;

                std::cout << "introdu numarul de cartonase galbene: ";
                int numar_cartonase_galbene;
                std::cin >> numar_cartonase_galbene;

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 1 + (numar_cartonase_galbene - rezultate[id_meci - 1].get_nr_cartonase_galbene()) * 0.3;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cartonase_galbene() - numar_cartonase_galbene) * 0.3;
                   
                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_galbene());
                    actiune.alegere = std::to_string(numar_cartonase_galbene);
                    actiune.cota = 3.0;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cartonase rosii")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;

                std::cout << "introdu numarul de cartonase rosii: ";
                int numar_cartonase_rosii;
                std::cin >> numar_cartonase_rosii;

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 1 + (numar_cartonase_rosii - rezultate[id_meci - 1].get_nr_cartonase_rosii()) * 0.5;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cartonase_rosii() - numar_cartonase_rosii) * 0.5;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cartonase_rosii());
                    actiune.alegere = std::to_string(numar_cartonase_rosii);
                    actiune.cota = 4.0;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
            else if (actiune_aleasa == "numar cornere")
            {
                std::cout << "alege metoda de pariere: " << std::endl;
                std::cout << "1. peste" << std::endl;
                std::cout << "2. sub" << std::endl;
                std::cout << "3. fix" << std::endl;
                std::cout << "introdu alegerea ta: ";
                std::string alegere;
                std::cin >> alegere;

                std::cout << "introdu numarul de cornere: ";
                int numar_cornere;
                std::cin >> numar_cornere;

                PariuSimplu* pariu = new PariuSimplu(miza);
                if (alegere == "peste")
                {
                    Actiune actiune;
                    actiune.tip = peste;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 1 + (numar_cornere - rezultate[id_meci - 1].get_nr_cornere()) * 0.25;

                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "sub")
                {
                    Actiune actiune;
                    actiune.tip = sub;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 1 + (rezultate[id_meci - 1].get_nr_cornere() - numar_cornere) * 0.25;
                   
                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
                else if (alegere == "fix")
                {
                    Actiune actiune;
                    actiune.tip = fix;
                    actiune.rezultat = std::to_string(rezultate[id_meci - 1].get_nr_cornere());
                    actiune.alegere = std::to_string(numar_cornere);
                    actiune.cota = 2.5;
                    
                    PariuMeci pariu_meci;
                    pariu_meci.vect_actiuni.push_back(actiune);
                    pariu->adaugaPariuMeci(pariu_meci);
                    return pariu;
                }
            }
        }
    }


}

int main()
{
    std::vector<std::string> actiuni = {"rezultat meci", "numar faulturi", "numar cartonase galbene",
    "numar cartonase rosii", "numar cornere"};
    
    std::map<int, double> vect_echipa1;
    std::map<int, double> vect_egal;
    std::map<int, double> vect_echipa2;

    std::map<int, std::pair<std::string, std::string>> meciuri;
    std::string linie;
    fin >> linie;
    if(linie == "meciuri")
    {   
        citire_meciuri(fin, meciuri, vect_echipa1, vect_egal, vect_echipa2);
    }
    std::vector<Rezultate> rezultate;
    std::cout << "introdu numele prenumele si varsta: ";
    std::string nume, prenume;
    int varsta;

    std::cin >> nume >> prenume >> varsta;

    if(varsta < 18)
    {
        std::cout << "nu poti paria, mars inapoi la scoala" << std::endl;
        return 0;
    }

    std::cout << "introdu suma pe care vrei sa o pariezi: ";
    double suma;

    std::cin >> suma;

    std::cout << "introdu numarul de pariuri pe care vrei sa le faci: ";
    int nr_pariuri;

    std::cin >> nr_pariuri;

    std::vector<Pariuri*> vect_pariuri;

    for(int ind = 0; ind < nr_pariuri; ind++)
    {
        std::cout << "introdu tipul pariului (simplu, multiplu sau sistem): ";
        std::string tip_pariu;

        std::cin >> tip_pariu;

        std::cout << "introdu suma pe care vrei sa o pui pe acest pariu: ";
        double miza;
        std::cin >> miza;

        if(miza > suma)
        {
            std::cout << "nu mai ai bani, saracule" << std::endl;
            break;
        }

        if(tip_pariu == "simplu")
        {
            Pariuri* pariu = creeazaPariuSimplu(miza, meciuri, actiuni, rezultate, vect_echipa1, vect_egal, vect_echipa2);
            vect_pariuri.push_back(pariu);
            suma -= miza;
        }
        else if(tip_pariu == "multiplu")
        {
            PariuMultiplu pariu(miza);
            vect_pariuri.push_back(new PariuMultiplu(pariu));
            suma -= miza;
        }
        else if(tip_pariu == "sistem")
        {
            std::cout << "introdu numarul minim de pariuri care trebuie sa iasa: ";
            int k;
            std::cin >> k;
            PariuSistem pariu(miza, k);
            vect_pariuri.push_back(new PariuSistem(pariu));
            suma -= miza;
        }
        else
        {
            std::cout << "tip de pariu invalid, incearca din nou" << std::endl;
            ind--;
        }
    }
}