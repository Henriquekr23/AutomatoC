#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {e0, e1, e2, e3, e4, e5, e6, e7, DEAD} State;

// Função de transição
State verificador(State s, char c){
    switch (s){
        case e0:
            if(c == '+' || c == '-') return e1;
            if(c == '.') return e2;
            if(isdigit(c)) return e3;
            return DEAD;
        case e1:
            if(c == '.') return e2;
            if(isdigit(c)) return e3;
            return DEAD;
        case e2:
            if(isdigit(c)) return e4;
            return DEAD;
        case e3:
            if(c == '.') return e4;
            if(isdigit(c)) return e3;
            if(c == 'E') return e5;
            return DEAD;
        case e4:
            if(isdigit(c)) return e4;
            if(c == 'E') return e5;
            return DEAD;
        case e5:
            if(c == '+' || c == '-') return e6;
            if(isdigit(c)) return e7;
            return DEAD;
        case e6:
            if(isdigit(c)) return e7;
            return DEAD;
        case e7:
            if(isdigit(c)) return e7;
            return DEAD;
        default:
            return DEAD;
    }
}

// Verifica se o estado atingido é de aceitação
bool eh_estado_final(State s) {
    return (s == e3 || s == e4 || s == e7);
}

int main(){
    char palavra[1024];
    State estAtual = e0;

    printf("Digite uma palavra (ex: -12.5E+2):\nDentro do alfabeto: {0,1,2,3,4,5,6,7,8,9,.,+,-,E}\n");
    scanf("%1023s", palavra);
    
    for (int i = 0; palavra[i] != '\0'; i++){
        estAtual = verificador(estAtual, palavra[i]);
        if (estAtual == DEAD) break;
    }

    if (eh_estado_final(estAtual)) {
        printf("Palavra aceita! Estado final: e%d\n", estAtual);
    } else {
        printf("Palavra rejeitada. Parou no estado: %s\n", (estAtual == DEAD ? "DEAD" : "Intermediario"));
    }

    return 0;
}