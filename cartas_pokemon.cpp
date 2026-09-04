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
    int quantidade;
    bool foil;

    void mostrar() {
        cout << "Nome: " << nome << endl;
        cout << "Colecao: " << colecao << endl;
        cout << "Elemento: " << elemento << endl;
        cout << "Raridade: " << raridade << endl;
        cout << "Quantidade: " << quantidade << endl;
        cout << "Foil: " << (foil ? "Sim" : "Nao") << endl;
        cout << "-----------------------------" << endl;
    }
};

vector<Carta> cartas; 
string nomeArquivo = "cartas.txt";

string lerTexto() {
    string texto;
    getline(cin, texto);
    return texto;
}

void carregarCartas() {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    Carta c;
    while (getline(arquivo, c.nome)) {
        getline(arquivo, c.colecao);
        getline(arquivo, c.elemento);
        getline(arquivo, c.raridade);

        string linhaQuantidade;
        getline(arquivo, linhaQuantidade);
        c.quantidade = stoi(linhaQuantidade);

        string linhaFoil;
        getline(arquivo, linhaFoil);
        c.foil = (linhaFoil == "1");

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
        arquivo << cartas[i].quantidade << endl;
        arquivo << (cartas[i].foil ? 1 : 0) << endl;
    }

    arquivo.close();
}

void adicionarCarta() {
    Carta novaCarta;

    cout << "\n--- Adicionar nova carta ---" << endl;

    cout << "Nome da carta: ";
    novaCarta.nome = lerTexto();

    cout << "Colecao: ";
    novaCarta.colecao = lerTexto();

    cout << "Elemento: ";
    novaCarta.elemento = lerTexto();

    cout << "Raridade: ";
    novaCarta.raridade = lerTexto();

    novaCarta.quantidade = 1; 

    char respostaFoil;
    cout << "E foil? (s/n): ";
    cin >> respostaFoil;
    cin.ignore();
    novaCarta.foil = (respostaFoil == 's' || respostaFoil == 'S');

    if (!novaCarta.foil) {
        for (int i = 0; i < cartas.size(); i++) {
            if (!cartas[i].foil &&
                cartas[i].nome == novaCarta.nome &&
                cartas[i].colecao == novaCarta.colecao &&
                cartas[i].elemento == novaCarta.elemento &&
                cartas[i].raridade == novaCarta.raridade) {

                cartas[i].quantidade = cartas[i].quantidade + novaCarta.quantidade;
                salvarCartas();
                cout << "\nJa existia essa carta, quantidade atualizada para " << cartas[i].quantidade << ".\n" << endl;
                return;
            }
        }
    }

    cartas.push_back(novaCarta);
    salvarCartas();

    cout << "\nCarta adicionada com sucesso!\n" << endl;
}

void excluirCarta() {
    cout << "\n--- Excluir carta ---" << endl;

    if (cartas.size() == 0) {
        cout << "Nenhuma carta cadastrada ainda\n" << endl;
        return;
    }

    for (int i = 0; i < cartas.size(); i++) {
        cout << (i + 1) << ") ";
        cout << cartas[i].nome << " - " << cartas[i].colecao << " - " << cartas[i].elemento;
        cout << " - " << cartas[i].raridade << " - Qtd: " << cartas[i].quantidade;
        cout << " - Foil: " << (cartas[i].foil ? "Sim" : "Nao") << endl;
    }

    cout << "\nDigite o numero da carta que deseja excluir (0 para cancelar): ";
    int escolha;
    cin >> escolha;
    cin.ignore();

    if (escolha == 0) {
        cout << "\nOperacao cancelada.\n" << endl;
        return;
    }

    if (escolha < 0 || escolha > cartas.size()) {
        cout << "\nOpcao invalida\n" << endl;
        return;
    }

    int indice = escolha - 1;

    if (cartas[indice].quantidade > 1) {
        cout << "Essa carta tem " << cartas[indice].quantidade << " unidades. Quantas deseja remover? ";
        int quantidadeRemover;
        cin >> quantidadeRemover;
        cin.ignore();

        if (quantidadeRemover < cartas[indice].quantidade) {
            cartas[indice].quantidade = cartas[indice].quantidade - quantidadeRemover;
            salvarCartas();
            cout << "\nQuantidade atualizada, restaram " << cartas[indice].quantidade << " unidades.\n" << endl;
            return;
        }
    }

    cartas.erase(cartas.begin() + indice);
    salvarCartas();

    cout << "\nCarta excluida\n" << endl;
}

void listarTodas() {
    cout << "\n--- Todas as cartas (" << cartas.size() << " tipos cadastrados) ---\n" << endl;

    if (cartas.size() == 0) {
        cout << "Nenhuma carta cadastrada ainda\n" << endl;
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
        cout << "Nenhuma carta encontrada nessa colecao\n" << endl;
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
        cout << "Nenhuma carta encontrada com esse elemento\n" << endl;
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
        cout << "Nenhuma carta encontrada com essa raridade\n" << endl;
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
    cout << "6 - Excluir carta" << endl;
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
        } else if (opcao == 6) {
            excluirCarta();
        } else if (opcao == 0) {
            cout << "\nSaindo... ate mais!\n" << endl;
        } else {
            cout << "\nOpcao invalida! Tente novamente\n" << endl;
        }
    }

    return 0;
}
