#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>
#include <limits>
#include <stdexcept>
#include <cctype>

// Estrutura de configuração
struct Config {
    string cor_principal = "verde";
    bool salvar_historico = true;
    bool mostrar_dicas = true;
    bool traduzir_inverso = false;
};

// Constantes de arquivos
const string DICIONARIO_ARQUIVO = "backend/dicionario.txt";
const string HISTORICO_ARQUIVO = "backend/historico.txt";
const string FAVORITOS_ARQUIVO = "backend/favoritos.txt";

// Funções utilitárias
string aplicarCor(const string& texto, const string& cor);
string toLowerCase(const string& str);
vector<string> splitFrase(const string& frase);
bool contemUTF8(const string& str);

// Carregamento e salvamento
Config carregarConfiguracoes();
void salvarConfiguracoes(const Config& config);
map<string, string> carregarDicionario(bool inverso = false);
void salvarDicionario(const map<string, string>& dicionario);
void salvarLista(const string& nome_arquivo, const vector<string>& lista);
vector<string> carregarLista(const string& nome_arquivo);

// Tradução
string traduzirTexto(const string& texto, const map<string, string>& dicionario, bool isFrase = false);
void processarTraducao(Config& config, map<string, string>& dicionario);
void adicionarNovaTraducao(map<string, string>& dicionario, const string& portugues, const string& umbundo);

// Menus
void mostrarMenuPrincipal(const Config& config);

// Histórico
void salvarHistorico(const string& entrada, const string& traducao);
vector<string> carregarHistorico();
void mostrarHistorico();
void limparHistorico();

// Dicionário
void gerenciarDicionario();
void buscarExpressoes(const map<string, string>& dicionario);

// Favoritos
void gerenciarFavoritos();
void mostrarFavoritos();
void adicionarAFavoritos(const string& traducao);

// Estatísticas
void mostrarEstatisticas(const map<string, string>& dicionario, const vector<string>& historico);

#endif
