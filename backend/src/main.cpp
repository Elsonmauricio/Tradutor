#include "funcoes.hpp"
#include "mongoose.h"

#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

using namespace std;

// Função de callback para lidar com requisições HTTP
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_http_match_uri(hm, "/api/translate")) {
            // Aqui você pode processar o JSON recebido e retornar a tradução
            mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"translation\":\"exemplo\"}");
        } else {
            mg_http_reply(c, 404, "", "Not found");
        }
    }
}

int main() {
    // Define o locale global para "C"
    locale::global(locale("C"));

    // Carrega configurações, dicionário e histórico
    Config config = carregarConfiguracoes();
    map<string, string> dicionario = carregarDicionario(config.traduzir_inverso);
    vector<string> historico = carregarHistorico();

    // Verifica se o dicionário foi carregado corretamente
    if (dicionario.empty()) {
        cerr << aplicarCor("Erro: Não foi possível carregar o dicionário.", "vermelho") << endl;
        return 1;
    }

    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://localhost:5000", fn, &mgr);

    printf("Servidor rodando em http://localhost:5000\n");
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);

    int opcao;
    do {
        // Mostra o menu
        cout << aplicarCor("\n--- Tradutor Inglês-Português ---", "azul") << endl;
        cout << "1. Traduzir palavra" << endl;
        cout << "2. Adicionar palavra ao dicionário" << endl;
        cout << "3. Mostrar histórico" << endl;
        cout << "4. Gerenciar favoritos" << endl;
        cout << "5. Buscar expressões" << endl;
        cout << "6. Mostrar estatísticas" << endl;
        cout << "7. Sair" << endl;
        cout << "Escolha uma opção: ";
        
        // Valida a entrada do usuário
        while (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << aplicarCor("Entrada inválida! Por favor, digite um número: ", "vermelho");
        }

        switch (opcao) {
            case 1: traduzirPalavra(dicionario, historico); break;
            case 2: adicionarPalavra(dicionario); break;
            case 3: mostrarHistorico(historico); break;
            case 4: gerenciarFavoritos(); break;
            case 5: buscarExpressoes(dicionario); break;
            case 6: mostrarEstatisticas(dicionario, historico); break;
            case 7: cout << aplicarCor("\nSaindo do tradutor...", "azul") << endl; break;
            default: cout << aplicarCor("Opção inválida!", "vermelho") << endl;
        }
    } while (opcao != 7);

    return 0;
}