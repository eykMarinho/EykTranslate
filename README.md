#EykTranslate
Include de Tradução Automática em Tempo Real para SA-MP e Open.mp. Traduza mensagens do chat ou comandos instantaneamente, sem precisar de plugins ou bots externos.

Como usar
Use as funções:
EykTrans_Translate(playerid, "Hello World"); // Envia texto para tradução
EykTrans_SetLanguage("en", "pt"); // Muda o idioma (Ex: Inglês -> Português)

Receba a tradução no seu gamemode:
public OnPlayerTranslate(playerid, const text[]) {
    // Use 'text' como quiser (ChatBubble, SendClientMessage, etc)
    SetPlayerChatBubble(playerid, text, -1, 20.0, 5000);
    return 1;
}

Configuração
Idioma padrão: Português (pt)
Compatibilidade: Open.mp (Nativo HTTPS) e SA-MP 0.3.7 (HTTP/Proxy)
Dependências: Nenhuma (Zero plugins)

Pronto para usar!
