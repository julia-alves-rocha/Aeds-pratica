// Função para incluir um novo imóvel com validação
void incluirNovoImovel(Imovel imoveis[], int& num_imoveis) {
    limparTela();
    cout << "--- Inclusão de Novo Imóvel ---" << endl;
    if (num_imoveis >= MAX_IMOVEIS) {
        cout << "Limite máximo de imóveis (" << MAX_IMOVEIS << ") atingido. Deseja excluir algum imóvel pra adionar novo? (SIM/NÃO)" << endl;
        // SIM - aparece a lista de imovies e qual deseja substituir.
        // NÃO - escrever choice 1. Que volta pro menu de opções. 
        // opção para excluir imóvel
        return; // tirar
    }
    // mudar pra funcionar no case
    Imovel novo; //ARRAY que representa a base de dados em que a entrada de todos os imóveis serão armazenados
    novo.tipo = lerStringNaoVazia("Tipo (ex: casa, apartamento, sala_comercial): ");
    novo.finalidade = lerFinalidade("Finalidade (venda, locacao, temporada): ");
    novo.endereco = lerStringNaoVazia("Endereço (rua_numero, sem espaços): "); 
    novo.bairro = lerStringNaoVazia("Bairro (sem espaços): ");
    novo.cidade = lerStringNaoVazia("Cidade (sem espaços): ");
    novo.area = lerFloatPositivo("Área (m²): ");
    novo.valor = lerFloatPositivo("Valor (R$): ");
    novo.iptu = lerFloatPositivo("IPTU (R$): ");
    novo.quartos = lerInteiroPositivo("Quartos: ");
    novo.suites = lerInteiroPositivo("Suítes: ");
    novo.banheiros = lerInteiroPositivo("Banheiros: ");
    novo.vagas = lerInteiroPositivo("Vagas de garagem: ");
    novo.cozinha = lerStringNaoVazia("Cozinha (tipo/descrição): ");
    novo.sala = lerStringNaoVazia("Sala (tipo/descrição): ");
    novo.varanda = lerStringNaoVazia("Varanda (sim/nao/gourmet/etc): "); // Mais flexível
    novo.area_servico = lerStringNaoVazia("Área de serviço (sim/nao/etc): "); // Mais flexível
    novo.piso = lerStringNaoVazia("Piso (tipo): ");
    novo.conservacao = lerStringNaoVazia("Conservação (estado): ");

    novo.armarios_embutidos = lerSimNao("Possui armários embutidos (sim/nao): ");
    novo.ar_condicionado = lerSimNao("Possui ar condicionado (sim/nao): ");
    novo.aquecedor = lerSimNao("Possui aquecedor (sim/nao): ");
    novo.ventilador = lerSimNao("Possui ventilador (sim/nao): ");

    imoveis[num_imoveis] = novo;
    num_imoveis++;
    cout << "\nImóvel incluído com sucesso!" << endl;
}
