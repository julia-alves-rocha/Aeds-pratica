// Função para buscar imóveis por características com validação
void buscarPorCaracteristicas(const Imovel imoveis[], int num_imoveis) {
    limparTela();
    cout << "--- Busca de Imóveis por Características ---" << endl;
    if (num_imoveis == 0) {
        cout << "Nenhum imóvel cadastrado para busca." << endl;
        return; // choice recebe 1. 
    }

    bool req_armarios, req_ar, req_aquecedor, req_ventilador;
    int encontrados = 0;

    req_armarios = lerSimNao("Deseja com armários embutidos? (sim/nao): ");
    req_ar = lerSimNao("Deseja com ar condicionado? (sim/nao): ");
    req_aquecedor = lerSimNao("Deseja com aquecedor? (sim/nao): ");
    req_ventilador = lerSimNao("Deseja com ventilador? (sim/nao): ");

    cout << "\n--- Imóveis Encontrados ---" << endl;
    for (int i = 0; i < num_imoveis; ++i) {
        bool atende = true; 
        // Se o usuário requisitou a característica (true), o imóvel deve tê-la (imoveis[i].<caracteristica> deve ser true)
        // Se !imoveis[i].<caracteristica> for true (ou seja, o imóvel NÃO tem), então não atende.
        if (req_armarios && !imoveis[i].armarios_embutidos) atende = false;
        if (req_ar && !imoveis[i].ar_condicionado) atende = false;
        if (req_aquecedor && !imoveis[i].aquecedor) atende = false;
        if (req_ventilador && !imoveis[i].ventilador) atende = false;
        
        if (atende) { // pegar todas as características do imóvel, menos valor.
            cout << "\nImóvel " << (i + 1) << ":" << endl;
            cout << "  Tipo: " << imoveis[i].tipo << ", Finalidade: " << imoveis[i].finalidade << endl;
            cout << "  Endereço: " << imoveis[i].endereco << ", " << imoveis[i].bairro << ", " << imoveis[i].cidade << endl;
            cout << "  Armários: " << (imoveis[i].armarios_embutidos ? "Sim" : "Não") 
                 << ", Ar Cond.: " << (imoveis[i].ar_condicionado ? "Sim" : "Não")
                 << ", Aquecedor: " << (imoveis[i].aquecedor ? "Sim" : "Não")
                 << ", Ventilador: " << (imoveis[i].ventilador ? "Sim" : "Não") << endl;
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "Nenhum imóvel encontrado com as características especificadas." << endl;
    } else {
        cout << "\nTotal de " << encontrados << " imóvel(is) encontrado(s)." << endl;
    }
}
