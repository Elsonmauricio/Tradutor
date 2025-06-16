#include "funcoes.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;


string toLowerCase(const string& str) {
    string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { 
            return std::tolower(c); 
        }
    );
    return result;
}

map<std::string, std::string> carregarDicionario(bool inverso) {
    map<std::string, std::string> dicionario;
    ifstream arquivo("dicionario.txt");  // Use nome fixo para teste
    
    // Adicione logs
    if (!arquivo.is_open()) {
        cerr << "Erro: Não foi possível abrir dicionario.txt" << endl;
        return dicionario;
    }

    std::string linha;
    int count = 0;
    while (getline(arquivo, linha)) {
        size_t pos = linha.find('=');
        if (pos != std::string::npos) {
            std::string chave = linha.substr(0, pos);
            std::string valor = linha.substr(pos + 1);
            
            // Adicione log
            cout << "Carregando: " << chave << " -> " << valor << endl;
            
            if (inverso)
                dicionario[valor] = chave;
            else
                dicionario[chave] = valor;
                
            count++;
        }
    }
    cout << "Total de palavras carregadas: " << count << endl;
    return dicionario;
}

void adicionarNovaTraducao(std::map<std::string, std::string>& dicionario, const std::string& portugues, const std::string& umbundo) {
    try {
        // Remover marcadores de não encontrado se existirem
        string cleanPt = portugues;
        string cleanUm = umbundo;
        
        if (cleanPt.front() == '[' && cleanPt.back() == ']') {
            cleanPt = cleanPt.substr(1, cleanPt.length() - 2);
        }
        if (cleanUm.front() == '[' && cleanUm.back() == ']') {
            cleanUm = cleanUm.substr(1, cleanUm.length() - 2);
        }

        // Verificar se já existe
        if (dicionario.find(cleanPt) != dicionario.end()) {
            throw runtime_error("Tradução já existe no dicionário");
        }

        // Adicionar ao dicionário e arquivo
        dicionario[cleanPt] = cleanUm;
        ofstream arquivo(DICIONARIO_ARQUIVO, ios::app);
        if (!arquivo) {
            throw runtime_error("Falha ao abrir arquivo do dicionário");
        }
        arquivo << cleanPt << "=" << cleanUm << "\n";
        arquivo.close();

        cout << aplicarCor("Tradução adicionada com sucesso!\n", "verde");
    }
    catch (const exception& e) {
        cerr << aplicarCor("Erro ao adicionar: " + string(e.what()) + "\n", "vermelho");
    }
}

// Implementações básicas das funções restantes (como placeholders)
void processarTraducao(Config& config, std::map<std::string, std::string>& dicionario) {
    try {
        cout << "\n" << aplicarCor("=== Modo de Tradução ===", config.cor_principal) << endl;
        cout << "1. Palavra única\n2. Frase completa\n3. Voltar\n";
        cout << "Escolha o tipo: ";
        
        int tipo;
        cin >> tipo;
        cin.ignore();
        
        if (tipo == 3) return;

        if (tipo != 1 && tipo != 2) {
            throw invalid_argument("Tipo de tradução inválido");
        }

        cout << (tipo == 1 ? "Digite a palavra: " : "Digite a frase: ");
        string entrada;
        getline(cin, entrada);

        if (entrada.empty()) {
            throw runtime_error("Entrada vazia");
        }

        string traducao = traduzirTexto(entrada, dicionario, tipo == 2);
        
        cout << "\n" << aplicarCor("Resultado:", "verde") << "\n";
        cout << aplicarCor(entrada, config.cor_principal) << " → " 
             << aplicarCor(traducao, "ciano") << "\n\n";

        if (config.salvar_historico) {
            salvarLista(HISTORICO_ARQUIVO, {entrada + "=" + traducao});
            
            if (config.mostrar_dicas) {
                cout << aplicarCor("Dica: Esta tradução foi salva no histórico.\n", "amarelo");
            }
        }

        // Sugerir adicionar ao dicionário se não encontrado
        if (traducao.find("[") != string::npos) {
            cout << aplicarCor("Deseja adicionar ao dicionário? (s/n): ", "amarelo");
            char resposta;
            cin >> resposta;
            if (tolower(resposta) == 's') {
                adicionarNovaTraducao(dicionario, entrada, traducao);
            }
        }
    } 
    catch (const exception& e) {
        cerr << aplicarCor("\nErro: " + string(e.what()) + "\n", "vermelho");
    }
}


void gerenciarDicionario() {
    try {
        map<string, string> dicionario = carregarDicionario();
        int opcao;
        
        do {
            cout << "\n=== Gerenciar Dicionário ===\n";
            cout << "1. Listar todas as traduções\n";
            cout << "2. Adicionar nova tradução\n";
            cout << "3. Remover tradução\n";
            cout << "4. Buscar tradução\n";
            cout << "5. Voltar\n";
            cout << "Escolha: ";
            
            cin >> opcao;
            cin.ignore();
            
            switch(opcao) {
                case 1: {
                    cout << "\n=== Traduções ===\n";
                    for (const auto& par : dicionario) {
                        cout << setw(20) << left << par.first << " → " << par.second << "\n";
                    }
                    break;
                }
                case 2: {
                    string pt, um;
                    cout << "Português: ";
                    getline(cin, pt);
                    cout << "Umbundo: ";
                    getline(cin, um);

                    if (pt.empty() || um.empty()) {
                        throw invalid_argument("Entradas não podem ser vazias");
                    }

                    adicionarNovaTraducao(dicionario, pt, um);
                    break;
                }
                case 3: {
                    string pt;
                    cout << "Palavra em Português para remover: ";
                    getline(cin, pt);
                    
                    auto it = dicionario.find(toLowerCase(pt));
                    if (it != dicionario.end()) {
                        dicionario.erase(it);
                        salvarDicionario(dicionario);
                        cout << "Tradução removida.\n";
                    } else {
                        cout << "Tradução não encontrada.\n";
                    }
                    break;
                }
                case 4: {
                    string termo;
                    cout << "Termo para buscar: ";
                    getline(cin, termo);
                    
                    cout << "\nResultados:\n";
                    bool encontrado = false;
                    for (const auto& par : dicionario) {
                        if (par.first.find(toLowerCase(termo)) != string::npos || 
                            par.second.find(toLowerCase(termo)) != string::npos) {
                            cout << setw(20) << left << par.first << " → " << par.second << "\n";
                            encontrado = true;
                        }
                    }
                    
                    if (!encontrado) {
                        cout << "Nenhum resultado encontrado.\n";
                    }
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Opção inválida.\n";
            }
        } while (opcao != 5);
    }
    catch (const exception& e) {
        cerr << aplicarCor("Erro no gerenciamento: " + string(e.what()) + "\n", "vermelho");
    }
}

vector<string> carregarHistorico() {
    vector<string> historico;
    ifstream arquivo(HISTORICO_ARQUIVO);
    string linha;
    while (getline(arquivo, linha)) {
        if (!linha.empty()) {
            historico.push_back(linha);
        }
    }
    return historico;
}

void salvarHistorico(const string& entrada, const string& traducao) {
    ofstream arquivo(HISTORICO_ARQUIVO, ios::app);
    if (arquivo.is_open()) {
        arquivo << entrada << "=" << traducao << "\n";
        arquivo.close();
    } else {
        cerr << "Erro ao salvar histórico." << endl;
    }
}

void gerenciarFavoritos() {
    vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO);
    int opcao;
    
    do {
        cout << "\n=== Gerenciar Favoritos ===\n";
        cout << "1. Listar favoritos\n";
        cout << "2. Adicionar a favoritos\n";
        cout << "3. Remover de favoritos\n";
        cout << "4. Voltar\n";
        cout << "Escolha: ";
        
        cin >> opcao;
        cin.ignore();
        
        switch(opcao) {
            case 1:
                mostrarFavoritos();
                break;
            case 2: {
                string traducao;
                cout << "Digite a tradução para adicionar aos favoritos: ";
                getline(cin, traducao);
                adicionarAFavoritos(traducao);
                break;
            }
            case 3: {
                mostrarFavoritos();
                cout << "Digite o número do favorito para remover: ";
                int idx;
                cin >> idx;
                cin.ignore();
                if (idx > 0 && idx <= favoritos.size()) {
                    favoritos.erase(favoritos.begin() + idx - 1);
                    salvarLista(FAVORITOS_ARQUIVO, favoritos);
                    cout << aplicarCor("Favorito removido!\n", "verde");
                } else {
                    cout << "Índice inválido.\n";
                }
                break;
            }
            case 4:
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 4);
}

void mostrarFavoritos() {
    vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO);
    cout << "\n=== Favoritos ===\n";
    int i = 1;
    for (const auto& item : favoritos) {
        cout << i++ << ". " << item << "\n";
    }
}

void adicionarAFavoritos(const string& traducao) {
    vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO);
    favoritos.push_back(traducao);
    salvarLista(FAVORITOS_ARQUIVO, favoritos);
    cout << aplicarCor("Tradução adicionada aos favoritos!\n", "verde");
}

void mostrarEstatisticas(const map<string, string>& dicionario, const vector<string>& historico) {
    cout << "\n=== Estatísticas ===\n";
    cout << "Total de traduções: " << dicionario.size() << "\n";
    cout << "Total de traduções no histórico: " << historico.size() << "\n";
    // Adicione mais estatísticas conforme necessário
}

void buscarExpressoes(const map<string, string>& dicionario) {
    cout << "Digite a expressão para buscar: ";
    string termo;
    getline(cin, termo);
    
    bool encontrado = false;
    for (const auto& par : dicionario) {
        if (par.first.find(toLowerCase(termo)) != string::npos || 
            par.second.find(toLowerCase(termo)) != string::npos) {
            cout << setw(20) << left << par.first << " → " << par.second << "\n";
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "Nenhum resultado encontrado.\n";
    }
}

void limparHistorico() {
    ofstream arquivo(HISTORICO_ARQUIVO, ios::trunc);
    if (arquivo.is_open()) {
        arquivo.close();
        cout << aplicarCor("Histórico limpo com sucesso!\n", "verde");
    } else {
        cerr << aplicarCor("Erro ao limpar histórico.\n", "vermelho");
    }
}

string traduzirTexto(const string& texto, const map<string, string>& dicionario, bool isFrase) {
    try {
        if (!isFrase) {
            // Busca por palavra única
            string lower = toLowerCase(texto);
            auto it = dicionario.find(lower);
            
            if (it != dicionario.end()) {
                return it->second;
            }
            
            // Tentar encontrar variações
            for (const auto& par : dicionario) {
                if (par.first.find(lower) != string::npos) {
                    return par.second + " (parcial)";
                }
            }
            
            return "[" + texto + "]";
        }
        else {
            // Tradução de frase
            vector<string> palavras = splitFrase(texto);
            string resultado;
            
            for (const string& palavra : palavras) {
                string lower = toLowerCase(palavra);
                auto it = dicionario.find(lower);
                
                if (it != dicionario.end()) {
                    resultado += it->second + " ";
                }
                else {
                    // Verificar se é pontuação
                    if (ispunct(palavra[0]) && palavra.size() == 1) {
                        resultado += palavra + " ";
                    }
                    else {
                        resultado += "[" + palavra + "] ";
                    }
                }
            }
            
            if (!resultado.empty()) {
                resultado.pop_back(); // Remover espaço extra
            }
            
            return resultado;
        }
    }
    catch (const exception& e) {
        cerr << aplicarCor("Erro na tradução: " + string(e.what()) + "\n", "vermelho");
        return "[erro]";
    }
}

bool contemUTF8(const string& str) {
    // Implementação simples - verifica se há caracteres não-ASCII
    for (char c : str) {
        if (static_cast<unsigned char>(c) > 127) {
            return true;
        }
    }
    return false;
}

string aplicarCor(const string& texto, const string& cor) {
    // Simples: retorna o texto sem cor (pode melhorar depois)
    return texto;
}

vector<string> splitFrase(const string& frase) {
    vector<string> palavras;
    istringstream iss(frase);
    string palavra;
    while (iss >> palavra) {
        palavras.push_back(palavra);
    }
    return palavras;
}

Config carregarConfiguracoes() {
    Config config;
    ifstream arquivo("config.txt");
    if (arquivo.is_open()) {
        arquivo >> config.salvar_historico;
        arquivo >> config.mostrar_dicas;
        arquivo >> config.traduzir_inverso;
        arquivo.close();
    }
    return config;
}

void salvarConfiguracoes(const Config& config) {
    ofstream arquivo("config.txt");
    if (arquivo.is_open()) {
        arquivo << config.salvar_historico << endl;
        arquivo << config.mostrar_dicas << endl;
        arquivo << config.traduzir_inverso << endl;
        arquivo.close();
    }
}

void salvarDicionario(const map<string, string>& dicionario) {
    ofstream arquivo(DICIONARIO_ARQUIVO, ios::trunc);
    for (const auto& par : dicionario) {
        arquivo << par.first << ";" << par.second << "\n";
    }
}

void salvarLista(const string& nome_arquivo, const vector<string>& lista) {
    ofstream arquivo(nome_arquivo, ios::app);
    for (const auto& item : lista) {
        arquivo << item << "\n";
    }
}

vector<string> carregarLista(const string& nome_arquivo) {
    vector<string> lista;
    ifstream arquivo(nome_arquivo);
    string linha;
    while (getline(arquivo, linha)) {
        if (!linha.empty())
            lista.push_back(linha);
    }
    return lista;
}

// void mostrarMenuPrincipal(const Config& config) {
//     cout << "\n=== Tradutor Português - Umbundo ===\n";
//     cout << "1. Traduzir\n";
//     cout << "2. Gerenciar Dicionário\n";
//     cout << "3. Ver Histórico\n";
//     cout << "4. Favoritos\n";
//     cout << "5. Buscar Expressões\n";
//     cout << "6. Estatísticas\n";
//     cout << "7. Sair\n";
//     cout << "Escolha uma opção: ";
// }

// Implementação de traduzirPalavra
void traduzirPalavra(std::map<std::string, std::string>& dicionario, 
                    std::vector<std::string>& historico) {
    std::string palavra;
    std::cout << "Digite a palavra para traduzir: ";
    std::cin >> palavra;
    
    auto it = dicionario.find(palavra);
    if (it != dicionario.end()) {
        std::cout << "Tradução: " << it->second << std::endl;
        historico.push_back(palavra + "=" + it->second);
    } else {
        std::cout << "Palavra não encontrada no dicionário." << std::endl;
    }
}

// Implementação de adicionarPalavra
void adicionarPalavra(std::map<std::string, std::string>& dicionario) {
    std::string pt, um;
    std::cout << "Digite a palavra em português: ";
    std::cin >> pt;
    std::cout << "Digite a tradução em umbundo: ";
    std::cin >> um;
    
    dicionario[pt] = um;
    
    // Salvar no arquivo
    std::ofstream arquivo(DICIONARIO_ARQUIVO, std::ios::app);
    if (arquivo) {
        arquivo << pt << ";" << um << "\n";
    }
    std::cout << "Palavra adicionada com sucesso!" << std::endl;
}

void mostrarHistorico(const std::vector<std::string>& historico) {
    std::cout << "\n=== Histórico de Traduções ===" << std::endl;
    
    if (historico.empty()) {
        std::cout << "Nenhuma tradução no histórico." << std::endl;
        return;
    }

    for (size_t i = 0; i < historico.size(); ++i) {
        std::cout << i+1 << ". " << historico[i] << std::endl;
    }
}

// Altere a implementação para:
void salvarDicionario(const std::map<std::string, std::string>& dicionario, bool traduzir_inverso) {
    std::ofstream arquivo("dicionario.txt");
    for (const auto& par : dicionario) {
        if (traduzir_inverso) {
            arquivo << par.second << "=" << par.first << "\n";  // Use = em vez de ;
        } else {
            arquivo << par.first << "=" << par.second << "\n";  // Use = em vez de ;
        }
    }
    arquivo.close();
}