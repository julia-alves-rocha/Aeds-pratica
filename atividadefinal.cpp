/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */
/*
 * Controle e Estatísticas de Base de Dados
 * * Joaquim Pedro do Nascimento Moreira de Jesus - 2025.1.08.014
 * Júlia Rocha - 2025.1.08.015
 * * Projeto de Aplicativo para Gestão de Imóveis
 * * Objetivo:
 * Desenvolver habilidades na manipulação de registros armazenados em vetores, utilizando estruturas de controle para gerar estatísticas com variáveis simples.
 * * Descrição Geral:
 * O aplicativo terá como função principal a leitura e escrita de dados a partir de um arquivo-texto contendo informações sobre imóveis disponíveis para venda ou locação.
 * No início da execução, os dados devem ser lidos do arquivo “BD_Imoveis2.txt” e armazenados em um vetor de registros com capacidade máxima de 200 imóveis. Cada linha do arquivo representa um único imóvel e deve ser carregada na ordem em que aparece. No encerramento da execução, os dados atualizados devem ser gravados de volta no mesmo arquivo.
 * É essencial que o vetor de registros não contenha espaços vazios (“buracos”): ao excluir um imóvel, os registros seguintes devem ser deslocados para a esquerda para manter a sequência contínua.
 * * Funcionalidades do Aplicativo: (As implemented based on combined requirements)
 * O sistema deverá exibir um menu de opções para que o usuário possa executar as seguintes operações:
 * Inclusão de um novo imóvel na base de dados.
 * Busca de um imóvel pela rua (endereço), e se encontrado, permitir a exclusão da base de dados (function available, not directly in main menu).
 * Busca de imóveis por faixa de valores (locação, venda ou temporada).
 * Busca de imóveis pelas características (comodidades como armários, ar-condicionado, etc., ou por número de quartos e suítes).
 * * Relatório estatístico contendo:
 * Percentual de imóveis por finalidade (venda, locação, temporada)
 * Percentual de casas com suítes
 * Percentual de salas comerciais com piso cerâmico
 * Listagem de todos os imóveis disponíveis.
 * * Formato do Arquivo de Imóveis:
 * O arquivo conterá até 200 linhas, onde cada linha apresenta 22 campos separados por espaços, com as seguintes informações:
 * Tipo
 * Finalidade
 * Endereço
 * Bairro
 * Cidade
 * Área
 * Valor
 * IPTU
 * Quartos
 * Suítes
 * Banheiros
 * Vagas
 * Cozinha
 * Sala
 * Varanda
 * Área de serviço
 * Piso
 * Conservação
 * Armários (sim/nao)
 * Ar-condicionado (sim/nao)
 * Aquecedor (sim/nao)
 * Ventilador (sim/nao)
 * * Observações:
 * A primeira linha do arquivo deve ser ignorada.
 * A última linha, que contém a palavra “fim” no campo do tipo de imóvel, não deve ser considerada nos cálculos.
 */

#include <cstdlib>    // Para funções padrão
#include <fstream>    // Para manipulação de arquivos
#include <iostream>   // Para entrada/saída
#include <string>     // Para manipulação de strings (C++ style)
#include <vector>     // Embora não usado para o array principal, útil para flexibilidade
#include <iomanip>    // Para std::fixed e std::setprecision
#include <limits>     // Para std::numeric_limits (para limpar buffer de entrada)

using namespace std;

// Estrutura do Imóvel (já definida em main, mas aqui para clareza das funções)
const int MAX_IMOVEIS = 200; // Capacidade máxima do vetor de imóveis
struct imovel {
    string tipo; // Tipo do imóvel (casa, apartamento, sala comercial, etc.)
    string finalidade; // Finalidade (venda, locação, temporada)
    string endereco;
    string bairro;
    string cidade;
    float area;
    float valor;
    float iptu;
    int quartos;
    int suites;
    int banheiros;
    int vagas;
    string cozinha;
    string sala;
    string varanda;
    string area_servico;
    string piso;
    string conservacao;
    bool armarios_embutidos;
    bool ar_condicionado;
    bool aquecedor;
    bool ventilador;
};

// Função para limpar a tela do console
void limparTela() {
    // Limpa a tela do console
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    // ANSI escape code para limpar a tela (Linux, macOS)
    cout << "\033[H\033[J";
#endif
}

// Função para pausar e esperar o usuário pressionar Enter
void pausar() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa buffer anterior
    cin.get(); // Espera Enter
}

// Função para ler um booleano (sim/nao) de forma robusta
bool lerBooleano(const string& prompt) {
    string resposta;
    while (true) {
        cout << prompt << " (sim/nao): ";
        cin >> resposta;
        if (resposta == "sim" || resposta == "Sim" || resposta == "s" || resposta == "S") return true;
        if (resposta == "nao" || resposta == "Nao" || resposta == "n" || resposta == "N") return false;
        cout << "Resposta inválida. Por favor, digite 'sim' ou 'nao'." << endl;
    }
}

// Protótipos das novas funções
void adicionarImovel(imovel imoveis[], int &num_imoveis);
void buscarPorRuaExcluir(imovel imoveis[], int &num_imoveis);
void buscarPorFaixaDeValor(const imovel imoveis[], int num_imoveis);
void buscarPorCaracteristicasComodidades(const imovel imoveis[], int num_imoveis);
void buscarPorQuartosSuites(const imovel imoveis[], int num_imoveis);
void gerarRelatorioEstatisticas(const imovel imoveis[], int num_imoveis);
void listarTodosImoveis(const imovel imoveis[], int num_imoveis);
void gravarDados(const imovel imoveis[], int num_imoveis, const string& nomeArquivo);


// Implementações das funções

void adicionarImovel(imovel imoveis[], int &num_imoveis) {
    limparTela();
    cout << "--- Inclusão de Novo Imóvel ---" << endl;
    if (num_imoveis >= MAX_IMOVEIS) {
        cout << "Erro: Capacidade máxima de imóveis atingida (" << MAX_IMOVEIS << ")." << endl;
        pausar();
        return;
    }

    imovel novo;
    cout << "Tipo (casa, apartamento, sala_comercial, etc.): "; cin >> novo.tipo;
    cout << "Finalidade (venda, locacao, temporada): "; cin >> novo.finalidade;
    cout << "Endereço (rua_nome_numero, sem espaços): "; cin >> novo.endereco;
    cout << "Bairro: "; cin >> novo.bairro;
    cout << "Cidade: "; cin >> novo.cidade;
    cout << "Área (m2): "; cin >> novo.area;
    cout << "Valor (R$): "; cin >> novo.valor;
    cout << "IPTU (R$): "; cin >> novo.iptu;
    cout << "Quartos: "; cin >> novo.quartos;
    cout << "Suítes: "; cin >> novo.suites;
    cout << "Banheiros: "; cin >> novo.banheiros;
    cout << "Vagas de garagem: "; cin >> novo.vagas;
    cout << "Cozinha (padrao, americana, etc.): "; cin >> novo.cozinha;
    cout << "Sala (estar, jantar, tv, etc.): "; cin >> novo.sala;
    cout << "Varanda (simples, gourmet, etc.): "; cin >> novo.varanda;
    cout << "Área de serviço (sim, nao): "; cin >> novo.area_servico;
    cout << "Piso (ceramica, porcelanato, madeira, etc.): "; cin >> novo.piso;
    cout << "Conservação (novo, bom, regular, reformar): "; cin >> novo.conservacao;

    novo.armarios_embutidos = lerBooleano("Armários embutidos?");
    novo.ar_condicionado = lerBooleano("Ar-condicionado?");
    novo.aquecedor = lerBooleano("Aquecedor?");
    novo.ventilador = lerBooleano("Ventilador de teto?");

    imoveis[num_imoveis] = novo;
    num_imoveis++;
    cout << "\nImóvel adicionado com sucesso!" << endl;
    pausar();
}

void buscarPorRuaExcluir(imovel imoveis[], int &num_imoveis) {
    limparTela();
    cout << "--- Busca e Exclusão de Imóvel por Endereço ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado para buscar ou excluir." << endl;
        pausar();
        return;
    }
    string enderecoBusca;
    cout << "Digite o endereço (rua_nome_numero) do imóvel a ser buscado: ";
    cin >> enderecoBusca;

    int encontrado_idx = -1;
    for (int i = 0; i < num_imoveis; ++i) {
        if (imoveis[i].endereco == enderecoBusca) {
            encontrado_idx = i;
            break;
        }
    }

    if (encontrado_idx != -1) {
        cout << "\nImóvel encontrado:" << endl;
        cout << "Tipo: " << imoveis[encontrado_idx].tipo << ", Finalidade: " << imoveis[encontrado_idx].finalidade
             << ", Endereço: " << imoveis[encontrado_idx].endereco << ", Valor: R$" << imoveis[encontrado_idx].valor << endl;

        char confirmacao;
        cout << "\nDeseja excluir este imóvel? (s/n): ";
        cin >> confirmacao;

        if (confirmacao == 's' || confirmacao == 'S') {
            for (int i = encontrado_idx; i < num_imoveis - 1; ++i) {
                imoveis[i] = imoveis[i+1];
            }
            num_imoveis--;
            cout << "Imóvel excluído com sucesso!" << endl;
        } else {
            cout << "Exclusão cancelada." << endl;
        }
    } else {
        cout << "Nenhum imóvel encontrado com o endereço '" << enderecoBusca << "'." << endl;
    }
    pausar();
}

void buscarPorFaixaDeValor(const imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Busca de Imóveis por Faixa de Valor ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado." << endl;
        pausar();
        return;
    }

    float valor_min, valor_max;
    string finalidade_busca;

    cout << "Digite a finalidade (venda, locacao, temporada): ";
    cin >> finalidade_busca;
    cout << "Digite o valor mínimo (R$): ";
    cin >> valor_min;
    cout << "Digite o valor máximo (R$): ";
    cin >> valor_max;

    cout << "\nImóveis encontrados:" << endl;
    int count = 0;
    cout << fixed << setprecision(2); // Para formatar valor e área
    for (int i = 0; i < num_imoveis; ++i) {
        if (imoveis[i].finalidade == finalidade_busca &&
            imoveis[i].valor >= valor_min && imoveis[i].valor <= valor_max) {
            cout << (i + 1) << ". Tipo: " << imoveis[i].tipo
                 << ", Endereço: " << imoveis[i].endereco
                 << ", Bairro: " << imoveis[i].bairro
                 << ", Valor: R$" << imoveis[i].valor
                 << ", Área: " << imoveis[i].area << " m2" << endl;
            count++;
        }
    }
    cout << setprecision(0); // Reset precision

    if (count == 0) {
        cout << "Nenhum imóvel encontrado para os critérios especificados." << endl;
    } else {
        cout << "\nTotal de " << count << " imóvel(is) encontrado(s)." << endl;
    }
    pausar();
}

void buscarPorCaracteristicasComodidades(const imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Busca de Imóveis por Comodidades ---" << endl;
     if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado." << endl;
        pausar();
        return;
    }

    bool req_armarios = lerBooleano("Exigir armários embutidos?");
    bool req_ar_condicionado = lerBooleano("Exigir ar-condicionado?");
    bool req_aquecedor = lerBooleano("Exigir aquecedor?");
    bool req_ventilador = lerBooleano("Exigir ventilador de teto?");

    cout << "\nImóveis encontrados com as comodidades especificadas:" << endl;
    int count = 0;
    cout << fixed << setprecision(2);
    for (int i = 0; i < num_imoveis; ++i) {
        bool atende = true;
        if (req_armarios && !imoveis[i].armarios_embutidos) atende = false;
        if (req_ar_condicionado && !imoveis[i].ar_condicionado) atende = false;
        if (req_aquecedor && !imoveis[i].aquecedor) atende = false;
        if (req_ventilador && !imoveis[i].ventilador) atende = false;

        if (atende) {
            cout << (i + 1) << ". Tipo: " << imoveis[i].tipo
                 << ", Endereço: " << imoveis[i].endereco
                 << ", Bairro: " << imoveis[i].bairro
                 << ", Valor: R$" << imoveis[i].valor << endl;
            count++;
        }
    }
    cout << setprecision(0);

    if (count == 0) {
        cout << "Nenhum imóvel encontrado com todas as comodidades especificadas." << endl;
    } else {
        cout << "\nTotal de " << count << " imóvel(is) encontrado(s)." << endl;
    }
    pausar();
}

void buscarPorQuartosSuites(const imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Busca de Imóveis por Número de Quartos e Suítes ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado." << endl;
        pausar();
        return;
    }

    int min_quartos, min_suites;
    cout << "Número mínimo de quartos desejado: ";
    cin >> min_quartos;
    cout << "Número mínimo de suítes desejado: ";
    cin >> min_suites;

    cout << "\nImóveis encontrados:" << endl;
    int count = 0;
    cout << fixed << setprecision(2);
    for (int i = 0; i < num_imoveis; ++i) {
        if (imoveis[i].quartos >= min_quartos && imoveis[i].suites >= min_suites) {
             cout << (i + 1) << ". Tipo: " << imoveis[i].tipo
                 << ", Endereço: " << imoveis[i].endereco
                 << ", Quartos: " << imoveis[i].quartos
                 << ", Suítes: " << imoveis[i].suites
                 << ", Valor: R$" << imoveis[i].valor << endl;
            count++;
        }
    }
    cout << setprecision(0);

    if (count == 0) {
        cout << "Nenhum imóvel encontrado para os critérios especificados." << endl;
    } else {
        cout << "\nTotal de " << count << " imóvel(is) encontrado(s)." << endl;
    }
    pausar();
}


void gerarRelatorioEstatisticas(const imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Relatório Estatístico ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado para gerar estatísticas." << endl;
        pausar();
        return;
    }

    int count_venda = 0, count_locacao = 0, count_temporada = 0;
    int count_casas = 0, count_casas_suites = 0;
    int count_salas_comerciais = 0, count_salas_ceramica = 0;

    for (int i = 0; i < num_imoveis; ++i) {
        // Percentual por finalidade
        if (imoveis[i].finalidade == "venda") count_venda++;
        else if (imoveis[i].finalidade == "locacao") count_locacao++;
        else if (imoveis[i].finalidade == "temporada") count_temporada++;

        // Percentual de casas com suítes
        if (imoveis[i].tipo == "casa") {
            count_casas++;
            if (imoveis[i].suites > 0) {
                count_casas_suites++;
            }
        }

        // Percentual de salas comerciais com piso cerâmico
        // (Assumindo que 'sala_comercial' é o tipo e 'ceramica' é o piso)
        if (imoveis[i].tipo == "sala_comercial") {
            count_salas_comerciais++;
            if (imoveis[i].piso == "ceramica") {
                count_salas_ceramica++;
            }
        }
    }

    cout << fixed << setprecision(2);
    cout << "\nPercentual de Imóveis por Finalidade:" << endl;
    cout << "  Venda: " << (static_cast<float>(count_venda) / num_imoveis) * 100 << "% (" << count_venda << ")" << endl;
    cout << "  Locação: " << (static_cast<float>(count_locacao) / num_imoveis) * 100 << "% (" << count_locacao << ")" << endl;
    cout << "  Temporada: " << (static_cast<float>(count_temporada) / num_imoveis) * 100 << "% (" << count_temporada << ")" << endl;

    cout << "\nPercentual de Casas com Suítes:" << endl;
    if (count_casas > 0) {
        cout << "  " << (static_cast<float>(count_casas_suites) / count_casas) * 100 << "% de casas possuem suítes (" << count_casas_suites << " de " << count_casas << " casas)." << endl;
    } else {
        cout << "  Nenhuma casa cadastrada." << endl;
    }

    cout << "\nPercentual de Salas Comerciais com Piso Cerâmico:" << endl;
    if (count_salas_comerciais > 0) {
        cout << "  " << (static_cast<float>(count_salas_ceramica) / count_salas_comerciais) * 100 << "% de salas comerciais possuem piso cerâmico (" << count_salas_ceramica << " de " << count_salas_comerciais << " salas)." << endl;
    } else {
        cout << "  Nenhuma sala comercial cadastrada." << endl;
    }
    cout << setprecision(0); // Reset precision
    pausar();
}

void listarTodosImoveis(const imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Lista de Todos os Imóveis Disponíveis ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado." << endl;
        pausar();
        return;
    }
    cout << fixed << setprecision(2);
    for (int i = 0; i < num_imoveis; i++) {
        cout << "\nImóvel " << (i + 1) << ":" << endl;
        cout << "  Tipo: " << imoveis[i].tipo << ", Finalidade: " << imoveis[i].finalidade << endl;
        cout << "  Endereço: " << imoveis[i].endereco << ", Bairro: " << imoveis[i].bairro << ", Cidade: " << imoveis[i].cidade << endl;
        cout << "  Área: " << imoveis[i].area << " m2, Valor: R$" << imoveis[i].valor << ", IPTU: R$" << imoveis[i].iptu << endl;
        cout << "  Quartos: " << imoveis[i].quartos << ", Suítes: " << imoveis[i].suites << ", Banheiros: " << imoveis[i].banheiros << ", Vagas: " << imoveis[i].vagas << endl;
        cout << "  Cozinha: " << imoveis[i].cozinha << ", Sala: " << imoveis[i].sala << ", Varanda: " << imoveis[i].varanda << ", Área Serv.: " << imoveis[i].area_servico << endl;
        cout << "  Piso: " << imoveis[i].piso << ", Conservação: " << imoveis[i].conservacao << endl;
        cout << "  Comodidades: "
             << (imoveis[i].armarios_embutidos ? "Armários " : "")
             << (imoveis[i].ar_condicionado ? "Ar-Cond. " : "")
             << (imoveis[i].aquecedor ? "Aquecedor " : "")
             << (imoveis[i].ventilador ? "Ventilador" : "") << endl;
    }
    cout << setprecision(0);
    cout << "\nTotal de " << num_imoveis << " imóvel(is) listado(s)." << endl;
    pausar();
}

void gravarDados(const imovel imoveis[], int num_imoveis, const string& nomeArquivo) {
    ofstream arquivo_saida(nomeArquivo);
    if (!arquivo_saida.is_open()) {
        cerr << "Erro fatal: Não foi possível abrir o arquivo " << nomeArquivo << " para escrita." << endl;
        return; // Ou exit(1) dependendo da criticidade
    }

    // Escreve o cabeçalho (igual ao arquivo de exemplo, se houver, ou um novo)
    // A descrição do problema diz "A primeira linha do arquivo deve ser ignorada",
    // o que implica que o arquivo lido tem um cabeçalho. Vamos recriá-lo.
    arquivo_saida << "Tipo Finalidade Endereco Bairro Cidade Area Valor IPTU Quartos Suites Banheiros Vagas Cozinha Sala Varanda Area_Servico Piso Conservacao Armarios Ar_Condicionado Aquecedor Ventilador" << endl;

    cout << fixed << setprecision(2); // Para formatar valor e área na gravação
    for (int i = 0; i < num_imoveis; ++i) {
        arquivo_saida << imoveis[i].tipo << " "
                      << imoveis[i].finalidade << " "
                      << imoveis[i].endereco << " "
                      << imoveis[i].bairro << " "
                      << imoveis[i].cidade << " "
                      << imoveis[i].area << " "
                      << imoveis[i].valor << " "
                      << imoveis[i].iptu << " "
                      << imoveis[i].quartos << " "
                      << imoveis[i].suites << " "
                      << imoveis[i].banheiros << " "
                      << imoveis[i].vagas << " "
                      << imoveis[i].cozinha << " "
                      << imoveis[i].sala << " "
                      << imoveis[i].varanda << " "
                      << imoveis[i].area_servico << " "
                      << imoveis[i].piso << " "
                      << imoveis[i].conservacao << " "
                      << (imoveis[i].armarios_embutidos ? "sim" : "nao") << " "
                      << (imoveis[i].ar_condicionado ? "sim" : "nao") << " "
                      << (imoveis[i].aquecedor ? "sim" : "nao") << " "
                      << (imoveis[i].ventilador ? "sim" : "nao") << endl;
    }
    cout << setprecision(0); // Reset precision

    arquivo_saida << "fim" << endl; // Adiciona a marcação de fim de arquivo
    arquivo_saida.close();
    cout << "\nDados gravados com sucesso no arquivo " << nomeArquivo << "." << endl;
}


int main() {
    // Variáveis para manipulação de arquivos
    imovel imoveis[MAX_IMOVEIS]; // Vetor de registros de imóveis (usando a struct global)

    int num_imoveis = 0; // Contador de imóveis lidos
    int i; // Variável de controle para loops
    int choice = 0; // Variável para armazenar a escolha do usuário no menu
    string resposta; // Variável para armazenar a resposta do usuário
    bool continuar = true; // Variável para controlar o loop principal  

    // Leitura do arquivo de imóveis
    ifstream arquivo("BD_Imoveis2.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo BD_Imoveis2.txt. Verifique se ele existe e está no local correto." << endl;
        cerr << "Um novo arquivo será criado ao sair se houverem dados." << endl;
        // Não retorna 1, permite que o programa continue e crie um novo arquivo ao salvar.
    } else {
        string linha_cabecalho;
        // Lê e descarta a primeira linha do arquivo (cabeçalho)
        getline(arquivo, linha_cabecalho);

        // Lê cada linha do arquivo e armazena os dados no vetor de registros
        for(i=0; i < MAX_IMOVEIS; i++) {
            string tipo_lido;
            arquivo >> tipo_lido; // Lê o tipo primeiro para checar por "fim"
            if (tipo_lido == "fim" || arquivo.eof()) break; // Interrompe a leitura se encontrar a linha "fim" ou fim do arquivo

            imoveis[i].tipo = tipo_lido;
            arquivo >> imoveis[i].finalidade;
            arquivo >> imoveis[i].endereco;
            arquivo >> imoveis[i].bairro;
            arquivo >> imoveis[i].cidade;
            arquivo >> imoveis[i].area;
            arquivo >> imoveis[i].valor;
            arquivo >> imoveis[i].iptu;
            arquivo >> imoveis[i].quartos;
            arquivo >> imoveis[i].suites;
            arquivo >> imoveis[i].banheiros;
            arquivo >> imoveis[i].vagas;
            arquivo >> imoveis[i].cozinha;
            arquivo >> imoveis[i].sala;
            arquivo >> imoveis[i].varanda;
            arquivo >> imoveis[i].area_servico;
            arquivo >> imoveis[i].piso;
            arquivo >> imoveis[i].conservacao;
            string armarios_str, ar_cond_str, aquecedor_str, ventilador_str;
            arquivo >> armarios_str; 
            imoveis[i].armarios_embutidos = (armarios_str == "sim");
            arquivo >> ar_cond_str; 
            imoveis[i].ar_condicionado = (ar_cond_str == "sim");
            arquivo >> aquecedor_str;
            imoveis[i].aquecedor = (aquecedor_str == "sim");
            arquivo >> ventilador_str; 
            imoveis[i].ventilador = (ventilador_str == "sim");
            
            // Consumir o resto da linha, se houver (para evitar problemas com getline depois)
            string dummy;
            getline(arquivo, dummy); 

            num_imoveis++; 
        }
        arquivo.close(); 
    }


    // Exibe o total de imóveis lidos
    cout << "Total de imóveis lidos do arquivo: " << num_imoveis << endl;
    pausar(); // Pausa para o usuário ver a mensagem

    limparTela(); 

    while(continuar) {
        switch(choice) {
            case 0: // Mostrar Menu Principal
                limparTela(); 
                cout << "--- Menu Principal --- Gestão de Imóveis ---" << endl;
                cout << "1. Visualizar Lista de Imóveis" << endl;
                cout << "2. Inclusão de um novo imóvel" << endl;
                cout << "3. Busca de imóveis por faixa de valores" << endl;
                cout << "4. Busca de imóveis por características" << endl;
                cout << "5. Relatório estatístico" << endl;
                cout << "6. Sair do Programa" << endl; // Adicionada opção de Sair
                // Opção não listada no menu, mas função existe:
                // cout << "7. Buscar por rua e excluir (Função de Teste)" << endl; 
                cout << "Escolha uma opção: ";
                cin >> choice; 
                
                // Validação básica da escolha
                // A lógica original incrementava choice e usava case X+1.
                // Para simplificar, vamos mapear diretamente.
                // Mas a lógica original no seu main.cpp era `choice++` *depois* do cin
                // e antes do switch, e `case 1` era o "Deseja voltar?".
                // Mantendo a sua lógica original de `choice++` e `case 1` para voltar:
                while(choice < 1 || choice > 6) { 
                    limparTela(); 
                    cout << "ERROR - Opção inválida.\nPor favor, escolha uma opção entre 1 e 6.\n\n";
                    cout << "--- Menu Principal --- Gestão de Imóveis ---" << endl;
                    cout << "1. Visualizar Lista de Imóveis" << endl;
                    cout << "2. Inclusão de um novo imóvel" << endl;
                    cout << "3. Busca de imóveis por faixa de valores" << endl;
                    cout << "4. Busca de imóveis por características" << endl;
                    cout << "5. Relatório estatístico" << endl;
                    cout << "6. Sair do Programa" << endl;
                    cout << "Escolha uma opção: ";
                    cin >> choice; 
                     if (cin.fail()) { // Verifica se a entrada falhou (e.g., não numérico)
                        cin.clear(); // Limpa os flags de erro
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta a entrada inválida
                        choice = 0; // Força a repetição da validação
                    }
                }
                if (choice == 6) { // Opção Sair
                    continuar = false;
                    choice = -1; // Para evitar entrar em outros cases e ir direto para o fim
                } else {
                    choice++; // Incrementa a escolha para corresponder ao índice do vetor de opções (como no original)
                }
                break;

            case 1: // Lógica de "Voltar ao menu / Sair"
                cout << "\n\nDeseja voltar ao menu principal? Digite 's' para SIM ou 'n' para NÃO (sair do programa): ";
                cin >> resposta;
                if (resposta == "s" || resposta == "S") {
                    choice = 0; 
                    limparTela(); 
                } else if (resposta == "n" || resposta == "N") {
                    continuar = false; 
                } else {
                    while (resposta != "s" && resposta != "S" && resposta != "n" && resposta != "N") {
                        cout << "Opção inválida. Digite 's' para SIM ou 'n' para NÃO: ";
                        cin >> resposta; 
                    }
                    if (resposta == "s" || resposta == "S") {
                        choice = 0; 
                        limparTela(); 
                    } else if (resposta == "n" || resposta == "N") {
                        continuar = false; 
                    }
                }
                break;

            case 2: // Menu Opção 1: Visualizar Lista de Imóveis
                listarTodosImoveis(imoveis, num_imoveis);
                choice = 1; // Vai para a pergunta "Deseja voltar..."
                break;

            case 3: // Menu Opção 2: Inclusão de um novo imóvel
                adicionarImovel(imoveis, num_imoveis);
                choice = 1; 
                break;

            case 4: // Menu Opção 3: Busca de imóveis por faixa de valores
                buscarPorFaixaDeValor(imoveis, num_imoveis);
                choice = 1; 
                break;

            case 5: // Menu Opção 4: Busca de imóveis por características
                { // Bloco para variável local sub_choice
                    limparTela();
                    int sub_choice_caracteristicas;
                    cout << "--- Busca por Características ---" << endl;
                    cout << "1. Buscar por Comodidades (Armários, Ar, etc.)" << endl;
                    cout << "2. Buscar por Número de Quartos e Suítes" << endl;
                    cout << "3. Voltar ao menu principal" << endl;
                    cout << "Escolha uma sub-opção: ";
                    cin >> sub_choice_caracteristicas;
                     if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        sub_choice_caracteristicas = 0; // inválido
                    }


                    switch (sub_choice_caracteristicas) {
                        case 1:
                            buscarPorCaracteristicasComodidades(imoveis, num_imoveis);
                            break;
                        case 2:
                            buscarPorQuartosSuites(imoveis, num_imoveis);
                            break;
                        case 3:
                            // Não faz nada, apenas volta ao fluxo normal
                            break;
                        default:
                            cout << "Sub-opção inválida." << endl;
                            pausar();
                            break;
                    }
                }
                choice = 1; 
                break;

            case 6: // Menu Opção 5: Relatório estatístico
                gerarRelatorioEstatisticas(imoveis, num_imoveis);
                choice = 1; 
                break;
            
            // Case para a função não listada no menu (exemplo de como chamar)
            /*
            case 7: // Menu Opção 6 (teste): Buscar por rua e excluir
                buscarPorRuaExcluir(imoveis, num_imoveis);
                choice = 1;
                break;
            */
            default: // Se choice for -1 (sair) ou outro valor inesperado
                if(continuar) choice = 0; // Volta ao menu se não for para sair
                break;
        }
    }   

    limparTela(); 
    cout << "\nPreparando para encerrar o programa..." << endl;
    gravarDados(imoveis, num_imoveis, "BD_Imoveis2.txt"); // Grava os dados antes de sair
    cout << "\nPrograma encerrado.\n\n";
    pausar(); // Pausa final para o usuário ver a mensagem de gravação.
    return 0;
}