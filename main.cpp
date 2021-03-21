#include <iostream>
#include <fstream>

#define NUMERO_MASSIMO_CONTATTI 200
#define PERCORSO_FILE "Rubrica.dat"

using namespace std;

struct Contatto
{
    int codiceContatto;
    int numeroTelefono;
    char nome[100];
    char cognome[100];
} rubrica[NUMERO_MASSIMO_CONTATTI];

void LetturaDaFile();
void InserisciContatto();
void StampaContatto(Contatto contatto);
void StampaRubrica();
void RicercaContatto();

int main()
{
    while(true)
    {
        cout << "1) Inserisci contatto" << endl;
        cout << "2) Stampa rubrica" << endl;
        cout << "3) Ricerca contatto" << endl;
        cout << "4) Esci" << endl;
        cout << "- Inserisci cosa vuoi fare: ";
        int scelta;
        cin >> scelta;

        LetturaDaFile();

        cout << endl << endl;

        if(scelta == 1)
            InserisciContatto();
        else if(scelta == 2)
            StampaRubrica();
        else if(scelta == 3)
            RicercaContatto();
        else if(scelta == 4)
            break;

        cout << endl << endl;
    }

    return 0;
}

void InserisciContatto()
{
    cout << "------INSERIMENTO CONTATTO------" << endl;

    Contatto contatto;

    cout << "- Inserisci il nome del contatto: ";
    cin >> contatto.nome;

    cout << "- Inserisci il cognome del contatto: ";
    cin >> contatto.cognome;

    cout << "- Inserisci il numero di telefono del contatto: ";
    cin >> contatto.numeroTelefono;

    cout << "- Inserisci il codice del contatto: ";
    cin >> contatto.codiceContatto;

    fstream file;
    file.open(PERCORSO_FILE, ios::app | ios::binary);
    file.write((char*) &contatto, sizeof(contatto));
    file.close();
}

void StampaContatto(Contatto contatto)
{
    cout << "Nome: " << contatto.nome << endl;
    cout << "Cognome: " << contatto.cognome << endl;
    cout << "Numero di telefono: " << contatto.numeroTelefono << endl;
    cout << "Codice: " << contatto.codiceContatto << endl;
}

void StampaRubrica()
{
    cout << "------RUBRICA------" << endl;

    for(int i = 0; i < NUMERO_MASSIMO_CONTATTI; i++)
    {
        //Controlla se i contatti sono finiti
        if(rubrica[i].nome[0] == '\0')
            break;

        StampaContatto(rubrica[i]);
        cout << endl;
    }
}

void RicercaContatto()
{
    fstream file;
    file.open(PERCORSO_FILE, ios::in | ios::binary);

    int codice;
    cout << "- Inserisci il codice del contatto da cercare: ";
    cin >> codice;

    Contatto contatto;
    long posizione = (codice - 1) * sizeof(contatto);
    file.seekg(posizione);
    file.read((char*) &contatto, sizeof(contatto));

    StampaContatto(contatto);

    file.close();
}

void LetturaDaFile()
{
    fstream file;
    file.open(PERCORSO_FILE, ios::in | ios::binary);

    for(int i = 0; file.read((char*) &rubrica[i], sizeof(rubrica[i])); i++);

    file.close();
}
