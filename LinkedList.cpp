#include <iostream>
#include <new>
#include <string>

using namespace std;

typedef struct Sarasas
{
    string vardas;
    string pavarde;
    int amzius;
    int laikas; //kiek truks konsultacija
    Sarasas* next;
    Sarasas* back;

}SAR;

struct temp
{
    string vardas;
    string pavarde;
    int amzius;
    int laikas;
}tmp;

int iteratorius = 0; // skaiciuokle
int kons_laikas = 0; // esamas konsltaciju laikas
const int visas_galimas_laikas = 180; // max 3 valandos minutemis

SAR* Pr; //Pradzia
SAR* Pab; // Pabaiga
SAR* A; // einamas
SAR* AU; // einamo uodega
SAR* TMP; // temp
SAR* LAST; // temp

bool take_input(temp &tmp)
{
    int amzius;
    int laikas;
    cout << "Iveskite varda: " << endl;
    cin >> tmp.vardas;
    cout << "Iveskite pavarde: " << endl;
    cin >> tmp.pavarde;
    cout << "Iveskite amziu: " << endl;    
    do
    {
        cin >> amzius;
        if (cin.fail() || amzius < 0)
        {
            cout << "Klaida ivedant, iveskite teigiama skaiciu! " << endl;
            cin.clear();
            cin.ignore();
            cin >> amzius;
        }
    } while (cin.fail() || amzius < 0);
    tmp.amzius = amzius;
    cout << "Iveskite laika: " << endl;
    do
    {
        cin >> laikas;
        if (cin.fail() || laikas < 0)
        {
            cout << "Klaida ivedant, iveskite teigiama skaiciu! " << endl;
            cin.clear();
            cin.ignore();
            cin >> laikas;
        }
    } while (cin.fail() || laikas < 0);
    tmp.laikas = laikas;
    if (tmp.laikas > (visas_galimas_laikas - kons_laikas))
    {
        cout << "Seimo narys tiek laiko jums skirti negali. Daugiausiai gali skirti: " << (visas_galimas_laikas - kons_laikas) << " min." << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}

void fill_struct(SAR* A, temp tmp)
{
    A->vardas = tmp.vardas;
    A->pavarde = tmp.pavarde;
    A->amzius = tmp.amzius;
    A->laikas = tmp.laikas;    
}

bool isEmpty(SAR* Pr)
{
    return Pr == NULL;
}

SAR* I_Pabaiga(SAR* Pr, temp tmp)
{
    Pab;
    if(take_input(tmp))
    {
        if (isEmpty(Pr))
        {
            Pr = new SAR;
            A = Pr;
            fill_struct(Pr, tmp);
            A->next = NULL;
            A->back = NULL;
            Pab = A;
            kons_laikas += A->laikas;
        }
        else
        {
            A = Pr;
            while (A->next != NULL)
            {
                A = A->next;
            }
            AU = A;
            A->next = new SAR;
            A = A->next;
            fill_struct(A, tmp);
            A->next = NULL;
            A->back = AU;
            Pab = A;
            kons_laikas += A->laikas;
        }
    }
    return Pr;
}

SAR* print_current(SAR* Pr)
{
    cout << endl;
    cout << "Vardas: " << A->vardas << endl << "Pavarde: " << A->pavarde << endl << "Amzius: " << A->amzius << endl;
    cout << "Konsultacijos trukme: " << A->laikas << endl;
    cout << endl;
    return 0;
}
int count_how_many(SAR* Pr)
{
    iteratorius = 0;
    A = Pr;
    while (A != NULL)
    {
        iteratorius++;
        A = A->next;
    }
    return iteratorius;
}

void print_kas_uzleido()
{
    cout << "Jus uzleido " << A->next->vardas << " " << A->next->pavarde << endl;
    cout << "Jusu laikas yra " << ((100 - (A->laikas * 100) / A->next->laikas)) << " % trumpesnis." << endl;
}

SAR* sort_by_time(SAR* Pab)
{
    A = Pab;
    while (A != NULL)
    {
        if (A == Pr) // Jei yra tik vienas elementas
        {
            break;
        }
        else
        {
            if ((A->laikas*2) <= A->back->laikas)
            {
                if (A->back == Pr && A == Pab) // Jei yra du elementai
                {                    
                    TMP = A->back;
                    A->next = TMP;
                    A->back = NULL;
                    TMP->back = A;
                    TMP->next = NULL;
                    Pr = A;
                    Pab = TMP;
                    print_kas_uzleido();
                                        
                }
                else if (A->back != Pr && A == Pab) // Jei trys
                {
                    TMP = A->back;
                    AU = A->back->back;
                    TMP->next = NULL;
                    A->next = TMP;
                    AU->next = A;
                    TMP->back = A;
                    A->back = AU;
                    Pab = TMP;
                    print_kas_uzleido();
                }
                else if (A->back == Pr && A != Pab) // Jei A yra antras bet ne paskutinis
                {
                    TMP = A->next;
                    AU = A->back;
                    AU->next = TMP;
                    AU->back = A;
                    TMP->back = AU;
                    A->next = AU;
                    A->back = NULL;
                    Pr = A;
                    print_kas_uzleido();
                }
                else if (A != Pab && A->back != Pr) // Jeigu A viduryje
                {
                    LAST = A->next;
                    AU = A->back;
                    TMP = AU->back;
                    TMP->next = A;
                    A->back = TMP;
                    A->next = AU;
                    AU->next = LAST;
                    AU->back = A;
                    LAST->back = AU;
                    print_kas_uzleido();
                }
                else
                {
                    cout << "Something wrong happened" << endl;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    return Pab;
}

SAR* print_list(SAR* Pr)
{
    if (isEmpty(Pr))
    {
        cout << "Sarasas tuscias" << endl;
    }
    else
    {
        A = Pr;
        while (A != NULL)
        {
            print_current(Pr);
            A = A->next;
        }
    }
    return Pr;
}

SAR* cancel_time(SAR* &Pab, SAR* &Pr)
{
    if (isEmpty(Pr))
    {
        cout << "Sarasas tuscias" << endl;
    }
    else
    {
        int laikas;
        cout << "Atsaukti konsultacijas trunkancias ilgiau nei: (iveskite laika)" << endl;
        do
        {
            cin >> laikas;
            if (cin.fail() || laikas < 0)
            {
                cout << "Klaida ivedant, iveskite teigiama skaiciu! " << endl;
                cin.clear();
                cin.ignore();
                cin >> laikas;
            }
        } while (cin.fail() || laikas < 0);

        A = Pab;
        while (A != NULL)
        {
            if (isEmpty(Pr))
            {
                cout << "Sarasas tuscias" << endl;
            }
            else if (A->laikas > laikas)
            {
                if (A == Pab && A == Pr)
                {
                    Pab = NULL;
                    Pr = NULL;
                    kons_laikas -= A->laikas;
                    cout << "Atsaukta " << A->vardas << " " << A->pavarde << " konsultacija trunkanti: " << A->laikas << " min." << endl;
                    delete A;
                    break;
                }
                else if (A == Pab && A != Pr)
                {
                    TMP = A;
                    AU = A->back;
                    AU->next = NULL;
                    Pab = AU;
                    A = A->back;
                    kons_laikas -= TMP->laikas;
                    cout << "Atsaukta " << TMP->vardas << " " << TMP->pavarde << " konsultacija trunkanti: " << TMP->laikas << " min." << endl;
                    delete TMP;
                }
                else if (A != Pab)
                {
                    TMP = A;
                    AU = A->back;
                    LAST = A->next;
                    AU->next = LAST;
                    LAST->back = AU;
                    A = A->back;
                    kons_laikas -= TMP->laikas;
                    cout << "Atsaukta " << TMP->vardas << " " << TMP->pavarde << " konsultacija trunkanti: " << TMP->laikas << " min." << endl;
                    delete TMP;
                }
            }
            else
            {
                A = A->back;
            }
        }       
    }
    return Pab;    
}

SAR* cancel_all(SAR*& Pab, SAR*& Pr)
{
    A = Pab;
    while (A != NULL)
    {
        if (A->back != NULL)
        {
            cout << "Gerbiamas, " << A->vardas << " atsiprasome, bet Jusu konsultacija yra atsaukta." << endl;
            TMP = A;
            A = A->back;
            Pab = A;
            kons_laikas -= TMP->laikas;
            delete TMP;
        }
        else
        {
            cout << "Gerbiamas, " << A->vardas << " atsiprasome, bet Jusu konsultacija yra atsaukta." << endl;
            kons_laikas -= A->laikas;
            delete A;
            Pr = NULL;
            Pab = NULL;
            break;
        }
    }
    return 0;
}

SAR* perkelti_i_pradzia(SAR*& Pab, SAR*& Pr)
{
    string pavarde;
    if (isEmpty(Pr))
    {
        cout << "Sarasas tuscias" << endl;
    }
    else
    {
        cout << "Iveskite pavarde zmogaus, kuri norite perkelti i pradzia: " << endl;
        cin >> pavarde;
        A = Pab;
        if (A == Pab && A == Pr)
        {
            cout << "Sarase yra tik vienas zmogus" << endl;
        }
        else
        {
            while (A != NULL)
            {
                if (A->pavarde == pavarde && A == Pab)
                {
                    TMP = Pr;
                    AU = A->back;
                    AU->next = NULL;
                    Pab = AU;
                    TMP->back = A;
                    A->next = TMP;
                    A->back = NULL;
                    Pr = A;
                    break;
                }
                else if (A->pavarde == pavarde && A != Pab)
                {
                    LAST = A->next;
                    AU = A->back;
                    TMP = Pr;
                    AU->next = LAST;
                    LAST->back = AU;
                    TMP->back = A;
                    A->back = NULL;
                    A->next = TMP;
                    Pr = A;
                    break;
                }
                else if (A->pavarde != pavarde && A != NULL)
                {
                    A = A->back;
                }
                else
                {
                    cout << "Zmogus tokia pavarde nerastas" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}

int meniu()
{
    int pasirinkimas;
    cout << "[1] Naujo piliecio registravimas konsultacijai" << endl;
    cout << "[2] Konsultaciju saraso isvedimas. (Pateikiama ir suvestine apie trukme ir skaiciu" << endl;
    cout << "[3] Atsaukti konsultacija ilgesnes nei nurodymas" << endl;
    cout << "[4] Atsaukti visas konsultacijas" << endl;
    cout << "[5] Perkelti i eiles pradzia nurodyta pilieti" << endl;
    cout << "[6] Baigti darba" << endl;
    do
    {
        cin >> pasirinkimas;
        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 6)
        {
            cout << "Klaida ivedant, iveskite skaiciuo nuo 1 iki 6!" << endl;
            cin.clear();
            cin.ignore();
            cin >> pasirinkimas;
        }
    } while (cin.fail() || pasirinkimas < 1 || pasirinkimas > 6);
    return pasirinkimas;
}
int main()
{    
    Pr = NULL;
    Pab = NULL;
    bool on = true;
    while (on)
    {
        system("cls");
        switch (meniu())
        {
        case 1:
            Pr = I_Pabaiga(Pr, tmp);
            Pab = sort_by_time(Pab); 
            system("pause");
            break;
        case 2:
            if (isEmpty(Pr))
            {
                cout << "Sarasas tuscias" << endl;
            }
            else
            {
                Pr = print_list(Pr);
                cout << "Bendras konsltaciju skaicius: " << count_how_many(Pr) << endl;
                cout << "Bendras konsultaciju laikas: " << kons_laikas << " min." << endl;
            }            
            system("pause");
            break;
        case 3:
            cancel_time(Pab, Pr);
            system("pause");
            break;
        case 4:
            cancel_all(Pab, Pr);
            system("pause");
            break;
        case 5:
            perkelti_i_pradzia(Pab, Pr);
            system("pause");
            break;
        case 6:
            on = false;
            break;
        default:
            break;
        }
    }    
}