#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// adicionar função que localiza as palavras
// identificar quantos prefixos a palavra é
struct NoTrie {
    char           letra;        //opcional
    NoTrie        *filhos[26];   //pode ser uma 'LinkedList' de ponteiros
    unsigned long  position;
    unsigned long  comprimento;  //se maior que zero, indica último caracter de uma palavra
    bool end_of_word;
};

void trie_put(struct NoTrie *root, string key, int position, int comprimento) {
    // função que adiciona uma chave na trie
    struct NoTrie *p_aux = root;
    for (int i = 0; i < key.size(); i++) {
        // iterar pelos caracteres da key e adicionar na trie
        struct NoTrie new_node;
        new_node.end_of_word = false;
        if (i == key.size()-1) {
            new_node.end_of_word = true;
        }
        new_node.letra = key[i];
        if (key[i]=='a') {
            if (p_aux->filhos[0]==nullptr) {
                p_aux->filhos[0] = &new_node;
            }
            p_aux->filhos[0];
        } else if (key[i]=='b') {
            if (p_aux->filhos[1]==nullptr) {
                p_aux->filhos[1] = &new_node;
            }
            p_aux->filhos[1];
        } else if (key[i]=='c') {
            if (p_aux->filhos[2]==nullptr) {
                p_aux->filhos[2] = &new_node;
            }
            p_aux->filhos[2];
        } else if (key[i]=='d') {
            if (p_aux->filhos[3]==nullptr) {
                p_aux->filhos[3] = &new_node;
            }
            p_aux->filhos[3];
        } else if (key[i]=='e') {
            if (p_aux->filhos[4]==nullptr) {
                p_aux->filhos[4] = &new_node;
            }
            p_aux->filhos[4];
        } else if (key[i]=='f') {
            if (p_aux->filhos[5]==nullptr) {
                p_aux->filhos[5] = &new_node;
            }
            p_aux->filhos[5];
        } else if (key[i]=='g') {
            if (p_aux->filhos[6]==nullptr) {
                p_aux->filhos[6] = &new_node;
            }
            p_aux->filhos[6];
        } else if (key[i]=='h') {
            if (p_aux->filhos[7]==nullptr) {
                p_aux->filhos[7] = &new_node;
            }
            p_aux->filhos[7];
        } else if (key[i]=='i') {
            if (p_aux->filhos[8]==nullptr) {
                p_aux->filhos[8] = &new_node;
            }
            p_aux->filhos[8];
        } else if (key[i]=='j') {
            if (p_aux->filhos[9]==nullptr) {
                p_aux->filhos[9] = &new_node;
            }
            p_aux->filhos[9];
        } else if (key[i]=='k') {
            if (p_aux->filhos[10]==nullptr) {
                p_aux->filhos[10] = &new_node;
            }
            p_aux->filhos[10];
        } else if (key[i]=='l') {
            if (p_aux->filhos[11]==nullptr) {
                p_aux->filhos[11] = &new_node;
            }
            p_aux->filhos[11];
        } else if (key[i]=='m') {
            if (p_aux->filhos[12]==nullptr) {
                p_aux->filhos[12] = &new_node;
            }
            p_aux->filhos[12];
        } else if (key[i]=='n') {
            if (p_aux->filhos[13]==nullptr) {
                p_aux->filhos[13] = &new_node;
            }
            p_aux->filhos[13];
        } else if (key[i]=='o') {
            if (p_aux->filhos[14]==nullptr) {
                p_aux->filhos[14] = &new_node;
            }
            p_aux->filhos[14];
        } else if (key[i]=='p') {
            if (p_aux->filhos[15]==nullptr) {
                p_aux->filhos[15] = &new_node;
            }
            p_aux->filhos[15];
        } else if (key[i]=='q') {
            if (p_aux->filhos[16]==nullptr) {
                p_aux->filhos[16] = &new_node;
            }
            p_aux->filhos[16];
        } else if (key[i]=='r') {
            if (p_aux->filhos[17]==nullptr) {
                p_aux->filhos[17] = &new_node;
            }
            p_aux->filhos[17];
        } else if (key[i]=='s') {
            if (p_aux->filhos[18]==nullptr) {
                p_aux->filhos[18] = &new_node;
            }
            p_aux->filhos[18];
        } else if (key[i]=='t') {
            if (p_aux->filhos[19]==nullptr) {
                p_aux->filhos[19] = &new_node;
            }
            p_aux->filhos[19];
        } else if (key[i]=='u') {
            if (p_aux->filhos[20]==nullptr) {
                p_aux->filhos[20] = &new_node;
            }
            p_aux->filhos[20];
        } else if (key[i]=='v') {
            if (p_aux->filhos[21]==nullptr) {
                p_aux->filhos[21] = &new_node;
            }
            p_aux->filhos[21];
        } else if (key[i]=='w') {
            if (p_aux->filhos[22]==nullptr) {
                p_aux->filhos[22] = &new_node;
            }
            p_aux->filhos[22];
        } else if (key[i]=='x') {
            if (p_aux->filhos[23]==nullptr) {
                p_aux->filhos[23] = &new_node;
            }
            p_aux->filhos[23];
        } else if (key[i]=='y') {
            if (p_aux->filhos[24]==nullptr) {
                p_aux->filhos[24] = &new_node;
            }
            p_aux->filhos[24];
        } else if (key[i]=='z') {
            if (p_aux->filhos[25]==nullptr) {
                p_aux->filhos[25] = &new_node;
            }
            p_aux->filhos[25];
        }
    }
    p_aux->position = position;
    p_aux->comprimento = comprimento;
}

void file_read(fstream &file, struct NoTrie *root) {
    // função que lê o arquivo linha a linha e coloca na trie as palavras
    bool registrar = false;
    if (file.is_open()) {
        string line = "";
        int pos = 0;
        while (getline(file, line)) {
            string key = "";
            for (int i = 0; i< line.size(); i++) {
                if (line[i] == '[') {
                    registrar = true;
                } else if (line[i] == ']') {
                    registrar = false;
                    break;
                } else if (registrar) {
                    key.append(line[i],1);
                }
            }
            trie_put(root, key, pos, line.size());
            pos += line.size()+1;
        }
    }
}

int prefix_node(NoTrie *perc) {
    int n_prefix = 0;
    for (int i=0; i<26; i++) {
        if (perc->end_of_word == true) {
            n_prefix++;
        }
        if (perc->filhos[i] != nullptr) {
            n_prefix += prefix_node(perc->filhos[i]);
        }
    }
    return n_prefix;
}

int prefix(string word, struct NoTrie *root) {
    // função que acha a quantidade de prefixos
    int n_prefix = 0;
    int i = 0;
    struct NoTrie *perc = root;
    
    while(i < word.size()) {
        if (word[i] == 'a') {
            perc = perc->filhos[0];
        } else if (word[i]=='b') {
            perc = perc->filhos[1];
        } else if (word[i]=='c') {
            perc = perc->filhos[2];
        } else if (word[i]=='d') {
            perc = perc->filhos[3];
        } else if (word[i]=='e') {
            perc = perc->filhos[4];
        } else if (word[i]=='f') {
            perc = perc->filhos[5];
        } else if (word[i]=='g') {
            perc = perc->filhos[6];
        } else if (word[i]=='h') {
            perc = perc->filhos[7];
        } else if (word[i]=='i') {
            perc = perc->filhos[8];
        } else if (word[i]=='j') {
            perc = perc->filhos[9];
        } else if (word[i]=='k') {
            perc = perc->filhos[10];
        } else if (word[i]=='l') {
            perc = perc->filhos[11];
        } else if (word[i]=='m') {
            perc = perc->filhos[12];
        } else if (word[i]=='n') {
            perc = perc->filhos[13];
        } else if (word[i]=='o') {
            perc = perc->filhos[14];
        } else if (word[i]=='p') {
            perc = perc->filhos[15];
        } else if (word[i]=='q') {
            perc = perc->filhos[16];
        } else if (word[i]=='r') {
            perc = perc->filhos[17];
        } else if (word[i]=='s') {
            perc = perc->filhos[18];
        } else if (word[i]=='t') {
            perc = perc->filhos[19];
        } else if (word[i]=='u') {
            perc = perc->filhos[20];
        } else if (word[i]=='v') {
            perc = perc->filhos[21];
        } else if (word[i]=='w') {
            perc = perc->filhos[22];
        } else if (word[i]=='x') {
            perc = perc->filhos[23];
        } else if (word[i]=='y') {
            perc = perc->filhos[24];
        } else if (word[i]=='z') {
            perc = perc->filhos[25];
        }
        i++;
    }
    if (perc->end_of_word == true) {
        n_prefix++;
    }
    for (int i=0; i<26; i++) {
        n_prefix += prefix_node(perc->filhos[i]);
    }
    return n_prefix;
}

int get_position(string word, struct NoTrie *root) {
    // pega a posição da word
    int i = 0;
    struct NoTrie *perc = root;
    
    while(i < word.size()) {
        if (word[i] == 'a') {
            perc = perc->filhos[0];
        } else if (word[i]=='b') {
            perc = perc->filhos[1];
        } else if (word[i]=='c') {
            perc = perc->filhos[2];
        } else if (word[i]=='d') {
            perc = perc->filhos[3];
        } else if (word[i]=='e') {
            perc = perc->filhos[4];
        } else if (word[i]=='f') {
            perc = perc->filhos[5];
        } else if (word[i]=='g') {
            perc = perc->filhos[6];
        } else if (word[i]=='h') {
            perc = perc->filhos[7];
        } else if (word[i]=='i') {
            perc = perc->filhos[8];
        } else if (word[i]=='j') {
            perc = perc->filhos[9];
        } else if (word[i]=='k') {
            perc = perc->filhos[10];
        } else if (word[i]=='l') {
            perc = perc->filhos[11];
        } else if (word[i]=='m') {
            perc = perc->filhos[12];
        } else if (word[i]=='n') {
            perc = perc->filhos[13];
        } else if (word[i]=='o') {
            perc = perc->filhos[14];
        } else if (word[i]=='p') {
            perc = perc->filhos[15];
        } else if (word[i]=='q') {
            perc = perc->filhos[16];
        } else if (word[i]=='r') {
            perc = perc->filhos[17];
        } else if (word[i]=='s') {
            perc = perc->filhos[18];
        } else if (word[i]=='t') {
            perc = perc->filhos[19];
        } else if (word[i]=='u') {
            perc = perc->filhos[20];
        } else if (word[i]=='v') {
            perc = perc->filhos[21];
        } else if (word[i]=='w') {
            perc = perc->filhos[22];
        } else if (word[i]=='x') {
            perc = perc->filhos[23];
        } else if (word[i]=='y') {
            perc = perc->filhos[24];
        } else if (word[i]=='z') {
            perc = perc->filhos[25];
        }
        i++;
    }
    return perc->position;
}

int get_length(string word, struct NoTrie *root) {
    // pega a length da word
    int i = 0;
    struct NoTrie *perc = root;
    
    while(i < word.size()) {
        if (word[i] == 'a') {
            perc = perc->filhos[0];
        } else if (word[i]=='b') {
            perc = perc->filhos[1];
        } else if (word[i]=='c') {
            perc = perc->filhos[2];
        } else if (word[i]=='d') {
            perc = perc->filhos[3];
        } else if (word[i]=='e') {
            perc = perc->filhos[4];
        } else if (word[i]=='f') {
            perc = perc->filhos[5];
        } else if (word[i]=='g') {
            perc = perc->filhos[6];
        } else if (word[i]=='h') {
            perc = perc->filhos[7];
        } else if (word[i]=='i') {
            perc = perc->filhos[8];
        } else if (word[i]=='j') {
            perc = perc->filhos[9];
        } else if (word[i]=='k') {
            perc = perc->filhos[10];
        } else if (word[i]=='l') {
            perc = perc->filhos[11];
        } else if (word[i]=='m') {
            perc = perc->filhos[12];
        } else if (word[i]=='n') {
            perc = perc->filhos[13];
        } else if (word[i]=='o') {
            perc = perc->filhos[14];
        } else if (word[i]=='p') {
            perc = perc->filhos[15];
        } else if (word[i]=='q') {
            perc = perc->filhos[16];
        } else if (word[i]=='r') {
            perc = perc->filhos[17];
        } else if (word[i]=='s') {
            perc = perc->filhos[18];
        } else if (word[i]=='t') {
            perc = perc->filhos[19];
        } else if (word[i]=='u') {
            perc = perc->filhos[20];
        } else if (word[i]=='v') {
            perc = perc->filhos[21];
        } else if (word[i]=='w') {
            perc = perc->filhos[22];
        } else if (word[i]=='x') {
            perc = perc->filhos[23];
        } else if (word[i]=='y') {
            perc = perc->filhos[24];
        } else if (word[i]=='z') {
            perc = perc->filhos[25];
        }
        i++;
    }
    return perc->comprimento;
}

int main() {

    std::fstream fs;

    string filename;
    string word;

    cin >> filename;  // entrada
    
    fstream file(filename);
    
    // criando a trie
    struct NoTrie root;
    root.end_of_word = false;
    struct NoTrie *p_root = &root;
    file_read(file, p_root);
    file.close();
    //cout << filename << endl;
    
    while (true) {  // leitura das palavras até encontrar "0"
        cin >> word;
        
        if (word.compare("0") == 0) {
            cout << "ola" << endl;
            break;
        }
        // lógica de procurar a palavra na trie
        int n_prefix = prefix(word, p_root);
        if(n_prefix == 0) {
            cout << word << " is not prefix" << endl;
            //printf("%s is not prefix", word.c_str());
        } else {
            cout << word << " is prefix of" << n_prefix << " words" <<endl;
            //printf("%s is prefix of %d words", word.c_str(), n_prefix);
            cout << word << " is at (" << get_position(word, p_root) << "," << get_length(word, p_root) << ")" << endl;
            //printf("%s is at (%d,%d)", word.c_str(), get_position(word, p_root), get_length(word, p_root));
        }
    }

    return 0;
}
