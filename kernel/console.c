#include <n7OS/console.h>
#include <n7OS/cpu.h>

uint16_t *scr_tab;
uint16_t pos;
uint8_t ligne, colonne;
uint8_t color = 0x0F;

// fonction pour placer le curseur a partir de la ligne et de la colonne
void set_cursor2(uint8_t l, uint8_t c) {
    uint16_t position = l*80+c;

    //gerer le bit de poids faible
    outb(CMD_LOW, PORT_CMD);
    outb(position, PORT_DATA);

    //gerer le bit de poids fort
    outb(CMD_HIGH, PORT_CMD);
    outb(position>>8, PORT_DATA);

    //update de la position
    pos = position;
    ligne = l;
    colonne = c;
}

// fonction pour placer le curseur a partir de la position (int)
void set_cursor(uint16_t position) {
    //gerer le bit de poids faible
    outb(CMD_LOW, PORT_CMD);
    outb(position, PORT_DATA);

    //gerer le bit de poids fort
    outb(CMD_HIGH, PORT_CMD);
    outb(position>>8, PORT_DATA);

    //update de la position
    pos = position;
    ligne = pos/80;
    colonne = pos%80;
}

void init_console() {
    scr_tab= (uint16_t *) SCREEN_ADDR;
}

void console_putchar(const char c) {
    if(c > 31 && c < 127) {
        // affichage du caractère a l'écran
        scr_tab[pos]= color<<8|c;
        pos++;
    } else if (c == '\n') {
        set_cursor2(ligne+1, 0);
    } else if (c == '\t') {
        set_cursor(pos+8);
    } else if (c == '\b') {
        // revenir en arriere de 1 caractère
        if (colonne > 0){
            set_cursor2(ligne,colonne-1);
        }
    } else if (c == '\r') {
        // revenir en début de ligne
        set_cursor2(ligne, 0);
    } else if (c == '\f') {
        // revenir en (0,0)
        set_cursor2(0,0);
    }
    //pour les couleurs

    else if (c == '\0') {
        color = 0;
    }
    else if (c == '\1') {
        color = 1;
    }
    else if (c == '\2') {
        color = 2;
    }
    else if (c == '\3') {
        color = 3;
    }
    else if (c == '\4') {
        color = 4;
    }
    else if (c == '\5') {
        color = 5;
    }
    else if (c == '\6') {
        color = 6;
    }
    else if (c == '\7') {
        color = 7;
    }
    else if (c == '\8') {
        color = 8;
    }
    else if (c == '\9') {
        color = 9;
    }
    
    else {
        // caractère non affichable
        scr_tab[pos]= color<<8|'?';
        pos++;
    }
}

void console_putbytes(const char *s, int len) {
    for (int i= 0; i<len; i++) {
        console_putchar(s[i]);
    }
}

void console_clear() {
    for (int i=0; i<80*25; i++) {
        scr_tab[i]=0x0F<<8|' ';
    }
    set_cursor2(0,0);
}

uint16_t get_cursor() {
    return pos;
}

void get_cursor2(uint8_t *l, uint8_t *c) {
    *l = ligne;
    *c = colonne;
}


void logo () {
    color = 1;
    printf("                                                              .:                                                                           :=+++=                                                                      :-+++++++++.                                                               .-=++++++++++++-                                                              ++++++++++++=--+=                                                                -++++++=-.   -+:                                                    .:-:.         ...        ++       .-=:                                    .:-=+++++++=  :==-             ++   :-=++++-                               .:-=++=-:.. .=++++=+++++.          .++-++++++++++                          :-=++=-:.         :+++++++++++:      .:=++++++++++=:.                     .:-===-:.               :++++++++++++=::-=++++++++++-:.                   .:----:.                      -+++++:=++++++++++++++++=:                  ..:::::.                            +++++=  -++++++++++=-.=+-                                                      :+++++.   .-++++=:.    =+-                                               .::-:   ::-==  ::---:         ++=                                            -=++=-:...     :=+++-++++.       +++                                          =+++:  .=+++-   -++++-  +++:       ++:                                        :+++=    :+++++   ++++++  ++:                                                  -++++      -++++   -++++++-.                                                   :++++:       +++=    .=++++++-                                                  +++++:      .+++.    . .=+++++:                                                 +++++=     .+++:  :+++:  -++++:                                                 .+++++-. .-++=    -++++: :+++=                                                    :=++++++=:       .-++++++=:                                                                          ...                                ");
    color = 15;
}


