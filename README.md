# EykTranslate
Include de Tradução Automática em Tempo Real para SA-MP e Open.mp. Traduza mensagens do chat ou comandos instantaneamente, sem precisar de plugins ou bots externos.

### Como usar
Use as funções:

```pawn
EykTrans_Translate(playerid, "Hello World"); // Envia texto para tradução
EykTrans_SetLanguage("en", "pt"); // Muda o idioma (Ex: Inglês -> Português)
```

Receba a tradução no seu gamemode:

```pawn
public OnPlayerTranslate(playerid, const text[]) {
    // Use 'text' como quiser (ChatBubble, SendClientMessage, etc)
    SetPlayerChatBubble(playerid, text, -1, 20.0, 5000);
    return 1;
}
```

### Configuração
- Idioma padrão: Português (pt)
- Compatibilidade: Open.mp (Nativo HTTPS) e SA-MP 0.3.7 (HTTP/Proxy)
- Dependências: Nenhuma (Zero plugins)

### Fotos

### Idiomas Suportados
<img width="480" height="88" alt="Capture" src="https://github.com/user-attachments/assets/f559480e-1acc-4d60-bb18-79723add7114" />

| Código | Idioma | Código | Idioma |
| :--- | :--- | :--- | :--- |
| **Auto** | Autodetectar | **it** | Italiano |
| **pt** | Português | **ru** | Russo |
| **en** | Inglês | **de** | Alemão |
| **es** | Espanhol | **ja** | Japonês |
| **fr** | Francês | **zh** | Chinês |

*E muitos outros suportados.*

---

### 📜 Licença

Livre para uso e modificação. Mantenha os créditos é humilde! 😉

---

**Criado por EykMarinho**
