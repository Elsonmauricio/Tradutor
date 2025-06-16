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

using namespace std;

// Estrutura de configuração
struct Config {
    std::string cor_principal = "verde";
    bool salvar_historico = true;
    bool mostrar_dicas = true;
    bool traduzir_inverso = false;
};

// Constantes de arquivos
const std::string DICIONARIO_ARQUIVO = "./dicionario.txt";
const std::string HISTORICO_ARQUIVO = "./historico.txt";
const std::string FAVORITOS_ARQUIVO = "./favoritos.txt";

// Funções utilitárias
std::string aplicarCor(const std::string& texto, const std::string& cor);
std::string toLowerCase(const std::string& str);
std::vector<std::string> splitFrase(const std::string& frase);
bool contemUTF8(const std::string& str);

// Carregamento e salvamento
Config carregarConfiguracoes();
void salvarConfiguracoes(const Config& config);
std::map<std::string, std::string> carregarDicionario(bool inverso = false);
void salvarDicionario(const std::map<std::string, std::string>& dicionario);
void salvarLista(const std::string& nome_arquivo, const std::vector<std::string>& lista);
std::vector<std::string> carregarLista(const std::string& nome_arquivo);

// Tradução
std::string traduzirTexto(const std::string& texto, const std::map<std::string, std::string>& dicionario, bool isFrase = false);
void processarTraducao(Config& config, std::map<std::string, std::string>& dicionario);
void adicionarNovaTraducao(std::map<std::string, std::string>& dicionario, const std::string& portugues, const std::string& umbundo);
void traduzirPalavra(std::map<std::string, std::string>& dicionario, std::vector<std::string>& historico);
void adicionarPalavra(std::map<std::string, std::string>& dicionario);

// Menus
void mostrarMenuPrincipal(const Config& config);

// Histórico
void salvarHistorico(const std::string& entrada, const std::string& traducao);
std::vector<std::string> carregarHistorico();
void mostrarHistorico(const std::vector<std::string>& historico);
void limparHistorico();

// Dicionário
void gerenciarDicionario();
void buscarExpressoes(const std::map<std::string, std::string>& dicionario);
void salvarDicionario(const std::map<std::string, std::string>& dicionario, bool traduzir_inverso);

// Favoritos
void gerenciarFavoritos();
void mostrarFavoritos();
void adicionarAFavoritos(const std::string& traducao);

// Estatísticas
void mostrarEstatisticas(const std::map<std::string, std::string>& dicionario, const std::vector<std::string>& historico);

std::string toLowerCase(const std::string& str);
#endif

