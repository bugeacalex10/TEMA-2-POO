#ifndef PARIURI_H
#define PARIURI_H


#include <vector>
#include <string>
#include <map>

enum TipActiune{
    echipa,
    fix,
    peste,
    sub
};
class Actiune{
    public:
        TipActiune tip;
        std::string rezultat;
        double cota;
        std::string alegere;
};
class PariuMeci{
    public:
        std::vector<Actiune> vect_actiuni;
};
class Pariuri {
    protected:
        double miza;
        std::vector<PariuMeci> vect_pariuri;
    public:
        Pariuri(double miza = 0.0) : miza(miza) {}

        double get_miza() const { return miza; }
        std::vector<PariuMeci> get_vect_pariuri() const { return vect_pariuri; }
        void adaugaPariuMeci(const PariuMeci& pm)
        {
            vect_pariuri.push_back(pm);
        }

        virtual double calculeaza_castig() const = 0;
        virtual void afisare(std::ostream& out) const = 0;
        virtual Pariuri* clone() const = 0;

        virtual ~Pariuri() = default;

};
class PariuSimplu : public Pariuri {
    public:
        PariuSimplu(double miza = 0.0) : Pariuri(miza) {}

        double calculeaza_castig() const override;
        void afisare(std::ostream& out) const override;
        Pariuri* clone() const override;
};
class PariuMultiplu : public Pariuri {
    public:
        PariuMultiplu(double miza = 0.0) : Pariuri(miza) {}

        double calculeaza_castig() const override;
        void afisare(std::ostream& out) const override;
        Pariuri* clone() const override;
};
class PariuSistem : public Pariuri {
    private:
        int k;
    public: 
        PariuSistem(double miza = 0.0, int k = 0) : Pariuri(miza), k(k) {}

        int get_k() const { return k; }

        double calculeaza_castig() const override;
        void afisare(std::ostream& out) const override;
        Pariuri* clone() const override;
};

#endif