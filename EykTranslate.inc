/* 
 * EykTranslate - Tradutor Automático em Tempo Real (Plug & Play)
 * Versão: 1.0 
 * Autor: Eyk 
 * 
 * Funções principais: 
 * - EykTrans_Translate(playerid, const text[]) - Envia texto para tradução
 * - EykTrans_SetLanguage(const source[], const target[]) - Configura idiomas (ex: "en", "pt")
 * 
 * Callbacks:
 * - OnPlayerTranslate(playerid, const text[]) - Chamada quando a tradução está pronta
 * 
 * Configuração Opcional (Defina antes do include):
 * - #define EYK_TRANSLATE_LANG "pt" (Idioma padrão)
 * 
 * Compatibilidade:
 * - Open.mp (Nativo HTTPS)
 * - SA-MP 0.3.7 (HTTP/Proxy Automático)
 */

#if defined _EykTranslate_included
    #endinput
#endif
#define _EykTranslate_included

#include <a_samp>
#include <a_http>

#if !defined EYK_TRANSLATE_LANG
    #define EYK_TRANSLATE_LANG "pt"
#endif

// Variáveis globais para armazenar os idiomas atuais
new g_EykTrans_SourceLang[6] = "Auto";
new g_EykTrans_TargetLang[6] = EYK_TRANSLATE_LANG;



#if !defined EYK_TRANSLATE_API
    #define EYK_TRANSLATE_API "api.mymemory.translated.net/get"
#endif

// --- Funções Auxiliares ---

static stock EykTrans_URLEncode(dest[], len, const source[]) {
    new idx = 0;
    static const hex[] = "0123456789ABCDEF";
    
    for(new i = 0; source[i] != 0 && idx < len - 3; i++) {
        new c = source[i];
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
            dest[idx++] = c;
        } else {
            dest[idx++] = '%';
            dest[idx++] = hex[(c >> 4) & 0xF];
            dest[idx++] = hex[c & 0xF];
        }
    }
    dest[idx] = 0;
}

// Extrai o valor de um campo JSON simples (sem parser complexo)
static stock EykTrans_ExtractJSON(const json[], const key[], output[], len) {
    new pos = strfind(json, key, true);
    if(pos == -1) return 0;
    
    pos = strfind(json, ":", true, pos) + 1;
    
    while(json[pos] == ' ' || json[pos] == '"') pos++;
    
    new idx = 0;
    while(json[pos] != 0 && idx < len - 1) {
        if(json[pos] == '"' && json[pos-1] != '\\') break;
        if(json[pos] == '}' || json[pos] == ']') break;
        if(json[pos] == ',' && (json[pos-1] != '"')) break; 
        
        output[idx++] = json[pos++];
    }
    output[idx] = 0;
    return 1;
}

forward OnTranslateResponse(playerid, response_code, data[]);
public OnTranslateResponse(playerid, response_code, data[]) {
    if(response_code != 200) return 0;
    
    new translatedText[256];
    
    if(EykTrans_ExtractJSON(data, "\"translatedText\"", translatedText, sizeof(translatedText))) {
        if(strlen(translatedText) > 0) {
            new originalText[144];
            GetPVarString(playerid, "EykTrans_Last", originalText, sizeof(originalText));
            
            if(strcmp(originalText, translatedText, true) == 0) return 1;
            
            CallLocalFunction("OnPlayerTranslate", "is", playerid, translatedText);
        }
    }
    return 1;
}

// Forward para quem quiser usar a tradução no gamemode
forward OnPlayerTranslate(playerid, const text[]);

stock EykTrans_SetLanguage(const source[], const target[]) {
    format(g_EykTrans_SourceLang, sizeof(g_EykTrans_SourceLang), "%s", source);
    format(g_EykTrans_TargetLang, sizeof(g_EykTrans_TargetLang), "%s", target);
}

stock EykTrans_Translate(playerid, const text[]) {
    new url[512];
    new encoded_text[256];
    
    SetPVarString(playerid, "EykTrans_Last", text);
    
    EykTrans_URLEncode(encoded_text, sizeof(encoded_text), text);
    
    new src_lang[12];
    if(strcmp(g_EykTrans_SourceLang, "Auto", true) == 0 || strlen(g_EykTrans_SourceLang) == 0) {
        src_lang = "Autodetect";
    } else {
        format(src_lang, sizeof(src_lang), "%s", g_EykTrans_SourceLang);
    }
    
    #if defined _OPEN_MP
        format(url, sizeof(url), "https://%s?q=%s&langpair=%s%%7C%s", EYK_TRANSLATE_API, encoded_text, src_lang, g_EykTrans_TargetLang);
    #else
        format(url, sizeof(url), "%s?q=%s&langpair=%s%%7C%s", EYK_TRANSLATE_API, encoded_text, src_lang, g_EykTrans_TargetLang);
        
        if(strfind(url, "http://", true) == 0) strdel(url, 0, 7);
        if(strfind(url, "https://", true) == 0) strdel(url, 0, 8);
    #endif
    
    HTTP(playerid, HTTP_GET, url, "", "OnTranslateResponse");
}


