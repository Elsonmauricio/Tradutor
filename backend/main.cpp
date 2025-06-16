#define _WIN32_WINNT 0x0601  // Windows 7 ou superior
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define CPPHTTPLIB_USE_POLL
#include <httplib.h>
#include "httplib.h"
#include <iostream>
#include <map>

#include "funcoes.hpp"
#include "json.hpp"

#ifdef NLOHMANN_JSON_ABI_TAG
    using json = nlohmann::NLOHMANN_JSON_ABI_TAG::json;
#else
    using json = nlohmann::json;
#endif

#include <limits.h>
#include <locale>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// #define NOMINMAX
#endif

using namespace std;

int main() {
    // Define o locale global para "C"
    locale::global(locale("C"));
    

    // Carrega configurações e dicionário
    Config config = carregarConfiguracoes();
    map<string, string> dicionario = carregarDicionario(config.traduzir_inverso);
    vector<string> historico = carregarHistorico();

    // Verifica se o dicionário foi carregado corretamente
    if (dicionario.empty()) {
        cerr << aplicarCor("Erro: Não foi possível carregar o dicionário.", "vermelho") << endl;
        return 1;
    }

    httplib::Server svr;

    // Permitir CORS
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
     // Handler OPTIONS com namespace completo
    svr.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
        res.status = 200;
    });

    // Endpoint para tradução
    svr.Post("/api/translate", [&](const httplib::Request& req, httplib::Response& res) {
    auto j = json::parse(req.body);
    std::string texto = j["text"];
    bool isFrase = texto.find(' ') != std::string::npos;
    string traducao = traduzirTexto(texto, dicionario, isFrase);
    
    // Salvar no histórico
    salvarHistorico(texto, traducao);
    
    json resposta;
    resposta["translation"] = traducao;
    res.set_content(resposta.dump(), "application/json");
    res.set_header("Access-Control-Allow-Origin", "*");
});

   // No endpoint /api/dictionary:
svr.Get("/api/dictionary", [&](const httplib::Request&, httplib::Response& res) {
    json lista;
    for (const auto& par : dicionario) {
        lista.push_back({
            {"portugues", par.first},
            {"umbundo", par.second}
        });
    }
    res.set_content(lista.dump(), "application/json");
    res.set_header("Access-Control-Allow-Origin", "*");
});

svr.Put("/api/dictionary", [&](const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = json::parse(req.body);
        std::string portuguesOriginal = j["portuguesOriginal"];
        std::string portugues = j["portugues"];
        std::string umbundo = j["umbundo"];

        auto it = dicionario.find(portuguesOriginal);
        if (it == dicionario.end()) {
            res.status = 404;
            res.set_content("{\"erro\":\"palavra_nao_encontrada\"}", "application/json");
            return;
        }

        dicionario.erase(it);
        dicionario[portugues] = umbundo;
        salvarDicionario(dicionario, config.traduzir_inverso);

        res.set_content("{\"status\":\"atualizado\"}", "application/json");
    } catch (const std::exception& e) {
        res.status = 500;
        res.set_content("{\"erro\":\"falha_ao_editar\"}", "application/json");
    }
    res.set_header("Access-Control-Allow-Origin", "*");
});

svr.Post("/api/dictionary", [&](const httplib::Request& req, httplib::Response& res) {
  try {
    auto j = json::parse(req.body);
    std::string portugues = j["portugues"];
    std::string umbundo = j["umbundo"];

    // Verificar se palavra já existe
    if (dicionario.find(portugues) != dicionario.end()) {
      res.status = 400;
      res.set_content("{\"erro\":\"palavra_ja_existe\"}", "application/json");
      return;
    }

    dicionario[portugues] = umbundo;
    salvarDicionario(dicionario, config.traduzir_inverso);
    res.set_content("{\"status\":\"adicionado\"}", "application/json");
  } catch (const std::exception& e) {
    res.status = 500;
    res.set_content("{\"erro\":\"falha_ao_adicionar\"}", "application/json");
  }
  res.set_header("Access-Control-Allow-Origin", "*");
});

svr.Delete("/api/dictionary", [&](const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = json::parse(req.body);
        std::string portugues = j["portugues"];
        std::string chave = toLowerCase(portugues);
        
        auto it = dicionario.find(portugues);
        if (it == dicionario.end()) {
            res.set_content("{\"status\":\"nao_encontrado\"}", "application/json");
            return;
        }

        dicionario.erase(it);
        salvarDicionario(dicionario, config.traduzir_inverso);
        res.set_content("{\"status\":\"removido\"}", "application/json");
    } catch (const exception& e) {
        res.status = 500;
        res.set_content("{\"erro\":\"falha_ao_remover\"}", "application/json");
    }
    res.set_header("Access-Control-Allow-Origin", "*");
});

   // Endpoint para obter histórico
svr.Get("/api/history", [&](const httplib::Request&, httplib::Response& res) {
    vector<string> historico = carregarHistorico();
    json resposta = historico;
    res.set_content(resposta.dump(), "application/json");
    res.set_header("Access-Control-Allow-Origin", "*");
});

// Endpoint para limpar todo o histórico
svr.Delete("/api/history", [&](const httplib::Request&, httplib::Response& res) {
    try {
        ofstream arquivo(HISTORICO_ARQUIVO, ios::trunc);
        if (!arquivo.is_open()) {
            throw runtime_error("Não foi possível abrir o arquivo de histórico");
        }
        arquivo.close();
        res.set_content("{\"status\":\"limpo\"}", "application/json");
    } catch (const exception& e) {
        res.status = 500;
        res.set_content("{\"erro\":\"" + string(e.what()) + "\"}", "application/json");
    }
    res.set_header("Access-Control-Allow-Origin", "*");
});

// Endpoint para remover uma entrada específica do histórico
svr.Delete("/api/history/entry", [&](const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = json::parse(req.body);
        std::string entry = j["entry"];
        
        vector<string> historico = carregarHistorico();
        auto it = find(historico.begin(), historico.end(), entry);
        if (it != historico.end()) {
            historico.erase(it);
            
            // Salvar histórico atualizado
            ofstream arquivo(HISTORICO_ARQUIVO);
            for (const auto& item : historico) {
                arquivo << item << "\n";
            }
            arquivo.close();
            
            res.set_content("{\"status\":\"removido\"}", "application/json");
        } else {
            res.set_content("{\"status\":\"nao_encontrado\"}", "application/json");
        }
    } catch (const exception& e) {
        res.status = 500;
        res.set_content("{\"erro\":\"falha_ao_remover\"}", "application/json");
    }
    res.set_header("Access-Control-Allow-Origin", "*");
});

    // Endpoint para obter favoritos
    svr.Get("/api/favorites", [&](const httplib::Request&, httplib::Response& res) {
        vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO); // já existe na sua funcoes.hpp
        json resposta = favoritos;
        res.set_content(resposta.dump(), "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    // Endpoint para adicionar favorito (opcional)
    svr.Post("/api/favorites", [&](const httplib::Request& req, httplib::Response& res) {
        auto j = json::parse(req.body);
        std::string favorito = j["favorito"];
        vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO);
        favoritos.push_back(favorito);
        salvarLista(FAVORITOS_ARQUIVO, favoritos);
        res.set_content("{\"status\":\"ok\"}", "application/json");
        res.set_header("Access-Control-Allow-Origin", "*");
    });

  svr.Delete("/api/favorites", [&](const httplib::Request& req, httplib::Response& res) {
    try {
        auto j = json::parse(req.body);
        std::string favorito = j["favorito"];
        
        vector<string> favoritos = carregarLista(FAVORITOS_ARQUIVO);
        auto it = std::find(favoritos.begin(), favoritos.end(), favorito);
        
        if (it != favoritos.end()) {
            favoritos.erase(it);
            salvarLista(FAVORITOS_ARQUIVO, favoritos);
            res.set_content("{\"status\":\"removido\"}", "application/json");
        } else {
            res.set_content("{\"status\":\"nao_encontrado\"}", "application/json");
        }
    } catch (const std::exception& e) {
        res.status = 500;
        res.set_content("{\"erro\":\"falha_ao_processar\"}", "application/json");
    }
    
    // Adicione ESSENCIAL para CORS:
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
});

  std::cout << "Servidor rodando em http://localhost:3002\n";
    svr.listen("0.0.0.0", 3002);

//     // Endpoint para adicionar nova entrada ao dicionário
// svr.Post("/api/dictionary", [&](const httplib::Request& req, httplib::Response& res) {
//     try {
//         auto j = json::parse(req.body);
//         std::string portugues = j["portugues"];
//         std::string umbundo = j["umbundo"];

//         dicionario[portugues] = umbundo;
//         salvarDicionario(dicionario, config.traduzir_inverso);

//         res.set_content("{\"status\":\"adicionado\"}", "application/json");
//     } catch (const std::exception& e) {
//         res.status = 500;
//         res.set_content("{\"erro\":\"falha_ao_adicionar\"}", "application/json");
//     }
//     res.set_header("Access-Control-Allow-Origin", "*");
// });

    // int opcao;
    // do {
    //     // Mostra o menu
    //     cout << aplicarCor("\n--- Tradutor Inglês-Português ---", "azul") << endl;
    //     cout << "1. Traduzir palavra" << endl;
    //     cout << "2. Adicionar palavra ao dicionário" << endl;
    //     cout << "3. Mostrar histórico" << endl;
    //     cout << "4. Gerenciar favoritos" << endl;
    //     cout << "5. Buscar expressões" << endl;
    //     cout << "6. Mostrar estatísticas" << endl;
    //     cout << "7. Sair" << endl;
    //     cout << "Escolha uma opção: ";
        
    //     // Valida a entrada do usuário
    //     while (!(cin >> opcao)) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //          cout << aplicarCor("Entrada inválida! Por favor, digite um número: ", "vermelho") << endl;
    //     }

    //     switch (opcao) {
    //         case 1: traduzirPalavra(dicionario, historico); break;
    //         case 2: adicionarPalavra(dicionario); break;
    //         case 3: mostrarHistorico(historico); break;
    //         case 4: gerenciarFavoritos(); break;
    //         case 5: buscarExpressoes(dicionario); break;
    //         case 6: mostrarEstatisticas(dicionario, historico); break;
    //         case 7: cout << aplicarCor("\nSaindo do tradutor...", "azul") << endl; break;
    //         default: cout << aplicarCor("Opção inválida!", "vermelho") << endl;
    //     }
    // }

        return 0;  
}  