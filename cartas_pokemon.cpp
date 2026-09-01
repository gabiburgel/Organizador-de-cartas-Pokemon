// Programa simples para organizar cartas de Pokemon
// Permite cadastrar cartas e listar por colecao, elemento ou raridade
// Os dados sao salvos em um arquivo de texto (cartas.txt) para nao se perder

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Carta {
public:
    string nome;
    string colecao;
    string elemento;
    string raridade;

    void mostrar() {
        cout << "Nome: " << nome << endl;
        cout << "Colecao: " << colecao << endl;
        cout << "Elemento: " << elemento << endl;
        cout << "Raridade: " << raridade << endl;
        cout << "-----------------------------" << endl;
    }
};

vector<Carta> cartas; // lista com todas as cartas cadastradas
string nomeArquivo = "cartas.txt";

string lerTexto() {
    string texto;
    getline(cin, texto);
    return texto;
}

void carregarCartas() {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return; // se o arquivo nao existe ainda, nao tem problema
    }

    Carta c;
    while (getline(arquivo, c.nome)) {
        getline(arquivo, c.colecao);
        getline(arquivo, c.elemento);
        getline(arquivo, c.raridade);
        cartas.push_back(c);
    }

    arquivo.close();
}

void salvarCartas() {
    ofstream arquivo(nomeArquivo);

    for (int i = 0; i < cartas.size(); i++) {
        arquivo << cartas[i].nome << endl;
        arquivo << cartas[i].colecao << endl;
        arquivo << cartas[i].elemento << endl;
        arquivo << cartas[i].raridade << endl;
    }

    arquivo.close();
}

void adicionarCarta() {
    Carta novaCarta;

    cout << "\n--- Adicionar nova carta ---" << endl;

    cout << "Nome da carta: ";
    novaCarta.nome = lerTexto();

    cout << "Colecao (ex: Base Set, Escarlate e Violeta...): ";
    novaCarta.colecao = lerTexto();

    cout << "Elemento (ex: Fogo, Agua, Planta, Eletrico...): ";
    novaCarta.elemento = lerTexto();

    cout << "Raridade (ex: Comum, Incomum, Rara, Ultra Rara...): ";
    novaCarta.raridade = lerTexto();

    cartas.push_back(novaCarta);
    salvarCartas();

    cout << "\nCarta adicionada com sucesso!\n" << endl;
}

void listarTodas() {
    cout << "\n--- Todas as cartas (" << cartas.size() << ") ---\n" << endl;

    if (cartas.size() == 0) {
        cout << "Nenhuma carta cadastrada ainda.\n" << endl;
        return;
    }

    for (int i = 0; i < cartas.size(); i++) {
        cartas[i].mostrar();
    }
}

void listarPorColecao() {
    cout << "\nDigite a colecao que deseja ver: ";
    string colecaoBuscada = lerTexto();

    cout << "\n--- Cartas da colecao " << colecaoBuscada << " ---\n" << endl;

    int encontrou = 0;
    for (int i = 0; i < cartas.size(); i++) {
        if (cartas[i].colecao == colecaoBuscada) {
            cartas[i].mostrar();
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        cout << "Nenhuma carta encontrada nessa colecao.\n" << endl;
    }
}

void listarPorElemento() {
    cout << "\nDigite o elemento que deseja ver: ";
    string elementoBuscado = lerTexto();

    cout << "\n--- Cartas do elemento " << elementoBuscado << " ---\n" << endl;

    int encontrou = 0;
    for (int i = 0; i < cartas.size(); i++) {
        if (cartas[i].elemento == elementoBuscado) {
            cartas[i].mostrar();
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        cout << "Nenhuma carta encontrada com esse elemento.\n" << endl;
    }
}

void listarPorRaridade() {
    cout << "\nDigite a raridade que deseja ver: ";
    string raridadeBuscada = lerTexto();

    cout << "\n--- Cartas com raridade " << raridadeBuscada << " ---\n" << endl;

    int encontrou = 0;
    for (int i = 0; i < cartas.size(); i++) {
        if (cartas[i].raridade == raridadeBuscada) {
            cartas[i].mostrar();
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        cout << "Nenhuma carta encontrada com essa raridade.\n" << endl;
    }
}

void mostrarMenu() {
    cout << "\n=========================================" << endl;
    cout << "   ORGANIZADOR DE CARTAS POKEMON" << endl;
    cout << "=========================================" << endl;
    cout << "1 - Adicionar carta" << endl;
    cout << "2 - Listar todas as cartas" << endl;
    cout << "3 - Listar por colecao" << endl;
    cout << "4 - Listar por elemento" << endl;
    cout << "5 - Listar por raridade" << endl;
    cout << "0 - Sair" << endl;
    cout << "=========================================" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    carregarCartas();

    int opcao = -1;

    while (opcao != 0) {
        mostrarMenu();
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            adicionarCarta();
        } else if (opcao == 2) {
            listarTodas();
        } else if (opcao == 3) {
            listarPorColecao();
        } else if (opcao == 4) {
            listarPorElemento();
        } else if (opcao == 5) {
            listarPorRaridade();
        } else if (opcao == 0) {
            cout << "\nSaindo... ate mais!\n" << endl;
        } else {
            cout << "\nOpcao invalida! Tente novamente.\n" << endl;
        }
    }

    return 0;
}
