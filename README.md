# 🌍 EykTranslate.inc

**Tradutor Automático em Tempo Real para SA-MP e Open.mp - Sem Plugins, Sem Bots!**

Chega de barreiras linguísticas no seu servidor. O **EykTranslate** é uma include inovadora que permite traduzir mensagens de jogadores em tempo real usando APIs públicas, sem a necessidade de instalar plugins complexos, configurar bots do Discord ou rodar executáveis externos. É só incluir e usar.

### 🚀 Por que usar?

*   **Zero Dependências:** Funciona apenas com a include. Nada de plugins `.dll` ou `.so` extras.
*   **Universal:** Compatível nativamente com **Open.mp** (HTTPS) e **SA-MP 0.3.7** (HTTP/Proxy).
*   **Plug & Play:** Adicione `#include <EykTranslate>` e comece a traduzir.
*   **Flexível:** Você decide o que fazer com a tradução (exibir no chat, criar um balão de fala, salvar em log) através da callback `OnPlayerTranslate`.
*   **Dinâmico:** Suporte para mudar idiomas de origem e destino em tempo real (ex: `en` -> `pt`, `es` -> `en`, `Auto` -> `pt`).

---

### 📦 Instalação

1.  Baixe o arquivo `EykTranslate.inc`.
2.  Coloque na pasta `pawno/include` do seu projeto.
3.  No seu gamemode:

```pawn
#include <EykTranslate>
```

---

### 🛠️ Como Usar

A include não interfere automaticamente no seu chat. Você tem total controle de quando traduzir.

#### 1. Traduzindo uma mensagem
Use a função `EykTrans_Translate` onde quiser (ex: em um comando ou no chat):

```pawn
CMD:traduzir(playerid, params[]) {
    // Traduz o que o jogador digitar para o idioma configurado
    EykTrans_Translate(playerid, params);
    return 1;
}
```

#### 2. Recebendo a tradução
A include chama a callback `OnPlayerTranslate` quando a tradução fica pronta. Adicione isso no seu gamemode:

```pawn
public OnPlayerTranslate(playerid, const text[]) {
    // Exemplo: Mostrar um balão de fala traduzido acima da cabeça do jogador
    SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 20.0, 5000);
    
    // Ou enviar no chat para todos
    new str[144], name[24];
    GetPlayerName(playerid, name, 24);
    format(str, sizeof(str), "[Traduzido] %s: %s", name, text);
    SendClientMessageToAll(-1, str);
    return 1;
}
```

#### 3. Mudando Idiomas (Opcional)
Você pode mudar os idiomas dinamicamente (padrão é `Auto` -> `pt`):

```pawn
// Exemplo: Traduzir de Inglês (en) para Espanhol (es)
EykTrans_SetLanguage("en", "es");

// Exemplo: Detectar idioma automaticamente e traduzir para Russo (ru)
EykTrans_SetLanguage("Auto", "ru");
```

---

### ⚙️ Configuração Avançada

Antes do include, você pode definir o idioma padrão:

```pawn
#define EYK_TRANSLATE_LANG "en" // Muda o alvo padrão para Inglês
#include <EykTranslate>
```

---

### 📜 Licença

Livre para uso e modificação. Mantenha os créditos é humilde! 😉

---

**Criado por Eyk**
